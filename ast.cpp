#include "ast.h"
#include <set>
#include <iostream>
#include <sstream>
#include <map>
#include "asm.h"

using namespace std ;
class TypeClass{
    public:
        TypeClass(string name, Type type, int isArray,int size){
            
            this->nameC = name; 
            this->type = type;
            this->isArray= isArray;
            this->size = size;
        }
        
        string nameC ;
        Type type ;
        int isArray;
        int size;
};
class MethodInfo{
    public:
        Type returnType;
        list<DeclExpr *> parameters;
};

class Context{
    public:
        Context(string name, Type method){
            prev =NULL;
            this->nameC = name; 
            this->method = method;
        }
        struct Context * prev;
        string nameC ;
        Type method ;
        map<string, TypeClass*> vars;
};



class CodeGenerationVariableInfo
{
public:
    CodeGenerationVariableInfo(int offset, bool isArray, bool isParameter, Type type, int size)
    {
        this->offset = offset;
        this->isArray = isArray;
        this->isParameter = isParameter;
        this->type = type;
        this->size=size;
    }
    int offset;
    bool isArray;
    bool isParameter;
    Type type;
    int size;
};
#define INT_TEMP_COUNT 10
#define FLOAT_TEMP_COUNT 32
extern Asm assemblyFile;
int globalStackPointer = 0;
set<string> intTempMap;
set<string> floatTempMap;
map<string, CodeGenerationVariableInfo *> codeGenerationVars = {};
map<string, TypeClass*> globalVars = {};
map<string, TypeClass*> vars = {};
map<string, MethodInfo *> methods = {};
Context * context = new Context("global", VOID);
map<string, Type> validOpArit = {

     {"INT,INT", INT},
     {"INT,FLOAT", FLOAT},
     {"FLOAT,FLOAT", FLOAT},
     {"FLOAT,INT", FLOAT},
};

map<string, Type> validCompare = {

     {"INT,INT", BOOL},
     {"INT,FLOAT", BOOL},
     {"FLOAT,FLOAT", BOOL},
     {"FLOAT,INT", BOOL},
     {"STRING,STRING", BOOL},
     {"BOOL,BOOL", BOOL},
};

const char *intTemps[] = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"};

const char *floatTemps[] = {"$f0",
                            "$f1",
                            "$f2",
                            "$f3",
                            "$f4",
                            "$f5",
                            "$f6",
                            "$f7",
                            "$f8",
                            "$f9",
                            "$f10",
                            "$f11",
                            "$f12",
                            "$f13",
                            "$f14",
                            "$f15",
                            "$f16",
                            "$f17",
                            "$f18",
                            "$f19",
                            "$f20",
                            "$f21",
                            "$f22",
                            "$f23",
                            "$f24",
                            "$f25",
                            "$f26",
                            "$f27",
                            "$f28",
                            "$f29",
                            "$f30",
                            "$f31"};

string getIntTemp()
{
    for (int i = 0; i < INT_TEMP_COUNT; i++)
    {
        if (intTempMap.find(intTemps[i]) == intTempMap.end())
        {
            intTempMap.insert(intTemps[i]);
            return string(intTemps[i]);
        }
    }
    return "";
}

string getFloatTemp()
{
    for (int i = 0; i < FLOAT_TEMP_COUNT; i++)
    {
        if (floatTempMap.find(floatTemps[i]) == floatTempMap.end())
        {
            floatTempMap.insert(floatTemps[i]);
            return string(floatTemps[i]);
        }
    }
    return "";
}

void releaseRegister(string temp)
{
    intTempMap.erase(temp);
    floatTempMap.erase(temp);
}

void toFloat(Code &context)
{
    if (context.type == INT)
    {
        string floatTemp = getFloatTemp();
        stringstream code;
        code << context.code
             << "mtc1 " << context.place << ", " << floatTemp << endl
             << "cvt.s.w " << floatTemp << ", " << floatTemp << endl;
        releaseRegister(context.place);
        context.place = floatTemp;
        context.type = FLOAT;
        context.code = code.str();
    }
}

int labelCounter = 0;
string newLabel(string prefix)
{
    stringstream ss;
    ss << prefix << "_" << labelCounter;
    labelCounter++;
    return ss.str();
}

Type getLocalVariableType(string id){
    Context  * currentContext = context;

    while (currentContext != NULL)
    {
        if (currentContext->vars.count(id)>0)
        {
            return currentContext->vars.find(id)->second->type;
        }
        currentContext = currentContext->prev;
    }
    return INVALID;
}

TypeClass* getLocalVariableClass(string id){
    Context  * currentContext = context;

    while (currentContext != NULL)
    {
        if (currentContext->vars.count(id)>0)
        {
            return currentContext->vars.find(id)->second;
        }
        currentContext = currentContext->prev;
    }
    return nullptr;
}

Type getValidContext(){
    Context  * currentContext = context;
   
    while (currentContext != NULL)
    {
        if (currentContext->nameC == "method")
        {
            return currentContext->method;
            
        }
        currentContext = currentContext->prev;
    }
    return INVALID;
}

Type getValidContext2(){
    Context  * currentContext = context;
    while (currentContext != NULL)
    {
        if (currentContext->nameC == "for" || currentContext->nameC == "forEach" )
        {
            return INT;
            
        }
        currentContext = currentContext->prev;
    }
    return INVALID;
}
string getTypeName(Type type){

        if(type==INT){
            return "INT";
        
        }
        else if (type == FLOAT){
          return "FLOAT";

        }
        else if (type == VOID){
          return "VOID";

        }
        else if (type == STRING){
          return "STRING";

        }   
        else if (type == BOOL){
         return "BOOL";

        } 
        else if (type == ARRAYBOOL){
         return "ARRAYBOOL";

        }  
        else if (type == ARRAYSTRING){
         return "ARRAYSTRING";

        } 
      else if (type == ARRAYNUMBER){
         return "ARRAYNUMBER";

        }           
       else{
       cerr<<"Invalid type"<<endl;
       exit(0);
       }
   
}

void pushContext(string name, Type mname){
    vars.clear();
    Context * c = new Context(name, mname);
    c->vars = vars;
    c->prev = context;
    context = c;
}

void popContext(){
    if (context != NULL)
    {
        Context * previous = context->prev;
        free(context);
        context = previous;
    }
}

Type DeclExpr::getType(){

     Type tmp = getLocalVariableType(this->name);
      if(tmp != INVALID){
        cerr << "Variable in parameter already declared " <<this->name<< this->line<< endl; 
        exit(0);
    }

    
    return tmp;
}

void DeclExpr::gen(Code &context, int isUnary){

}

Type IdExpr::getType(){

   Type tipo = getLocalVariableType(name);
   if(tipo == INVALID){
       cerr<<"ERROR VARIABLE NO DECLARADA"<<line<<endl; 
        exit(0);
   }
   return tipo; 
}

void IdExpr::gen(Code &context, int isUnary){
stringstream code;

if(codeGenerationVars.find(this->name) == codeGenerationVars.end()){
 
  TypeClass* tmp = globalVars.find(this->name)->second;
  if(tmp->type ==INT ){
    string reg1= getIntTemp();
    code<<"lw "<<reg1<<" ,"<<this->name<<endl;
    context.type=INT;
    context.place= reg1;
    context.code = code.str();
  }
  else if(tmp->type == ARRAYINT){
    string reg1= getIntTemp();
    code<<"la "<<reg1<<" ,"<<this->name<<endl;
    context.type=ARRAYINT;
    context.place= reg1;
    context.code = code.str();

  }
  else{
   string reg1= getFloatTemp();
   code<<"l.s "<<reg1<<this->name<<endl;
    context.type=FLOAT;
    context.place= reg1;
    context.code = code.str();
  }
}else{
  
   CodeGenerationVariableInfo* tmp = codeGenerationVars.find(this->name)->second;
   if(tmp->type ==INT ){
    string reg1= getIntTemp();
    code<<"lw "<<reg1<<" ,"<<tmp->offset<<"($sp)"<<endl;
    context.type=INT;
    context.place= reg1;
    context.code = code.str();
  }
  else if(tmp->type == ARRAYINT){
    string reg1= getIntTemp();
    code<<"la "<<reg1<<" ,"<<tmp->offset<<"($sp)"<<endl;
    context.type=ARRAYINT;
    context.place= reg1;
    context.code = code.str();

  }
  else{
   string reg1= getFloatTemp();
   code<<"l.s "<<reg1<<" ,"<<tmp->offset<<"($sp)"<<endl;
    context.type=FLOAT;
    context.place= reg1;
    context.code = code.str();
  }

}
}

Type IntExpr::getType(){
    return INT;
}

void IntExpr::gen(Code &context , int isUnary){
    stringstream code;
    string intTemp = getIntTemp();
    code << "li " << intTemp << ", " << this->valor<< endl;
    context.code = code.str();
    context.place = intTemp;
    context.type = INT;
}

Type FloatExpr::getType(){
   return FLOAT; 
}

void FloatExpr::gen(Code &context, int isUnary){
    stringstream code;
    string tempReg = getFloatTemp();
    code << "li.s " << tempReg << ", " << this->valor << endl;
    context.code = code.str();
    context.place = tempReg;
    context.type = FLOAT;
}

