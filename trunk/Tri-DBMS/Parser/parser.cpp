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
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  116
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  163
/* YYNRULES -- Number of states.  */
#define YYNSTATES  297

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
      42,    44,    46,    48,    50,    52,    54,    61,    63,    67,
      69,    71,    75,    76,    79,    82,    86,    91,    94,    97,
     100,   105,   108,   114,   119,   125,   133,   144,   149,   151,
     155,   157,   159,   164,   166,   168,   170,   175,   176,   178,
     185,   187,   191,   194,   200,   201,   205,   210,   212,   216,
     218,   220,   222,   224,   226,   228,   230,   232,   234,   239,
     240,   242,   245,   246,   250,   254,   257,   261,   263,   265,
     267,   269,   271,   275,   279,   286,   292,   298,   303,   304,
     307,   314,   320,   327,   333,   335,   339,   341,   348,   352,
     356,   360,   364,   367,   370,   372,   374,   378,   384,   385,
     387,   391,   395,   399,   403,   407,   411,   415,   418,   421,
     423,   427,   434,   435,   437,   439,   441,   443,   445,   447,
     449,   450,   454,   456,   460,   461,   464,   466,   470,   476,
     479,   482,   485,   487,   490,   493,   496,   499,   502,   504,
     507,   510,   513,   516
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     117,     0,    -1,    -1,   117,   118,   111,    -1,   117,     1,
     111,    -1,   119,    -1,   120,    -1,   137,    -1,   162,    -1,
     158,    -1,   144,    -1,   170,    -1,   173,    -1,   131,    -1,
     182,    -1,   174,    -1,   175,    -1,   176,    -1,   133,    -1,
     135,    -1,   136,    -1,   177,    -1,   178,    -1,   179,    -1,
     180,    -1,   181,    -1,    24,    84,   128,   112,   121,   113,
      -1,   122,    -1,   121,   114,   122,    -1,   123,    -1,   126,
      -1,   129,   130,   124,    -1,    -1,   124,   125,    -1,    59,
      60,    -1,    59,    60,    88,    -1,    59,    60,    69,    55,
      -1,    30,   142,    -1,    30,    60,    -1,    30,    90,    -1,
      20,   112,   147,   113,    -1,    74,   128,    -1,    74,   128,
     112,   127,   113,    -1,    88,   112,   127,   113,    -1,    69,
      55,   112,   127,   113,    -1,    42,    55,   112,   127,   113,
      74,   128,    -1,    42,    55,   112,   127,   113,    74,   128,
     112,   127,   113,    -1,    20,   112,   147,   113,    -1,   129,
      -1,   127,   114,   129,    -1,     5,    -1,     5,    -1,    92,
     112,     6,   113,    -1,    52,    -1,     8,    -1,     9,    -1,
      24,    27,   172,   132,    -1,    -1,     6,    -1,    24,    49,
     134,    63,   128,   138,    -1,     5,    -1,    31,    49,   134,
      -1,    79,    49,    -1,    51,    53,   128,   138,   139,    -1,
      -1,   112,   127,   113,    -1,    91,   112,   140,   113,    -1,
     141,    -1,   140,   114,   141,    -1,   142,    -1,     4,    -1,
       6,    -1,     7,    -1,     5,    -1,     4,    -1,     6,    -1,
       7,    -1,     5,    -1,    31,    44,   128,   145,    -1,    -1,
     146,    -1,    95,   147,    -1,    -1,   147,    64,   147,    -1,
     147,    12,   147,    -1,    59,   147,    -1,   112,   147,   113,
      -1,   148,    -1,   149,    -1,   150,    -1,   151,    -1,   153,
      -1,   169,   104,   157,    -1,   169,   104,   156,    -1,   157,
      59,    17,   157,    12,   157,    -1,   157,    17,   157,    12,
     157,    -1,   157,    59,    57,   155,   152,    -1,   157,    57,
     155,   152,    -1,    -1,    37,   155,    -1,   157,    59,    48,
     112,   156,   113,    -1,   157,    48,   112,   156,   113,    -1,
     157,    59,    48,   112,   154,   113,    -1,   157,    48,   112,
     154,   113,    -1,   155,    -1,   154,   114,   155,    -1,   143,
      -1,   112,    77,   163,   164,   165,   113,    -1,   157,   105,
     157,    -1,   157,   106,   157,    -1,   157,   107,   157,    -1,
     157,   108,   157,    -1,   105,   157,    -1,   106,   157,    -1,
     155,    -1,   169,    -1,   112,   157,   113,    -1,    89,   128,
      78,   159,   145,    -1,    -1,   160,    -1,   159,   114,   160,
      -1,   129,   104,   161,    -1,   129,   104,    60,    -1,   161,
     105,   161,    -1,   161,   106,   161,    -1,   161,   107,   161,
      -1,   161,   108,   161,    -1,   105,   161,    -1,   106,   161,
      -1,   141,    -1,   112,   161,   113,    -1,    77,   163,   164,
      44,   128,   165,    -1,    -1,    10,    -1,    34,    -1,   127,
      -1,   107,    -1,   145,    -1,   166,    -1,   168,    -1,    -1,
      46,    18,   167,    -1,   169,    -1,   167,   114,   169,    -1,
      -1,    47,   147,    -1,     5,    -1,     5,   115,     5,    -1,
       5,   115,     5,   115,     5,    -1,    36,   171,    -1,    27,
     172,    -1,    84,   128,    -1,     5,    -1,    32,   128,    -1,
      33,   128,    -1,    79,    99,    -1,    79,    85,    -1,   100,
     172,    -1,   102,    -1,   103,    63,    -1,   103,    62,    -1,
      49,    63,    -1,    49,    62,    -1,    21,   172,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    81,    81,    83,    84,    90,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   119,   129,   130,   134,
     135,   139,   142,   144,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   160,   161,   162,   164,   166,   170,   171,
     175,   178,   184,   188,   192,   196,   205,   215,   217,   223,
     230,   234,   239,   244,   251,   253,   257,   261,   262,   266,
     270,   273,   276,   279,   285,   289,   293,   297,   304,   313,
     315,   319,   324,   325,   329,   333,   337,   338,   342,   343,
     344,   345,   349,   353,   360,   361,   365,   366,   369,   371,
     375,   376,   377,   378,   382,   383,   387,   391,   398,   399,
     400,   401,   402,   403,   404,   405,   406,   418,   426,   427,
     428,   432,   433,   437,   438,   439,   440,   441,   442,   443,
     444,   453,   461,   463,   464,   469,   470,   474,   475,   476,
     480,   482,   486,   487,   490,   492,   496,   500,   501,   505,
     509,   510,   515,   520,   521,   525,   529,   533,   539,   546,
     553,   560,   566,   572
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
  "opt_db_size", "create_index", "index_name", "delete_index",
  "show_index", "insert_statement", "opt_column_commalist",
  "values_or_query_spec", "insert_atom_commalist", "insert_atom",
  "literal", "where_literal", "delete_statement", "opt_where_clause",
  "where_clause", "search_condition", "predicate", "comparison_predicate",
  "between_predicate", "like_predicate", "opt_escape", "in_predicate",
  "atom_commalist", "atom", "subquery", "scalar_exp", "update_statement",
  "assignment_commalist", "assignment", "value_exp", "select_statement",
  "opt_all_distinct", "selection", "table_exp", "opt_group_by_clause",
  "column_ref_commalist", "opt_having_clause", "column_ref",
  "drop_statement", "db_struct", "db_name", "describe_statement",
  "show_databases", "show_tables", "use_db", "exit_stmt", "cache_on",
  "cache_off", "index_on", "index_off", "close_db", 0
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
     119,   119,   119,   119,   119,   119,   120,   121,   121,   122,
     122,   123,   124,   124,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   126,   126,   126,   126,   126,   127,   127,
     128,   129,   130,   130,   130,   130,   131,   132,   132,   133,
     134,   135,   136,   137,   138,   138,   139,   140,   140,   141,
     142,   142,   142,   142,   143,   143,   143,   143,   144,   145,
     145,   146,   147,   147,   147,   147,   147,   147,   148,   148,
     148,   148,   149,   149,   150,   150,   151,   151,   152,   152,
     153,   153,   153,   153,   154,   154,   155,   156,   157,   157,
     157,   157,   157,   157,   157,   157,   157,   158,   159,   159,
     159,   160,   160,   161,   161,   161,   161,   161,   161,   161,
     161,   162,   163,   163,   163,   164,   164,   165,   165,   165,
     166,   166,   167,   167,   168,   168,   169,   169,   169,   170,
     171,   171,   172,   173,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     6,     1,     3,     1,
       1,     3,     0,     2,     2,     3,     4,     2,     2,     2,
       4,     2,     5,     4,     5,     7,    10,     4,     1,     3,
       1,     1,     4,     1,     1,     1,     4,     0,     1,     6,
       1,     3,     2,     5,     0,     3,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     0,
       1,     2,     0,     3,     3,     2,     3,     1,     1,     1,
       1,     1,     3,     3,     6,     5,     5,     4,     0,     2,
       6,     5,     6,     5,     1,     3,     1,     6,     3,     3,
       3,     3,     2,     2,     1,     1,     3,     5,     0,     1,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     1,
       3,     6,     0,     1,     1,     1,     1,     1,     1,     1,
       0,     3,     1,     3,     0,     2,     1,     3,     5,     2,
       2,     2,     1,     2,     2,     2,     2,     2,     1,     2,
       2,     2,     2,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   132,     0,     0,     0,   158,     0,     0,     5,
       6,    13,    18,    19,    20,     7,    10,     9,     8,    11,
      12,    15,    16,    17,    21,    22,    23,    24,    25,    14,
       4,   152,   163,     0,     0,     0,     0,     0,    50,   153,
     154,     0,     0,   149,   162,   161,     0,   133,   134,     0,
      62,   156,   155,     0,   157,   160,   159,     3,    57,    60,
       0,     0,    79,    61,   150,   151,    64,    51,   136,   135,
      48,     0,   118,    58,    56,     0,     0,    82,    78,    80,
       0,     0,     0,     0,     0,    79,   119,    64,     0,     0,
       0,     0,     0,    27,    29,    30,     0,    74,    77,    75,
      76,    82,     0,     0,    82,   106,    81,    87,    88,    89,
      90,    91,   114,     0,   115,     0,     0,    63,    49,    79,
       0,     0,   117,    59,    82,     0,     0,     0,    26,     0,
      54,    55,    53,     0,    32,     0,    85,     0,   112,   115,
     113,     0,     0,    82,    82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,     0,     0,    82,   137,   131,
     138,   139,    70,    73,    71,    72,   122,     0,     0,     0,
     129,    69,   121,   120,     0,     0,     0,     0,    28,     0,
      31,   147,     0,    86,   116,    84,    83,     0,     0,    77,
      98,     0,     0,     0,   108,   109,   110,   111,     0,    93,
      92,     0,    67,     0,   145,   127,   128,     0,     0,     0,
       0,     0,    47,     0,     0,    43,     0,     0,     0,     0,
       0,    33,     0,     0,     0,     0,   104,     0,     0,    97,
       0,     0,    98,   132,    66,     0,   146,   141,   142,   130,
     123,   124,   125,   126,     0,    44,    52,    82,    38,    39,
      37,    34,    41,   148,    95,   103,     0,   101,    99,     0,
       0,     0,    96,     0,    68,     0,     0,     0,     0,    35,
       0,   105,    94,   102,   100,    79,   143,    45,    40,    36,
       0,     0,     0,    42,   107,     0,    46
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,   102,   103,   104,   190,   231,
     105,    79,    49,    80,   144,    21,    84,    22,    70,    23,
      24,    25,    91,   127,   211,   180,   181,   115,    26,   168,
      89,   116,   117,   118,   119,   120,   239,   121,   235,   122,
     209,   123,    27,    95,    96,   182,    28,    59,    81,   169,
     170,   247,   171,   149,    29,    53,    42,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -186
