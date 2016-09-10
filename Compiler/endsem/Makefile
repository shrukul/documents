CC=cc
LEX=lex
YACC=yacc 

YFLAGS=-d

lex: lex.yy.c y.tab.c
	$(CC) lex.yy.c y.tab.c

y.tab.c: parse.y
	$(YACC) $(YFLAGS) parse.y

lex.yy.c: lex.l
	$(LEX) lex.l

clean: 
	rm -rf *.o *.out lex.yy.c scan
