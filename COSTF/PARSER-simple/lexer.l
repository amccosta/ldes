%{
#include "defs.h"
#include "y.tab.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EXIT_LEXER(message) \
do { fprintf(stderr, "%s in lexer\n", message); exit(99); } while (0)

extern int yylinecount, yyinlinecount;
extern char end_reached;
%}

%option noyywrap
%option never-interactive
%%

<<EOF>> {
    end_reached = 1;
    return 0;
}
"$" {
    end_reached = 1;
    return 0;
}

[ \t]+    ;

\n {
    yylinecount++;
    yyinlinecount = 1;
}
\; {
    yyinlinecount++;
}

\#|\% {
    int c;
    while ((c = input()) != '\n' && c != EOF);
    yylinecount++;
}

([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {
    yylval.double_type = atof(yytext);
    return NUMBER;
}

importance  { return IMPORTANCE; }
IMPORTANCE  { return IMPORTANCE; }
PRINTVAR  { return PRINTVAR; }
RETURN    { return RETURN; }
PRINT   { return PRINT; }
AND   { return AND; }
NOT   { return NOT; }
IF    { return IF; }
OR    { return OR; }
">="    { return GE; }
"<="    { return LE; }
"=="    { return EQ; }
"<"   { return LT; }
">"   { return GT; }
"="   { return ASSIGN; }
","   { return COMMA; }
"("   { return LPAREN; }
")"   { return RPAREN; }
"["   { return LAPAREN; }
"]"   { return RAPAREN; }
"+"   { return PLUS; }
"-"   { return MINUS; }
"*"   { return MULTIPLY; }
"/"   { return DIVIDE; }
"{"   { return START; }
"}"   { return END; }

[A-Za-z][A-Za-z0-9_]* {
    symbol *sp = symblook(yytext);
    yylval.symbp_type = sp;
    return NAME;
}

\"[A-Za-z0-9_\-\.]+\" {
    int l = yyleng - 2;
    strncpy(yylval.string_type, &yytext[1], l);
    yylval.string_type[l] = 0;
    return FNAME;
}
\'[^']*\' {
    int l = yyleng - 2;
    strncpy(yylval.string_type, &yytext[1], l);
    yylval.string_type[l] = 0;
    return TEXT;
}

.   { return yytext[0]; }
%%
