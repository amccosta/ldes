
/*  A Bison parser, made from parser.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define LPAREN  257
#define RPAREN  258
#define COMMA 259
#define ASSIGN  260
#define LAPAREN 261
#define RAPAREN 262
#define IMPORTANCE  263
#define IF  264
#define RETURN  265
#define AND 266
#define OR  267
#define NOT 268
#define LT  269
#define GT  270
#define LE  271
#define GE  272
#define EQ  273
#define START 274
#define END 275
#define PRINT 276
#define PRINTVAR  277
#define NAME  278
#define NUMBER  279
#define FNAME 280
#define TEXT  281
#define MINUS 282
#define PLUS  283
#define MULTIPLY  284
#define DIVIDE  285
#define UMINUS  286

#line 1 "parser.y"

#include "defs.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ZERO(x) (fabs(x) < TOL)
#define LEVEL_MAX 16

char true[LEVEL_MAX];
char level;
double result;
int yylinecount, yyinlinecount;
char end_reached;
char parse_error;

extern char *yytext;
extern void yyerror(char *);
extern void yyerror2(char *, char *);
extern float radcalcdir(char *, float, float, float,
                        float, float, float, float,
                        char *, float, float, float);

#define if_PROCEED(level) \
if (parse_error) YYABORT; if (level >= 0 && true[level])

#line 29 "parser.y"
typedef union {
  double double_type;
  vector vector_type;
  symbol *symbp_type;
  string string_type;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif

#define YYFINAL   132
#define YYFLAG    -32768
#define YYNTBASE  33

#define YYTRANSLATE(x) ((unsigned)(x) <= 286 ? yytranslate[x] : 41)

static const char yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,    10,    12,    16,    22,    23,    30,
    31,    40,    45,    50,    55,    58,    60,    62,    66,    70,
    74,    78,    82,    86,    90,    93,    97,   101,   105,   109,
   112,   116,   121,   128,   137,   142,   149,   168,   189,   216,
   218,   226,   230,   234,   238,   243
};

static const short yyrhs[] = {    38,
     0,    34,    38,     0,    35,     0,    34,    35,     0,    38,
     0,    24,     6,    39,     0,    24,     6,     7,    40,     8,
     0,     0,    10,     3,    39,     4,    36,    35,     0,     0,
    10,     3,    39,     4,    37,    20,    34,    21,     0,    22,
     3,    27,     4,     0,    23,     3,    39,     4,     0,    23,
     7,    40,     8,     0,    11,    39,     0,    25,     0,    24,
     0,    39,    15,    39,     0,    39,    16,    39,     0,    39,
    17,    39,     0,    39,    18,    39,     0,    39,    19,    39,
     0,    39,    12,    39,     0,    39,    13,    39,     0,    14,
    39,     0,    39,    29,    39,     0,    39,    28,    39,     0,
    39,    30,    39,     0,    39,    31,    39,     0,    28,    39,
     0,     3,    39,     4,     0,    24,     3,    39,     4,     0,
    24,     3,    39,     5,    39,     4,     0,    24,     3,    39,
     5,    39,     5,    39,     4,     0,    24,     7,    40,     8,
     0,    24,     7,    40,     5,    40,     8,     0,     9,     3,
    26,     5,    39,     5,    39,     5,    39,     5,    39,     5,
    39,     5,    39,     5,    39,     4,     0,     9,     3,    26,
     5,    39,     5,    39,     5,    39,     5,    39,     5,    39,
     5,    39,     5,    39,     5,    26,     4,     0,     9,     3,
    26,     5,    39,     5,    39,     5,    39,     5,    39,     5,
    39,     5,    39,     5,    39,     5,    26,     5,    39,     5,
    39,     5,    39,     4,     0,    24,     0,     3,    39,     5,
    39,     5,    39,     4,     0,    40,    29,    40,     0,    40,
    28,    40,     0,    40,    30,    39,     0,    24,     7,    40,
     8,     0,    24,     7,    40,     5,    40,     8,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    54,    56,    59,    61,    64,    66,    74,    84,    90,    93,
    98,   102,   110,   114,   120,   131,   133,   143,   147,   151,
   155,   159,   163,   167,   171,   175,   179,   183,   187,   195,
   199,   203,   216,   229,   242,   255,   268,   282,   296,   313,
   327,   336,   345,   354,   363,   382
};
#endif

#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","LPAREN",
"RPAREN","COMMA","ASSIGN","LAPAREN","RAPAREN","IMPORTANCE","IF","RETURN","AND",
"OR","NOT","LT","GT","LE","GE","EQ","START","END","PRINT","PRINTVAR","NAME",
"NUMBER","FNAME","TEXT","MINUS","PLUS","MULTIPLY","DIVIDE","UMINUS","program",
"statement_list","statement","@1","@2","return_statement","expression","vector_expression", NULL
};
#endif

static const short yyr1[] = {     0,
    33,    33,    34,    34,    35,    35,    35,    36,    35,    37,
    35,    35,    35,    35,    38,    39,    39,    39,    39,    39,
    39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
    39,    39,    39,    39,    39,    39,    39,    39,    39,    40,
    40,    40,    40,    40,    40,    40
};

static const short yyr2[] = {     0,
     1,     2,     1,     2,     1,     3,     5,     0,     6,     0,
     8,     4,     4,     4,     2,     1,     1,     3,     3,     3,
     3,     3,     3,     3,     2,     3,     3,     3,     3,     2,
     3,     4,     6,     8,     4,     6,    18,    20,    26,     1,
     7,     3,     3,     3,     4,     6
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     0,     3,     5,     0,     0,
     0,     0,    17,    16,     0,    15,     0,     0,     0,     0,
     4,     5,     0,     0,     0,    25,     0,     0,    30,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    40,     0,     0,     6,     8,    31,     0,
     0,     0,    23,    24,    18,    19,    20,    21,    22,    27,
    26,    28,    29,    12,    13,     0,     0,    14,     0,     0,
     0,     0,     0,     0,     0,    32,     0,     0,    35,     0,
     0,    43,    42,    44,     7,     9,     5,     0,     0,     0,
     0,     0,     0,    45,     0,     0,    33,     0,    36,     0,
     0,    11,     0,     0,     0,    46,     0,    34,    41,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    37,     0,
     0,    38,     0,     0,     0,     0,     0,     0,    39,     0,
     0,     0
};

static const short yydefgoto[] = {   130,
     6,     7,    73,    74,    87,    16,    45
};

static const short yypact[] = {   509,
    10,    45,    13,     5,     1,   509,-32768,    35,    45,    45,
    46,    45,    12,-32768,    45,   475,    23,    45,    62,    33,
-32768,    51,   167,   187,    29,-32768,    45,    62,-32768,    45,
    45,    45,    45,    45,    45,    45,    45,    45,    45,    45,
    60,   207,    45,    81,    52,    62,   475,    54,-32768,    85,
   107,     9,    99,    99,   260,   260,   260,   260,   260,     2,
     2,-32768,-32768,-32768,-32768,   287,    62,-32768,    62,    62,
    45,    55,   509,    72,    45,-32768,    45,    62,-32768,    45,
    48,    63,    63,   495,-32768,-32768,-32768,   509,   307,   127,
    67,   327,    62,-32768,   506,    45,-32768,    45,-32768,    45,
    71,-32768,   347,   227,   247,-32768,    45,-32768,-32768,   367,
    45,   387,    45,   407,    45,   427,    45,   147,-32768,    77,
    41,-32768,    45,   447,    45,   467,    45,   267,-32768,   105,
   109,-32768
};

static const short yypgoto[] = {-32768,
    19,    -1,-32768,-32768,     4,    -9,   -26
};

#define YYLAST    533

static const short yytable[] = {    23,
    24,    52,    26,     8,    21,    29,    20,    18,    42,    22,
    47,    19,     9,    78,    27,    17,    79,    51,    28,    72,
    53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
    63,    39,    40,    66,    -1,    10,    69,    70,    71,    46,
    81,    11,    82,    83,   122,   123,    12,    10,    25,    41,
    -2,    91,    93,    11,    50,    94,    13,    14,    12,    68,
    15,    84,    85,    64,    43,    89,   101,    90,    13,    14,
    92,    86,    15,   -10,    99,    69,    70,    71,   106,    69,
    70,    71,    69,    70,    71,    44,   103,    67,   104,    75,
   105,    88,    71,    21,    69,    70,    71,   110,    69,    70,
    71,   112,   121,   114,   131,   116,    95,   118,   132,     0,
    76,    77,     0,   124,     0,   126,     0,   128,    30,    31,
     0,    32,    33,    34,    35,    36,    37,    38,    39,    40,
    97,    98,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
   119,   120,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
    48,     0,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
    49,     0,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
    65,     0,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
   108,     0,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
   109,     0,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
   129,    30,    31,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,    37,    38,    39,
    40,    80,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
     0,    96,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
     0,   100,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
     0,   107,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
     0,   111,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
     0,   113,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
     0,   115,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
     0,   117,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
     0,   125,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,     0,     0,     0,     0,
     0,   127,     0,     0,    37,    38,    39,    40,    30,    31,
     0,    32,    33,    34,    35,    36,    30,    31,     0,    32,
    33,    34,    35,    36,    37,    38,    39,    40,     0,     0,
     0,     0,    37,    38,    39,    40,    30,    31,     0,    32,
    33,    34,    35,    36,     0,     1,     2,     0,     1,     2,
     0,     0,     0,     0,     0,    40,   102,     3,     4,     5,
     3,     4,     5
};

static const short yycheck[] = {     9,
    10,    28,    12,     0,     6,    15,     6,     3,    18,     6,
    20,     7,     3,     5,     3,     3,     8,    27,     7,    46,
    30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
    40,    30,    31,    43,     0,     3,    28,    29,    30,     7,
    67,     9,    69,    70,     4,     5,    14,     3,     3,    27,
     0,    78,     5,     9,    26,     8,    24,    25,    14,     8,
    28,    71,     8,     4,     3,    75,    93,    77,    24,    25,
    80,    73,    28,    20,     8,    28,    29,    30,     8,    28,
    29,    30,    28,    29,    30,    24,    96,     7,    98,     5,
   100,    20,    30,    95,    28,    29,    30,   107,    28,    29,
    30,   111,    26,   113,     0,   115,    88,   117,     0,    -1,
     4,     5,    -1,   123,    -1,   125,    -1,   127,    12,    13,
    -1,    15,    16,    17,    18,    19,    28,    29,    30,    31,
     4,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
     4,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
     4,    -1,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
     4,    -1,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
     4,    -1,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
     4,    -1,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
     4,    -1,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
     4,    12,    13,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    28,    29,    30,
    31,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
    -1,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
    -1,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
    -1,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
    -1,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
    -1,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
    -1,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
    -1,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
    -1,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
    -1,     5,    -1,    -1,    28,    29,    30,    31,    12,    13,
    -1,    15,    16,    17,    18,    19,    12,    13,    -1,    15,
    16,    17,    18,    19,    28,    29,    30,    31,    -1,    -1,
    -1,    -1,    28,    29,    30,    31,    12,    13,    -1,    15,
    16,    17,    18,    19,    -1,    10,    11,    -1,    10,    11,
    -1,    -1,    -1,    -1,    -1,    31,    21,    22,    23,    24,
    22,    23,    24
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/lib/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
   instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
     and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok   (yyerrstatus = 0)
#define yyclearin (yychar = YYEMPTY)
#define YYEMPTY   -2
#define YYEOF   0
#define YYACCEPT  goto yyacceptlab
#define YYABORT   goto yyabortlab
#define YYERROR   goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL    goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                \
  if (yychar == YYEMPTY && yylen == 1)        \
    { yychar = (token), yylval = (value);     \
      yychar1 = YYTRANSLATE (yychar);       \
      YYPOPSTACK;           \
      goto yybackup;            \
    }               \
  else                \
    { yyerror ("syntax error: cannot back up"); YYERROR; }  \
while (0)

#define YYTERROR  1
#define YYERRCODE 256

#ifndef YYPURE
#define YYLEX   yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX   yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX   yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX   yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX   yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int yychar;     /*  the lookahead symbol    */
YYSTYPE yylval;     /*  the semantic value of the   */
        /*  lookahead symbol      */

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;     /*  location data for the lookahead */
        /*  symbol        */
