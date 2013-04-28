/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     LPAREN = 258,
     RPAREN = 259,
     COMMA = 260,
     ASSIGN = 261,
     LAPAREN = 262,
     RAPAREN = 263,
     IMPORTANCE = 264,
     IF = 265,
     RETURN = 266,
     AND = 267,
     OR = 268,
     NOT = 269,
     LT = 270,
     GT = 271,
     LE = 272,
     GE = 273,
     EQ = 274,
     START = 275,
     END = 276,
     PRINT = 277,
     PRINTVAR = 278,
     NAME = 279,
     NUMBER = 280,
     FNAME = 281,
     TEXT = 282,
     PLUS = 283,
     MINUS = 284,
     DIVIDE = 285,
     MULTIPLY = 286,
     UMINUS = 287
   };
#endif
/* Tokens.  */
#define LPAREN 258
#define RPAREN 259
#define COMMA 260
#define ASSIGN 261
#define LAPAREN 262
#define RAPAREN 263
#define IMPORTANCE 264
#define IF 265
#define RETURN 266
#define AND 267
#define OR 268
#define NOT 269
#define LT 270
#define GT 271
#define LE 272
#define GE 273
#define EQ 274
#define START 275
#define END 276
#define PRINT 277
#define PRINTVAR 278
#define NAME 279
#define NUMBER 280
#define FNAME 281
#define TEXT 282
#define PLUS 283
#define MINUS 284
#define DIVIDE 285
#define MULTIPLY 286
#define UMINUS 287




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 30 "parser.y"
{
  double double_type;
  vector vector_type;
  symbol *symbp_type;
  string string_type;
}
/* Line 1529 of yacc.c.  */
#line 120 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

