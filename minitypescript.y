%code requires{
    #include "ast.h"
}

%{
    #include <cstdio>
    #include "asm.h"
    #define EQUAL 1
    #define PLUSEQUAL 2
    #define SUBEQUAL 3
    #define MULTEQUAL 4
    #define MODEQUAL 5
    #define DIVEQUAL 6

    using namespace std;
    Asm assemblyFile;
    int yylex();
    extern int yylineno;
    void yyerror(const char * s){
       fprintf(stderr, "Line %d, error: %s\n", yylineno, s);
    }
    void writeFile(string name){
        ofstream file;
        file.open(name);
        file << assemblyResultFile.data <<endl
        << assemblyResultFile.global<<endl
        << assemblyResultFile.text<< endl;
        file.close();
    }
%}
%union{
    const char* string_t;
    int int_t;
    float float_t;
    bool  bool_t;
    ExprList * expr_list;
    StmtList * stmt_list;
    StmtList2 * stmt_list2;
    DeclList * declList;
    Expr * expr_t;
    Statement * stmt_t;
}

%token TK_NUM_TYPE TK_BOOL_TYPE TK_STRING_TYPE TK_ARRAY_TYPE TK_ERROR TK_VAR TK_NEW TK_READ
%token  TK_BREAK TK_CONST TK_DO TK_ELSE TK_FOR TK_IF TK_IN TK_VOID  TK_RETURN  TK_WHILE TK_OF TK_CONTINUE TK_CONSOLE TK_LOG TK_PUSH TK_DELETE TK_FUNC TK_MAIN TK_IMPORT TK_FROM 
%token <bool_t> TK_FALSE TK_TRUE 
%token <int_t> TK_INT_LIT 
%token <float_t> TK_FLOAT_LIT
%token <string_t>  TK_ID TK_STRING_LIT
%token TK_PLUS_EQ TK_AMP_EQ TK_AND TK_EQ_EQ TK_NOT_EQ TK_SUB_EQ TK_OR_EQ TK_OR TK_LTE TK_MULT_EQ TK_GTE TK_XOR_EQ TK_DIV_EQ TK_PLUS_PLUS TK_DOTDOT_EQ TK_MOD_EQ TK_SUB_SUB TK_ARROW 
%type <expr_t> primary_expression unary_expression postfix_expression logical_or_expression logical_and_expression equalityExpression relational_expression additive_expression multiplicative_expression assignment_expression
%type <expr_list> params2 paramsList2
%type <declList> params paramsList 
%type <int_t> assignment_operator type
%type <stmt_t> DeclareVariableStmt DeclareVariableStmt2 MainFunc BreakStmt ContinueStmt ReturnStmt DeclareMethodStmt IfStmt IfElseStmt ElseStmt ForStmt AssignationStmt PrintStmt DeleteArrayStmt AddArrayStmt Statement
%type <stmt_t> LeerStmt
%type <stmt_list> StatementList
%%
Program : IncludeBlock StatementList MainFunc{ 
    assemblyResultFile.global = ".globl main\n";
    assemblyResultFile.data = ".data \n";
    assemblyResultFile.text = ".text\n";
    list<Statement *>::iterator stmtIt = $1->begin();
    string code = "";
    while(stmtIt != $1->end()){
        (*stmtIt)->evaluateSemantic();
        code += (*stmtIt)->genCode(0);
        stmtIt++;
    }
    assemblyResultFile.text += code;
    writeFile("result.asm");
};

StatementList : Statement StatementList {$$ = $2 ; $$->push_front($1);}
                                      |{$$ = new StmtList;} ;

IncludeBlock : IncludeStmt IncludeBlock |;

IncludeStmt : TK_IMPORT '{' TK_ID '}' TK_FROM TK_STRING_LIT ';'

