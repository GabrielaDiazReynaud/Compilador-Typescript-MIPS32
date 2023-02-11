/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 5 "minitypescript.y" /* yacc.c:339  */

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

#line 85 "minitypescript_parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "tokens.h".  */
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
#line 1 "minitypescript.y" /* yacc.c:355  */

    #include "ast.h"

#line 119 "minitypescript_parser.cpp" /* yacc.c:355  */

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
#line 23 "minitypescript.y" /* yacc.c:355  */

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

#line 199 "minitypescript_parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_TOKENS_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 216 "minitypescript_parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   342

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  74
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  284

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    72,     2,     2,     2,    71,     2,     2,
      62,    63,    69,    67,    73,    68,    64,    70,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    57,
      66,    59,    65,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    60,     2,    61,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    55,     2,    56,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    51,    51,    60,    61,    63,    63,    65,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      80,    83,    88,    93,    97,    98,    99,   100,   101,   102,
     104,   106,   106,   107,   107,   109,   111,   113,   115,   116,
     117,   119,   121,   122,   126,   129,   131,   133,   134,   137,
     138,   141,   142,   143,   146,   147,   148,   149,   150,   153,
     154,   155,   158,   159,   160,   161,   164,   181,   185,   186,
     187,   188,   189,   190,   193,   194,   197,   198,   199,   200,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   215,   215,   215,   217,   217,   228,   229,   239,   242,
     243,   243,   245
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_NUM_TYPE", "TK_BOOL_TYPE",
  "TK_STRING_TYPE", "TK_ARRAY_TYPE", "TK_ERROR", "TK_VAR", "TK_NEW",
  "TK_READ", "TK_BREAK", "TK_CONST", "TK_DO", "TK_ELSE", "TK_FOR", "TK_IF",
  "TK_IN", "TK_VOID", "TK_RETURN", "TK_WHILE", "TK_OF", "TK_CONTINUE",
  "TK_CONSOLE", "TK_LOG", "TK_PUSH", "TK_DELETE", "TK_FUNC", "TK_MAIN",
  "TK_IMPORT", "TK_FROM", "TK_FALSE", "TK_TRUE", "TK_INT_LIT",
  "TK_FLOAT_LIT", "TK_ID", "TK_STRING_LIT", "TK_PLUS_EQ", "TK_AMP_EQ",
  "TK_AND", "TK_EQ_EQ", "TK_NOT_EQ", "TK_SUB_EQ", "TK_OR_EQ", "TK_OR",
  "TK_LTE", "TK_MULT_EQ", "TK_GTE", "TK_XOR_EQ", "TK_DIV_EQ",
  "TK_PLUS_PLUS", "TK_DOTDOT_EQ", "TK_MOD_EQ", "TK_SUB_SUB", "TK_ARROW",
  "'{'", "'}'", "';'", "':'", "'='", "'['", "']'", "'('", "')'", "'.'",
  "'>'", "'<'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "','", "$accept",
  "Program", "StatementList", "IncludeBlock", "IncludeStmt", "Statement",
  "DeclareVariableStmt", "DeclareVariableStmt2", "DeclareMethodStmt",
  "IfStmt", "IfElseStmt", "ElseStmt", "ReturnStmt", "BreakStmt",
  "ContinueStmt", "ForStmt", "AssignationStmt", "PrintStmt",
  "DeleteArrayStmt", "LeerStmt", "AddArrayStmt", "logical_or_expression",
  "logical_and_expression", "equalityExpression", "relational_expression",
  "additive_expression", "multiplicative_expression",
  "assignment_expression", "assignment_operator", "unary_expression",
  "postfix_expression", "primary_expression", "type", "params",
  "paramsList", "params2", "paramsList2", "MainFunc", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   123,   125,    59,    58,    61,
      91,    93,    40,    41,    46,    62,    60,    43,    45,    42,
      47,    37,    33,    44
};
# endif