#endif

int yynerrs;      /*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;      /*  nonzero means print parse trace */
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks */

#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1    /* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)  __builtin_memcpy(TO,FROM,COUNT)
#else       /* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/lib/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;  /*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;    /*  lookahead token as an internal (translated) token number */

  short yyssa[YYINITDEPTH]; /*  the state stack     */
  YYSTYPE yyvsa[YYINITDEPTH]; /*  the semantic value stack    */

  short *yyss = yyssa;    /*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;  /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH]; /*  the location stack      */
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;    /*  the variable used to return   */
        /*  semantic values from the action */
        /*  routines        */

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;   /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
   the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
   but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
     &yyss1, size * sizeof (*yyssp),
     &yyvs1, size * sizeof (*yyvsp),
     &yyls1, size * sizeof (*yylsp),
     &yystacksize);
#else
      yyoverflow("parser stack overflow",
     &yyss1, size * sizeof (*yyssp),
     &yyvs1, size * sizeof (*yyvsp),
     &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
  {
    yyerror("parser stack overflow");
    if (yyfree_stacks)
      {
        free (yyss);
        free (yyvs);
#ifdef YYLSP_NEEDED
        free (yyls);
#endif
      }
    return 2;
  }
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
  yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
       size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
       size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
       size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
  fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
  YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
  fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)    /* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;   /* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
  fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
  {
    fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
    /* Give the individual parser a way to print the precise meaning
       of a token, for further debugging info.  */