Statement : DeclareVariableStmt {$$ = $1;}| 
DeclareMethodStmt {$$ = $1;}| 
IfStmt {$$ = $1;}| 
ReturnStmt {$$ = $1;}| 
BreakStmt {$$ = $1;}| 
ContinueStmt {$$ = $1;}|
ForStmt {$$ = $1;}|
AssignationStmt {$$ = $1;}|
PrintStmt {$$ = $1;}|
DeleteArrayStmt {$$ = $1;} | 
AddArrayStmt  {$$ = $1;} |
LeerStmt {$$ = $1;};
//DeclareArrayVariableStatement(string name, Type  type,list<Expr*> params, int line) {
DeclareVariableStmt : TK_VAR TK_ID ':' type '=' logical_or_expression ';' {
     $$ = new DeclareVariableStatement($2, (Type)$4, $6, yylineno);
   } |
 TK_VAR TK_ID ':' type '['']' '=' TK_NEW TK_ARRAY_TYPE '(' params2 ')' ';'
 {  
    $$ = new  DeclareArrayVariableStatement($2,(Type)$4, *($11), yylineno);
 }
  |
TK_VAR TK_ID ':' type ';'
 {  
    $$ = new  DeclareVariableStatement($2,(Type)$4,nullptr, yylineno);
 } ;

DeclareVariableStmt2 : TK_VAR TK_ID ':' type '=' logical_or_expression ';' {
     $$ = new DeclareVariableStatement($2, (Type)$4, $6, yylineno);
   } ;

DeclareMethodStmt : TK_CONST TK_ID '=' '(' params ')' ':' type  TK_ARROW '{' StatementList '}' ';' {$$ = new DeclareMethodStatement($2,*($5),(Type)$8, *($11),yylineno);}|
TK_CONST TK_ID '=' '(' params ')' ':' TK_VOID TK_ARROW '{' StatementList '}' ';' {$$ = new DeclareMethodStatement($2,*($5),(Type)VOID, *($11),yylineno);}| 
TK_CONST TK_ID '=' '(' ')' ':' type  TK_ARROW '{' StatementList '}' ';' { $$ = new DeclareMethodStatement($2,*(new DeclList),(Type)$7, *($10),yylineno); } |
TK_CONST TK_ID '=' '(' ')' ':' type '['']' TK_ARROW '{' StatementList '}' ';' {$$ = new DeclareArrayMethodStatement($2, *(new DeclList) ,(Type)$7, *($12),yylineno);} |
TK_CONST TK_ID '=' '('params')' ':' type '['']' TK_ARROW '{' StatementList '}' ';' {$$ = new DeclareArrayMethodStatement($2,*($5),(Type)$8, *($13),yylineno);} |
TK_CONST TK_ID '=' '(' ')' ':' TK_VOID  TK_ARROW '{' StatementList '}' ';'  {$$ = new DeclareMethodStatement($2, *(new DeclList), (Type)VOID, *($10),yylineno);} ; 

IfStmt : TK_IF '(' logical_or_expression')' '{' StatementList '}' IfElseStmt {$$ = new IfStatement($3,*($6), $8, yylineno);};

IfElseStmt : TK_ELSE TK_IF '(' logical_or_expression ')' '{' StatementList '}' IfElseStmt { $$ = new IfElseStatement($4,*($7), $9, yylineno); }| ElseStmt
ElseStmt : TK_ELSE '{' StatementList '}'{$$ = new ElseStatement(*($3),yylineno);} | {$$= nullptr;};

ReturnStmt : TK_RETURN logical_or_expression ';' {$$ = new ReturnStatement($2, yylineno);} ;

BreakStmt : TK_BREAK ';' {$$ = new BreakStatement(yylineno);} ;

ContinueStmt : TK_CONTINUE ';' {$$= new ContinueStatement(yylineno);} ;

ForStmt : TK_FOR '(' DeclareVariableStmt2 logical_or_expression ';' assignment_expression  ')' '{'StatementList'}' {$$ = new ForStatement1((DeclareVariableStatement*)$3, $4, $6, *($9), yylineno);} |
  TK_FOR '(' TK_ID '=' logical_or_expression';' logical_or_expression ';' assignment_expression ')' '{'StatementList'}'{$$ = new ForStatement2($3,$5, $7, $9, *($12), yylineno);} |
  TK_FOR '(' TK_VAR TK_ID TK_IN TK_ID ')' '{'StatementList'}' {$$ = new ForEachStatement($4, $6, *($9), yylineno); } ;