Type StringExpr::getType(){
   return STRING;
}
void StringExpr::gen(Code &context, int isUnary)
{
    string strLabel = newLabel("string");
    stringstream code;
    code << strLabel << ": .asciiz " << this->valor<< endl;
    context.place = strLabel;
    context.type = STRING;
    context.code = "";
    assemblyFile.data += code.str();
}

Type BoolExpr::getType(){
   
    return BOOL;
}

void BoolExpr::gen(Code &context, int isUnary){

}

Type EqualExpr::getType(){

    if(this->expr1->tipo != 1 && this->expr1->tipo != 2){
      cerr<<"Left side of equality isnt correct "<<line<<endl; 
       exit(0);
    }

    Type tipo1= this->expr1->getType();
    Type tipo2= this->expr2->getType();

    if(tipo1 != tipo2){
        cerr<<"Equality isnt the same type "<<line<<endl; 
         exit(0);
    }
    
    return tipo1; 

}
void EqualExpr::gen(Code &context, int isUnary){
  Code rightCode;
  stringstream code;
  this->expr2->gen(rightCode, isUnary);
  code<<rightCode.code<<endl;
   
  if(this->expr1->tipo==2){
    ArrayAccessExpr* tmp = (ArrayAccessExpr*)this->expr1;

    if(codeGenerationVars.find(tmp->name->name)== codeGenerationVars.end()){
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<tmp->name->name<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"sw "<<rightCode.place<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
  
      
    } else{
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<codeGenerationVars.find(tmp->name->name)->second->offset<<"($sp)"<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"sw "<<rightCode.place<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
        
    }
  
  } else{
    IdExpr* tmp = (IdExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name)== codeGenerationVars.end()){
    if(codeGenerationVars.find(tmp->name)->second->type == INT){
    code<<"sw " << rightCode.place<<" ,"<<tmp->name<<endl ;
     
   
    } else{

    code<<"s.s " << rightCode.place<<" ,"<<tmp->name<<endl ;
    }

    }
    else{
     
    if(codeGenerationVars.find(tmp->name)->second->type == INT){
    code<<"sw " << rightCode.place<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
    } else{

    code<<"s.s " << rightCode.place<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
    }
    }
  }
  releaseRegister(rightCode.place);
  context.code=code.str();
}

Type PlusEqExpr::getType(){
    if(this->expr1->tipo != 1  &&  this->expr1->tipo != 2){
      cerr<<"Left side of equality isnt correct "<<line<<endl; 
       exit(0);
    }

    Type tipo1= this->expr1->getType();
    Type tipo2= this->expr2->getType();

    if(tipo1 != INT && tipo1 != FLOAT  ){
        cerr<<"Cant operate in none number types "<<line<<endl; 
         exit(0);
    }
    if(tipo2 != INT && tipo2 != FLOAT  ){
        cerr<<"Cant operate in none number types "<<line<<endl; 
         exit(0);
    }

      if(tipo1 != tipo2){
        cerr<<"Equality isnt the same type "<<line<<endl; 
        exit(0);
    }
    
    return tipo1; 

}


void PlusEqExpr::gen(Code &context, int isUnary){
  Code rightCode;
  stringstream code;
  this->expr2->gen(rightCode, isUnary);
  code<<rightCode.code<<endl;
   
  if(this->expr1->tipo==2){
    ArrayAccessExpr* tmp = (ArrayAccessExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name->name)== codeGenerationVars.end()){
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<tmp->name->name<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"lw "<<reg2<<", "<<"0("<<reg3<<")"<<endl;
        code<<"add "<<reg1<<","<<reg2<<rightCode.place<<endl;
        code<<"sw "<<reg1<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
  
      
    } else{
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<codeGenerationVars.find(tmp->name->name)->second->offset<<"($sp)"<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"lw "<<reg2<<", "<<"0("<<reg3<<")"<<endl;
        code<<"add "<<reg1<<","<<reg2<<rightCode.place<<endl;
        code<<"sw "<<reg1<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
        
    }
  
  } else{
   
    IdExpr* tmp = (IdExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name)== codeGenerationVars.end()){
    if(codeGenerationVars.find(tmp->name)->second->type == INT){

    string reg1 = getIntTemp();
    code<<"lw "<<reg1<<tmp->name;
    code<<"add "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"sw " << reg1<<" ,"<<tmp->name<<endl ;
    releaseRegister(reg1);
   
    } else{
 
     string reg1 = getFloatTemp();
    code<<"l.s "<<reg1<<tmp->name;
    code<<"add.s "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"s.s " << reg1<<" ,"<<tmp->name<<endl ;
    releaseRegister(reg1);
    }

    }
    else{
    if(codeGenerationVars.find(tmp->name)->second->type == INT){
    string reg1 = getIntTemp();
    code<<"lw "<<reg1<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl;
    code<<"add "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"sw " << reg1<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
     releaseRegister(reg1);
    } else{

    string reg1 = getFloatTemp();
    code<<"l.s "<<reg1<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl;
    code<<"add.s "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"s.s " << reg1<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
     releaseRegister(reg1);
    }
    }
  }
  releaseRegister(rightCode.place);
  context.code=code.str();
}


Type SubEqExpr::getType(){
    if(this->expr1->tipo != 1  &&  this->expr1->tipo != 2){
      cerr<<"Left side of equality isnt correct "<<line<<endl; 
       exit(0);
    }

    Type tipo1= this->expr1->getType();
    Type tipo2= this->expr2->getType();

    if(tipo1 != INT  &&  tipo1 != FLOAT  ){
        cerr<<"Cant operate in none number types "<<line<<endl; 
         exit(0);
    }
    if(tipo2 != INT  &&  tipo2 != FLOAT  ){
        cerr<<"Cant operate in none number types "<<line<<endl; 
         exit(0);
    }

      if(tipo1 != tipo2){
        cerr<<"Equality isnt the same type "<<line<<endl; 
         exit(0);
    }
    
    return tipo1; 

}

void SubEqExpr::gen(Code &context, int isUnary){
Code rightCode;
  stringstream code;
  this->expr2->gen(rightCode, isUnary);
  code<<rightCode.code<<endl;
   
  if(this->expr1->tipo==2){
    ArrayAccessExpr* tmp = (ArrayAccessExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name->name)== codeGenerationVars.end()){
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<tmp->name->name<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"lw "<<reg2<<", "<<"0("<<reg3<<")"<<endl;
        code<<"sub "<<reg1<<","<<reg2<<rightCode.place<<endl;
        code<<"sw "<<reg1<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
  
      
    } else{
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<codeGenerationVars.find(tmp->name->name)->second->offset<<"($sp)"<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"lw "<<reg2<<", "<<"0("<<reg3<<")"<<endl;
        code<<"sub "<<reg1<<","<<reg2<<rightCode.place<<endl;
        code<<"sw "<<reg1<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
        
    }
  
  } else{
   
    IdExpr* tmp = (IdExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name)== codeGenerationVars.end()){
    if(codeGenerationVars.find(tmp->name)->second->type == INT){

    string reg1 = getIntTemp();
    code<<"lw "<<reg1<<tmp->name;
    code<<"sub "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"sw " << reg1<<" ,"<<tmp->name<<endl ;
    releaseRegister(reg1);
   
    } else{
 
     string reg1 = getFloatTemp();
    code<<"l.s "<<reg1<<tmp->name;
    code<<"sub.s "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"s.s " << reg1<<" ,"<<tmp->name<<endl ;
    releaseRegister(reg1);
    }

    }
    else{
    if(codeGenerationVars.find(tmp->name)->second->type == INT){
    string reg1 = getIntTemp();
    code<<"lw "<<reg1<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl;
    code<<"sub "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"sw " << reg1<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
     releaseRegister(reg1);
    } else{

    string reg1 = getFloatTemp();
    code<<"l.s "<<reg1<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl;
    code<<"sub.s "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"s.s " << reg1<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
     releaseRegister(reg1);
    }
    }
  }
  releaseRegister(rightCode.place);
  context.code=code.str();
}

Type MultEqExpr::getType(){
    if(this->expr1->tipo != 1  && this->expr1->tipo != 2){
      cerr<<"Left side of equality isnt correct "<<line<<endl; 
       exit(0);
    }

    Type tipo1= this->expr1->getType();
    Type tipo2= this->expr2->getType();

    if(tipo1 != INT  &&  tipo1 != FLOAT  ){
        cerr<<"Cant operate in none number types "<<line<<endl; 
         exit(0);
    }
    if(tipo2 != INT  &&  tipo2 != FLOAT  ){
        cerr<<"Cant operate in none number types "<<line<<endl; 
         exit(0);
    }

      if(tipo1 != tipo2){
        cerr<<"Equality isnt the same type "<<line<<endl; 
         exit(0);
    }
    
    return tipo1; 

}