static const yytype_int16 yypact[] =
{
    -186,   174,  -186,  -103,    21,    -2,    64,    91,    91,   -12,
      81,   -39,   124,    26,    91,    21,  -186,   119,   -82,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,  -186,
    -186,  -186,  -186,    21,   102,    91,    91,   102,  -186,  -186,
    -186,    21,    91,  -186,  -186,  -186,    91,  -186,  -186,     2,
    -186,  -186,  -186,    32,  -186,  -186,  -186,  -186,   110,  -186,
      75,    34,    57,  -186,  -186,  -186,    45,  -186,  -186,    46,
    -186,   121,   166,  -186,  -186,    91,   100,    12,  -186,  -186,
     166,    92,   166,    91,    95,   -86,  -186,    45,   108,   185,
     195,   126,    83,  -186,  -186,  -186,   169,  -186,    11,  -186,
    -186,    12,    74,    74,    12,  -186,    40,  -186,  -186,  -186,
    -186,  -186,  -186,   128,   148,    98,   144,  -186,  -186,    89,
      27,   166,  -186,  -186,    12,   150,   161,   166,  -186,   100,
    -186,  -186,  -186,   163,  -186,   255,  -186,    74,  -186,  -186,
    -186,     9,   111,    12,    12,    74,   181,   239,    73,    74,
      74,    74,    74,    88,  -186,   260,   269,    12,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186,    96,    96,    96,
    -186,  -186,   193,  -186,    10,   166,   166,   101,  -186,   300,
     183,   192,   175,  -186,  -186,  -186,   296,    43,    60,  -186,
     272,    74,   198,   239,    82,    82,  -186,  -186,    35,  -186,
     197,   113,  -186,   306,    40,  -186,  -186,   184,    96,    96,
      96,    96,  -186,   118,   135,  -186,   199,   201,   149,   254,
      91,  -186,   310,    74,   240,   141,  -186,   203,   239,  -186,
      56,    60,   272,   124,  -186,   260,   204,   206,  -186,  -186,
     151,   151,  -186,  -186,   244,  -186,  -186,    12,  -186,  -186,
    -186,   -34,   209,  -186,   197,  -186,   239,  -186,  -186,    74,
     165,   210,  -186,     2,  -186,   306,    91,    24,   267,  -186,
     166,  -186,   197,  -186,  -186,    89,  -186,   212,  -186,  -186,
     171,   213,   166,  -186,  -186,   182,  -186
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -186,  -186,  -186,  -186,  -186,  -186,   186,  -186,  -186,  -186,
    -186,   -88,    -8,   155,  -186,  -186,  -186,  -186,   280,  -186,
    -186,  -186,   231,  -186,  -186,  -161,   103,  -186,  -186,   -71,
    -186,   -91,  -186,  -186,  -186,  -186,    87,  -186,    93,  -152,
    -185,  -102,  -186,  -186,   202,    51,  -186,    94,    59,    50,
    -186,  -186,  -186,   -84,  -186,  -186,    76,  -186,  -186,  -186,
    -186,  -186,  -186,  -186,  -186,  -186,  -186
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -147
static const yytype_int16 yytable[] =
{
      50,    88,   125,   124,   212,   200,    63,    77,    40,    87,
     148,   150,   152,   237,    56,    51,   107,   108,   109,   110,
     146,   153,   153,   151,   132,    43,    41,   124,   131,    67,
     124,   172,   173,   174,   175,   278,   153,    71,    72,   107,
     108,   109,   110,   184,    75,   192,   236,    44,    76,   187,
     124,   242,   153,   197,   279,   233,   271,   204,   205,   206,
     207,   210,   195,   196,   107,   199,   109,   110,   269,   124,
     124,   111,    52,   154,   154,    60,   214,    97,   107,   108,
     109,   110,    45,   124,   274,   129,   268,   176,   154,   236,
     201,    64,   107,   108,   109,   110,    48,   223,   224,   240,
     172,   173,   174,   175,   154,    77,   192,    69,    46,    78,
      82,    61,   243,    47,   281,  -146,    83,   112,   113,    68,
      98,   202,   193,   222,   114,    62,   145,    74,   155,   248,
     203,   264,   177,   178,    57,   166,   167,   288,    85,   179,
     112,   113,    99,    54,    55,   155,    86,   147,   159,   160,
     161,   162,    87,   172,   173,   174,   175,    90,    58,   156,
      92,   159,   160,   161,   162,    93,   277,   282,   157,   100,
     158,    77,   234,   124,     2,     3,   156,   140,   141,   112,
     113,    65,    66,   126,    87,   157,   147,   158,   101,   161,
     162,   286,   290,   112,   113,     4,   138,   139,     5,   130,
     208,   177,   178,   227,   295,     6,     7,     8,   179,   258,
       9,   164,    92,   228,   225,    92,   159,   160,   161,   162,
     134,   142,   262,    10,   194,    11,   244,   245,   215,   216,
     217,   254,    92,   159,   160,   161,   162,    94,   137,   259,
     135,   106,   229,   107,   199,   109,   110,   128,   255,    92,
     136,    12,   163,    13,   265,   266,   165,   230,   220,   221,
     191,   143,   185,    14,   172,   173,   174,   175,   287,   250,
     251,   252,   253,   186,    15,   189,    16,    17,   283,   266,
     159,   160,   161,   162,   293,    92,    94,   213,   194,   218,
     219,   220,   221,   198,   106,   296,    92,   249,   218,   219,
     220,   221,   159,   160,   161,   162,   226,   232,   153,   238,
     241,   246,   256,   257,   261,   263,   267,   243,   276,   145,
     275,   280,   289,   284,   292,   188,   294,    73,   133,   272,
       0,   260,   285,   183,   270,   291,     0,   273
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-186))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       8,    72,    90,    87,   165,   157,    14,     5,   111,    95,
     112,   113,   114,   198,    53,    27,     4,     5,     6,     7,
     111,    12,    12,   114,    95,    27,     5,   111,   114,   111,
     114,     4,     5,     6,     7,    69,    12,    45,    46,     4,
       5,     6,     7,   134,    52,   147,   198,    49,    56,   137,
     134,   203,    12,   155,    88,    12,   241,   159,   160,   161,
     162,   163,   153,   154,     4,     5,     6,     7,    12,   153,
     154,    59,    84,    64,    64,    49,   167,    85,     4,     5,
       6,     7,    84,   167,   245,    93,   238,    60,    64,   241,
      17,    15,     4,     5,     6,     7,     5,   185,   186,   201,
       4,     5,     6,     7,    64,     5,   208,     5,    44,   107,
      78,    85,    77,    49,   266,   104,     6,   105,   106,    43,
      20,    48,   113,   113,   112,    99,   115,    51,    17,   213,
      57,   233,   105,   106,    10,    46,    47,   113,    63,   112,
     105,   106,    42,    62,    63,    17,   112,   112,   105,   106,
     107,   108,    95,     4,     5,     6,     7,   112,    34,    48,
     114,   105,   106,   107,   108,    44,   257,   269,    57,    69,
      59,     5,   112,   257,     0,     1,    48,     8,     9,   105,
     106,    62,    63,    91,    95,    57,   112,    59,    88,   107,
     108,   275,   280,   105,   106,    21,   113,   114,    24,   104,
     112,   105,   106,    20,   292,    31,    32,    33,   112,    60,
      36,   113,   114,    30,   113,   114,   105,   106,   107,   108,
     112,    52,   230,    49,   113,    51,   113,   114,   177,   178,
     179,   113,   114,   105,   106,   107,   108,    82,   112,    90,
      55,    86,    59,     4,     5,     6,     7,    92,   113,   114,
      55,    77,   104,    79,   113,   114,   112,    74,   107,   108,
       5,    92,   112,    89,     4,     5,     6,     7,   276,   218,
     219,   220,   221,   112,   100,   112,   102,   103,   113,   114,
     105,   106,   107,   108,   113,   114,   131,    18,   113,   105,
     106,   107,   108,   112,   139,   113,   114,   113,   105,   106,
     107,   108,   105,   106,   107,   108,     6,   115,    12,    37,
     112,     5,   113,   112,    60,     5,   113,    77,    74,   115,
     114,   112,    55,   113,   112,   139,   113,    47,    97,   242,
      -1,   228,   273,   131,   241,   285,    -1,   243
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   117,     0,     1,    21,    24,    31,    32,    33,    36,
      49,    51,    77,    79,    89,   100,   102,   103,   118,   119,
     120,   131,   133,   135,   136,   137,   144,   158,   162,   170,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     111,     5,   172,    27,    49,    84,    44,    49,     5,   128,
     128,    27,    84,   171,    62,    63,    53,    10,    34,   163,
      49,    85,    99,   128,   172,    62,    63,   111,   172,     5,
     134,   128,   128,   134,   172,   128,   128,     5,   107,   127,
     129,   164,    78,     6,   132,    63,   112,    95,   145,   146,
     112,   138,   114,    44,   129,   159,   160,   128,    20,    42,
      69,    88,   121,   122,   123,   126,   129,     4,     5,     6,
       7,    59,   105,   106,   112,   143,   147,   148,   149,   150,
     151,   153,   155,   157,   169,   127,    91,   139,   129,   128,
     104,   114,   145,   138,   112,    55,    55,   112,   113,   114,
       8,     9,    52,    92,   130,   115,   147,   112,   157,   169,
     157,   147,   157,    12,    64,    17,    48,    57,    59,   105,
     106,   107,   108,   104,   113,   112,    46,    47,   145,   165,
     166,   168,     4,     5,     6,     7,    60,   105,   106,   112,
     141,   142,   161,   160,   147,   112,   112,   127,   122,   112,
     124,     5,   157,   113,   113,   147,   147,   157,   112,     5,
     155,    17,    48,    57,   157,   157,   157,   157,   112,   156,
     157,   140,   141,    18,   147,   161,   161,   161,   105,   106,
     107,   108,   113,   127,   127,   113,     6,    20,    30,    59,
      74,   125,   115,    12,   112,   154,   155,   156,    37,   152,
     157,   112,   155,    77,   113,   114,     5,   167,   169,   113,
     161,   161,   161,   161,   113,   113,   113,   112,    60,    90,
     142,    60,   128,     5,   157,   113,   114,   113,   155,    12,
     154,   156,   152,   163,   141,   114,    74,   147,    69,    88,
     112,   155,   157,   113,   113,   164,   169,   128,   113,    55,
     127,   165,   112,   113,   113,   127,   113
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

  case 26:

