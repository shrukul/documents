all: compiler

compiler: parser lexer
	gcc -Wall -o compiler ast.c print.c lex.yy.c parser.tab.c -lfl

lexer: lexer.l
	flex lexer.l

parser: parser.y
	bison -d parser.y

clean:
	rm lex.yy.c parser.tab.c parser.tab.h compiler
