/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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
/* Line 2068 of yacc.c  */
#line 12 "Parser/yparser.ypp"
YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 12 "Parser/yparser.ypp"

	int ival;
	char *sval;
	int subtok;



/* Line 2068 of yacc.c  */
#line 166 "yparser.tab.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