#define YYPACT_NINF -226

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-226)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,   -45,    30,    38,    23,    28,  -226,    33,    47,    50,
      35,    67,   138,    75,    45,   100,  -226,  -226,  -226,  -226,
      43,  -226,     5,   138,   138,   123,    38,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,   117,
     125,   -21,   -34,   144,   169,   119,   140,    98,  -226,  -226,
     111,   127,  -226,   120,     0,   138,    58,    95,  -226,  -226,
       4,   130,  -226,  -226,   156,  -226,   -40,   126,   -19,  -226,
     165,  -226,  -226,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,   138,   138,    85,   167,   238,   142,   160,
     147,   138,    15,  -226,   161,   163,   138,   164,   138,  -226,
    -226,  -226,   170,   125,   -21,   -34,   -34,   144,   144,   144,
     144,   169,   169,  -226,  -226,  -226,   117,    14,  -226,   146,
     186,  -226,  -226,  -226,    81,   -29,   -15,   138,   102,   189,
     138,    91,    18,   138,   -40,   182,  -226,  -226,   192,  -226,
     138,   185,   194,   195,   187,   166,   238,   105,   138,    38,
      32,   197,   193,   198,    39,  -226,   202,  -226,   121,   200,
     238,    87,   203,   201,   204,   138,   205,   209,   210,  -226,
     212,  -226,   213,    38,  -226,   251,   -31,   217,   -36,   110,
     211,   138,   131,   218,   260,  -226,  -226,  -226,   219,   270,
     244,   243,  -226,   224,   225,   220,   228,    52,    38,   139,
     138,    38,     1,  -226,  -226,  -226,   221,   223,   227,    38,
      38,   232,   233,   234,   226,   235,  -226,   229,   237,   236,
      38,   138,   222,   238,   240,   241,   239,    38,    38,   245,
    -226,   246,  -226,   138,   247,   242,  -226,    71,   249,   250,
      38,   248,   252,   254,    38,    40,  -226,   253,   257,  -226,
    -226,  -226,   255,   256,   258,    38,   261,   259,  -226,   262,
     263,  -226,  -226,   265,  -226,    38,   222,  -226,   267,   266,
    -226,  -226,   260,  -226
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       6,     0,     0,     4,     6,     0,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    87,    88,    90,    89,
      85,    86,     0,     0,     0,     0,     4,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    19,    18,    67,
      48,    50,    53,    58,    61,     0,    65,    75,    79,     5,
       0,     0,    36,     0,     0,     0,    85,     0,    65,    37,
       0,     0,    83,    84,     0,    82,   101,     0,     0,    74,
       0,     2,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    69,    70,    71,
      72,    73,    68,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    35,     0,     0,     0,     0,     0,    99,
      81,    80,     0,    47,    49,    51,    52,    57,    56,    54,
      55,    59,    60,    62,    63,    64,    66,     0,    77,     0,
       0,    91,    92,    93,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,     0,    76,    78,     0,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       0,     0,     0,     0,     0,   100,     0,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
       0,    44,     0,     4,    20,     0,    98,     0,     0,     0,
       0,     0,     0,     0,    34,    45,    42,    46,     0,     0,
       0,     0,    94,     0,     0,     0,     0,     0,     4,     0,
       0,     4,     0,    30,    32,   102,     0,     0,     0,     4,
       4,     0,     0,     0,     0,     0,    23,     0,     0,     0,
       4,     0,    98,     0,     0,     0,     0,     4,     4,     0,
      40,     0,    38,     0,     0,     0,    95,    98,     0,     0,
       4,     0,     0,     0,     4,     0,    33,     0,     0,    96,
      29,    26,     0,     0,     0,     4,     0,     0,    21,     0,
       0,    25,    24,     0,    39,     4,    98,    27,     0,     0,
      97,    28,    34,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -226,  -226,   -17,   296,  -226,  -226,  -226,  -226,  -226,  -226,
      20,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,    -7,   264,   268,   143,   151,   133,  -155,  -226,    -3,
    -226,  -226,  -144,  -226,  -225,   -94,   168,  -226
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    25,     3,     4,    26,    27,   101,    28,    29,
     213,   214,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    93,    58,
      47,    48,   134,   154,   202,    67,   109,    71
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      46,   129,   155,   176,    73,    57,   152,   246,    99,    72,
       5,    77,   174,    78,   104,    66,    68,   229,   204,    75,
      76,    69,   259,    46,   205,    73,   186,   188,   105,   200,
       6,    79,    80,   108,   153,   100,    16,    17,    18,    19,
      56,    21,   201,   156,   111,   207,     7,   162,   102,     8,
       9,   280,     1,    10,    11,   227,   230,    12,    73,    73,
      13,    14,    73,    50,    15,    22,    65,    23,    51,    16,
      17,    18,    19,    20,    21,   146,    73,    24,   139,   163,
     123,   124,   125,    73,    73,    53,   126,   127,    66,   247,
     131,   132,   133,    62,   138,   178,    63,    54,    22,   142,
      23,   144,   182,   267,    52,   187,   223,    64,    62,    60,
      24,    63,   224,   131,   132,   133,    16,    17,    18,    19,
      56,    21,    16,    17,    18,    19,    56,    21,   206,    55,
     157,   258,    59,   160,    66,    61,   164,   245,   149,    73,
     150,   151,   177,   168,   201,    22,    73,    23,   128,    73,
      70,    22,   103,    23,   161,    46,    46,    24,    94,   158,
      95,    73,   175,    24,    74,    73,   198,    96,   192,    16,
      17,    18,    19,    56,    21,    73,    86,    87,   184,    98,
      46,   107,    88,    73,   209,    97,    89,   110,   210,    90,
     106,   225,    91,   112,   228,   136,   226,   130,    22,    92,
      23,   173,   234,   235,   135,    46,   137,    46,    46,   147,
      24,    81,    82,   244,   121,   122,    46,    46,   115,   116,
     251,   252,   148,   140,    66,   141,   143,    46,   117,   118,
     119,   120,   145,   262,    46,    46,   255,   266,    83,    84,
      85,   131,   132,   133,   159,   166,   169,    46,   273,   167,
     172,    46,   170,   171,   179,   181,   180,   183,   279,   185,
     199,   189,    46,   191,   190,   194,   208,   195,   193,   196,
     197,   203,    46,   211,   212,   215,   216,   217,   218,   219,
     220,   221,   222,   231,   232,   233,   236,   239,   237,   238,
     269,   240,   241,   242,   250,   201,   248,   249,   243,   253,
      49,   254,   283,   256,   263,   257,   260,   261,   264,   265,
     268,   270,   165,   271,   275,   272,     0,   274,     0,     0,
     277,   278,   282,   276,   281,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,     0,     0,
       0,     0,   114
};

