#ifndef _AST_H_
#define _AST_H_

#include "code.h"
#include <string>
#include <list>
#include <iostream>
using namespace std;
class Expr;
class Statement;
class DeclExpr;
class DeclareVariableStatement;
typedef list<Expr *> ExprList;
typedef list<Statement *> StmtList;
typedef list<DeclExpr *> DeclList;
typedef list<DeclareVariableStatement*> StmtList2;
string getTypeName(Type type);
class Expr{
    public:
    Expr(int line , int tipo){
        this->line= line;
        this->tipo = tipo;
     }
        int line;
        int tipo;
        virtual Type  getType() = 0;
        virtual void gen(Code &context, int isUnary) = 0;
};

class DeclExpr: public Expr{
    public:
         DeclExpr(string name , Type  type ,int tipo, int index,int line): Expr(line, tipo){
             this->name = name;
             this->type = type;
             this->line=line;
             this->tipo= tipo;
             this->index= index;
         }
        string name;
        Type  type;
        int line;
        int index;
        int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
     
};

class IdExpr : public Expr{
    public:
    IdExpr(string name, int line, int tipo): Expr(line, tipo){
        this->name = name ;
        this->line = line ; 
        this->tipo= tipo ;
    }
        string name ;
        int line;
        int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class EqualExpr : public Expr{
    public:
    EqualExpr(Expr * expr1,Expr * expr2, int line, int tipo): Expr(line, tipo){
        this->expr1 = expr1;
        this->expr2 = expr2;
        this->line = line ; 
        this->tipo= tipo ;
    }
        Expr * expr1;
        Expr * expr2;
        int line;
        int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class PlusEqExpr : public Expr{
    public:
    PlusEqExpr(Expr * expr1,Expr * expr2, int line, int tipo): Expr(line, tipo){
        this->expr1 = expr1;
        this->expr2 = expr2;
        this->line = line ; 
        this->tipo= tipo ;
    }
        Expr * expr1;
        Expr * expr2;
        int line;
        int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class SubEqExpr : public Expr{
    public:
    SubEqExpr(Expr * expr1,Expr * expr2, int line, int tipo): Expr(line, tipo){
        this->expr1 = expr1;
        this->expr2 = expr2;
        this->line = line ; 
        this->tipo= tipo ;
    }
        Expr * expr1;
        Expr * expr2;
        int line;
        int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};
class MultEqExpr : public Expr{
    public:
     MultEqExpr(Expr * expr1,Expr * expr2, int line, int tipo): Expr(line, tipo){
        this->expr1 = expr1;
        this->expr2 = expr2;
        this->line = line ; 
        this->tipo= tipo ;
    }
        Expr * expr1;
        Expr * expr2;
        int line;
        int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class DivEqExpr : public Expr{
    public:
    DivEqExpr(Expr * expr1,Expr * expr2, int line, int tipo): Expr(line, tipo){
        this->expr1 = expr1;
        this->expr2 = expr2;
        this->line = line ; 
        this->tipo= tipo ;
    }
        Expr * expr1;
        Expr * expr2;
        int line;
        int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class ModEqExpr : public Expr{
    public:
    ModEqExpr(Expr * expr1,Expr * expr2, int line, int tipo): Expr(line, tipo){
        this->expr1 = expr1;
        this->expr2 = expr2;
        this->line = line ; 
        this->tipo= tipo ;
    }
        Expr * expr1;
        Expr * expr2;
        int line;
        int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class IntExpr : public Expr{
    public:
    IntExpr(int valor , int line , int tipo): Expr(line, tipo){
        this->valor = valor ;
        this->line = line ; 
        this->tipo= tipo ;
    }
        int valor;
        int line;
         int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class FloatExpr : public Expr{
    public:
    FloatExpr(float valor , int line , int tipo): Expr(line, tipo){
        this->valor = valor ;
        this->line = line ; 
        this->tipo= tipo ;
    }
        float valor;
        int line;
         int tipo;
        Type  getType() ;
        void gen(Code &context, int isUnary);
};

class BoolExpr : public Expr{
    public:
     BoolExpr(bool valor , int line, int tipo): Expr(line, tipo){
        this->valor = valor ;
        this->line = line ; 
        this->tipo= tipo ;
    }
        bool valor;
        int line;
         int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class StringExpr : public Expr{
    public:
     StringExpr(string valor , int line , int tipo): Expr(line, tipo){
        this->valor = valor ;
        this->line = line ; 
        this->tipo= tipo ;
    }
        string valor;
        int line;
         int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class PlusPlusExpr : public Expr{
    public:
     PlusPlusExpr(IdExpr * id , int line , int tipo): Expr(line, tipo){
         this->id =id;
        this->line = line ; 
        this->tipo= tipo ;
    }
        IdExpr * id;
        int line;
         int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class SubSubExpr : public Expr{
    public:
     SubSubExpr(IdExpr * id , int line , int tipo): Expr(line, tipo){
         this->id =id;
        this->line = line ; 
        this->tipo= tipo ;
    }
        IdExpr * id;
        int line;
         int tipo;
        Type  getType();
        void gen(Code &context, int isUnary);
};

class ArrayExpr : public Expr{
     
    public:
    ArrayExpr( list<Expr*> valor , int line , int tipo): Expr(line, tipo){
        this->valor = valor ;
        this->line = line ; 
        this->tipo= tipo ;
     }
    list<Expr*> valor;
    int line;
     int tipo;
    Type  getType();
    void gen(Code &context, int isUnary);
};

class ArrayAccessExpr : public Expr{
     
    public:
    ArrayAccessExpr( IdExpr * name, Expr * index , int line , int tipo): Expr(line, tipo){
        this->name = name ;
        this->index = index;
        this->line = line ; 
        this->tipo= tipo ;
     }
     IdExpr *  name;
     Expr * index ;
    int line;
     int tipo;
     Type  getType();
      void gen(Code &context, int isUnary);
};

class MethodAccessExpr : public Expr{
    public:
    MethodAccessExpr( IdExpr  * name, list<Expr*> params , int line , int tipo): Expr(line, tipo){
        this->name = name ;
        this->params = params;
        this->line = line ; 
        this->tipo= tipo ;
     }
    IdExpr  * name;
    list<Expr*> params;
    int line;
     int tipo;
    Type  getType() ;
      void gen(Code &context, int isUnary);
};

class NegationExpr : public Expr{
    public:
     NegationExpr( Expr * expr, int line , int tipo): Expr(line, tipo){
        this->expr = expr ;
        this->line = line ; 
        this->tipo= tipo ;
     }
    Expr * expr;
    int line;
     int tipo;
    Type  getType();
    void gen(Code &context, int isUnary);
};



class BinaryExpr : public Expr{
    public:
        BinaryExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo): Expr(line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
        int tipo;
};

class AddExpr : public BinaryExpr{
    public:
        AddExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};

class SubExpr : public BinaryExpr{
    public:
        SubExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};

class MultExpr : public BinaryExpr{
    public:
         MultExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};

class DivExpr : public BinaryExpr{
    public:
         DivExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};

class ModExpr : public BinaryExpr{
    public:
         ModExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};

class GreaterExpr : public BinaryExpr{
    public:
         GreaterExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};

class GreaterEqExpr : public BinaryExpr{
    public:
         GreaterEqExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};

class LessEqExpr : public BinaryExpr{
    public:
         LessEqExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};

class LesserExpr : public BinaryExpr{
    public:
          LesserExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
       Type  getType();
          void gen(Code &context, int isUnary);

};

class EqEqExpr : public BinaryExpr{
    public:
         EqEqExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};

class NotEqExpr : public BinaryExpr{
    public:
         NotEqExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};

class LogicalOrExpr : public BinaryExpr{
    public:
         LogicalOrExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line, tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type getType();
          void gen(Code &context, int isUnary);

};

class LogicalAndExpr : public BinaryExpr{
    public:
         LogicalAndExpr(Expr * leftExpr, Expr * rightExpr, int line , int tipo) : BinaryExpr (leftExpr, rightExpr,line,tipo){
            this->leftExpr = leftExpr;
            this->rightExpr = rightExpr;
            this->line = line;
            this->tipo= tipo ;
        }
        Expr * leftExpr;
        Expr * rightExpr;
        int line;
         int tipo;
        Type  getType();
          void gen(Code &context, int isUnary);

};


class Statement{
    public:
        int line;
        virtual int evaluateSemantic() = 0;
        virtual string genCode(int) = 0;
};

class DeclareVariableStatement: public Statement{
    public:
      DeclareVariableStatement(string name, Type  type, Expr * expr, int line) {
            this->name =name;
            if(expr!= nullptr){
             if(type == FLOAT){
                 Type  tmp = expr->getType();
                 if(tmp ==INT){
                     this->type = INT;
                 }
                 else{
                     this->type = type;
                 }
             }
              else{
                     this->type = type;
                 }
            }else{
              this->type = type;
            }
            
            this->expr = expr;
            this->line = line ; 
        }
        string name;
        Type  type;
        Type  typeO;
        Expr * expr;
        int line;
        int tipo;
        int evaluateSemantic();
         string genCode(int);
};

class DeclareArrayVariableStatement: public Statement{
    public:
      DeclareArrayVariableStatement(string name, Type  type,list<Expr*> params, int line) {
            this->name =name;
            if(type == FLOAT){
            this->type = ARRAYNUMBER;
            } else if( type == STRING){
             this->type = ARRAYSTRING;
            } else {
              this->type = ARRAYBOOL;
            }
            this->expr = expr;
            this->line = line ; 
            this->params=params;
          
        }
        string name;
        Type  type;
        Expr * expr;
        list<Expr*> params;
        int line;
         int tipo;
        int evaluateSemantic();
        string genCode(int);
};
class DeclareMethodStatement: public Statement{
    public:
      DeclareMethodStatement(string name, list<DeclExpr*> params,  Type  type, list<Statement*> stmts, int line) {
            this->name =name;
            this->params = params;
            this->stmts = stmts;
            this->type = type;
        
            this->line = line ; 
        }
        string name;
        Type  type;
        list<DeclExpr*> params;
        list<Statement*> stmts;
        int line;
    
       int evaluateSemantic();
       string genCode(int);
};

class DeclareArrayMethodStatement:public Statement{
    public:
      DeclareArrayMethodStatement(string name, list<DeclExpr*> params,  Type  type, list<Statement*> stmts, int line) {
            this->name =name;
            this->params = params;
            this->stmts = stmts;
           if(type == FLOAT){
            this->type = ARRAYNUMBER;
            } else if( type == STRING){
             this->type = ARRAYSTRING;
            } else {
              this->type = ARRAYBOOL;
            }
        
            this->line = line ; 
        }
        string name;
        Type  type;
        list<DeclExpr*> params;
        list<Statement*> stmts;
        int line;
    
       int evaluateSemantic();
       string genCode(int);
};


class IfStatement: public Statement{
    public:
      IfStatement(Expr * expr,list<Statement*> stmts, Statement * falseSmt,  int line) {
            this->expr = expr;
            this->stmts = stmts;
            this->falseSmt = falseSmt;
            this->line = line ; 
        } 

        Expr * expr;
        list<Statement*> stmts;
        Statement * falseSmt;
        int line;
       
       int evaluateSemantic() ;
       string genCode(int);
};

class IfElseStatement :public Statement{
    public:
      IfElseStatement(Expr * expr,list<Statement*> stmts, Statement * falseSmt,  int line) {
            this->expr = expr;
            this->stmts = stmts;
            this->falseSmt = falseSmt;
            this->line = line ; 
        } 

        Expr * expr;
        list<Statement*> stmts;
        Statement * falseSmt;
        int line;
        
       int evaluateSemantic() ;
       string genCode(int);
};

class ElseStatement:public Statement{
    public:
      ElseStatement(list<Statement*> stmts,int line) {
           this->stmts = stmts;
            this->line = line ; 
        } 

        list<Statement*> stmts;
        int line;
       
        int evaluateSemantic();
        string genCode(int);
};
class ReturnStatement:public Statement{
    public:
      ReturnStatement(Expr* expr ,int line) {
           this->expr = expr;
            this->line = line ; 
        } 

        Expr* expr;
        int line;
     
        int evaluateSemantic() ;
        string genCode(int);
};

class BreakStatement:public Statement{
    public:
      BreakStatement(int line) {
     
            this->line = line ; 
        } 

        int line;
        
      int evaluateSemantic();
      string genCode(int);
};

class ContinueStatement:public Statement{
    public:
      ContinueStatement(int line) {
     
            this->line = line ; 
        } 

        int line;
      int evaluateSemantic() ;
      string genCode(int);
};

class ForStatement1:public Statement{
    public:
      ForStatement1(DeclareVariableStatement * var , Expr* exprL , Expr* exprIt , list <Statement*> stmts,  int line) {
            this-> var = var ; 
            this->exprL = exprL;
            this->exprIt = exprIt;
            this->stmts = stmts;
            this->line = line ; 
        } 
        DeclareVariableStatement * var ;
        Expr* exprL ;
         Expr* exprIt ;
          list <Statement*> stmts;
        int line;
        int evaluateSemantic();
        string genCode(int);
};

class ForStatement2:public Statement{
    public:
      ForStatement2( string name , Expr* equalityValue , Expr* exprL , Expr* exprIt , list <Statement*> stmts,  int line) {
             this->name = name;
             this->equalityValue = equalityValue;
            this->exprL = exprL;
            this->exprIt = exprIt;
            this->stmts = stmts;
            this->line = line ; 
        } 
         string name ;
         Expr* equalityValue;
         Expr* exprL ;
         Expr* exprIt ;
         list <Statement*> stmts;
         int line;
         int evaluateSemantic();
         string genCode(int);
};
class ForEachStatement:public Statement{
    public:
     ForEachStatement(string name , string id , list <Statement*> stmts,  int line) {
            this->name = name ;
             this->id = id;
            this->stmts = stmts;
            this->line = line ; 
        } 
        string name;
        string id ;
        list <Statement*> stmts;
        int line;
        int evaluateSemantic();
        string genCode(int);
};

class AssignationStatement:public Statement{
    public:
      AssignationStatement(Expr* expr ,  int line) {
          this->expr =expr;
            this->line = line ; 
        } 
        Expr * expr; 
        int line;
        int evaluateSemantic();
        string genCode(int);
};

class PrintStatement:public Statement{
    public:
      PrintStatement(list<Expr*> expr ,  int line) {
          this->expr =expr;
            this->line = line ; 
        } 
        list<Expr*> expr; 
        int line;
        int evaluateSemantic();
        string genCode(int);
};

class ReadStatement:public Statement{
    public:
      ReadStatement(Expr* expr ,  int line) {
          this->expr =expr;
            this->line = line ; 
        } 
        Expr* expr; 
        int line;
        int evaluateSemantic();
        string genCode(int);
};

class DeleteArrayStatement:public Statement{
    public:
      DeleteArrayStatement(IdExpr * expr , Expr * index , int line) {
          this->expr =expr;
          this->index = index ;
            this->line = line ; 
        } 
        IdExpr * expr ;
        Expr * index; 
        int line;
        int evaluateSemantic();
        string genCode(int);
};

class AddArrayStatement:public Statement{
    public:
      AddArrayStatement(IdExpr * expr , Expr * index, int line) {
          this->expr =expr;
          this->index = index ;
            this->line = line ; 
        } 
        IdExpr * expr ;
        Expr * index; 
        int line;
       int evaluateSemantic();
       string genCode(int);
};

class MainStatement:public Statement{
    public:
      MainStatement(list<Statement*> stmts ,  int line) {
          this->stmts =stmts;
            this->line = line ; 
        } 
        list<Statement*> stmts; 
        int line;
       int evaluateSemantic();
       string genCode(int);
};
#endif