#ifdef YYPRINT
    YYPRINT (stderr, yychar, yylval);
#endif
    fprintf (stderr, ")\n");
  }
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
  goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
         yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
  fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 6:
#line 67 "parser.y"
{
    if_PROCEED(level)
    {
      yyvsp[-2].symbp_type->value1 = yyvsp[0].double_type;
      yyvsp[-2].symbp_type->type = SCALAR_TYPE;
    }
  ;
    break;}
case 7:
#line 75 "parser.y"
{
    if_PROCEED(level)
    {
      yyvsp[-4].symbp_type->value1 = yyvsp[-1].vector_type.x;
      yyvsp[-4].symbp_type->value2 = yyvsp[-1].vector_type.y;
      yyvsp[-4].symbp_type->value3 = yyvsp[-1].vector_type.z;
      yyvsp[-4].symbp_type->type = VECTOR_TYPE;
    }
  ;
    break;}
case 8:
#line 85 "parser.y"
{
    if (++level == LEVEL_MAX) yyerror("too many levels");
    true[level] = true[level - 1] & !ZERO(yyvsp[-1].double_type);
  ;
    break;}
case 9:
#line 90 "parser.y"
{
    level--;
  ;
    break;}
case 10:
#line 94 "parser.y"
{
    if (++level == LEVEL_MAX) yyerror("too many levels");
    true[level] = true[level - 1] & !ZERO(yyvsp[-1].double_type);
  ;
    break;}
