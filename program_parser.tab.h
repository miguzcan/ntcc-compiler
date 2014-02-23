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
     NUMBER = 258,
     INT = 259,
     NAME = 260,
     INVOCNAME = 261,
     DEF = 262,
     SYSTEM = 263,
     TELL = 264,
     WHEN = 265,
     DO = 266,
     LOCAL = 267,
     IN = 268,
     NEXT = 269,
     UNLESS = 270,
     WEVER = 271,
     SKIP = 272,
     ABORT = 273,
     NOT = 274,
     EXISTS = 275,
     ARROW = 276,
     STAR = 277,
     PAR = 278,
     TU = 279,
     FD = 280,
     XRI = 281,
     EQ = 282,
     SQRT = 283,
     TIMES = 284,
     PLUS = 285,
     SIN = 286,
     COS = 287,
     TAN = 288,
     ABS = 289,
     SQUARE = 290,
     BEG = 291,
     END = 292,
     ASSIGN = 293,
     LESS = 294,
     LEQ = 295,
     EQUAL = 296,
     DIFFERENT = 297,
     GEQXRI = 298,
     GTXRI = 299,
     NEXRI = 300,
     LTXRI = 301,
     LEQXRI = 302,
     GREATER = 303,
     GEQ = 304,
     DOMVAR = 305,
     ALLVARS = 306,
     DOMALLVARS = 307,
     DEFCS = 308
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 193 "program_parser.y"

  double real;
  int integer;
  char* text;
  char* id;




/* Line 2068 of yacc.c  */
#line 113 "program_parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