static const yytype_int16 yycheck[] =
{
       3,    95,    17,   158,    44,    12,    35,   232,     8,    26,
      55,    45,   156,    47,    10,    22,    23,    16,    54,    40,
      41,    24,   247,    26,    60,    44,   170,   171,    24,    60,
       0,    65,    66,    73,    63,    35,    31,    32,    33,    34,
      35,    36,    73,    58,    63,   189,     8,   141,    55,    11,
      12,   276,    29,    15,    16,   210,    55,    19,    44,    44,
      22,    23,    44,    35,    26,    60,    61,    62,    35,    31,
      32,    33,    34,    35,    36,    61,    44,    72,    63,    61,
      83,    84,    85,    44,    44,    35,    93,    94,    95,   233,
       3,     4,     5,    50,   101,    63,    53,    62,    60,   106,
      62,   108,    63,    63,    57,    18,    54,    64,    50,    64,
      72,    53,    60,     3,     4,     5,    31,    32,    33,    34,
      35,    36,    31,    32,    33,    34,    35,    36,    18,    62,
     137,    60,    57,   140,   141,    35,   143,   231,    57,    44,
      59,    60,   159,   150,    73,    60,    44,    62,    63,    44,
      27,    60,    57,    62,    63,   158,   159,    72,    60,    57,
      62,    44,    57,    72,    39,    44,   183,    56,   175,    31,
      32,    33,    34,    35,    36,    44,    57,    37,    57,    59,
     183,    25,    42,    44,   191,    58,    46,    61,    57,    49,
      60,   208,    52,    28,   211,    35,    57,    30,    60,    59,
      62,    35,   219,   220,    62,   208,    59,   210,   211,    63,
      72,    67,    68,   230,    81,    82,   219,   220,    75,    76,
     237,   238,    36,    62,   231,    62,    62,   230,    77,    78,
      79,    80,    62,   250,   237,   238,   243,   254,    69,    70,
      71,     3,     4,     5,    55,    63,    61,   250,   265,    57,
      63,   254,    58,    58,    57,    57,    63,    55,   275,    59,
       9,    58,   265,    59,    63,    56,    55,    57,    63,    57,
      57,    54,   275,    55,    14,    56,     6,    33,    35,    55,
      55,    61,    54,    62,    61,    58,    54,    61,    55,    55,
      33,    56,    63,    56,    55,    73,    56,    56,    62,    54,
       4,    55,   282,    56,    56,    63,    57,    57,    56,    55,
      57,    56,   144,    57,    55,    57,    -1,    56,    -1,    -1,
      57,    56,    56,    61,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,    -1,
      -1,    -1,    74
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    29,    75,    77,    78,    55,     0,     8,    11,    12,
      15,    16,    19,    22,    23,    26,    31,    32,    33,    34,
      35,    36,    60,    62,    72,    76,    79,    80,    82,    83,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   103,   104,   105,    77,
      35,    35,    57,    35,    62,    62,    35,    95,   103,    57,
      64,    35,    50,    53,    64,    61,    95,   109,    95,   103,
      27,   111,    76,    44,    39,    40,    41,    45,    47,    65,
      66,    67,    68,    69,    70,    71,    57,    37,    42,    46,
      49,    52,    59,   102,    60,    62,    56,    58,    59,     8,
      35,    81,    95,    57,    10,    24,    60,    25,    73,   110,
      61,    63,    28,    96,    97,    98,    98,    99,    99,    99,
      99,   100,   100,   103,   103,   103,    95,    95,    63,   109,
      30,     3,     4,     5,   106,    62,    35,    59,    95,    63,
      62,    62,    95,    62,    95,    62,    61,    63,    36,    57,
      59,    60,    35,    63,   107,    17,    58,    95,    57,    55,
      95,    63,   109,    61,    95,   110,    63,    57,    95,    61,
      58,    58,    63,    35,   106,    57,   101,    76,    63,    57,
      63,    57,    63,    55,    57,    59,   106,    18,   106,    58,
      63,    59,    95,    63,    56,    57,    57,    57,    76,     9,
      60,    73,   108,    54,    54,    60,    18,   106,    55,    95,
      57,    55,    14,    84,    85,    56,     6,    33,    35,    55,
      55,    61,    54,    54,    60,    76,    57,   101,    76,    16,
      55,    62,    61,    58,    76,    76,    54,    55,    55,    61,
      56,    63,    56,    62,    76,   109,   108,   106,    56,    56,
      55,    76,    76,    54,    55,    95,    56,    63,    60,   108,
      57,    57,    76,    56,    56,    55,    76,    63,    57,    33,
      56,    57,    57,    76,    56,    55,    61,    57,    56,    76,
     108,    57,    56,    84
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    74,    75,    76,    76,    77,    77,    78,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      80,    80,    80,    81,    82,    82,    82,    82,    82,    82,
      83,    84,    84,    85,    85,    86,    87,    88,    89,    89,
      89,    90,    91,    91,    92,    93,    94,    95,    95,    96,
      96,    97,    97,    97,    98,    98,    98,    98,    98,    99,
      99,    99,   100,   100,   100,   100,   101,   101,   102,   102,
     102,   102,   102,   102,   103,   103,   104,   104,   104,   104,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   106,   106,   106,   107,   107,   108,   108,   108,   109,
     110,   110,   111
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     0,     2,     0,     7,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       7,    13,     5,     7,    13,    13,    12,    14,    15,    12,
       8,     9,     1,     4,     0,     3,     2,     2,    10,    13,
      10,     2,     7,     6,     6,     7,     7,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     4,     3,     4,     1,
       3,     3,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     7,     5,     8,     0,     2,
       3,     0,     7
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 51 "minitypescript.y" /* yacc.c:1646  */
    { 
    list<Statement *>::iterator stmtIt = (yyvsp[-1].stmt_list)->begin();
    while(stmtIt != (yyvsp[-1].stmt_list)->end()){
        (*stmtIt)->evaluateSemantic();
        stmtIt++;
    }
    (yyvsp[0].stmt_t)->evaluateSemantic();
}
#line 1508 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 60 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_list) = (yyvsp[0].stmt_list) ; (yyval.stmt_list)->push_front((yyvsp[-1].stmt_t));}
#line 1514 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 61 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_list) = new StmtList;}
#line 1520 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 67 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1526 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 68 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1532 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 69 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1538 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 70 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1544 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 71 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1550 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 72 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1556 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 73 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1562 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 74 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1568 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 75 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1574 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 76 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1580 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 77 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1586 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 78 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = (yyvsp[0].stmt_t);}
#line 1592 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 80 "minitypescript.y" /* yacc.c:1646  */
    {
     (yyval.stmt_t) = new DeclareVariableStatement((yyvsp[-5].string_t), (Type)(yyvsp[-3].int_t), (yyvsp[-1].expr_t), yylineno);
   }
#line 1600 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 84 "minitypescript.y" /* yacc.c:1646  */
    {  
    (yyval.stmt_t) = new  DeclareArrayVariableStatement((yyvsp[-11].string_t),(Type)(yyvsp[-9].int_t), *((yyvsp[-2].expr_list)), yylineno);
 }
#line 1608 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 89 "minitypescript.y" /* yacc.c:1646  */
    {  
    (yyval.stmt_t) = new  DeclareVariableStatement((yyvsp[-3].string_t),(Type)(yyvsp[-1].int_t),nullptr, yylineno);
 }
#line 1616 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 93 "minitypescript.y" /* yacc.c:1646  */
    {
     (yyval.stmt_t) = new DeclareVariableStatement((yyvsp[-5].string_t), (Type)(yyvsp[-3].int_t), (yyvsp[-1].expr_t), yylineno);
   }
#line 1624 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 97 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new DeclareMethodStatement((yyvsp[-11].string_t),*((yyvsp[-8].declList)),(Type)(yyvsp[-5].int_t), *((yyvsp[-2].stmt_list)),yylineno);}
#line 1630 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 98 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new DeclareMethodStatement((yyvsp[-11].string_t),*((yyvsp[-8].declList)),(Type)VOID, *((yyvsp[-2].stmt_list)),yylineno);}
#line 1636 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 99 "minitypescript.y" /* yacc.c:1646  */
    { (yyval.stmt_t) = new DeclareMethodStatement((yyvsp[-10].string_t),*(new DeclList),(Type)(yyvsp[-5].int_t), *((yyvsp[-2].stmt_list)),yylineno); }
#line 1642 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 100 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new DeclareArrayMethodStatement((yyvsp[-12].string_t), *(new DeclList) ,(Type)(yyvsp[-7].int_t), *((yyvsp[-2].stmt_list)),yylineno);}
#line 1648 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 101 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new DeclareArrayMethodStatement((yyvsp[-13].string_t),*((yyvsp[-10].declList)),(Type)(yyvsp[-7].int_t), *((yyvsp[-2].stmt_list)),yylineno);}
#line 1654 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 102 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new DeclareMethodStatement((yyvsp[-10].string_t), *(new DeclList), (Type)VOID, *((yyvsp[-2].stmt_list)),yylineno);}
#line 1660 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 104 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new IfStatement((yyvsp[-5].expr_t),*((yyvsp[-2].stmt_list)), (yyvsp[0].stmt_t), yylineno);}
#line 1666 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 106 "minitypescript.y" /* yacc.c:1646  */
    { (yyval.stmt_t) = new IfElseStatement((yyvsp[-5].expr_t),*((yyvsp[-2].stmt_list)), (yyvsp[0].stmt_t), yylineno); }
#line 1672 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 107 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new ElseStatement(*((yyvsp[-1].stmt_list)),yylineno);}
#line 1678 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 107 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t)= nullptr;}
#line 1684 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 109 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new ReturnStatement((yyvsp[-1].expr_t), yylineno);}
#line 1690 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 111 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new BreakStatement(yylineno);}
#line 1696 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 113 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t)= new ContinueStatement(yylineno);}
#line 1702 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 115 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new ForStatement1((DeclareVariableStatement*)(yyvsp[-7].stmt_t), (yyvsp[-6].expr_t), (yyvsp[-4].expr_t), *((yyvsp[-1].stmt_list)), yylineno);}
#line 1708 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 116 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new ForStatement2((yyvsp[-10].string_t),(yyvsp[-8].expr_t), (yyvsp[-6].expr_t), (yyvsp[-4].expr_t), *((yyvsp[-1].stmt_list)), yylineno);}
#line 1714 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 117 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new ForEachStatement((yyvsp[-6].string_t), (yyvsp[-4].string_t), *((yyvsp[-1].stmt_list)), yylineno); }
#line 1720 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 119 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new AssignationStatement((yyvsp[-1].expr_t), yylineno);}
#line 1726 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 121 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new PrintStatement(*((yyvsp[-2].expr_list)), yylineno);}
#line 1732 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 122 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new PrintStatement(*(new ExprList), yylineno);}
#line 1738 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 126 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new DeleteArrayStatement(new IdExpr((yyvsp[-4].string_t),yylineno,1),(yyvsp[-2].expr_t),yylineno);}
#line 1744 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 129 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new ReadStatement((yyvsp[-2].expr_t), yylineno);}
#line 1750 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 131 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new AddArrayStatement(new IdExpr((yyvsp[-6].string_t), yylineno, 1), (yyvsp[-2].expr_t), yylineno);}
#line 1756 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 133 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new LogicalOrExpr((yyvsp[-2].expr_t),(yyvsp[0].expr_t), yylineno,0);}
#line 1762 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 134 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t)=(yyvsp[0].expr_t);}
#line 1768 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 137 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new LogicalAndExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);}
#line 1774 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 138 "minitypescript.y" /* yacc.c:1646  */
    { (yyval.expr_t) =(yyvsp[0].expr_t);}
#line 1780 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 141 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new EqEqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);}
#line 1786 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 142 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new NotEqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);}
#line 1792 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 143 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1798 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 146 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new GreaterExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);}
#line 1804 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 147 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new LesserExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);}
#line 1810 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 148 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new GreaterEqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);}
#line 1816 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 149 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new LessEqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);}
#line 1822 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 153 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new AddExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);}
#line 1828 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 154 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new SubExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);}
#line 1834 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 155 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) =(yyvsp[0].expr_t);}
#line 1840 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 158 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new MultExpr((yyvsp[-2].expr_t),(yyvsp[0].expr_t), yylineno,0);}
#line 1846 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 159 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new DivExpr((yyvsp[-2].expr_t),(yyvsp[0].expr_t), yylineno,0);}
#line 1852 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 160 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new ModExpr((yyvsp[-2].expr_t),(yyvsp[0].expr_t), yylineno,0);}
#line 1858 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 161 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1864 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 164 "minitypescript.y" /* yacc.c:1646  */
    {
                         if((yyvsp[-1].int_t) == EQUAL){
                            
                             (yyval.expr_t) = new EqualExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);
                          } else if ((yyvsp[-1].int_t) == PLUSEQUAL){
                             (yyval.expr_t) = new PlusEqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);
                         }else if ((yyvsp[-1].int_t) == SUBEQUAL){
                             (yyval.expr_t) = new SubEqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);
                         } else if ((yyvsp[-1].int_t) == MULTEQUAL){
                             (yyval.expr_t) = new MultEqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);
                         } else if ((yyvsp[-1].int_t) == DIVEQUAL){
                             (yyval.expr_t) = new DivEqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);
                         } else if ((yyvsp[-1].int_t) == MODEQUAL){
                             (yyval.expr_t) = new ModEqExpr((yyvsp[-2].expr_t), (yyvsp[0].expr_t), yylineno,0);
                         }

                       }