void MultEqExpr::gen(Code &context , int isUnary){
Code rightCode;
  stringstream code;
  this->expr2->gen(rightCode, isUnary);
  code<<rightCode.code<<endl;
   
  if(this->expr1->tipo==2){
    ArrayAccessExpr* tmp = (ArrayAccessExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name->name)== codeGenerationVars.end()){
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<tmp->name->name<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"lw "<<reg2<<", "<<"0("<<reg3<<")"<<endl;
        code<<"mult "<<reg2<<", "<<rightCode.place<<endl<<"mflo "<<" ,"<<reg1<<endl;
        code<<"sw "<<reg1<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
  
      
    } else{
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<codeGenerationVars.find(tmp->name->name)->second->offset<<"($sp)"<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"lw "<<reg2<<", "<<"0("<<reg3<<")"<<endl;
        code<<"mult "<<reg2<<", "<<rightCode.place<<endl<<"mflo "<<" ,"<<reg1<<endl;
        code<<"sw "<<reg1<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
        
    }
  
  } else{
   
    IdExpr* tmp = (IdExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name)== codeGenerationVars.end()){
    if(codeGenerationVars.find(tmp->name)->second->type == INT){

    string reg1 = getIntTemp();
    code<<"lw "<<reg1<<tmp->name;
    code<<"mult "<<reg1<<", "<<rightCode.place<<endl<<"mflo "<<" ,"<<reg1<<endl;
    code<<"sw " << reg1<<" ,"<<tmp->name<<endl ;
    releaseRegister(reg1);
   
    } else{
 
     string reg1 = getFloatTemp();
    code<<"l.s "<<reg1<<tmp->name;
    code<<"mult.s "<<reg1<<", "<<reg1<<" ,"<<rightCode.place<<endl;
    code<<"s.s " << reg1<<" ,"<<tmp->name<<endl ;
    releaseRegister(reg1);
    }

    }
    else{
    if(codeGenerationVars.find(tmp->name)->second->type == INT){
    string reg1 = getIntTemp();
    code<<"lw "<<reg1<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl;
    code<<"mult "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"sw " << reg1<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
     releaseRegister(reg1);
    } else{

    string reg1 = getFloatTemp();
    code<<"l.s "<<reg1<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl;
    code<<"mult.s "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"s.s " << reg1<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
     releaseRegister(reg1);
    }
    }
  }
  releaseRegister(rightCode.place);
  context.code=code.str();
}

Type DivEqExpr::getType(){
    if(this->expr1->tipo != 1  &&  this->expr1->tipo != 2){
      cerr<<"Left side of equality isnt correct "<<line<<endl; 
       exit(0);
    }

    Type tipo1= this->expr1->getType();
    Type tipo2= this->expr2->getType();

    if(tipo1 != INT  &&  tipo1 != FLOAT  ){
        cerr<<"Cant operate in none number types "<<line<<endl; 
         exit(0);
    }
    if(tipo2 != INT  &&  tipo2 != FLOAT  ){
        cerr<<"Cant operate in none number types "<<line<<endl; 
         exit(0);
    }

      if(tipo1 != tipo2){
        cerr<<"Equality isnt the same type "<<line<<endl; 
         exit(0);
    }
    
    return tipo1; 

}

void DivEqExpr::gen(Code &context, int isUnary){
  Code rightCode;
  stringstream code;
  this->expr2->gen(rightCode, isUnary);
  code<<rightCode.code<<endl;
   
  if(this->expr1->tipo==2){
    ArrayAccessExpr* tmp = (ArrayAccessExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name->name)== codeGenerationVars.end()){
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<tmp->name->name<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"lw "<<reg2<<", "<<"0("<<reg3<<")"<<endl;
        code<<"div "<<reg2<<", "<<rightCode.place<<endl<<"mflo "<<" ,"<<reg1<<endl;
        code<<"sw "<<reg1<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
  
      
    } else{
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<codeGenerationVars.find(tmp->name->name)->second->offset<<"($sp)"<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"lw "<<reg2<<", "<<"0("<<reg3<<")"<<endl;
        code<<"div "<<reg2<<", "<<rightCode.place<<endl<<"mflo "<<" ,"<<reg1<<endl;
        code<<"sw "<<reg1<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
        
    }
  
  } else{
   
    IdExpr* tmp = (IdExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name)== codeGenerationVars.end()){
    if(codeGenerationVars.find(tmp->name)->second->type == INT){

    string reg1 = getIntTemp();
    code<<"lw "<<reg1<<tmp->name;
    code<<"div "<<reg1<<", "<<rightCode.place<<endl<<"mflo "<<" ,"<<reg1<<endl;
    code<<"sw " << reg1<<" ,"<<tmp->name<<endl ;
    releaseRegister(reg1);
   
    } else{
 
     string reg1 = getFloatTemp();
    code<<"l.s "<<reg1<<tmp->name;
    code<<"div.s "<<reg1<<", "<<reg1<<" ,"<<rightCode.place<<endl;
    code<<"s.s " << reg1<<" ,"<<tmp->name<<endl ;
    releaseRegister(reg1);
    }

    }
    else{
    if(codeGenerationVars.find(tmp->name)->second->type == INT){
    string reg1 = getIntTemp();
    code<<"lw "<<reg1<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl;
    code<<"div "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"sw " << reg1<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
     releaseRegister(reg1);
    } else{

    string reg1 = getFloatTemp();
    code<<"l.s "<<reg1<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl;
    code<<"div.s "<<reg1<<" ,"<<reg1<<" ,"<<rightCode.place;
    code<<"s.s " << reg1<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
     releaseRegister(reg1);
    }
    }
  }
  releaseRegister(rightCode.place);
  context.code=code.str();
}

Type ModEqExpr::getType(){
    if(this->expr1->tipo != 1  &&  this->expr1->tipo != 2){
      cerr<<"Left side of equality isnt correct "<<line<<endl; 
       exit(0);
    }

    Type tipo1= this->expr1->getType();
    Type tipo2= this->expr2->getType();

    if(tipo1 != INT  &&  tipo1 != FLOAT  ){
        cerr<<"Cant operate in none number types "<<line<<endl; 
         exit(0);
    }
    if(tipo2 != INT  &&  tipo2 != FLOAT  ){
        cerr<<"Cant operate in none number types "<<line<<endl; 
         exit(0);
    }

      if(tipo1 != tipo2){
        cerr<<"Equality isnt the same type "<<line<<endl; 
         exit(0);
    }
    
    return tipo1; 

}

void ModEqExpr::gen(Code &context, int isUnary){
  Code rightCode;
  stringstream code;
  this->expr2->gen(rightCode, isUnary);
  code<<rightCode.code<<endl;
   
  if(this->expr1->tipo==2){
    ArrayAccessExpr* tmp = (ArrayAccessExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name->name)== codeGenerationVars.end()){
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<tmp->name->name<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"lw "<<reg2<<", "<<"0("<<reg3<<")"<<endl;
        code<<"div "<<reg2<<", "<<rightCode.place<<endl<<"mfhi "<<" ,"<<reg1<<endl;
        code<<"sw "<<reg1<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
  
      
    } else{
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<codeGenerationVars.find(tmp->name->name)->second->offset<<"($sp)"<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<tmp->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        code<<"lw "<<reg2<<", "<<"0("<<reg3<<")"<<endl;
        code<<"div "<<reg2<<", "<<rightCode.place<<endl<<"mfhi "<<" ,"<<reg1<<endl;
        code<<"sw "<<reg1<<" ,"<<"0("<<reg3<<")"<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        releaseRegister(reg3);
        
    }
  
  } else{
   
    IdExpr* tmp = (IdExpr*)this->expr1;
    if(codeGenerationVars.find(tmp->name)== codeGenerationVars.end()){
    if(codeGenerationVars.find(tmp->name)->second->type == INT){

    string reg1 = getIntTemp();
    code<<"lw "<<reg1<<tmp->name;
    code<<"div "<<reg1<<", "<<rightCode.place<<endl<<"mfhi "<<" ,"<<reg1<<endl;
    code<<"sw " << reg1<<" ,"<<tmp->name<<endl ;
    releaseRegister(reg1);
   
    } 

    }
    else{
    if(codeGenerationVars.find(tmp->name)->second->type == INT){
    string reg1 = getIntTemp();
    code<<"lw "<<reg1<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl;
    code<<"div "<<reg1<<", "<<rightCode.place<<endl<<"mfhi "<<" ,"<<reg1<<endl;
    code<<"sw " << reg1<<" ,"<<codeGenerationVars.find(tmp->name)->second->offset<<"($sp)"<<endl ;
     releaseRegister(reg1);
    } 
    }
  }
  releaseRegister(rightCode.place);
  context.code=code.str();
}

Type PlusPlusExpr::getType(){
    Type tipo = this->id->getType();
    if(tipo != INT ){
         cerr<<"Cant increment variable type that is not int or float"<<line<<endl; 
          exit(0);
    }
    return tipo; 
}

void PlusPlusExpr::gen(Code &context, int isUnary){
stringstream code;

if(codeGenerationVars.find(this->id->name)== codeGenerationVars.end()){
string reg1 = getIntTemp();
code<<"lw "<<reg1<<" ,"<<this->id->name<<endl;
code<<"addi "<<reg1 <<" ,"<< reg1<<" ,1"<<endl;
code<<"sw "<<reg1<<" ,"<<this->id->name<<endl;
releaseRegister(reg1);
}
else{
string reg1 = getIntTemp();
code<<"lw "<<reg1<<" ,"<<codeGenerationVars.find(this->id->name)->second->offset<<"($sp)"<<endl;
code<<"addi "<<reg1 <<" ,"<< reg1<<" ,1"<<endl;
code<<"sw "<<reg1<<" ,"<<codeGenerationVars.find(this->id->name)->second->offset<<"($sp)"<<endl;
releaseRegister(reg1);
}
context.type =INT;
context.code= code.str();

}

