%option noyywrap
%option yylineno
%x mcomment
%x stringLit
%x scomment
%{
 #include "tokens.h"
%}


%%
[\t \r \n] { /* do nothing */}
"import" { return TK_IMPORT; }
"Main" { return TK_MAIN; }
"func" { return TK_FUNC; }
"from" { return TK_FROM; }
"push" { return TK_PUSH; }
"delete" { return TK_DELETE; }
"console" { return TK_CONSOLE; }
"log" { return TK_LOG; }
"number" { return TK_NUM_TYPE; }
"boolean" { return TK_BOOL_TYPE; }
"string" { return TK_STRING_TYPE; }
"Array" { return TK_ARRAY_TYPE; }
"new" { return TK_NEW; }
"break" { return TK_BREAK;}
"const" { return TK_CONST; }
"do" { return TK_DO; }
"else" { return TK_ELSE; }
"false" { return TK_FALSE; }
"for" { return TK_FOR; }
"if" { return TK_IF; }
"in" { return TK_IN; }
"return" { return TK_RETURN; }
"true" { return TK_TRUE; }
"void" { return TK_VOID; }
"while" { return TK_WHILE; }
"var" { return TK_VAR; }
"of" { return TK_OF; }
"continue" { return TK_CONTINUE; }
"read" {return TK_READ;}
"+" {return '+';}
"+=" {return TK_PLUS_EQ;}
"&=" {return TK_AMP_EQ;}
"&&" {return TK_AND;}
"==" {return TK_EQ_EQ; }
"!=" {return TK_NOT_EQ;}
"(" { return '(';}
")" {return ')';}
"-" {return '-';}
"-=" {return TK_SUB_EQ;}
"|=" {return TK_OR_EQ;}
"||" {return TK_OR;}
"<" { return '<';}
"<=" { return TK_LTE ;}
"[" {return '[';}
"]" { return ']';}
"*" {return '*';}
"*=" { return TK_MULT_EQ;}
"=" { return '=';}
">" {return '>';}
">=" {return TK_GTE;}
"^" {return '^';}
"^=" {return TK_XOR_EQ;}
"{" { return '{';}
"}" {return '}';}
"//" {BEGIN(scomment);}
"/" { return '/';}
"/=" {return TK_DIV_EQ;}
"++" {return TK_PLUS_PLUS;}
":=" {return TK_DOTDOT_EQ;}
"," {return ',';}
";" {return ';';}
"%" { return '%';}
"%=" { return TK_MOD_EQ;}
"--" { return TK_SUB_SUB;}
"!" {return '!';}
":" { return ':';}
"." { return '.';}
"=>" { return TK_ARROW;}
"/*" {BEGIN(mcomment);}
"\"" {BEGIN(stringLit); yylval.string_t = strdup(yytext); return TK_STRING_LIT;}
[0-9]+ {yylval.int_t = atoi(yytext); return TK_INT_LIT;}
[0-9]"."[0-9]+ { yylval.float_t = atof(yytext); return TK_FLOAT_LIT;}
[a-zA-Z][a-zA-Z0-9]* { yylval.string_t = strdup(yytext);  return TK_ID;}
. {printf("Invalid character %c, line %d\n", yytext[0], yylineno); return TK_ERROR;}

<mcomment>"*/" {BEGIN(INITIAL);}
<mcomment>. {}
<mcomment>\n { } 
<mcomment><<EOF>> {printf("incomplete comment, line : %d\n", yylineno); yyterminate();} 
<stringLit>"\"" {BEGIN(INITIAL);}
<stringLit>[\n] { printf("string cant have new line, line: %d\n", yylineno); }
<stringLit>[^\n] {/*IGNORE*/}
<stringLit><<EOF>> {printf("incomplete string, line : %d\n", yylineno); yyterminate(); }
<scomment>[\n] {BEGIN(INITIAL);}
<scomment>[^\n] {}
%%