CC=gcc -mpentium
CFLAGS=-O6
LDFLAGS=-s -lm
LEX=flex -Cfa
YACC=bison -y -d

OBJS=y.tab.o lex.yy.o main.o radcalcdir2.o data.o
EXEC=cfparser

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(EXEC)

y.tab.c: parser.y func.c defs.h
	$(YACC) $<

lex.yy.c: lexer.l defs.h
	$(LEX) $<
