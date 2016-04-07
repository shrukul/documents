default: clear yacc -d -v --debug parse.y lex -l scan.l gcc -o cfc symtab.c lex.yy.c y.tab.c clean: $(RM) cfc *.o lex.yy.c parse.tab.c y.tab.h y.output dump.symtab
