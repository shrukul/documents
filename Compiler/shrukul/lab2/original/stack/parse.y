%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

#define DEBUG 0
#define TRUE 1
#define FALSE 0
#define MAX_MSG_LEN 50
#define YYDEBUG 1

int errcnt = 0;
char errmsg[40];
extern char *yytext;
extern FILE *yyin;
extern FILE *yyout;
extern int yyparse();
extern int lineno;
int yydebug = 1;
int t;
%}

/* no warning for fewer than 1 shift/reduce conflicts and 0 reduce/reduce */ 
%expect 0
%union { int tokid;
         char *tokname;
       }

%token <tokname> IDENT NUMBER
%token <tokid> ASSIGN PLUS LBRACE RBRACE LPAREN RPAREN SEMI ERROR FLOAT INTEGER 
/* ADDED */
%token <tokid> IF THEN ELSE WHILE RETURN GOTO READ WRITE VOID CHAR
/* ADDED */
%token <tokid> NE EQ LT LE GT GE AND OR MINUS TIMES OVER MOD INT REAL
/* ADDED */
%token <tokid> LBRACK RBRACK COMMA CHRLIT STRLIT
%type <tokid> block stmt_seq stmt decl expr term assignmnt decltype error

%start block

%% 

block       : LBRACE stmt_seq RBRACE  
            | LPAREN stmt_seq RPAREN  
            | error { yyerrok; return 0; } 
            ;

stmt_seq    : stmt_seq stmt SEMI
            | stmt SEMI
            | error  { yyerrok; return 0;} 
            ;

stmt        : expr
            | decl
            | assignmnt { $$ = $1; }
            | error  { yyerrok; return 0;} 
            ;

decl        : decltype IDENT { 
                setType($2,$1);
                fprintf(stdout,"set decltype to: %d for %s\n",$$,$2);  
            }
            ;

expr        : expr PLUS term 
              { /* add constraint here */ }

            | term { $$ = $1; }
            ;

assignmnt   : IDENT ASSIGN expr  
              { /* add constraint here */ }
            ;

term        : NUMBER { $$ = lookupType($1); }

            | IDENT  { $$ = lookupType($1); }
            ;

decltype    : INTEGER  { $$ = INT_TYPE; }
            | FLOAT { $$ = REAL_TYPE; }
            ;

%%

int main( int argc,char *argv[] )
{
   strcpy(errmsg,"type error\n");
   int i;
   if(argc < 2) {
      printf("Usage: ./cfc <source filename>\n");
      exit(0);
   }
   FILE *fp = fopen(argv[1],"r");
   if(!fp) {
     printf("Unable to open file for reading\n");
     exit(0);
   }
   yyin = fp;

   fp = fopen("dump.symtab","w");
   if(!fp) {
     printf("Unable to open file for writing\n");
     exit(0);
   }

   int flag = yyparse();

   /* dump symtab for debugging if necessary  */
   symtab_dump(fp);  
   lineno--;  /* don't count the last newline */ 
   printf("\nsemantic error cnt: %d \tlines of code: %d\n",errcnt,lineno);

   /* cleanup */
   fclose(fp);
   fclose(yyin);

   return flag;
}


yywrap()
{
   return(1);
}

int yyerror(char * msg)
{ fprintf(stderr,"%s: line %d: \n",msg,lineno);
  return 0;
}