/* Line 1806 of yacc.c  */
#line 119 "Parser/yparser.ypp"
    {
			dbOps->createTable((yyvsp[(3) - (6)].sval),globalColumnNameList,globalColumnDatatypeList,globalColumnDatasizeList);
			cout<<"Table "<<(yyvsp[(3) - (6)].sval)<<" created successfully with "<<globalColumnNameList.size()<<" column(s)!"<<endl;
			globalColumnNameList.clear();
			globalColumnDatatypeList.clear();
			globalColumnDatasizeList.clear();
		}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 178 "Parser/yparser.ypp"
    { 
				globalColumnNameList.push_back( CommonUtil::char_to_string((yyvsp[(1) - (1)].sval)) );
			}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 185 "Parser/yparser.ypp"
    { globalColumnDatatypeList.push_back(CommonUtil::int_to_string(DataTypeLookup::getType((yyvsp[(1) - (4)].sval))));
		  globalColumnDatasizeList.push_back((yyvsp[(3) - (4)].sval)); 
		}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 189 "Parser/yparser.ypp"
    { globalColumnDatatypeList.push_back(CommonUtil::int_to_string(DataTypeLookup::getType((yyvsp[(1) - (1)].sval))));
	      globalColumnDatasizeList.push_back(CommonUtil::int_to_string(FieldLengthLookup::getType((yyvsp[(1) - (1)].sval)))); 
		}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 193 "Parser/yparser.ypp"
    { globalColumnDatatypeList.push_back(CommonUtil::int_to_string(DataTypeLookup::getType((yyvsp[(1) - (1)].sval))));
		  globalColumnDatasizeList.push_back(CommonUtil::int_to_string(FieldLengthLookup::getType((yyvsp[(1) - (1)].sval)))); 
		}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 197 "Parser/yparser.ypp"
    { globalColumnDatatypeList.push_back(CommonUtil::int_to_string(DataTypeLookup::getType((yyvsp[(1) - (1)].sval)))); 
		  globalColumnDatasizeList.push_back(CommonUtil::int_to_string(FieldLengthLookup::getType((yyvsp[(1) - (1)].sval))));
		}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 205 "Parser/yparser.ypp"
    {
		if(dbSize==0)
			dbOps->createDatabase((yyvsp[(3) - (4)].sval));
		else
			{dbOps->createDatabase((yyvsp[(3) - (4)].sval),dbSize);}
		cout<<"Database created successfully!"<<endl;
		dbSize=0;
		}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 217 "Parser/yparser.ypp"
    {
		dbSize=CommonUtil::string_to_int((yyvsp[(1) - (1)].sval));
		}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 223 "Parser/yparser.ypp"
    {
			dbOps->createIndex((yyvsp[(3) - (6)].sval),(yyvsp[(5) - (6)].sval),globalColumnNameList);
			globalColumnNameList.clear();
		}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 234 "Parser/yparser.ypp"
    {
			dbOps->deleteIndex((yyvsp[(3) - (3)].sval));
		}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 239 "Parser/yparser.ypp"
    {
			dbOps->listIndex();
		}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 244 "Parser/yparser.ypp"
    {
			dbOps->insertIntoTable((yyvsp[(3) - (5)].sval),globalColumnValueList); 
			cout<<"Inserted 1 row successfully!"<<endl;
        	globalColumnValueList.clear();
		}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 270 "Parser/yparser.ypp"
    { 
			globalColumnValueList.push_back((yyvsp[(1) - (1)].sval));
		}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 273 "Parser/yparser.ypp"
    { 
			globalColumnValueList.push_back((yyvsp[(1) - (1)].sval));
		}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 276 "Parser/yparser.ypp"
    { 
			globalColumnValueList.push_back((yyvsp[(1) - (1)].sval));
		}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 279 "Parser/yparser.ypp"
    { 
			globalColumnValueList.push_back((yyvsp[(1) - (1)].sval));
		}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 285 "Parser/yparser.ypp"
    { 
			WhereExpressionElement whereExpr(WhereExpressionElement::LITERAL_TYPE,(yyvsp[(1) - (1)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 289 "Parser/yparser.ypp"
    { 
			WhereExpressionElement whereExpr(WhereExpressionElement::LITERAL_TYPE,(yyvsp[(1) - (1)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 293 "Parser/yparser.ypp"
    { 
			WhereExpressionElement whereExpr(WhereExpressionElement::LITERAL_TYPE,(yyvsp[(1) - (1)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 297 "Parser/yparser.ypp"
    { 
			WhereExpressionElement whereExpr(WhereExpressionElement::LITERAL_TYPE,(yyvsp[(1) - (1)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 304 "Parser/yparser.ypp"
    {
		dbOps->deleteFromTable((yyvsp[(3) - (4)].sval),globalWhereList); 
       	globalColumnNameList.clear();
       	globalColumnValueList.clear();
		globalWhereList.clear();
		
	}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 325 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::OPERATOR_TYPE,"OR");
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 329 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::OPERATOR_TYPE,"OR");
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 333 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::OPERATOR_TYPE,"OR");
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 349 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::OPERATOR_TYPE,(yyvsp[(2) - (3)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 353 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::OPERATOR_TYPE,(yyvsp[(2) - (3)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 418 "Parser/yparser.ypp"
    {
			dbOps->updateTable((yyvsp[(2) - (5)].sval),globalColumnNameList,globalColumnValueList,globalWhereList);
        	globalColumnNameList.clear();
        	globalColumnValueList.clear();
			globalWhereList.clear();
		}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 453 "Parser/yparser.ypp"
    {
			dbOps->selectAllFromTable((yyvsp[(5) - (6)].sval),globalColumnNameList,globalWhereList);
        	globalColumnNameList.clear();
        	globalColumnValueList.clear();
			globalWhereList.clear();
		}
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 496 "Parser/yparser.ypp"
    {
			WhereExpressionElement whereExpr(WhereExpressionElement::IDENTIFIER_TYPE,(yyvsp[(1) - (1)].sval));
			globalWhereList.push_back(whereExpr);
		}
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 510 "Parser/yparser.ypp"
    {
			dbOps->dropTable((yyvsp[(2) - (2)].sval));
		}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 521 "Parser/yparser.ypp"
    {cout<<"DESCRIBE TABLE "<<endl<<endl;}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 525 "Parser/yparser.ypp"
    {dbOps->listDatabases();}
    break;

  case 156:

/* Line 1806 of yacc.c  */
#line 529 "Parser/yparser.ypp"
    {dbOps->listTables();}
    break;

  case 157:

/* Line 1806 of yacc.c  */
#line 533 "Parser/yparser.ypp"
    {
		dbOps->openDatabase((yyvsp[(2) - (2)].sval));
	}
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 539 "Parser/yparser.ypp"
    {
		cout<<"Exiting..."<<endl;
		exit(-1);
	}
    break;

  case 159:

/* Line 1806 of yacc.c  */
#line 546 "Parser/yparser.ypp"
    {
		buffManager->setInitCache(true);
		cout<<"Cache mode on"<<endl;
	}
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 553 "Parser/yparser.ypp"
    {
		buffManager->setInitCache(false);
		cout<<"Cache mode off"<<endl;
	}
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 560 "Parser/yparser.ypp"
    {
		cout<<"Index mode on"<<endl;
	}
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 566 "Parser/yparser.ypp"
    {
		cout<<"Index mode off"<<endl;
	}
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 572 "Parser/yparser.ypp"
    {
		buffManager->commitCache();
		cout<<(yyvsp[(2) - (2)].sval)<<" database committed to disk"<<endl;
	}
    break;



/* Line 1806 of yacc.c  */
#line 2187 "yparser.tab.cpp"
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
#line 578 "Parser/yparser.ypp"


void yyerror(const char *s) {
	cout << "\nERROR  MSG: " << s << endl;
}