Type SubSubExpr::getType(){
    Type tipo = this->id->getType();
    if(tipo != INT ){
         cerr<<"Cant decrement variable type that is not int or float"<<line<<endl; 
          exit(0);
    }
    return tipo; 
}

void SubSubExpr::gen(Code &context , int isUnary){
stringstream code;

if(codeGenerationVars.find(this->id->name)== codeGenerationVars.end()){
string reg1 = getIntTemp();
string reg2 = getIntTemp();
code<<"lw "<<reg1<<" ,"<<this->id->name<<endl;
code<<"li "<<reg2<<" ,1"<<endl;
code<<"sub "<<reg1 <<" ,"<< reg1<<" ,"<<reg2<<endl;
code<<"sw "<<reg1<<" ,"<<this->id->name<<endl;
releaseRegister(reg1);
releaseRegister(reg2);
}
else{

string reg1 = getIntTemp();
string reg2 = getIntTemp();
code<<"lw "<<reg1<<" ,"<<codeGenerationVars.find(this->id->name)->second->offset<<"($sp)"<<endl;
code<<"li "<<reg2<<" ,1"<<endl;
code<<"sub "<<reg1 <<" ,"<< reg1<<" ,"<<reg2<<endl;
code<<"lw "<<reg1<<" ,"<<codeGenerationVars.find(this->id->name)->second->offset<<"($sp)"<<endl;
releaseRegister(reg1);
releaseRegister(reg2);
}
context.type =INT;
context.code= code.str();
}

Type ArrayExpr::getType(){

   list<Expr *>::iterator it = this->valor.begin();
   Type tipo = (*it)->getType();
    while (it != this->valor.end())
    {
        if(tipo != (*it)->getType()){
            cerr<<"Array element is not same type as Array expression" << line << endl;
             exit(0);
        }
        it++;
    }
    if(tipo == INT  || tipo == FLOAT){
      return ARRAYNUMBER;
    } 
    else if (tipo == STRING) {
      return ARRAYSTRING;
    }
    else {
       return ARRAYBOOL;
    }
}

void ArrayExpr::gen(Code &context , int isUnary){

}

Type ArrayAccessExpr::getType(){
   Type tipo = this->name->getType();


   if(this->index->getType()!= INT){
      cerr<<"Array index not a number"<< line << endl;
       exit(0);
   }

   if(tipo== ARRAYNUMBER){
      return INT;
   }
   else if(tipo== ARRAYSTRING){
      return STRING;
   }
    else {
      return BOOL;
   }
   
}

void ArrayAccessExpr::gen(Code &context , int isUnary){
stringstream code;

if(codeGenerationVars.find(this->name->name)== codeGenerationVars.end()){

        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<this->name->name<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<this->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        context.code= code.str();
        context.place = reg3;
        context.type = INT;

}else{
        string reg1 = getIntTemp();
        code<<"la "<<reg1<<", "<<codeGenerationVars.find(this->name->name)->second->offset<<"($sp)"<<endl;
        string reg2 = getIntTemp();
        string reg3 = getIntTemp();
        code<<"li "<<reg2<<" ,"<<"4"<<endl<<"li "<<reg3<<" ,"<<this->index<<endl<<"mult "<<reg2<<", "<<reg3<<endl;
        code<<"mflo "<<reg2<<endl;
        code<<"add "<<reg3<<" ,"<<reg2<<" ,"<<reg1<<endl;
        releaseRegister(reg1);
        releaseRegister(reg2);
        context.code= code.str();
        context.place = reg3;
        context.type = INT;

}
}

Type MethodAccessExpr::getType(){
if(methods.count(this->name->name)>0){
  MethodInfo* tmp = methods.find(this->name->name)->second;

  if(tmp->parameters.size() != this->params.size()){
      cerr << "Method parameter arent same in size" << line << endl;
       exit(0);
  }
  list<Expr*>::iterator it1 = this->params.begin();
  list<DeclExpr*>::iterator it2 = tmp->parameters.begin();
    while (it1 != this->params.end())
    {
       if((*it1)->getType() != (*it2)->tipo){
         cerr << "Types in method do not match" << line << endl;
          exit(0);
       }else
       {
        if((*it1)->tipo==3)
        {
            if(((ArrayExpr*)(*it1))->valor.size()!=(*it2)->index)
            {
                cerr << "Array index must be a number" << line << endl;
                exit(0);
            }

        }else if((*it1)->getType()==ARRAYBOOL || (*it1)->getType()==ARRAYSTRING || (*it1)->getType()==ARRAYFLOAT || (*it1)->getType()==ARRAYINT  )
        {
            if((*it1)->tipo==1)
            {
                TypeClass* temp= getLocalVariableClass(((IdExpr*)(*it1))->name);
            
            if((*it2)->index!=temp->size)
            {
                cerr << "Array size don't match" << line << endl;
                exit(0);

            };
            }   
            


        }

       }
       it1++;
       it2++;
    }
 return tmp->returnType;
}
else{
  cerr << "Method doesnt exist" << line << endl;  
   exit(0);
  return INVALID;
}
}

void MethodAccessExpr::gen(Code &context , int isUnary){
list<Expr *>::iterator it = this->params.begin();
    list<Code> codes;
    stringstream code;
    Code argCode;
    while (it != this->params.end())
    {
        (*it)->gen(argCode,0);
        code << argCode.code << endl;
        codes.push_back(argCode);
        it++;
    }

    int i = 0;
    list<Code>::iterator codeIt = codes.begin();
    while (codeIt != codes.end())
    {
        releaseRegister((*codeIt).place);
        if ((*codeIt).type == INT)
        {
            code << "move $a" << i << ", " << (*codeIt).place << endl;
        }
        else
        {
            code << "mfc1 $a" << i << ", " << (*codeIt).place << endl;
        }
        i++;
        codeIt++;
    }

    code << "jal " << this->name->name << endl;
    string result;
    if (methods[this->name->name]->returnType == FLOAT)
    {
        result = getFloatTemp();
        code << "mtc1 $v0, " << result << endl;
    }
    else
    {
        result = getIntTemp();
        code << "move " << result << ", $v0" << endl;
    }
    context.code = code.str();
    context.place = result;
    context.type = methods[this->name->name]->returnType;

}

Type NegationExpr::getType(){

    if(this->expr->getType()!= BOOL){
        cerr << "Negation expression is not boolean " << line << endl; 
         exit(0);
    }
    return BOOL;
}

void NegationExpr::gen(Code &context , int isUnary){
    Code expr1;
    this->expr->gen(expr1,1);
    context.place=expr1.place;
    context.code=expr1.code;
}