#line 1886 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 181 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) =(yyvsp[0].expr_t);}
#line 1892 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 185 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.int_t) = EQUAL;}
#line 1898 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 186 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.int_t) = PLUSEQUAL;}
#line 1904 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 187 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.int_t) = SUBEQUAL;}
#line 1910 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 188 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.int_t) = MULTEQUAL;}
#line 1916 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 189 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.int_t) = DIVEQUAL;}
#line 1922 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 190 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.int_t) = MODEQUAL;}
#line 1928 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 193 "minitypescript.y" /* yacc.c:1646  */
    { (yyval.expr_t) = new NegationExpr((yyvsp[0].expr_t), yylineno,0);}
#line 1934 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 194 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) =(yyvsp[0].expr_t);}
#line 1940 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 197 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new ArrayAccessExpr((IdExpr*)(yyvsp[-3].expr_t),(yyvsp[-1].expr_t), yylineno,2);}
#line 1946 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 198 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t)= new MethodAccessExpr((IdExpr*)(yyvsp[-2].expr_t), *(new ExprList), yylineno, 0);}
#line 1952 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 199 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t)= new MethodAccessExpr((IdExpr*)(yyvsp[-3].expr_t), *((yyvsp[-1].expr_list)), yylineno,0);}
#line 1958 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 200 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = (yyvsp[0].expr_t);}
#line 1964 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 203 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t)= (yyvsp[-1].expr_t);}
#line 1970 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 204 "minitypescript.y" /* yacc.c:1646  */
    { (yyval.expr_t) = new ArrayExpr(*((yyvsp[-1].expr_list)) , yylineno,3);}