case 11:
#line 99 "parser.y"
{
    level--;
  ;
    break;}
case 12:
#line 103 "parser.y"
{
    if_PROCEED(level)
    {
      if (yyvsp[-1].string_type && yyvsp[-1].string_type[0]) fprintf(stderr, "%s", yyvsp[-1].string_type);
      else fprintf(stderr, "\n");
    }
  ;
    break;}
case 13:
#line 111 "parser.y"
{
    if_PROCEED(level) fprintf(stderr, "%g ", yyvsp[-1].double_type);
  ;
    break;}
case 14:
#line 115 "parser.y"
{
    if_PROCEED(level) fprintf(stderr, "%g %g %g ", yyvsp[-1].vector_type.x, yyvsp[-1].vector_type.y, yyvsp[-1].vector_type.z);
  ;
    break;}
case 15:
#line 122 "parser.y"
{
    if_PROCEED(level)
    {
      result = yyvsp[0].double_type;
      level = -1;
    }
  ;
    break;}
case 17:
#line 134 "parser.y"
{
    if_PROCEED(level)
    {
      if (yyvsp[0].symbp_type->type == SCALAR_TYPE)
        yyval.double_type = yyvsp[0].symbp_type->value1;
      else
        yyerror2("non-scalar variable", yyvsp[0].symbp_type->name);
    }
  ;
    break;}