AssignationStmt: assignment_expression ';'  {$$ = new AssignationStatement($1, yylineno);}  ;

PrintStmt : TK_CONSOLE '.' TK_LOG '(' params2 ')' ';' {$$ = new PrintStatement(*($5), yylineno);} |
 TK_CONSOLE '.' TK_LOG '('')' ';' {$$ = new PrintStatement(*(new ExprList), yylineno);} ;



DeleteArrayStmt : TK_DELETE TK_ID '['logical_or_expression']'';' {$$ = new DeleteArrayStatement(new IdExpr($2,yylineno,1),$4,yylineno);} ;

// ReadStatement(Expr* expr ,  int line) {
LeerStmt : TK_CONSOLE '.' TK_READ '(' logical_or_expression ')' ';' {$$ = new ReadStatement($5, yylineno);};

AddArrayStmt : TK_ID '.' TK_PUSH '('logical_or_expression ')' ';'{$$ = new AddArrayStatement(new IdExpr($1, yylineno, 1), $5, yylineno);};

logical_or_expression: logical_or_expression TK_OR logical_and_expression {$$ = new LogicalOrExpr($1,$3, yylineno,0);}
                    | logical_and_expression {$$=$1;}
                    ;

logical_and_expression: logical_and_expression TK_AND equalityExpression {$$ = new LogicalAndExpr($1, $3, yylineno,0);}
                      | equalityExpression  { $$ =$1;}
                      ;

equalityExpression: equalityExpression TK_EQ_EQ relational_expression {$$ = new EqEqExpr($1, $3, yylineno,0);} 
                   | equalityExpression TK_NOT_EQ relational_expression  {$$ = new NotEqExpr($1, $3, yylineno,0);} 
                   | relational_expression {$$ = $1;}
                   ;

relational_expression: relational_expression '>' additive_expression {$$ = new GreaterExpr($1, $3, yylineno,0);}
                     | relational_expression '<' additive_expression {$$ = new LesserExpr($1, $3, yylineno,0);}
                     | relational_expression TK_GTE additive_expression {$$ = new GreaterEqExpr($1, $3, yylineno,0);}
                     | relational_expression TK_LTE additive_expression {$$ = new LessEqExpr($1, $3, yylineno,0);}
                     | additive_expression 
                     ;
                
additive_expression: additive_expression '+' multiplicative_expression {$$ = new AddExpr($1, $3, yylineno,0);}
                   | additive_expression '-' multiplicative_expression {$$ = new SubExpr($1, $3, yylineno,0);}
                   | multiplicative_expression {$$ =$1;}
                   ;

multiplicative_expression: multiplicative_expression '*' unary_expression {$$ = new MultExpr($1,$3, yylineno,0);}
                         | multiplicative_expression '/' unary_expression {$$ = new DivExpr($1,$3, yylineno,0);}
                         |multiplicative_expression '%' unary_expression {$$ = new ModExpr($1,$3, yylineno,0);}
                         | unary_expression {$$ = $1;}
                         ;

assignment_expression: unary_expression assignment_operator logical_or_expression  {
                         if($2 == EQUAL){
                            
                             $$ = new EqualExpr($1, $3, yylineno,0);
                          } else if ($2 == PLUSEQUAL){
                             $$ = new PlusEqExpr($1, $3, yylineno,0);
                         }else if ($2 == SUBEQUAL){
                             $$ = new SubEqExpr($1, $3, yylineno,0);
                         } else if ($2 == MULTEQUAL){
                             $$ = new MultEqExpr($1, $3, yylineno,0);
                         } else if ($2 == DIVEQUAL){
                             $$ = new DivEqExpr($1, $3, yylineno,0);
                         } else if ($2 == MODEQUAL){
                             $$ = new ModEqExpr($1, $3, yylineno,0);
                         }

                       }
                      | logical_or_expression {$$ =$1;}
                     ;


