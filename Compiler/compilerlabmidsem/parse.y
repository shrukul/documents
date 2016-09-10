%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "symtab.h"
	extern int yyparse();
	extern char * yytext;
	extern FILE * yyin;
	extern int yylineno;
	extern int yyerror(const char *msg);
	int yydebug = 1;
	#define YYDEBUG 0
%}

%token INT FOR ELSE RETURN IF
%token LBRACE RBRACE LPAREN RPAREN SEMI COMMA
%token ADD ASSIGN
%token LT INCRE
%token IDENTIFIER FLOAT INTEGER

%start func
%%
func		: func decl LPAREN decl_seq RPAREN block
			| 
			| error {yyerror("not a func"); return 0;}
			;

decl		: type	IDENTIFIER
			| IDENTIFIER
			|
			;

type		: INT
			| error {yyerror("Not a valid statement"); return 0;}
			;

decl_seq	: decl_seq decl
			| decl
			|
			;

block		: LBRACE stmt_seq RBRACE
			;

stmt_seq	: stmt_seq stmt
			| stmt
			;

stmt		: decl_stmt
			| for_st
			| assign_st
			| block
			| if_st
			| RETURN INTEGER SEMI
			| error {yyerror("Not a valid statement"); return 0;}
			;

decl_stmt	: type decl_seq SEMI
			;

decl_seq	: decl_seq COMMA declr
			| declr
			;

declr		: IDENTIFIER
			| IDENTIFIER ASSIGN INTEGER
			;

for_st		: FOR LPAREN decl_seq SEMI cond SEMI expr RPAREN block
			| FOR LPAREN decl_seq SEMI cond SEMI expr RPAREN stmt
			;

cond		: expr LT expr
			;

expr		: expr ADD expr
			| INCRE
			| IDENTIFIER
			;

assign_st	: IDENTIFIER ASSIGN expr SEMI
			; 

if_st		: IF LPAREN cond RPAREN block
			| IF LPAREN cond RPAREN block ELSE block
			;

%%

int main(int argc, char *argv[])
{
	FILE *fp = fopen(argv[1], "r");
	
	if(!fp)
	 {
		printf("File not Found");
		exit(0);
	 }

	yyin = fp;
	symDump();
	int flag = yyparse();
	symDump();
}

yywrap()
{
	return 1;
}

int yyerror(const char *msg)
{
	printf("Error : %s line : %d\n",msg,yylineno);
	symDump();
	exit (0);
}