Type AddExpr ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);

 if(validOpArit.count(busqueda)>0){
     Type tmp = validOpArit.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void AddExpr::gen(Code &context , int isUnary){
stringstream code;
Code leftCode, rightCode;
this->leftExpr->gen(leftCode, isUnary);
this->rightExpr->gen(rightCode, isUnary);
releaseRegister(leftCode.place);
releaseRegister(rightCode.place);
code<<leftCode.code<<endl<<rightCode.code<<endl;

if(leftCode.type==INT && rightCode.type==INT){
    string reg1 = getIntTemp();
    code<<"add "<<reg1<<" ,"<<leftCode.place<<" ,"<<rightCode.place<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= INT;

} else if(leftCode.type==FLOAT && rightCode.type == FLOAT){
    string reg1 = getFloatTemp();
    code<<"add.s "<<reg1<<" ,"<<leftCode.place<<" ,"<<rightCode.place<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= FLOAT;
}else{
 if(leftCode.type== INT){
  toFloat(leftCode);
  releaseRegister(leftCode.place);
  code<<leftCode.code<<endl;
 }
 else if(rightCode.type== INT){
 toFloat(rightCode);
 releaseRegister(rightCode.place);
 code<<rightCode.code<<endl;
 }
   string reg1 = getFloatTemp();
    code<<"add.s "<<reg1<<" ,"<<leftCode.place<<" ,"<<rightCode.place<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= FLOAT;
}
}

Type SubExpr ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);

 if(validOpArit.count(busqueda)>0){
     Type tmp = validOpArit.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void SubExpr::gen(Code &context , int isUnary){
stringstream code;
Code leftCode, rightCode;
this->leftExpr->gen(leftCode, isUnary);
this->rightExpr->gen(rightCode, isUnary);
releaseRegister(leftCode.place);
releaseRegister(rightCode.place);
code<<leftCode.code<<endl<<rightCode.code<<endl;

if(leftCode.type==INT && rightCode.type==INT){
    string reg1 = getIntTemp();
    code<<"sub "<<reg1<<" ,"<<leftCode.place<<" ,"<<rightCode.place<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= INT;

} else if(leftCode.type==FLOAT && rightCode.type == FLOAT){
    string reg1 = getFloatTemp();
    code<<"sub.s "<<reg1<<" ,"<<leftCode.place<<" ,"<<rightCode.place<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= FLOAT;
}else{
 if(leftCode.type== INT){
  toFloat(leftCode);
  releaseRegister(leftCode.place);
  code<<leftCode.code<<endl;
 }
 else if(rightCode.type== INT){
 toFloat(rightCode);
 releaseRegister(rightCode.place);
 code<<rightCode.code<<endl;
 }
   string reg1 = getFloatTemp();
    code<<"sub.s "<<reg1<<" ,"<<leftCode.place<<" ,"<<rightCode.place<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= FLOAT;
}
}

Type MultExpr ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);

 if(validOpArit.count(busqueda)>0){
     Type tmp = validOpArit.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void MultExpr::gen(Code &context , int isUnary){

stringstream code;
Code leftCode, rightCode;
this->leftExpr->gen(leftCode, isUnary);
this->rightExpr->gen(rightCode, isUnary);
releaseRegister(leftCode.place);
releaseRegister(rightCode.place);
code<<leftCode.code<<endl<<rightCode.code<<endl;

if(leftCode.type==INT && rightCode.type==INT){
    string reg1 = getIntTemp();
    code<<"mult "<<leftCode.place<<" ,"<<rightCode.place<<endl<<"mflo "<<reg1<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= INT;

} else if(leftCode.type==FLOAT && rightCode.type == FLOAT){
    string reg1 = getFloatTemp();
    code<<"mult.s "<<reg1<<", "<<leftCode.place<<" ,"<<rightCode.place<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= FLOAT;
}else{
 if(leftCode.type== INT){
  toFloat(leftCode);
  releaseRegister(leftCode.place);
  code<<leftCode.code<<endl;
 }
 else if(rightCode.type== INT){
 toFloat(rightCode);
 releaseRegister(rightCode.place);
 code<<rightCode.code<<endl;
 }
   string reg1 = getFloatTemp();
   code<<"mult.s "<<reg1<<", "<<leftCode.place<<" ,"<<rightCode.place<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= FLOAT;
}
}

Type DivExpr ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);

 if(validOpArit.count(busqueda)>0){
     Type tmp = validOpArit.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void DivExpr::gen(Code &context , int isUnary){
stringstream code;
Code leftCode, rightCode;
this->leftExpr->gen(leftCode, isUnary);
this->rightExpr->gen(rightCode, isUnary);
releaseRegister(leftCode.place);
releaseRegister(rightCode.place);
code<<leftCode.code<<endl<<rightCode.code<<endl;

if(leftCode.type==INT && rightCode.type==INT){
    string reg1 = getIntTemp();
    code<<"div "<<leftCode.place<<" ,"<<rightCode.place<<endl<<"mflo "<<reg1<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= INT;

} else if(leftCode.type==FLOAT && rightCode.type == FLOAT){
    string reg1 = getFloatTemp();
    code<<"div.s "<<reg1<<", "<<leftCode.place<<" ,"<<rightCode.place<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= FLOAT;
}else{
 if(leftCode.type== INT){
  toFloat(leftCode);
  releaseRegister(leftCode.place);
  code<<leftCode.code<<endl;
 }
 else if(rightCode.type== INT){
 toFloat(rightCode);
 releaseRegister(rightCode.place);
 code<<rightCode.code<<endl;
 }
   string reg1 = getFloatTemp();
   code<<"div.s "<<reg1<<", "<<leftCode.place<<" ,"<<rightCode.place<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= FLOAT;
}
}

Type ModExpr ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);

 if(validOpArit.count(busqueda)>0){
     Type tmp = validOpArit.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void ModExpr::gen(Code &context , int isUnary){

stringstream code;
Code leftCode, rightCode;
this->leftExpr->gen(leftCode, isUnary);
this->rightExpr->gen(rightCode, isUnary);
releaseRegister(leftCode.place);
releaseRegister(rightCode.place);
code<<leftCode.code<<endl<<rightCode.code<<endl;


    string reg1 = getIntTemp();
    code<<"div "<<leftCode.place<<" ,"<<rightCode.place<<endl<<"mfhi "<<reg1<<endl;
    context.place=reg1;
    context.code= code.str();
    context.type= INT;

}

Type GreaterExpr  ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);

 if(validCompare.count(busqueda)>0){
     Type tmp = validCompare.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void GreaterExpr::gen(Code &context, int isUnary){
    Code leftCode, rightCode;
    stringstream code;
    string label = newLabel("label");
    string finalLabel = newLabel("finalLabel");
    string falseLabel = newLabel("false");
    string endGtrLabel = newLabel("endGtr");
   
    this->leftExpr->gen(leftCode,isUnary);
    this->rightExpr->gen(rightCode,isUnary);
    
    if (leftCode.type == INT && rightCode.type == INT)
    {
        context.type = INT;
        code << leftCode.code << endl
             << rightCode.code << endl;
        releaseRegister(leftCode.place);
        releaseRegister(rightCode.place);
        string temp = getIntTemp();
        if(isUnary==0)
            code << "sgt " << temp << ", " << leftCode.place << ", " << rightCode.place << endl;
        else
            code << "slt " << temp << ", " << leftCode.place << ", " << rightCode.place << endl;
        
        context.place = temp;
    }
    else
    {
        context.type = FLOAT;
        toFloat(leftCode);
        toFloat(rightCode);
        code << leftCode.code << endl
             << rightCode.code << endl;
        releaseRegister(leftCode.place);
        releaseRegister(rightCode.place);
        string temp = getIntTemp();
        if(isUnary==0)
            code << "c.lt.s " << rightCode.place << ", " << leftCode.place << endl;
        else
            code << "c.lt.s " << leftCode.place << ", " << rightCode.place << endl;
    

       code<< "bc1f "<<falseLabel<<endl
           <<"li " <<temp<<", 1"<<endl
           <<"j "<<endGtrLabel<<endl
           <<falseLabel<<": "<<endl
           <<"li "<<temp<<", 0"<<endl
           <<endGtrLabel<<":"<<endl;
        
        
        context.place = temp;
    }

    context.code = code.str();

}

Type GreaterEqExpr  ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);

 if(validCompare.count(busqueda)>0){
     Type tmp = validCompare.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void GreaterEqExpr::gen(Code &context, int isUnary){
    Code leftCode, rightCode;
    stringstream code;
    string label = newLabel("label");
    string finalLabel = newLabel("finalLabel");
    string falseLabel = newLabel("false");
    string endGtrLabel = newLabel("endGtr");
     if(isUnary==1)
    {
        this->leftExpr->gen(leftCode,1);
        this->rightExpr->gen(rightCode,1);

    }else
    {
        this->leftExpr->gen(leftCode,0);
        this->rightExpr->gen(rightCode,0);
    }
    if (leftCode.type == INT && rightCode.type == INT)
    {
        context.type = INT;
        code << leftCode.code << endl
             << rightCode.code << endl;
        releaseRegister(leftCode.place);
        releaseRegister(rightCode.place);
        string temp = getIntTemp();
        if(isUnary==0)
            code << "sge " << temp << ", " << leftCode.place << ", " << rightCode.place << endl;
        else
            code << "sle " << temp << ", " << leftCode.place << ", " << rightCode.place << endl;
        
        
        context.place = temp;
    }
    else
    {
        context.type = FLOAT;
        toFloat(leftCode);
        toFloat(rightCode);
        code << leftCode.code << endl
             << rightCode.code << endl;
        releaseRegister(leftCode.place);
        releaseRegister(rightCode.place);
        string temp = getFloatTemp();
        if(isUnary==0)
            code << "c.le.s " << rightCode.place << ", " << leftCode.place << endl;
        else
            code << "c.le.s " << leftCode.place << ", " << rightCode.place << endl;

        code<< "bc1f "<<falseLabel<<endl
           <<"li " <<temp<<", 1"<<endl
           <<"j "<<endGtrLabel<<endl
           <<falseLabel<<": "<<endl
           <<"li "<<temp<<", 0"<<endl
           <<endGtrLabel<<":"<<endl;
            
        
        context.place = temp;
    }

    context.code = code.str();

}

Type LesserExpr  ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);
 
 if(validCompare.count(busqueda)>0){
     Type tmp = validCompare.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void LesserExpr::gen(Code &context, int isUnary){
    Code leftCode, rightCode;
    stringstream code;
    string falseLabel = newLabel("false");
    string endGtrLabel = newLabel("endGtr");
    if(isUnary==1)
    {
        this->leftExpr->gen(leftCode,1);
        this->rightExpr->gen(rightCode,1);

    }else
    {
        this->leftExpr->gen(leftCode,0);
        this->rightExpr->gen(rightCode,0);
    }
    if (leftCode.type == INT && rightCode.type == INT)
    {
        context.type = INT;
        code << leftCode.code << endl
             << rightCode.code << endl;
        releaseRegister(leftCode.place);
        releaseRegister(rightCode.place);
        string temp = getIntTemp();
        if(isUnary==0)
            code << "slt " << temp << ", " << leftCode.place << ", " << rightCode.place << endl;
        else
            code << "sgt " << temp << ", " << leftCode.place << ", " << rightCode.place << endl;
        context.place = temp;
    }
    else
    {
        context.type = FLOAT;
        toFloat(leftCode);
        toFloat(rightCode);
        code << leftCode.code << endl
             << rightCode.code << endl;
        releaseRegister(leftCode.place);
        releaseRegister(rightCode.place);
        string temp = getFloatTemp();
        if(isUnary==0)
            code << "c.lt.s " << leftCode.place << ", " << rightCode.place << endl;
        else
            code << "c.lt.s " <<  rightCode.place<< ", " << leftCode.place << endl;

         code<< "bc1f "<<falseLabel<<endl
           <<"li " <<temp<<", 1"<<endl
           <<"j "<<endGtrLabel<<endl
           <<falseLabel<<": "<<endl
           <<"li "<<temp<<", 0"<<endl
           <<endGtrLabel<<":"<<endl;

        context.place = temp;
    }

    context.code = code.str();
}

Type LessEqExpr  ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);

 if(validCompare.count(busqueda)>0){
     Type tmp = validCompare.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void LessEqExpr ::gen(Code &context , int isUnary){
    Code leftCode, rightCode;
    stringstream code;
    string falseLabel = newLabel("false");
    string endGtrLabel = newLabel("endGtr");
    if(isUnary==1)
    {
        this->leftExpr->gen(leftCode,1);
        this->rightExpr->gen(rightCode,1);

    }else
    {
        this->leftExpr->gen(leftCode,0);
        this->rightExpr->gen(rightCode,0);
    }
    if (leftCode.type == INT && rightCode.type == INT)
    {
        context.type = INT;
        code << leftCode.code << endl
             << rightCode.code << endl;
        releaseRegister(leftCode.place);
        releaseRegister(rightCode.place);
        string temp = getIntTemp();
        if(isUnary==0)
            code << "sle " << temp << ", " << leftCode.place << ", " << rightCode.place << endl;
        else
            code << "sge " << temp << ", " << leftCode.place << ", " << rightCode.place << endl;
        context.place = temp;
    }
    else
    {
        context.type = FLOAT;
        toFloat(leftCode);
        toFloat(rightCode);
        code << leftCode.code << endl
             << rightCode.code << endl;
        releaseRegister(leftCode.place);
        releaseRegister(rightCode.place);
        string temp = getIntTemp();
        if(isUnary==0)
            code << "c.le.s " << leftCode.place << ", " << rightCode.place << endl;
        else
            code << "c.le.s " <<  rightCode.place<< ", " << leftCode.place << endl;

        
        code<< "bc1f "<<falseLabel<<endl
           <<"li " <<temp<<", 1"<<endl
           <<"j "<<endGtrLabel<<endl
           <<falseLabel<<": "<<endl
           <<"li "<<temp<<", 0"<<endl
           <<endGtrLabel<<":"<<endl;

        
        context.place = temp;
    }

    context.code = code.str();
}

Type EqEqExpr  ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);

 if(validCompare.count(busqueda)>0){
     Type tmp = validCompare.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void EqEqExpr::gen(Code &context, int isUnary){
    Code leftSideCode, rightSideCode;
    this->leftExpr->gen(leftSideCode,0);
    this->rightExpr->gen(rightSideCode,0);
    stringstream code;
    string falseLabel = newLabel("false");
    string endGtrLabel = newLabel("endGtr");
    if (leftSideCode.type == INT && rightSideCode.type == INT)
    {
        context.type = INT;
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        code << leftSideCode.code << endl
             << rightSideCode.code;
        string tempInt = getIntTemp();
        string label = newLabel("eqlabel");
        string finalLabel = newLabel("finalEqLabel");
        code << "beq " << leftSideCode.place << ", " << rightSideCode.place << ", " << label << endl;
        code << "li " << tempInt << ", 0" << endl
             << " j " << finalLabel << endl;
        code << label << ": " << endl
             << "li " << tempInt << ", 1" << endl;
        code << finalLabel << ": " << endl;
        context.place = tempInt;
    }
    else
    {
        context.type = FLOAT;
        toFloat(leftSideCode);
        toFloat(rightSideCode);
        releaseRegister(leftSideCode.place);
        releaseRegister(rightSideCode.place);
        code << leftSideCode.code << endl
             << rightSideCode.code << endl;

        string temp = getIntTemp();
        if(isUnary==0)
            code << "c.eq.s " << leftSideCode.place << ", " << rightSideCode.place << endl;
        else
            code << "c.eq.s " <<  rightSideCode.place<< ", " << leftSideCode.place << endl;

        
        code<< "bc1f "<<falseLabel<<endl
           <<"li " <<temp<<", 1"<<endl
           <<"j "<<endGtrLabel<<endl
           <<falseLabel<<": "<<endl
           <<"li "<<temp<<", 0"<<endl
           <<endGtrLabel<<":"<<endl;

        
        context.place = temp;
    }
    context.code = code.str();

}


Type NotEqExpr  ::getType(){
 Type tipo1 = this->leftExpr->getType();
 Type tipo2 =this->rightExpr->getType();
 string busqueda = getTypeName(tipo1)+","+getTypeName(tipo2);

 if(validCompare.count(busqueda)>0){
     Type tmp = validCompare.find(busqueda)->second;
     return tmp;

 }
 else{
     cerr << "Arithmetic operation type dont match " << line << endl; 
     exit(0);
 }
}

void NotEqExpr::gen(Code &context, int isUnary){
    
    Code leftCode, rightCode;
    stringstream code;
    this->leftExpr->gen(leftCode,isUnary);
    this->rightExpr->gen(rightCode,isUnary);
    releaseRegister(rightCode.code);
    code<<leftCode.code<<endl<<rightCode.code<<endl;
    if(leftCode.type==INT && rightCode.type==INT  ){
        context.type = INT;
     string newPlace = getIntTemp();
     if(isUnary==0){
         code<<"sne "<<newPlace<<" , "<<leftCode.place<<" , "<<rightCode.place;
     } else {
         code<<"seq "<<newPlace<<" , "<<leftCode.place<<" , "<<rightCode.place;
     }
     context.place = newPlace;
    } else if(leftCode.type==FLOAT && rightCode.type==FLOAT  ){
           context.type = FLOAT;
     if(isUnary==0){
         code<<"div.s"<<leftCode.place <<" , "<< leftCode.place<<" , " << rightCode.place<<endl;
         string reg1 = getIntTemp();
         string lab = newLabel("isEq");
         string endNEQ = newLabel("endNEQ");
         code <<"li " << reg1 <<" , "<<"1"<<endl;
         string floatTemp = getFloatTemp();
         code << "mtc1 " << reg1<< ", " << floatTemp << endl
             << "cvt.s.w " << floatTemp << ", " << floatTemp << endl;
         
         code <<"c.eq.s " <<floatTemp <<", "<<leftCode.place<<endl;
         code <<"bc1t " << lab <<endl;
         code <<"li " << reg1 <<" , "<<"1"<<endl;
         code<<"li.s "<<floatTemp<<" , "<< "3.2"<<endl;

         code<<"c.eq.s " <<floatTemp<<", "<<floatTemp<<endl <<"j " <<endNEQ<<endl;
         code<<lab<<": " <<endl << "li.s " << floatTemp <<" , "<<"3.1"<<endl;
         code <<"li " << reg1 <<" , "<<"0"<<endl;
         code<<"c.eq.s " <<floatTemp <<", "<<leftCode.place<<endl <<"j "<<endNEQ<<endl;
         code<<endNEQ<<": "<<endl;
         
         context.place=reg1;
     } else {
         code<<"c.eq.s"<<leftCode.place<<" , "<<rightCode.place;
         context.place = leftCode.place;
     }
    } else{
           context.type = FLOAT;
       if(leftCode.type==INT){
          toFloat(leftCode);
          code<<leftCode.code<<endl;
       } else if(rightCode.type==INT){
          toFloat(rightCode);
           code<<rightCode.code<<endl;
       }
         if(isUnary==0){
          code<<"div.s"<<leftCode.place <<" , "<< leftCode.place<<" , " << rightCode.place<<endl;
         string reg1 = getIntTemp();
         string lab = newLabel("isEq");
         string endNEQ = newLabel("endNEQ");
         code <<"li " << reg1 <<" , "<<"1"<<endl;
         string floatTemp = getFloatTemp();
         code << "mtc1 " << reg1<< ", " << floatTemp << endl
             << "cvt.s.w " << floatTemp << ", " << floatTemp << endl;
         
         code <<"c.eq.s " <<floatTemp <<", "<<leftCode.place<<endl;
         code <<"bc1t " << lab <<endl;
         code <<"li " << reg1 <<" , "<<"1"<<endl;
         code<<"li.s "<<floatTemp<<" , "<< "3.2"<<endl;

         code<<"c.eq.s " <<floatTemp<<", "<<floatTemp<<endl <<"j " <<endNEQ<<endl;
         code<<lab<<": " <<endl << "li.s " << floatTemp <<" , "<<"3.1"<<endl;
         code <<"li " << reg1 <<" , "<<"0"<<endl;
         code<<"c.eq.s " <<floatTemp <<", "<<leftCode.place<<endl <<"j "<<endNEQ<<endl;
         code<<endNEQ<<": "<<endl;
         
         context.place=reg1;
         } else {
         code<<"c.eq.s"<<leftCode.place<<" , "<<rightCode.place;
         context.place = leftCode.place;
        }

    }
    context.code = code.str();
}

Type LogicalOrExpr ::getType(){
     Type tipo1 = this->leftExpr->getType();
     Type tipo2 =this->rightExpr->getType();
     if(tipo1!= BOOL || tipo2!= BOOL){
          cerr << "Or expression needs bool" << line << endl; 
          exit(0);
     }
     return BOOL;
}

void LogicalOrExpr::gen(Code &context, int isUnary){
    Code leftCode, rightCode;
   
    this->leftExpr->gen(leftCode,isUnary);
    this->rightExpr->gen(rightCode,isUnary);
    stringstream code;
    code << leftCode.code << endl
         << rightCode.code << endl;
    context.type=leftCode.type;
    releaseRegister(leftCode.place);
    releaseRegister(rightCode.place);
    string temp = getIntTemp();
    string label = newLabel("label");
    string finalLabel = newLabel("finalLabel");
    code << "li " << temp << ", 1" << endl;
    code << "beq " << leftCode.place << ", " << temp<<", " << finalLabel << endl;
    code << "beq " << rightCode.place << ", " << temp<<", " << finalLabel << endl;
    code << label << ": " << endl
         << "li " << temp << ", 0" << endl
         << finalLabel << ":" << endl;
    context.place = temp;
    context.code = code.str();

}

Type LogicalAndExpr ::getType(){
     Type tipo1 = this->leftExpr->getType();
     Type tipo2 =this->rightExpr->getType();
     if(tipo1!= BOOL || tipo2!= BOOL){
          cerr << " AND expression needs bool" << line << endl; 
          exit(0);
     }
     return BOOL;
}

void LogicalAndExpr::gen(Code &context, int isUnary){
    Code leftCode, rightCode;
   
    this->leftExpr->gen(leftCode,isUnary);
    this->rightExpr->gen(rightCode,isUnary);

    stringstream code;
    code << leftCode.code << endl
         << rightCode.code << endl;
    
    string temp = getIntTemp();
    string label = newLabel("label");
    string finalLabel = newLabel("finalLabel");
    code << "li " << temp << ", 0" << endl;
    code << "beq " << leftCode.place << ", " << temp <<", "<< finalLabel << endl;
    code << "beq " << rightCode.place << ", " << temp<<", " << finalLabel << endl;
    code << label << ": " << endl
         << "li " << temp << ", 1" << endl
         << finalLabel << ":" << endl;
    context.place = temp;
    releaseRegister(leftCode.place);
    releaseRegister(rightCode.place);
    context.code = code.str();

}

int DeclareVariableStatement ::evaluateSemantic(){
    Type tipo = getLocalVariableType(this->name);
    if(tipo != INVALID){
    cerr << " Variable already declared " <<this->name<< line << endl; 
    exit(0);
    }
if(expr!= nullptr){
    if(expr->getType() != type){
         cerr << " Variable type is not the same as expression " << line << endl; 
         exit(0);
    }
}
    TypeClass* tipazo=new TypeClass(this->name,this->type,0,0);
    context->vars.insert(std::pair<string,TypeClass*>(this->name,tipazo));

    return 0;
}

string DeclareVariableStatement::genCode(int context){
    stringstream code;
    Code cod;
    
    if(context==1)
    {
        //CodeGenerationVariableInfo(int offset, bool isArray, bool isParameter, Type type, int size)
        this->expr->gen(cod,0);
        if(cod.type==INT )
        {
            codeGenerationVars[this->name] =
            new CodeGenerationVariableInfo(globalStackPointer,0,0,FLOAT,0);
            globalStackPointer += 4;
            code << "sw " << cod.place << ", " << codeGenerationVars.find(this->name)->second->offset << "($sp)" << endl;
        }else if(cod.type==FLOAT){
            codeGenerationVars[this->name] =
            new CodeGenerationVariableInfo(globalStackPointer,0,0,FLOAT,0);
            globalStackPointer += 4;
            code << "s.s " << cod.place << ", " << codeGenerationVars.find(this->name)->second->offset << "($sp)" << endl;

        }

        
        code<<cod.code<<endl;
    
    }else
    {
        //TypeClass(string name, Type type, int isArray,int size){
        if(cod.type==FLOAT)
        {
            stringstream codigo2;
            codigo2<<this->name<<": .word 0"<<endl;
            assemblyFile.data+=codigo2.str();
            TypeClass* tipazo= new TypeClass(this->name,this->type,0,0);
            globalVars[this->name] =tipazo;
           
            code << "s.s " <<cod.place<<","<<this->name<<endl;

        }else{

            stringstream codigo2;
            codigo2<<this->name<<": .word 0"<<endl;
            assemblyFile.data+=codigo2.str();
            TypeClass* tipazo= new TypeClass(this->name,this->type,0,0);
            globalVars[this->name] =tipazo;
           
            code << "sw " <<cod.place<<","<<this->name<<endl;
        }
        

        

    }
    
    return code.str();
}

int DeclareArrayVariableStatement ::evaluateSemantic(){

    Type tipo = getLocalVariableType(this->name);
    if(tipo != INVALID){
    cerr << " Variable already declared " <<this->name<< line << endl; 
    exit(0);
    }

    if(expr->getType() != INT){
         cerr << " Array size type is not int " << line << endl; 
         exit(0);
    }


    
    TypeClass* tipazo=new TypeClass(this->name,this->type,1,this->params.size());
    context->vars.insert(std::pair<string,TypeClass*>(this->name,tipazo));
    return 0;
}

string DeclareArrayVariableStatement::genCode(int context){

    stringstream code;
    Code cod;
    
    if(context==1)
    {
        //CodeGenerationVariableInfo(int offset, bool isArray, bool isParameter, Type type, int size)
        this->expr->gen(cod,0);
      
            codeGenerationVars[this->name] =
            new CodeGenerationVariableInfo(globalStackPointer,1,0,ARRAYINT,this->params.size());
            globalStackPointer += 4;
            code << "sw " << cod.place << ", " << codeGenerationVars.find(this->name)->second->offset << "($sp)" << endl;
            globalStackPointer+= 4 * this->params.size();

            list<Expr *>::iterator itExpr = this->params.begin();
            int tempoffset= codeGenerationVars.find(this->name)->second->offset;
            while((itExpr)!=this->params.end())
            {
                Code expr;
                (*itExpr)->gen(expr,0);
                code<<expr.code<<endl;
                code << "sw " << expr.place << ", " << tempoffset<< "($sp)" << endl;

                tempoffset+=4;
            }

       
            
    
    }else
    {
        //TypeClass(string name, Type type, int isArray,int size){
        

        stringstream codigo2;
        int size= this->params.size()*4;
        codigo2<<this->name<<": .space "<<size<<endl;
        assemblyFile.data+=codigo2.str();
        TypeClass* tipazo= new TypeClass(this->name,this->type,1,this->params.size());
        globalVars[this->name] =tipazo;
        string temp= getIntTemp();
        code << "la " <<temp<<","<<this->name<<endl;

        list<Expr *>::iterator itExpr = this->params.begin();
            
            while((itExpr)!=this->params.end())
            {
                Code expr;
                (*itExpr)->gen(expr,0);
                code<<expr.code<<endl;
                code << "sw " << expr.place << ", " << "0"<< "("<<temp<<")" << endl;
                
                code<<"addi " << temp <<","<< temp<<","<<"4"<<endl;
            }
      
            releaseRegister(temp);
        

        

    }
    
    return code.str();


  
}

int DeclareMethodStatement ::evaluateSemantic(){

    if(methods.count(name) >0){
                cerr << " Method already declared " <<this->name<< line << endl; 
                exit(0);
    }
    if(params.size()>4){
        cerr << " Method parameters cant be greater than 4" <<this->name<< line << endl; 
        exit(0);
    }
    MethodInfo * temp = new MethodInfo();
   temp->parameters = params;
   temp->returnType =this->type;
   methods.insert(std::pair<string, MethodInfo *>( this->name, temp));
    
    pushContext("method", this->type);
     list<DeclExpr*>::iterator it = this->params.begin();

    while (it != this->params.end())
    { 
    Type tmp = getLocalVariableType((*it)->name);
    (*it)->getType();
    if( (*it)->tipo==2)
    {
        TypeClass* tipazo=new TypeClass(this->name,this->type,1,params.size());
        context->vars.insert(std::pair<string,TypeClass*>(this->name,tipazo));
    }else
    {
        TypeClass* tipazo=new TypeClass(this->name,this->type,0,0);
        context->vars.insert(std::pair<string,TypeClass*>(this->name,tipazo));

    }
    
    
    it++;
    }


    list<Statement *>::iterator it2 = this->stmts.begin();

    while (it2 != this->stmts.end())
    { 
    (*it2)->evaluateSemantic();
    it2++;
     }

   popContext();
   return 0;
}

string DeclareMethodStatement::genCode(int context){
    return "";
}

int DeclareArrayMethodStatement ::evaluateSemantic(){

    if(methods.count(name) >0){
                cerr << " Method already declared " <<this->name<< line << endl; 
                exit(0);
    }
    if(params.size()>4){
        cerr << " Method parameters cant be greater than 4" <<this->name<< line << endl; 
        exit(0);
    }
    MethodInfo * temp = new MethodInfo();
   temp->parameters = params;
   temp->returnType =this->type;
   methods.insert(std::pair<string, MethodInfo *>( this->name, temp));
    
    pushContext("method", this->type);
     list<DeclExpr*>::iterator it = this->params.begin();

    while (it != this->params.end())
    { 
    Type tmp = getLocalVariableType((*it)->name);
    if(tmp != INVALID){
        cerr << "Variable in parameter already declared " <<this->name<< line << endl; 
        exit(0);
    }
    (*it)->getType();
    if( (*it)->tipo==2)
    {
        TypeClass* tipazo=new TypeClass(this->name,this->type,1,params.size());
        context->vars.insert(std::pair<string,TypeClass*>(this->name,tipazo));
    }else
    {
        TypeClass* tipazo=new TypeClass(this->name,this->type,0,0);
        context->vars.insert(std::pair<string,TypeClass*>(this->name,tipazo));

    }
    it++;
    }


    list<Statement *>::iterator it2 = this->stmts.begin();

    while (it2 != this->stmts.end())
    { 
    (*it2)->evaluateSemantic();
    it2++;
     }

   popContext();
   return 0;
}

string DeclareArrayMethodStatement::genCode(int context){
 return "";
}

int IfStatement::evaluateSemantic(){
    if(this->expr->getType()!= BOOL){
        cerr << " If expression must be boolean" << line << endl; 
        exit(0);
    }

    list<Statement *>::iterator it = this->stmts.begin();
    pushContext("if", VOID);
    while (it != this->stmts.end())
    { 
     (*it)->evaluateSemantic();
    it++;
   }
   popContext();
   if(falseSmt!= nullptr){

       falseSmt->evaluateSemantic();
   }
  return 0;
}

string IfStatement::genCode(int context){
    return "";
}

int IfElseStatement::evaluateSemantic(){
    if(this->expr->getType()!= BOOL){
        cerr << "Else If expression must be boolean" << line << endl; 
        exit(0);
    }

    list<Statement *>::iterator it = this->stmts.begin();
    pushContext("ifElse", VOID);
    while (it != this->stmts.end())
    { 
     (*it)->evaluateSemantic();
    it++;
   }
   popContext();
   if(falseSmt!= nullptr){

       falseSmt->evaluateSemantic();
   }
  return 0;
}

string IfElseStatement::genCode(int context){
    return "";
}

int ElseStatement::evaluateSemantic(){

    list<Statement *>::iterator it = this->stmts.begin();
    pushContext("else", VOID);
    while (it != this->stmts.end())
    { 
     (*it)->evaluateSemantic();
    it++;
   }
   popContext();
   return 0;
}

string ElseStatement::genCode(int context){

}

int ReturnStatement::evaluateSemantic(){
 Type tmp = getValidContext();
 if(tmp == INVALID){
  cerr << "Return must be in method" << line << endl; 
        exit(0);
  }
  if (tmp != this->expr->getType()){
       cerr << "return doesnt match type of method" << line << endl; 
        exit(0);
  }
   return 0; 
}

string ReturnStatement::genCode(int context){
    Code exprCode;
    this->expr->gen(exprCode,0);
    releaseRegister(exprCode.code);
    stringstream code;
    code << exprCode.code << endl;
    if (exprCode.type == INT)
    {
        code << "move $v0, " << exprCode.place << endl;
    }
    else
    {
        code << "mfc1 $v0, " << exprCode.place << endl;
    }

    return code.str();
}

int BreakStatement::evaluateSemantic(){
    Type tmp = getValidContext2();
      if(tmp == INVALID){
      cerr << "Break must be in loop" << line << endl; 
        exit(0);
      }
   return 0; 
}

string BreakStatement::genCode(int context){
return "";
}

int ContinueStatement::evaluateSemantic(){
     Type tmp = getValidContext2();
      if(tmp == INVALID){
      cerr << "Continue must be in loop" << line << endl; 
        exit(0);
      }
   return 0; 
}

string ContinueStatement::genCode(int context){
    /*
    for i=0

        if x = papa
            continue
        
        y = tomate
        x +eee 

    continue:
    i++;
    j for

    for: 
    
    sle t0, t1, t2


    */
return "";
}
int ForStatement1::evaluateSemantic(){
    
    if(this->var->type!= INT ){
        cerr << "Iterator in for needs to be number" << line << endl;
        exit(0);
    }
    pushContext("for", VOID);
    Type tipo = getLocalVariableType(this->var->name);
    if(tipo != INVALID){
          cerr << "Variable as iterator already declared" << line << endl;
          exit(0);
    }
        TypeClass* tipazo=new TypeClass(this->var->name,this->var->type,0,0);
        context->vars.insert(std::pair<string,TypeClass*>(this->var->name,tipazo));
     if(this->exprL->getType()!= BOOL){
        cerr << "Condition in for needs to be bool" << line << endl;
        exit(0);
    }
    if(this->exprIt->getType()!= INT ){
        cerr << "Iterator in for needs to be number" << line << endl;
        exit(0);
    }
       list<Statement*>::iterator it = this->stmts.begin();
   
    while (it != this->stmts.end())
    {
         (*it)->evaluateSemantic();
        it++;
    }
    popContext();

    return 0;
}

string ForStatement1::genCode(int context){
    return "";
}

int ForStatement2::evaluateSemantic(){
  Type tipo = getLocalVariableType(this->name);
    if(tipo == INVALID){
          cerr << "Variable as iterator is not declared" << line << endl;
          exit(0);
    }
    if(tipo!= INT ){
        cerr << "Iterator in for needs to be number" << line << endl;
        exit(0);
    }
     if(this->equalityValue->getType()!= INT ){
       cerr << "Iterator in for needs to be number" << line << endl;
        exit(0);
    }
    if(tipo != this->equalityValue->getType()){
       cerr << "Iterator in for needs to be number" << line << endl;
        exit(0);
    }

    if(this->exprL->getType()!= BOOL){
        cerr << "Condition in for needs to be bool" << line << endl;
        exit(0);
    }
    if(this->exprIt->getType()!= INT ){
        cerr << "Iterator in for needs to be number" << line << endl;
        exit(0);
    }
 

    pushContext("for", VOID);

   
    list<Statement*>::iterator it = this->stmts.begin();
   
    while (it != this->stmts.end())
    {
         (*it)->evaluateSemantic();
        it++;
    }
    popContext();

    return 0;
}

string ForStatement2::genCode(int context){
    return "";
}

int ForEachStatement::evaluateSemantic(){
     Type tmp = getLocalVariableType(this->id);

     if(tmp == INVALID){
         cerr << "Array variable in foreach not declared" << line << endl;
         exit(0);
     }
      Type nuevo =INVALID;
      if(tmp == ARRAYNUMBER){
       nuevo =FLOAT;
     }
     else if (tmp == ARRAYSTRING)
     {
         nuevo =STRING;
         /* code */
     }
     else if(tmp == ARRAYBOOL){
         nuevo = BOOL; 
     }
     else{
         cerr << "Element to iterate in foreach not an array" << line << endl;
         exit(0);
     }

    Type tmp2 = getLocalVariableType(this->name);

     if(tmp2 != INVALID){
         cerr << "Variable already declared" << line << endl;
         exit(0);
     }
     
     pushContext("forEach", VOID);
     TypeClass* arr=getLocalVariableClass(this->name);
     TypeClass* tipazo=new TypeClass(this->name,arr->type,0,0);
     context->vars.insert(std::pair<string,TypeClass*>(this->name,tipazo));
     
      list<Statement*>::iterator it = this->stmts.begin();
   
      while (it != this->stmts.end())
      {
         (*it)->evaluateSemantic();
        it++;
     }
    popContext();

    return 0;
}

string ForEachStatement::genCode(int context){
    return "";
}

int AssignationStatement::evaluateSemantic(){
    this->expr->getType();
    return 0;
}

string AssignationStatement::genCode(int context){
    Code cod;
    this->expr->gen(cod,0);
    stringstream ss;
    ss<<cod.code<<endl;
 
    return ss.str();
}

int PrintStatement::evaluateSemantic(){
    return 0;
}

int ReadStatement::evaluateSemantic(){
    if(this->expr->tipo!=1  || this->expr->tipo!=2 )
    {
         cerr << "Expresion to read must be a variable" << line << endl;
         exit(0);
    }
    return 0;
}

string ReadStatement::genCode(int context){
    
    return "";
}

string PrintStatement::genCode(int context){
    return "";
}

int DeleteArrayStatement::evaluateSemantic(){
    Type tmp = getLocalVariableType(this->expr->name); 
    if(tmp == INVALID){
        cerr << "Array in delete is not declared " << line << endl;
        exit(0);
    }

    if( tmp != ARRAYBOOL && tmp != ARRAYNUMBER && tmp != ARRAYSTRING){
        cerr << "Expression is not array " << line << endl;
        exit(0);
    }

    if(this->index->getType()!= INT){
         cerr << "Array index is not int" << line << endl;
         exit(0);
    } 
  return 0;
}

string DeleteArrayStatement::genCode(int context){
    //no necesario agregar al proyecto
    return "";
}

int AddArrayStatement::evaluateSemantic(){
    Type tmp = getLocalVariableType(this->expr->name); 
    if(tmp == INVALID){
        cerr << "Array in delete is not declared " << line << endl;
        exit(0);
    }

    Type nuevo =INVALID;
      if(tmp == ARRAYNUMBER){
       nuevo =FLOAT;
     }
     else if (tmp == ARRAYSTRING)
     {
         nuevo =STRING;
         /* code */
     }
     else if(tmp == ARRAYBOOL){
         nuevo = BOOL; 
     }
     else{
         cerr << "Element to iterate in foreach not an array" << line << endl;
         exit(0);
     }

    if(this->index->getType()!= nuevo){
         cerr << "Expression to be added doesnt match array type" << line << endl;
         exit(0);
    } 

    return 0; 
}

string AddArrayStatement::genCode(int context){
     //no necesario agregar al proyecto
    return "";
}

int MainStatement::evaluateSemantic(){
    pushContext("main", VOID);
    list<Statement*>::iterator it = this->stmts.begin();
   
    while (it != this->stmts.end())
    {
         (*it)->evaluateSemantic();
        it++;
    }

    popContext();
    return 0;
}

string MainStatement::genCode(int context){
    return "";
}








