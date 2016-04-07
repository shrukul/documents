%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "symtab.h"

	extern char *yytext;
	extern FILE *yyin,*yyout;
	extern int yyparse();
	extern int yylineno;
	extern node;

	#define YYDEBUG 1
	int yydebug = 1;
%}
%union
{
	int number;
	char *name;
};

%token <node> IDENTIFIER
%token <number> INTEGER FLOAT
%token <number> IF ELSE EQ ASSIGN LPAREN RPAREN LBRACE RBRACE COMMA INT SEMI
%token <number> OR AND LE GE LT GR NE GT
%token <number> ADD MULT SUB DIV

%start func
%%
func		: func decl LPAREN decl_seq RPAREN block
			| func decl LPAREN decl_seq RPAREN SEMI
			|
			;

decl 		: decl_type IDENTIFIER {setType($2.name, 10)}
			;

decl_type 	: INT
			;

decl_seq	: decl_seq COMMA decl
			| decl
			|
			;

block		: LBRACE stmt_seq RBRACE
			;

stmt_seq	: stmt_seq stmt
			| stmt
			;

stmt 		: ifst
			| ass_st
			;

ass_st		: IDENTIFIER ASSIGN expr SEMI
			;

ifst		: IF LPAREN cond_seq RPAREN block ELSE block
			| IF LPAREN cond_seq RPAREN block
			;

cond_seq	: cond_seq lop cond_st
			| cond_st
			;

lop			: OR
			| AND
			;

cond_st		: expr op expr
			;

expr		: expr op expr
			| LPAREN expr RPAREN
			| IDENTIFIER
			;

condo 		: ADD
			| MULT
			| DIV
			| SUB
			;


op 			: LE
			| GE
			| LT
			| GT
			| EQ
			| NE
			;

%%
int main(int argc, char *argv[])
 {
 	FILE *fp = fopen(argv[1],"r");

 	if(!fp)
 	 {
 	 	printf("Unable to open the file");
 	 	exit(0);
 	 }

 	 yyin = fp;

 	 int flag = yyparse();
 	 symDump();
 	 printf("\nlines of code: %d\n",yylineno);
 }

yywrap()
 {
 	return 1;
 }

int yyerror(char *msg)
 {
 	fprintf(stderr,"%s line : %d \n",msg,yylineno);
 	return 0;
 }