#line 1976 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 205 "minitypescript.y" /* yacc.c:1646  */
    { (yyval.expr_t) = new ArrayExpr(*(new ExprList) , yylineno,0);}
#line 1982 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 206 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new PlusPlusExpr(new IdExpr((yyvsp[-1].string_t), yylineno,1), yylineno,0); }
#line 1988 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 207 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new SubSubExpr(new IdExpr((yyvsp[-1].string_t), yylineno,1), yylineno,0); }
#line 1994 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 208 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) = new IdExpr((yyvsp[0].string_t) , yylineno, 1);}
#line 2000 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 209 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) =  new StringExpr((yyvsp[0].string_t), yylineno, 0);}
#line 2006 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 210 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) =  new BoolExpr((yyvsp[0].bool_t), yylineno,0);}
#line 2012 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 211 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) =  new BoolExpr((yyvsp[0].bool_t), yylineno,0);}
#line 2018 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 212 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) =  new FloatExpr((yyvsp[0].float_t), yylineno,0);}
#line 2024 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 213 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_t) =  new IntExpr((yyvsp[0].int_t), yylineno , 0);}
#line 2030 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 215 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.int_t) = FLOAT;}
#line 2036 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 215 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.int_t) = BOOL;}
#line 2042 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 215 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.int_t) = STRING;}
#line 2048 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 217 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.declList) = (yyvsp[0].declList) ; (yyval.declList)->push_front(new DeclExpr((yyvsp[-3].string_t) , (Type)(yyvsp[-1].int_t),1,0, yylineno));}
#line 2054 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 218 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.declList) = (yyvsp[0].declList) ;
if((yyvsp[-4].int_t) == FLOAT){
 (yyval.declList)->push_front(new DeclExpr((yyvsp[-6].string_t) , (Type)ARRAYNUMBER,2,(yyvsp[-2].int_t),yylineno));
} else if((yyvsp[-4].int_t) == STRING){
 (yyval.declList)->push_front(new DeclExpr((yyvsp[-6].string_t) , (Type)ARRAYSTRING,2,(yyvsp[-2].int_t),yylineno));
} else{
 (yyval.declList)->push_front(new DeclExpr((yyvsp[-6].string_t) , (Type)ARRAYBOOL,2,(yyvsp[-2].int_t),yylineno));
}
}
#line 2068 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 228 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.declList) = (yyvsp[0].declList) ; (yyval.declList)->push_front(new DeclExpr((yyvsp[-3].string_t) , (Type)(yyvsp[-1].int_t),1,0,yylineno));}
#line 2074 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 229 "minitypescript.y" /* yacc.c:1646  */
    {
 (yyval.declList) = (yyvsp[0].declList) ;
if((yyvsp[-4].int_t) == FLOAT){
 (yyval.declList)->push_front(new DeclExpr((yyvsp[-6].string_t) , (Type)ARRAYNUMBER,2,(yyvsp[-2].int_t),yylineno));
} else if((yyvsp[-4].int_t) == STRING){
 (yyval.declList)->push_front(new DeclExpr((yyvsp[-6].string_t) , (Type)ARRAYSTRING,2,(yyvsp[-2].int_t),yylineno));
} else{
 (yyval.declList)->push_front(new DeclExpr((yyvsp[-6].string_t) , (Type)ARRAYBOOL,2,(yyvsp[-2].int_t),yylineno));
}

}
#line 2090 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 239 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.declList) = new DeclList ;}
#line 2096 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 242 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_list)= (yyvsp[0].expr_list); (yyval.expr_list)->push_front((yyvsp[-1].expr_t));}
#line 2102 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 243 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.expr_list)= (yyvsp[0].expr_list); (yyval.expr_list)->push_front((yyvsp[-1].expr_t));}
#line 2108 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 243 "minitypescript.y" /* yacc.c:1646  */
    { (yyval.expr_list) = new ExprList;}
#line 2114 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 245 "minitypescript.y" /* yacc.c:1646  */
    {(yyval.stmt_t) = new   MainStatement(*((yyvsp[-1].stmt_list)) , yylineno);}
#line 2120 "minitypescript_parser.cpp" /* yacc.c:1646  */
    break;


#line 2124 "minitypescript_parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 246 "minitypescript.y" /* yacc.c:1906  */