case 18:
#line 144 "parser.y"
{
    if_PROCEED(level) yyval.double_type = yyvsp[-2].double_type < yyvsp[0].double_type;
  ;
    break;}
case 19:
#line 148 "parser.y"
{
    if_PROCEED(level) yyval.double_type = yyvsp[-2].double_type > yyvsp[0].double_type;
  ;
    break;}
case 20:
#line 152 "parser.y"
{
    if_PROCEED(level) yyval.double_type = yyvsp[-2].double_type <= yyvsp[0].double_type;
  ;
    break;}
case 21:
#line 156 "parser.y"
{
    if_PROCEED(level) yyval.double_type = yyvsp[-2].double_type >= yyvsp[0].double_type;
  ;
    break;}
case 22:
#line 160 "parser.y"
{
    if_PROCEED(level) yyval.double_type = ZERO(yyvsp[-2].double_type - yyvsp[0].double_type) ? 1 : 0;
  ;
    break;}
case 23:
#line 164 "parser.y"
{
    if_PROCEED(level) yyval.double_type = yyvsp[-2].double_type && yyvsp[0].double_type;
  ;
    break;}
case 24:
#line 168 "parser.y"
{
    if_PROCEED(level) yyval.double_type = yyvsp[-2].double_type || yyvsp[0].double_type;
  ;
    break;}
case 25:
#line 172 "parser.y"
{
    if_PROCEED(level) yyval.double_type = !yyvsp[0].double_type;
  ;
    break;}
case 26:
#line 176 "parser.y"
{
    if_PROCEED(level) yyval.double_type = yyvsp[-2].double_type + yyvsp[0].double_type;
  ;
    break;}
case 27:
#line 180 "parser.y"
{
    if_PROCEED(level) yyval.double_type = yyvsp[-2].double_type - yyvsp[0].double_type;
  ;
    break;}
case 28:
#line 184 "parser.y"
{
    if_PROCEED(level) yyval.double_type = yyvsp[-2].double_type * yyvsp[0].double_type;
  ;
    break;}
case 29:
#line 188 "parser.y"
{
    if_PROCEED(level)
    {
      if (ZERO(yyvsp[0].double_type)) yyerror("divide by zero");
      else yyval.double_type = yyvsp[-2].double_type / yyvsp[0].double_type;
    }
  ;
    break;}
case 30:
#line 196 "parser.y"
{
    if_PROCEED(level) yyval.double_type = -yyvsp[0].double_type;
  ;
    break;}
case 31:
#line 200 "parser.y"
{
    if_PROCEED(level) yyval.double_type = yyvsp[-1].double_type;
  ;
    break;}
case 32:
#line 204 "parser.y"
{
    if_PROCEED(level)
    {
      if (yyvsp[-3].symbp_type->type == FUNCTION_TYPE && yyvsp[-3].symbp_type->funcptr)
        if (yyvsp[-3].symbp_type->args == 1)
          yyval.double_type = (yyvsp[-3].symbp_type->funcptr)(yyvsp[-1].double_type);
        else
          yyerror2("bad args in scalar function", yyvsp[-3].symbp_type->name);
      else
        yyerror2("non-scalar function", yyvsp[-3].symbp_type->name);
    }
  ;
    break;}
case 33:
#line 217 "parser.y"
{
    if_PROCEED(level)
    {
      if (yyvsp[-5].symbp_type->type == FUNCTION_TYPE && yyvsp[-5].symbp_type->funcptr)
        if (yyvsp[-5].symbp_type->args == 2)
          yyval.double_type = (yyvsp[-5].symbp_type->funcptr)(yyvsp[-3].double_type, yyvsp[-1].double_type);
        else
          yyerror2("bad args in scalar function", yyvsp[-5].symbp_type->name);
      else
        yyerror2("non-scalar function", yyvsp[-5].symbp_type->name);
    }
  ;
    break;}
