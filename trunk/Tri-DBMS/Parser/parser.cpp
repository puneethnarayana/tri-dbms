/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 2 "Parser/yparser.ypp"

#include "heading.h"

extern int yylex();
extern void yyerror(const char *s);

DatabaseOperations *dbOps= new DatabaseOperations();
BufferManager *buffManager=BufferManager::getInstance();


/* Line 268 of yacc.c  */
#line 82 "yparser.tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     STRING = 259,
     NAME = 260,
     INTNUM = 261,
     APPROXNUM = 262,
     BOOL = 263,
     DATE = 264,
     ALL = 265,
     AMMSC = 266,
     AND = 267,
     ANY = 268,
     AS = 269,
     ASC = 270,
     AUTHORIZATION = 271,
     BETWEEN = 272,
     BY = 273,
     CHARACTER = 274,
     CHECK = 275,
     CLOSE = 276,
     COMMIT = 277,
     CONTINUE = 278,
     CREATE = 279,
     CURRENT = 280,
     CURSOR = 281,
     DATABASE = 282,
     DECIMAL = 283,
     DECLARE = 284,
     DEFAULT = 285,
     DELETE = 286,
     DESC = 287,
     DESCRIBE = 288,
     DISTINCT = 289,
     DOUBLE = 290,
     DROP = 291,
     ESCAPE = 292,
     EXISTS = 293,
     FETCH = 294,
     FLOAT = 295,
     FOR = 296,
     FOREIGN = 297,
     FOUND = 298,
     FROM = 299,
     GRANT = 300,
     GROUP = 301,
     HAVING = 302,
     IN = 303,
     INDEX = 304,
     INDICATOR = 305,
     INSERT = 306,
     INTEGER = 307,
     INTO = 308,
     IS = 309,
     KEY = 310,
     LANGUAGE = 311,
     LIKE = 312,
     MODULE = 313,
     NOT = 314,
     NULLX = 315,
     NUMERIC = 316,
     OFF = 317,
     ON = 318,
     OR = 319,
     OPEN = 320,
     OPTION = 321,
     ORDER = 322,
     PRECISION = 323,
     PRIMARY = 324,
     PRIVILEGES = 325,
     PROCEDURE = 326,
     PUBLIC = 327,
     REAL = 328,
     REFERENCES = 329,
     ROLLBACK = 330,
     SCHEMA = 331,
     SELECT = 332,
     SET = 333,
     SHOW = 334,
     SMALLINT = 335,
     SOME = 336,
     SQLCODE = 337,
     SQLERROR = 338,
     TABLE = 339,
     TABLES = 340,
     TO = 341,
     UNION = 342,
     UNIQUE = 343,
     UPDATE = 344,
     USER = 345,
     VALUES = 346,
     VARCHAR = 347,
     VIEW = 348,
     WHENEVER = 349,
     WHERE = 350,
     WITH = 351,
     WORK = 352,
     C = 353,
     DATABASES = 354,
     USE = 355,
     QUERY = 356,
     EXIT = 357,
     CACHE = 358,
     COMPARISON = 359,
     UMINUS = 360
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union 
/* Line 293 of yacc.c  */
#line 12 "Parser/yparser.ypp"
YYSTYPE
{

/* Line 293 of yacc.c  */
#line 12 "Parser/yparser.ypp"

	int ival;
	char *sval;
	int subtok;



/* Line 293 of yacc.c  */
#line 234 "yparser.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 246 "yparser.tab.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   330

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  116
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNRULES -- Number of states.  */
#define YYNSTATES  287

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   360

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     112,   113,   107,   105,   114,   106,   115,   108,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   111,
       2,   109,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     110
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     8,    12,    14,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      42,    44,    46,    53,    55,    59,    61,    63,    67,    68,
      71,    74,    78,    83,    86,    89,    92,    97,   100,   106,
     111,   117,   125,   136,   141,   143,   147,   149,   151,   156,
     158,   160,   162,   167,   168,   170,   177,   179,   185,   186,
     190,   195,   197,   201,   203,   205,   207,   209,   211,   213,
     215,   217,   219,   224,   225,   227,   230,   231,   235,   239,
     242,   246,   248,   250,   252,   254,   256,   260,   264,   271,
     277,   283,   288,   289,   292,   299,   305,   312,   318,   320,
     324,   326,   333,   337,   341,   345,   349,   352,   355,   357,
     359,   363,   369,   370,   372,   376,   380,   384,   388,   392,
     396,   400,   403,   406,   408,   412,   419,   420,   422,   424,
     426,   428,   430,   432,   434,   435,   439,   441,   445,   446,
     449,   451,   455,   461,   464,   467,   470,   472,   475,   478,
     481,   484,   487,   489,   492,   495
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     117,     0,    -1,    -1,   117,   118,   111,    -1,   117,     1,
     111,    -1,   119,    -1,   120,    -1,   135,    -1,   160,    -1,
     156,    -1,   142,    -1,   168,    -1,   171,    -1,   131,    -1,
     178,    -1,   172,    -1,   173,    -1,   174,    -1,   133,    -1,
     175,    -1,   176,    -1,   177,    -1,    24,    84,   128,   112,
     121,   113,    -1,   122,    -1,   121,   114,   122,    -1,   123,
      -1,   126,    -1,   129,   130,   124,    -1,    -1,   124,   125,
      -1,    59,    60,    -1,    59,    60,    88,    -1,    59,    60,
      69,    55,    -1,    30,   140,    -1,    30,    60,    -1,    30,
      90,    -1,    20,   112,   145,   113,    -1,    74,   128,    -1,
      74,   128,   112,   127,   113,    -1,    88,   112,   127,   113,
      -1,    69,    55,   112,   127,   113,    -1,    42,    55,   112,
     127,   113,    74,   128,    -1,    42,    55,   112,   127,   113,
      74,   128,   112,   127,   113,    -1,    20,   112,   145,   113,
      -1,   129,    -1,   127,   114,   129,    -1,     5,    -1,     5,
      -1,    92,   112,     6,   113,    -1,    52,    -1,     8,    -1,
       9,    -1,    24,    27,   170,   132,    -1,    -1,     6,    -1,
      24,    49,   134,    63,   128,   136,    -1,     5,    -1,    51,
      53,   128,   136,   137,    -1,    -1,   112,   127,   113,    -1,
      91,   112,   138,   113,    -1,   139,    -1,   138,   114,   139,
      -1,   140,    -1,     4,    -1,     6,    -1,     7,    -1,     5,
      -1,     4,    -1,     6,    -1,     7,    -1,     5,    -1,    31,
      44,   128,   143,    -1,    -1,   144,    -1,    95,   145,    -1,
      -1,   145,    64,   145,    -1,   145,    12,   145,    -1,    59,
     145,    -1,   112,   145,   113,    -1,   146,    -1,   147,    -1,
     148,    -1,   149,    -1,   151,    -1,   167,   104,   155,    -1,
     167,   104,   154,    -1,   155,    59,    17,   155,    12,   155,
      -1,   155,    17,   155,    12,   155,    -1,   155,    59,    57,
     153,   150,    -1,   155,    57,   153,   150,    -1,    -1,    37,
     153,    -1,   155,    59,    48,   112,   154,   113,    -1,   155,
      48,   112,   154,   113,    -1,   155,    59,    48,   112,   152,
     113,    -1,   155,    48,   112,   152,   113,    -1,   153,    -1,
     152,   114,   153,    -1,   141,    -1,   112,    77,   161,   162,
     163,   113,    -1,   155,   105,   155,    -1,   155,   106,   155,
      -1,   155,   107,   155,    -1,   155,   108,   155,    -1,   105,
     155,    -1,   106,   155,    -1,   153,    -1,   167,    -1,   112,
     155,   113,    -1,    89,   128,    78,   157,   143,    -1,    -1,
     158,    -1,   157,   114,   158,    -1,   129,   104,   159,    -1,
     129,   104,    60,    -1,   159,   105,   159,    -1,   159,   106,
     159,    -1,   159,   107,   159,    -1,   159,   108,   159,    -1,
     105,   159,    -1,   106,   159,    -1,   139,    -1,   112,   159,
     113,    -1,    77,   161,   162,    44,   128,   163,    -1,    -1,
      10,    -1,    34,    -1,   127,    -1,   107,    -1,   143,    -1,
     164,    -1,   166,    -1,    -1,    46,    18,   165,    -1,   167,
      -1,   165,   114,   167,    -1,    -1,    47,   145,    -1,     5,
      -1,     5,   115,     5,    -1,     5,   115,     5,   115,     5,
      -1,    36,   169,    -1,    27,   170,    -1,    84,   128,    -1,
       5,    -1,    32,   128,    -1,    33,   128,    -1,    79,    99,
      -1,    79,    85,    -1,   100,   170,    -1,   102,    -1,   103,
      63,    -1,   103,    62,    -1,    21,   170,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    81,    81,    83,    84,    90,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   115,   125,   126,   130,   131,   135,   138,   140,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   156,
     157,   158,   160,   162,   166,   167,   171,   174,   180,   184,
     188,   192,   201,   211,   213,   219,   223,   228,   240,   242,
     246,   250,   251,   255,   259,   262,   265,   268,   274,   278,
     282,   286,   293,   306,   308,   312,   317,   318,   322,   326,
     330,   331,   335,   336,   337,   338,   342,   346,   353,   354,
     358,   359,   362,   364,   368,   369,   370,   371,   375,   376,
     380,   384,   391,   392,   393,   394,   395,   396,   397,   398,
     399,   411,   434,   435,   436,   440,   441,   445,   446,   447,
     448,   449,   450,   451,   452,   461,   479,   481,   482,   487,
     488,   492,   493,   494,   498,   500,   504,   505,   508,   510,
     514,   518,   519,   523,   527,   528,   533,   538,   539,   543,
     547,   551,   557,   564,   571,   578
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "STRING", "NAME", "INTNUM",
  "APPROXNUM", "BOOL", "DATE", "ALL", "AMMSC", "AND", "ANY", "AS", "ASC",
  "AUTHORIZATION", "BETWEEN", "BY", "CHARACTER", "CHECK", "CLOSE",
  "COMMIT", "CONTINUE", "CREATE", "CURRENT", "CURSOR", "DATABASE",
  "DECIMAL", "DECLARE", "DEFAULT", "DELETE", "DESC", "DESCRIBE",
  "DISTINCT", "DOUBLE", "DROP", "ESCAPE", "EXISTS", "FETCH", "FLOAT",
  "FOR", "FOREIGN", "FOUND", "FROM", "GRANT", "GROUP", "HAVING", "IN",
  "INDEX", "INDICATOR", "INSERT", "INTEGER", "INTO", "IS", "KEY",
  "LANGUAGE", "LIKE", "MODULE", "NOT", "NULLX", "NUMERIC", "OFF", "ON",
  "OR", "OPEN", "OPTION", "ORDER", "PRECISION", "PRIMARY", "PRIVILEGES",
  "PROCEDURE", "PUBLIC", "REAL", "REFERENCES", "ROLLBACK", "SCHEMA",
  "SELECT", "SET", "SHOW", "SMALLINT", "SOME", "SQLCODE", "SQLERROR",
  "TABLE", "TABLES", "TO", "UNION", "UNIQUE", "UPDATE", "USER", "VALUES",
  "VARCHAR", "VIEW", "WHENEVER", "WHERE", "WITH", "WORK", "C", "DATABASES",
  "USE", "QUERY", "EXIT", "CACHE", "COMPARISON", "'+'", "'-'", "'*'",
  "'/'", "'='", "UMINUS", "';'", "'('", "')'", "','", "'.'", "$accept",
  "list", "query", "query_list", "create_statement",
  "base_table_element_commalist", "base_table_element", "column_def",
  "column_def_opt_list", "column_def_opt", "table_constraint_def",
  "column_commalist", "table", "column", "data_type", "createdb_statement",
  "opt_db_size", "create_index", "index_name", "insert_statement",
  "opt_column_commalist", "values_or_query_spec", "insert_atom_commalist",
  "insert_atom", "literal", "where_literal", "delete_statement",
  "opt_where_clause", "where_clause", "search_condition", "predicate",
  "comparison_predicate", "between_predicate", "like_predicate",
  "opt_escape", "in_predicate", "atom_commalist", "atom", "subquery",
  "scalar_exp", "update_statement", "assignment_commalist", "assignment",
  "value_exp", "select_statement", "opt_all_distinct", "selection",
  "table_exp", "opt_group_by_clause", "column_ref_commalist",
  "opt_having_clause", "column_ref", "drop_statement", "db_struct",
  "db_name", "describe_statement", "show_databases", "show_tables",
  "use_db", "exit_stmt", "cache_on", "cache_off", "close_db", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,    43,    45,    42,    47,    61,
     360,    59,    40,    41,    44,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   116,   117,   117,   117,   118,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   120,   121,   121,   122,   122,   123,   124,   124,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   126,
     126,   126,   126,   126,   127,   127,   128,   129,   130,   130,
     130,   130,   131,   132,   132,   133,   134,   135,   136,   136,
     137,   138,   138,   139,   140,   140,   140,   140,   141,   141,
     141,   141,   142,   143,   143,   144,   145,   145,   145,   145,
     145,   145,   146,   146,   146,   146,   147,   147,   148,   148,
     149,   149,   150,   150,   151,   151,   151,   151,   152,   152,
     153,   154,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   156,   157,   157,   157,   158,   158,   159,   159,   159,
     159,   159,   159,   159,   159,   160,   161,   161,   161,   162,
     162,   163,   163,   163,   164,   164,   165,   165,   166,   166,
     167,   167,   167,   168,   169,   169,   170,   171,   171,   172,
     173,   174,   175,   176,   177,   178
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     6,     1,     3,     1,     1,     3,     0,     2,
       2,     3,     4,     2,     2,     2,     4,     2,     5,     4,
       5,     7,    10,     4,     1,     3,     1,     1,     4,     1,
       1,     1,     4,     0,     1,     6,     1,     5,     0,     3,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     0,     1,     2,     0,     3,     3,     2,
       3,     1,     1,     1,     1,     1,     3,     3,     6,     5,
       5,     4,     0,     2,     6,     5,     6,     5,     1,     3,
       1,     6,     3,     3,     3,     3,     2,     2,     1,     1,
       3,     5,     0,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     3,     6,     0,     1,     1,     1,
       1,     1,     1,     1,     0,     3,     1,     3,     0,     2,
       1,     3,     5,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     1,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,   126,     0,     0,     0,   152,     0,     0,     5,     6,
      13,    18,     7,    10,     9,     8,    11,    12,    15,    16,
      17,    19,    20,    21,    14,     4,   146,   155,     0,     0,
       0,     0,    46,   147,   148,     0,     0,   143,     0,   127,
     128,     0,   150,   149,     0,   151,   154,   153,     3,    53,
      56,     0,     0,    73,   144,   145,    58,    47,   130,   129,
      44,     0,   112,    54,    52,     0,     0,    76,    72,    74,
       0,     0,     0,     0,     0,    73,   113,    58,     0,     0,
       0,     0,     0,    23,    25,    26,     0,    68,    71,    69,
      70,    76,     0,     0,    76,   100,    75,    81,    82,    83,
      84,    85,   108,     0,   109,     0,     0,    57,    45,    73,
       0,     0,   111,    55,    76,     0,     0,     0,    22,     0,
      50,    51,    49,     0,    28,     0,    79,     0,   106,   109,
     107,     0,     0,    76,    76,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    59,     0,     0,    76,   131,   125,
     132,   133,    64,    67,    65,    66,   116,     0,     0,     0,
     123,    63,   115,   114,     0,     0,     0,     0,    24,     0,
      27,   141,     0,    80,   110,    78,    77,     0,     0,    71,
      92,     0,     0,     0,   102,   103,   104,   105,     0,    87,
      86,     0,    61,     0,   139,   121,   122,     0,     0,     0,
       0,     0,    43,     0,     0,    39,     0,     0,     0,     0,
       0,    29,     0,     0,     0,     0,    98,     0,     0,    91,
       0,     0,    92,   126,    60,     0,   140,   135,   136,   124,
     117,   118,   119,   120,     0,    40,    48,    76,    34,    35,
      33,    30,    37,   142,    89,    97,     0,    95,    93,     0,
       0,     0,    90,     0,    62,     0,     0,     0,     0,    31,
       0,    99,    88,    96,    94,    73,   137,    41,    36,    32,
       0,     0,     0,    38,   101,     0,    42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    17,    18,    19,    92,    93,    94,   180,   221,
      95,    69,    43,    70,   134,    20,    74,    21,    61,    22,
      81,   117,   201,   170,   171,   105,    23,   158,    79,   106,
     107,   108,   109,   110,   229,   111,   225,   112,   199,   113,
      24,    85,    86,   172,    25,    51,    71,   159,   160,   237,
     161,   139,    26,    47,    37,    27,    28,    29,    30,    31,
      32,    33,    34
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -144
static const yytype_int16 yypact[] =
{
    -144,   116,  -144,  -103,     7,   126,     2,    69,    69,     3,
      23,   117,   -46,    69,     7,  -144,    70,   -17,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,     7,    94,
      69,    69,  -144,  -144,  -144,     7,    69,  -144,    69,  -144,
    -144,     1,  -144,  -144,    56,  -144,  -144,  -144,  -144,   132,
    -144,    78,    38,    48,  -144,  -144,    58,  -144,  -144,    87,
    -144,   165,   209,  -144,  -144,    69,   104,    13,  -144,  -144,
     209,   139,   209,    69,   136,    25,  -144,    58,   120,   189,
     191,   140,    51,  -144,  -144,  -144,   102,  -144,   100,  -144,
    -144,    13,    30,    30,    13,  -144,    29,  -144,  -144,  -144,
    -144,  -144,  -144,   154,   153,    75,   184,  -144,  -144,   152,
      17,   209,  -144,  -144,    13,   185,   186,   209,  -144,   104,
    -144,  -144,  -144,   187,  -144,   279,  -144,    30,  -144,  -144,
    -144,    -9,   128,    13,    13,    30,   188,   259,   160,    30,
      30,    30,    30,    57,  -144,   268,   275,    13,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,    74,    74,    74,
    -144,  -144,   171,  -144,    31,   209,   209,   107,  -144,   295,
     148,   190,   118,  -144,  -144,  -144,   290,    -5,    85,  -144,
     266,    30,   192,   259,    49,    49,  -144,  -144,     9,  -144,
     175,   125,  -144,   301,    29,  -144,  -144,   143,    74,    74,
      74,    74,  -144,   129,   141,  -144,   194,   196,   177,   249,
      69,  -144,   305,    30,   234,   172,  -144,   199,   259,  -144,
      53,    85,   266,   117,  -144,   268,   198,   200,  -144,  -144,
     180,   180,  -144,  -144,   241,  -144,  -144,    13,  -144,  -144,
    -144,    43,   204,  -144,   175,  -144,   259,  -144,  -144,    30,
     176,   205,  -144,     1,  -144,   301,    69,    42,   262,  -144,
     209,  -144,   175,  -144,  -144,   152,  -144,   207,  -144,  -144,
     178,   208,   209,  -144,  -144,   181,  -144
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,  -144,  -144,  -144,   193,  -144,  -144,  -144,
    -144,   -79,    -8,   124,  -144,  -144,  -144,  -144,  -144,  -144,
     233,  -144,  -144,  -128,   105,  -144,  -144,   -38,  -144,   -73,
    -144,  -144,  -144,  -144,    92,  -144,    95,  -143,  -105,   -93,
    -144,  -144,   206,    60,  -144,    96,    62,    55,  -144,  -144,
    -144,   -75,  -144,  -144,    28,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -141
static const yytype_int16 yytable[] =
{
      44,   115,   114,   143,   190,    54,    67,   223,    35,   138,
     140,   142,    36,    97,    98,    99,   100,    97,    98,    99,
     100,   162,   163,   164,   165,    78,   114,   202,   136,   114,
      45,   141,    62,    63,    97,    98,    99,   100,    65,    52,
      66,   143,    55,   143,   182,   226,    41,   122,   177,   114,
     232,   174,   187,    53,   143,   144,   194,   195,   196,   197,
     200,    97,    98,    99,   100,   259,    59,    87,   114,   114,
     185,   186,   101,    64,    42,   119,    48,   166,   162,   163,
     164,   165,   114,   227,   204,   258,   233,    46,   226,    97,
     189,    99,   100,   144,    58,   144,   213,   214,   230,    60,
     149,   150,   151,   152,   183,   182,   144,   264,    68,    67,
     130,   131,   268,   271,   102,   103,     2,     3,   102,   103,
      77,   137,   167,   168,    88,   104,   261,    49,   238,   169,
     254,   269,    56,    57,    72,   102,   103,     4,    73,   121,
       5,    75,   137,    77,   212,   145,    89,     6,     7,     8,
      76,    50,     9,    38,   132,   278,   151,   152,   149,   150,
     151,   152,   102,   103,   128,   129,   272,    10,   217,   198,
      80,   145,   114,    90,   267,    39,   146,   191,   218,   167,
     168,   162,   163,   164,   165,   147,   169,   148,   154,    82,
     276,   280,    91,    11,   133,    12,    84,   224,   156,   157,
      96,    82,   146,   285,  -140,    13,   118,   219,   192,    83,
      40,   147,   252,   148,    67,   135,    14,   193,    15,    16,
     215,    82,   220,   149,   150,   151,   152,   205,   206,   207,
     116,   184,   124,   149,   150,   151,   152,   248,   234,   235,
     120,   184,   244,    82,   125,    84,   126,    77,   208,   209,
     210,   211,   127,    96,   245,    82,   239,   153,   277,   149,
     150,   151,   152,    97,   189,    99,   100,   249,   240,   241,
     242,   243,   162,   163,   164,   165,   208,   209,   210,   211,
     149,   150,   151,   152,   181,   255,   256,   210,   211,   273,
     256,   283,    82,   203,   286,    82,   155,   175,   176,   179,
     188,   216,   143,   228,   231,   222,   236,   246,   247,   251,
     253,   233,   257,   135,   265,   266,   270,   279,   274,   282,
     123,   284,   178,   250,   262,   275,   260,   173,     0,   263,
     281
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-144))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       8,    80,    77,    12,   147,    13,     5,    12,   111,   102,
     103,   104,     5,     4,     5,     6,     7,     4,     5,     6,
       7,     4,     5,     6,     7,    63,   101,   155,   101,   104,
      27,   104,    40,    41,     4,     5,     6,     7,    46,    85,
      48,    12,    14,    12,   137,   188,    44,    85,   127,   124,
     193,   124,   145,    99,    12,    64,   149,   150,   151,   152,
     153,     4,     5,     6,     7,    12,    38,    75,   143,   144,
     143,   144,    59,    45,     5,    83,    53,    60,     4,     5,
       6,     7,   157,   188,   157,   228,    77,    84,   231,     4,
       5,     6,     7,    64,   111,    64,   175,   176,   191,     5,
     105,   106,   107,   108,   113,   198,    64,   235,   107,     5,
       8,     9,    69,   256,   105,   106,     0,     1,   105,   106,
      95,   112,   105,   106,    20,   112,   231,    10,   203,   112,
     223,    88,    62,    63,    78,   105,   106,    21,     6,   114,
      24,    63,   112,    95,   113,    17,    42,    31,    32,    33,
     112,    34,    36,    27,    52,   113,   107,   108,   105,   106,
     107,   108,   105,   106,   113,   114,   259,    51,    20,   112,
     112,    17,   247,    69,   247,    49,    48,    17,    30,   105,
     106,     4,     5,     6,     7,    57,   112,    59,   113,   114,
     265,   270,    88,    77,    92,    79,    72,   112,    46,    47,
      76,   114,    48,   282,   104,    89,    82,    59,    48,    44,
      84,    57,   220,    59,     5,   115,   100,    57,   102,   103,
     113,   114,    74,   105,   106,   107,   108,   167,   168,   169,
      91,   113,   112,   105,   106,   107,   108,    60,   113,   114,
     104,   113,   113,   114,    55,   121,    55,    95,   105,   106,
     107,   108,   112,   129,   113,   114,   113,   104,   266,   105,
     106,   107,   108,     4,     5,     6,     7,    90,   208,   209,
     210,   211,     4,     5,     6,     7,   105,   106,   107,   108,
     105,   106,   107,   108,     5,   113,   114,   107,   108,   113,
     114,   113,   114,    18,   113,   114,   112,   112,   112,   112,
     112,     6,    12,    37,   112,   115,     5,   113,   112,    60,
       5,    77,   113,   115,   114,    74,   112,    55,   113,   112,
      87,   113,   129,   218,   232,   263,   231,   121,    -1,   233,
     275
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   117,     0,     1,    21,    24,    31,    32,    33,    36,
      51,    77,    79,    89,   100,   102,   103,   118,   119,   120,
     131,   133,   135,   142,   156,   160,   168,   171,   172,   173,
     174,   175,   176,   177,   178,   111,     5,   170,    27,    49,
      84,    44,     5,   128,   128,    27,    84,   169,    53,    10,
      34,   161,    85,    99,   128,   170,    62,    63,   111,   170,
       5,   134,   128,   128,   170,   128,   128,     5,   107,   127,
     129,   162,    78,     6,   132,    63,   112,    95,   143,   144,
     112,   136,   114,    44,   129,   157,   158,   128,    20,    42,
      69,    88,   121,   122,   123,   126,   129,     4,     5,     6,
       7,    59,   105,   106,   112,   141,   145,   146,   147,   148,
     149,   151,   153,   155,   167,   127,    91,   137,   129,   128,
     104,   114,   143,   136,   112,    55,    55,   112,   113,   114,
       8,     9,    52,    92,   130,   115,   145,   112,   155,   167,
     155,   145,   155,    12,    64,    17,    48,    57,    59,   105,
     106,   107,   108,   104,   113,   112,    46,    47,   143,   163,
     164,   166,     4,     5,     6,     7,    60,   105,   106,   112,
     139,   140,   159,   158,   145,   112,   112,   127,   122,   112,
     124,     5,   155,   113,   113,   145,   145,   155,   112,     5,
     153,    17,    48,    57,   155,   155,   155,   155,   112,   154,
     155,   138,   139,    18,   145,   159,   159,   159,   105,   106,
     107,   108,   113,   127,   127,   113,     6,    20,    30,    59,
      74,   125,   115,    12,   112,   152,   153,   154,    37,   150,
     155,   112,   153,    77,   113,   114,     5,   165,   167,   113,
     159,   159,   159,   159,   113,   113,   113,   112,    60,    90,
     140,    60,   128,     5,   155,   113,   114,   113,   153,    12,
     152,   154,   150,   161,   139,   114,    74,   145,    69,    88,
     112,   153,   155,   113,   113,   162,   167,   128,   113,    55,
     127,   163,   112,   113,   113,   127,   113
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
      yychar = YYLEX;
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 4:

/* Line 1806 of yacc.c  */
#line 84 "Parser/yparser.ypp"
    {
			yyclearin;
		}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 115 "Parser/yparser.ypp"
    {
			dbOps->createTable((yyvsp[(3) - (6)].sval),globalColumnNameList,globalColumnDatatypeList,globalColumnDatasizeList);
			cout<<"Table "<<(yyvsp[(3) - (6)].sval)<<" created successfully with "<<globalColumnNameList.size()<<" column(s)!"<<endl;
			globalColumnNameList.clear();
			globalColumnDatatypeList.clear();
			globalColumnDatasizeList.clear();
		}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 174 "Parser/yparser.ypp"
    { 
				globalColumnNameList.push_back( CommonUtil::char_to_string((yyvsp[(1) - (1)].sval)) );
			}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 181 "Parser/yparser.ypp"
    { globalColumnDatatypeList.push_back(CommonUtil::int_to_string(DataTypeLookup::getType((yyvsp[(1) - (4)].sval))));
		  globalColumnDatasizeList.push_back((yyvsp[(3) - (4)].sval)); 
		}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 185 "Parser/yparser.ypp"
    { globalColumnDatatypeList.push_back(CommonUtil::int_to_string(DataTypeLookup::getType((yyvsp[(1) - (1)].sval))));
	      globalColumnDatasizeList.push_back(CommonUtil::int_to_string(FieldLengthLookup::getType((yyvsp[(1) - (1)].sval)))); 
		}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 189 "Parser/yparser.ypp"
    { globalColumnDatatypeList.push_back(CommonUtil::int_to_string(DataTypeLookup::getType((yyvsp[(1) - (1)].sval))));
		  globalColumnDatasizeList.push_back(CommonUtil::int_to_string(FieldLengthLookup::getType((yyvsp[(1) - (1)].sval)))); 
		}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 193 "Parser/yparser.ypp"
    { globalColumnDatatypeList.push_back(CommonUtil::int_to_string(DataTypeLookup::getType((yyvsp[(1) - (1)].sval)))); 
		  globalColumnDatasizeList.push_back(CommonUtil::int_to_string(FieldLengthLookup::getType((yyvsp[(1) - (1)].sval))));
		}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 201 "Parser/yparser.ypp"
    {
		if(dbSize==0)
			dbOps->createDatabase((yyvsp[(3) - (4)].sval));
		else
			{dbOps->createDatabase((yyvsp[(3) - (4)].sval),dbSize);}
		cout<<"Database created successfully!"<<endl;
		dbSize=0;
		}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 213 "Parser/yparser.ypp"
    {
		dbSize=CommonUtil::string_to_int((yyvsp[(1) - (1)].sval));
		}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 219 "Parser/yparser.ypp"
    {cout<<"CREATE INDEX "<<endl<<endl;}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 223 "Parser/yparser.ypp"
    { cout<<"index name = "<< (yyvsp[(1) - (1)].sval) <<endl ;}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 228 "Parser/yparser.ypp"
    {
			cout<<endl<<"VALUES inserted"<<endl;
				for(unsigned ii=0; ii < globalColumnValueList.size(); ii++)
    		    {
                cout << globalColumnValueList[ii];
        		}
			dbOps->insertIntoTable((yyvsp[(3) - (5)].sval),globalColumnValueList); 
			cout<<"Inserted 1 row successfully!"<<endl;
        	globalColumnValueList.clear();
		}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 259 "Parser/yparser.ypp"
    { 
			globalColumnValueList.push_back((yyvsp[(1) - (1)].sval));
		}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 262 "Parser/yparser.ypp"
    { 
			globalColumnValueList.push_back((yyvsp[(1) - (1)].sval));
		}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 265 "Parser/yparser.ypp"
    { 
			globalColumnValueList.push_back((yyvsp[(1) - (1)].sval));
		}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 268 "Parser/yparser.ypp"
    { 
			globalColumnValueList.push_back((yyvsp[(1) - (1)].sval));
		}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 274 "Parser/yparser.ypp"
    { 
			WhereExpressionElement whereExpr(WhereExpressionElement::LITERAL_TYPE,(yyvsp[(1) - (1)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 278 "Parser/yparser.ypp"
    { 
			WhereExpressionElement whereExpr(WhereExpressionElement::LITERAL_TYPE,(yyvsp[(1) - (1)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 282 "Parser/yparser.ypp"
    { 
			WhereExpressionElement whereExpr(WhereExpressionElement::LITERAL_TYPE,(yyvsp[(1) - (1)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 286 "Parser/yparser.ypp"
    { 
			WhereExpressionElement whereExpr(WhereExpressionElement::LITERAL_TYPE,(yyvsp[(1) - (1)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 293 "Parser/yparser.ypp"
    {
		for(unsigned ii=0; ii < globalWhereList.size(); ii++)
    		    {
                cout << "1. "<<globalWhereList[ii].identifierValue<<" 2. "<<globalWhereList[ii].literalValue<<" 3. "<<globalWhereList[ii].operatorValue<<endl ;
        		}
		dbOps->deleteFromTable((yyvsp[(3) - (4)].sval),globalWhereList); 
       	globalColumnNameList.clear();
       	globalColumnValueList.clear();
		globalWhereList.clear();
		
	}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 318 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::OPERATOR_TYPE,"OR");
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 322 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::OPERATOR_TYPE,"OR");
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 326 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::OPERATOR_TYPE,"OR");
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 342 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::OPERATOR_TYPE,(yyvsp[(2) - (3)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 346 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::OPERATOR_TYPE,(yyvsp[(2) - (3)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 411 "Parser/yparser.ypp"
    {
			cout<<endl<<"NAMES part"<<endl;
			for(unsigned ii=0; ii < globalColumnNameList.size(); ii++)
    		    {
                cout << globalColumnNameList[ii];
        		}
			cout<<endl<<"VALUES part"<<endl;
				for(unsigned ii=0; ii < globalColumnValueList.size(); ii++)
    		    {
                cout << globalColumnValueList[ii];
        		}
			cout<<endl<<"WHERE part"<<endl;
		for(unsigned ii=0; ii < globalWhereList.size(); ii++)
    		    {
                cout << "1. "<<globalWhereList[ii].identifierValue<<" 2. "<<globalWhereList[ii].literalValue<<" 3. "<<globalWhereList[ii].operatorValue<<endl ;
        		}
			dbOps->updateTable((yyvsp[(2) - (5)].sval),globalColumnNameList,globalColumnValueList,globalWhereList);
        	globalColumnNameList.clear();
        	globalColumnValueList.clear();
			globalWhereList.clear();
		}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 461 "Parser/yparser.ypp"
    {
			cout<<endl<<"NAMES part"<<endl;
			for(unsigned ii=0; ii < globalColumnNameList.size(); ii++)
    		    {
                cout << globalColumnNameList[ii];
        		}
			cout<<endl<<"WHERE part"<<endl;
		for(unsigned ii=0; ii < globalWhereList.size(); ii++)
    		    {
                cout << "1. "<<globalWhereList[ii].identifierValue<<" 2. "<<globalWhereList[ii].literalValue<<" 3. "<<globalWhereList[ii].operatorValue<<endl ;
        		}
			dbOps->selectAllFromTable((yyvsp[(5) - (6)].sval),globalColumnNameList,globalWhereList);
        	globalColumnNameList.clear();
        	globalColumnValueList.clear();
			globalWhereList.clear();
		}
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 514 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::IDENTIFIER_TYPE,(yyvsp[(1) - (1)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 528 "Parser/yparser.ypp"
    {
			dbOps->dropTable((yyvsp[(2) - (2)].sval));
		}
    break;

  case 148:

/* Line 1806 of yacc.c  */
#line 539 "Parser/yparser.ypp"
    {cout<<"DESCRIBE TABLE "<<endl<<endl;}
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 543 "Parser/yparser.ypp"
    {dbOps->listDatabases();}
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 547 "Parser/yparser.ypp"
    {dbOps->listTables();}
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 551 "Parser/yparser.ypp"
    {
		dbOps->openDatabase((yyvsp[(2) - (2)].sval));
	}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 557 "Parser/yparser.ypp"
    {
		cout<<"Exiting..."<<endl;
		exit(-1);
	}
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 564 "Parser/yparser.ypp"
    {
		buffManager->setInitCache(true);
		cout<<"Cache mode on"<<endl;
	}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 571 "Parser/yparser.ypp"
    {
		buffManager->setInitCache(false);
		cout<<"Cache mode off"<<endl;
	}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 578 "Parser/yparser.ypp"
    {
		buffManager->commitCache();
		cout<<(yyvsp[(2) - (2)].sval)<<" database committed to disk"<<endl;
	}
    break;



/* Line 1806 of yacc.c  */
#line 2179 "yparser.tab.cpp"
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

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 584 "Parser/yparser.ypp"


void yyerror(const char *s) {
	cout << "\nERROR  MSG: " << s << endl;
}

