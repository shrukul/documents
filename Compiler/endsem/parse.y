%{

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "sym_tab.h"

	extern int yylineno;
	extern FILE *yyin,*yyout;
	extern int yyparse();
	extern char * yytext;
	extern int yyerror(const char *msg);
	#define YYDEBUG 1
	int yydebug = 1;
	int current_type;
	extern int level;

	typedef struct sym sym;
%}

%union{
	int intval;
	char charval;
	char *strval;
	float floatval;
}

%token <strval> IDENTIFIER
%token <intval> INTEGER REAL CHAR
%token <intval> FLOAT INT RETURN

%token ADD SUB MULT DIV
%token EQ ASSIGN LT LE GT GE NE

%token LPAREN RPAREN LBRACE RBRACE
%token COMMA SEMI

%type <intval> decl_type decl_seq term expr

%start program

%%

program		:	program module
			|	module
			|	error{yyerror("Not a valid function.");}
			;

module		: 	func_decl
			|	func_defn
			;

func_decl	:	decl LPAREN arg_seq RPAREN SEMI
			;

func_defn	:	decl LPAREN arg_seq RPAREN block
			;

decl  		: 	decl_type IDENTIFIER		{printf("here"); insert($2,$1,yylineno,0,level);}
			;

decl_type	: 	INTEGER						{$$ = $1; current_type = $1;}
			| 	REAL						{$$ = $1; current_type = $1;}
			| 	CHAR 						{$$ = $1; current_type = $1;}
			| 	{yyerror("Not a valid type.");}
			;

arg_seq 	: 	arg_seq COMMA decl
			| 	decl
			|
			;

block		: 	LBRACE stmt_seq RBRACE
			;

stmt_seq	:	stmt_seq stmt
			|   stmt
			;

stmt 		: 	declaration SEMI
			| 	expr SEMI
			|	assignment SEMI
			| 	return_st SEMI
			| 	block
			;

declaration	: 	decl_type decl_seq						{current_type = $1;}
			| 	decl_type decl_chain					{current_type = $1;}
			;

decl_chain	:	decl_chain COMMA decl_as
			|	decl_as
			;

decl_as		:	IDENTIFIER ASSIGN expr					{insert($1,current_type,yylineno,0,level);}
			;

decl_seq	:	decl_seq COMMA IDENTIFIER				{insert($3,current_type,yylineno,0,level);}
			| 	IDENTIFIER								{$$ = getval($1); insert($1,current_type,yylineno,0,level);}
			;

assignment	: 	IDENTIFIER ASSIGN expr					{if(!isExist($1,level)) yyerror("Not defined"); if(getType($1) != current_type) yyerror("Not same types");}			
			;

expr		: 	expr ADD expr							{$$ = $1 + $3;}
			| 	expr SUB expr							{$$ = $1 - $3;}
			|	expr MULT expr							{$$ = $1 * $3;}
			|   expr DIV expr							{$$ = $1 / $3;}
			| 	LPAREN expr RPAREN						{$$ = $2;}
			|	term									{$$ = $1;}
			| 	func_call								{$$ = 20;}
			;

func_call	:	IDENTIFIER LPAREN call_seq RPAREN
			;

call_seq	: 	call_seq COMMA term
			| 	term
			|
			;

return_st	:	RETURN
			|	RETURN term
			;

term 		: 	IDENTIFIER								{$$ = getval($1);}
			|	INT 									{$$ = $1; current_type = $1;}
			|	FLOAT 									{$$ = $1; current_type = $1;}
			;

%%

int main(int argc, char *argv[])
{
	FILE *fp = fopen(argv[1],"r");
	yyin = fp;

	int flag = yyparse();

	if(flag == 0)
	 printf("Successfully parsed!");

	sym_dump();
	fclose(fp);
	return 0;
}

yywrap()
{
	return 1;
}

int yyerror(const char *msg)
{
	printf("Error: %s at line %d",msg,yylineno);
	exit(0);
}