case 34:
#line 230 "parser.y"
{
    if_PROCEED(level)
    {
      if (yyvsp[-7].symbp_type->type == FUNCTION_TYPE && yyvsp[-7].symbp_type->funcptr)
        if (yyvsp[-7].symbp_type->args == 3)
          yyval.double_type = (yyvsp[-7].symbp_type->funcptr)(yyvsp[-5].double_type, yyvsp[-3].double_type, yyvsp[-1].double_type);
        else
          yyerror2("bad args in scalar function", yyvsp[-7].symbp_type->name);
      else
        yyerror2("non-scalar function", yyvsp[-7].symbp_type->name);
    }
  ;
    break;}
case 35:
#line 243 "parser.y"
{
    if_PROCEED(level)
    {
      if (yyvsp[-3].symbp_type->type == FUNCTION_TYPE && yyvsp[-3].symbp_type->funcptr)
        if (yyvsp[-3].symbp_type->args == 1)
          yyval.double_type = (yyvsp[-3].symbp_type->funcptr)(&yyvsp[-1].vector_type);
        else
          yyerror2("bad args in vector function", yyvsp[-3].symbp_type->name);
      else
        yyerror2("non-vector function", yyvsp[-3].symbp_type->name);
    }
  ;
    break;}
case 36:
#line 256 "parser.y"
{
    if_PROCEED(level)
    {
      if (yyvsp[-5].symbp_type->type == FUNCTION_TYPE && yyvsp[-5].symbp_type->funcptr)
        if (yyvsp[-5].symbp_type->args == 2)
          yyval.double_type = (yyvsp[-5].symbp_type->funcptr)(&yyvsp[-3].vector_type, &yyvsp[-1].vector_type);
        else
          yyerror2("bad args in vector function", yyvsp[-5].symbp_type->name);
      else
        yyerror2("non-vector function", yyvsp[-5].symbp_type->name);
    }
  ;
    break;}
case 37:
#line 271 "parser.y"
{
    if_PROCEED(level)
    {
      yyval.double_type = radcalcdir(yyvsp[-15].string_type, yyvsp[-13].double_type, yyvsp[-11].double_type, yyvsp[-9].double_type, yyvsp[-7].double_type, yyvsp[-5].double_type, yyvsp[-3].double_type, yyvsp[-1].double_type, "", 0.0, 0.0, 0.0);
      if (yyval.double_type < 0)
      {
        yyval.double_type = 0;
        yyerror2("importance error related to", yyvsp[-15].string_type);
      }
    }
  ;
    break;}
case 38:
#line 285 "parser.y"
{
    if_PROCEED(level)
    {
      yyval.double_type = radcalcdir(yyvsp[-17].string_type, yyvsp[-15].double_type, yyvsp[-13].double_type, yyvsp[-11].double_type, yyvsp[-9].double_type, yyvsp[-7].double_type, yyvsp[-5].double_type, yyvsp[-3].double_type, yyvsp[-1].string_type, 0.0, 0.0, 0.0);
      if (yyval.double_type < 0)
      {
        yyval.double_type = 0;
        yyerror2("importance error related to", yyvsp[-17].string_type);
      }
    }
  ;
    break;}
case 39:
#line 300 "parser.y"
{
    if_PROCEED(level)
    {
      yyval.double_type = radcalcdir(yyvsp[-23].string_type, yyvsp[-21].double_type, yyvsp[-19].double_type, yyvsp[-17].double_type, yyvsp[-15].double_type, yyvsp[-13].double_type, yyvsp[-11].double_type, yyvsp[-9].double_type, yyvsp[-7].string_type, yyvsp[-5].double_type, yyvsp[-3].double_type, yyvsp[-1].double_type);
      if (yyval.double_type < 0)
      {
        yyval.double_type = 0;
        yyerror2("importance error related to", yyvsp[-23].string_type);
      }
    }
  ;
    break;}