assignment_operator: '=' {$$ = EQUAL;}
                  | TK_PLUS_EQ {$$ = PLUSEQUAL;}
                  | TK_SUB_EQ {$$ = SUBEQUAL;}
                  | TK_MULT_EQ  {$$ = MULTEQUAL;}
                  | TK_DIV_EQ  {$$ = DIVEQUAL;}
                  | TK_MOD_EQ {$$ = MODEQUAL;}
                  ;

unary_expression: '!' unary_expression { $$ = new NegationExpr($2, yylineno,0);}
                | postfix_expression {$$ =$1;}
                ;

postfix_expression: postfix_expression '[' logical_or_expression ']' {$$ = new ArrayAccessExpr((IdExpr*)$1,$3, yylineno,2);}
                  | postfix_expression '(' ')' {$$= new MethodAccessExpr((IdExpr*)$1, *(new ExprList), yylineno, 0);}
                  | postfix_expression '(' params2 ')' {$$= new MethodAccessExpr((IdExpr*)$1, *($3), yylineno,0);}
                  |primary_expression {$$ = $1;}
                 
                  ;
primary_expression: '(' logical_or_expression ')'{$$= $2;}
                  | '[' params2 ']' { $$ = new ArrayExpr(*($2) , yylineno,3);}
                  | '['']' { $$ = new ArrayExpr(*(new ExprList) , yylineno,0);}
                  | TK_ID TK_PLUS_PLUS {$$ = new PlusPlusExpr(new IdExpr($1, yylineno,1), yylineno,0); }
                  | TK_ID TK_SUB_SUB {$$ = new SubSubExpr(new IdExpr($1, yylineno,1), yylineno,0); }
                  | TK_ID {$$ = new IdExpr($1 , yylineno, 1);}
                  | TK_STRING_LIT  {$$ =  new StringExpr($1, yylineno, 0);}
                  | TK_FALSE  {$$ =  new BoolExpr($1, yylineno,0);}
                  | TK_TRUE   {$$ =  new BoolExpr($1, yylineno,0);}
                  | TK_FLOAT_LIT {$$ =  new FloatExpr($1, yylineno,0);}
                  | TK_INT_LIT {$$ =  new IntExpr($1, yylineno , 0);};

type : TK_NUM_TYPE {$$ = FLOAT;} | TK_BOOL_TYPE {$$ = BOOL;}| TK_STRING_TYPE {$$ = STRING;} ;
//DeclExpr(string name , Type  type ,int tipo, Expr * index,int line): Expr(line, tipo){
params : TK_ID ':' type  paramsList {$$ = $4 ; $$->push_front(new DeclExpr($1 , (Type)$3,1,0, yylineno));} | TK_ID ':' type '['TK_INT_LIT']' paramsList 
{$$ = $7 ;
if($3 == FLOAT){
 $$->push_front(new DeclExpr($1 , (Type)ARRAYNUMBER,2,$5,yylineno));
} else if($3 == STRING){
 $$->push_front(new DeclExpr($1 , (Type)ARRAYSTRING,2,$5,yylineno));
} else{
 $$->push_front(new DeclExpr($1 , (Type)ARRAYBOOL,2,$5,yylineno));
}
} ;

paramsList : ',' TK_ID ':' type  paramsList {$$ = $5 ; $$->push_front(new DeclExpr($2 , (Type)$4,1,0,yylineno));} | 
',' TK_ID ':' type '['TK_INT_LIT']' paramsList {
 $$ = $8 ;
if($4 == FLOAT){
 $$->push_front(new DeclExpr($2 , (Type)ARRAYNUMBER,2,$6,yylineno));
} else if($4 == STRING){
 $$->push_front(new DeclExpr($2 , (Type)ARRAYSTRING,2,$6,yylineno));
} else{
 $$->push_front(new DeclExpr($2 , (Type)ARRAYBOOL,2,$6,yylineno));
}

} | {$$ = new DeclList ;}

;
params2 : logical_or_expression  paramsList2 {$$= $2; $$->push_front($1);};
paramsList2 :',' logical_or_expression   paramsList2   {$$= $3; $$->push_front($2);}| { $$ = new ExprList;};

MainFunc : TK_FUNC TK_MAIN '('')''{' StatementList '}' {$$ = new   MainStatement(*($6) , yylineno);}
%%
