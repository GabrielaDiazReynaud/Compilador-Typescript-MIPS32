/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_TOKENS_H_INCLUDED
# define YY_YY_TOKENS_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "minitypescript.y" /* yacc.c:1909  */

    #include "ast.h"

#line 48 "tokens.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_NUM_TYPE = 258,
    TK_BOOL_TYPE = 259,
    TK_STRING_TYPE = 260,
    TK_ARRAY_TYPE = 261,
    TK_ERROR = 262,
    TK_VAR = 263,
    TK_NEW = 264,
    TK_READ = 265,
    TK_BREAK = 266,
    TK_CONST = 267,
    TK_DO = 268,
    TK_ELSE = 269,
    TK_FOR = 270,
    TK_IF = 271,
    TK_IN = 272,
    TK_VOID = 273,
    TK_RETURN = 274,
    TK_WHILE = 275,
    TK_OF = 276,
    TK_CONTINUE = 277,
    TK_CONSOLE = 278,
    TK_LOG = 279,
    TK_PUSH = 280,
    TK_DELETE = 281,
    TK_FUNC = 282,
    TK_MAIN = 283,
    TK_IMPORT = 284,
    TK_FROM = 285,
    TK_FALSE = 286,
    TK_TRUE = 287,
    TK_INT_LIT = 288,
    TK_FLOAT_LIT = 289,
    TK_ID = 290,
    TK_STRING_LIT = 291,
    TK_PLUS_EQ = 292,
    TK_AMP_EQ = 293,
    TK_AND = 294,
    TK_EQ_EQ = 295,
    TK_NOT_EQ = 296,
    TK_SUB_EQ = 297,
    TK_OR_EQ = 298,
    TK_OR = 299,
    TK_LTE = 300,
    TK_MULT_EQ = 301,
    TK_GTE = 302,
    TK_XOR_EQ = 303,
    TK_DIV_EQ = 304,
    TK_PLUS_PLUS = 305,
    TK_DOTDOT_EQ = 306,
    TK_MOD_EQ = 307,
    TK_SUB_SUB = 308,
    TK_ARROW = 309
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "minitypescript.y" /* yacc.c:1909  */

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

#line 128 "tokens.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKENS_H_INCLUDED  */