case 40:
#line 315 "parser.y"
{
    if_PROCEED(level)
    {
      if (yyvsp[0].symbp_type->type == VECTOR_TYPE)
      {
        yyval.vector_type.x = yyvsp[0].symbp_type->value1;
        yyval.vector_type.y = yyvsp[0].symbp_type->value2;
        yyval.vector_type.z = yyvsp[0].symbp_type->value3;
      } else
        yyerror2("non-vector variable", yyvsp[0].symbp_type->name);
    }
  ;
    break;}
case 41:
#line 328 "parser.y"
{
    if_PROCEED(level)
    {
      yyval.vector_type.x = yyvsp[-5].double_type;
      yyval.vector_type.y = yyvsp[-3].double_type;
      yyval.vector_type.z = yyvsp[-1].double_type;
    }
  ;
    break;}
case 42:
#line 337 "parser.y"
{
    if_PROCEED(level)
    {
      yyval.vector_type.x = yyvsp[-2].vector_type.x + yyvsp[0].vector_type.x;
      yyval.vector_type.y = yyvsp[-2].vector_type.y + yyvsp[0].vector_type.y;
      yyval.vector_type.z = yyvsp[-2].vector_type.z + yyvsp[0].vector_type.z;
    }
  ;
    break;}
case 43:
#line 346 "parser.y"
{
    if_PROCEED(level)
    {
      yyval.vector_type.x = yyvsp[-2].vector_type.x - yyvsp[0].vector_type.x;
      yyval.vector_type.y = yyvsp[-2].vector_type.y - yyvsp[0].vector_type.y;
      yyval.vector_type.z = yyvsp[-2].vector_type.z - yyvsp[0].vector_type.z;
    }
  ;
    break;}
case 44:
#line 355 "parser.y"
{
    if_PROCEED(level)
    {
      yyval.vector_type.x = yyvsp[0].double_type * yyvsp[-2].vector_type.x;
      yyval.vector_type.y = yyvsp[0].double_type * yyvsp[-2].vector_type.y;
      yyval.vector_type.z = yyvsp[0].double_type * yyvsp[-2].vector_type.z;
    }
  ;
    break;}
case 45:
#line 364 "parser.y"
{
    if_PROCEED(level)
    {
      if (yyvsp[-3].symbp_type->type == FUNCTION_TYPE && yyvsp[-3].symbp_type->funcptr)
        if (yyvsp[-3].symbp_type->args == 2)
        {
          vector temp;

          (yyvsp[-3].symbp_type->funcptr)(&yyvsp[-1].vector_type, &temp);
          yyval.vector_type.x = temp.x;
          yyval.vector_type.y = temp.y;
          yyval.vector_type.z = temp.z;
        } else
          yyerror2("bad args in vector function", yyvsp[-3].symbp_type->name);
      else
        yyerror2("non-vector function", yyvsp[-3].symbp_type->name);
    }
  ;
    break;}
case 46:
#line 383 "parser.y"
{
    if_PROCEED(level)
    {
      if (yyvsp[-5].symbp_type->type == FUNCTION_TYPE && yyvsp[-5].symbp_type->funcptr)
        if (yyvsp[-5].symbp_type->args == 3)
        {
          vector temp;

          (yyvsp[-5].symbp_type->funcptr)(&yyvsp[-3].vector_type, &yyvsp[-1].vector_type, &temp);
          yyval.vector_type.x = temp.x;
          yyval.vector_type.y = temp.y;
          yyval.vector_type.z = temp.z;
        } else
          yyerror2("bad args in vector function", yyvsp[-5].symbp_type->name);
      else
        yyerror2("non-vector function", yyvsp[-5].symbp_type->name);
    }
  ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/lib/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
  fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
  {
    int size = 0;
    char *msg;
    int x, count;

    count = 0;
    /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
    for (x = (yyn < 0 ? -yyn : 0);
         x < (sizeof(yytname) / sizeof(char *)); x++)
      if (yycheck[x + yyn] == x)
        size += strlen(yytname[x]) + 15, count++;
    msg = (char *) malloc(size + 15);
    if (msg != 0)
      {
        strcpy(msg, "parse error");

        if (count < 5)
    {
      count = 0;
      for (x = (yyn < 0 ? -yyn : 0);
           x < (sizeof(yytname) / sizeof(char *)); x++)
        if (yycheck[x + yyn] == x)
          {
      strcat(msg, count == 0 ? ", expecting `" : " or `");
      strcat(msg, yytname[x]);
      strcat(msg, "'");
      count++;
          }
    }
        yyerror(msg);
        free(msg);
      }
    else
      yyerror ("parse error; also virtual memory exceeded");
  }
      else
#endif /* YYERROR_VERBOSE */
  yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
  YYABORT;

#if YYDEBUG != 0
      if (yydebug)
  fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;    /* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
  fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
  goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 402 "parser.y"

symbol *
symblook(char *name)
{
  char *p;
  symbol *sp;

  for (sp = symbol_table; sp < &symbol_table[SYMB_MAX]; sp++)
  {
    if (sp->name && !strcmp(sp->name, name)) return sp;
    if (!sp->name)
    {
      sp->name = strdup(name);
      if (!sp->name) yyerror("out of memory");
      return sp;
    }
  }
  yyerror("too many symbols");
}

void
yyerror2(char *message, char *data)
{
  char *p, *whole_message, *unknown = "(unknown?)";

  if (data) p = data;
  else p = unknown;
  whole_message = malloc(strlen(message) + strlen(p) + 4);
  if (!whole_message) yyerror("out of memory");
  sprintf(whole_message, "%s \"%s\"", message, p);
  yyerror(whole_message);
}

void
yyerror(char *message)
{
  if (yytext[0])
  {
    if (yyinlinecount > 1)
      fprintf(stderr, "error in line %d (instruction %d) reading \"%s\"",
        yylinecount, yyinlinecount, yytext);
    else
      fprintf(stderr, "error in line %d reading \"%s\"",
        yylinecount, yytext);
  } else
  {
    if (yyinlinecount > 1)
      fprintf(stderr, "error in line %d (instruction %d)",
        yylinecount, yyinlinecount);
    else
      fprintf(stderr, "error in line %d",
        yylinecount);
  }
  if (end_reached)
    fprintf(stderr, " [%s - missing return statement]\n", message);
  else
    fprintf(stderr, " [%s]\n", message);
  parse_error = 1;
}

void
addfunc(int n, char *name, double (*func)())
{
  symbol *sp = symblook(name);
  sp->type = FUNCTION_TYPE;
  sp->args = n;
  sp->funcptr = func;
}

#include "func.c"

void
addsymb(char *name, double value)
{
  symbol *sp = symblook(name);
  sp->type = SCALAR_TYPE;
  sp->value1 = value;
}

#include "symb.c"

extern FILE *yyin;

static char *last_name = 0;
static int last_n = 0;

int
evalcf(char *name, double cost, int n, double *param, double *value)
{
  int i;
  char var[5];

  if (n < 0)
  {
    n = -n;
    last_name = 0;
    last_n = 0;
  }

  if (n < 1 || n > 100) return 1;
  if (last_n && last_n != n) return 1;
  if (last_name && strcmp(last_name, name)) return 1;

  if (!last_name)
  {
    yyin = fopen(name, "r");
    if (!yyin) return 2;
  }

  sprintf(var, "x0");
  addsymb(var, cost);
  for (i = 0; i < n; i++)
  {
    sprintf(var, "x%d", i + 1);
    addsymb(var, param[i]);
  }

#ifdef WIN32
  srand(time(0));
#else
  srandom(time(0));
#endif
  true[level] = 1;

  if (!last_name)
  {
    define_symbols();
    define_functions();
  }

  level = 0;
  result = 0;
  end_reached = 0;
  parse_error = 0;
  yylinecount = 1;
  yyinlinecount = 1;

  if (yyparse())
  {
    if (!last_name && yyin) fclose(yyin);
    return 3;
  }
  if (!last_name && yyin) fclose(yyin);
  *value = result;
  last_n = n;
  last_name = name;
  return 0;
}
