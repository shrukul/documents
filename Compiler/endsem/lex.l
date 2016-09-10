%option yylineno

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "y.tab.h"

	int level = 0;
%}

digit			[0-9]
ichar			[a-z_A-Z]
whitespace		[ \t\n]
newline 		\n

%%

"int"								{yylval.intval = 21; return INTEGER;}
"float"								{yylval.intval = 22; return REAL;}
"char"								{yylval.intval = 23; return CHAR;}

"#include<"{ichar}+".h>"			{}		
"return"							{return RETURN;}

","									{return COMMA;}
";"									{return SEMI;}

"+"									{return ADD;}
"*"									{return MULT;}
"/"									{return DIV;}
"-"									{return SUB;}

"=="								{return EQ;}
"="									{return ASSIGN;}
"!="								{return NE;}
"<"									{return LT;}
"<="								{return LE;}
">"									{return GT;}
">="								{return GE;}

"("									{printf("curly"); return LPAREN;}
")"									{return RPAREN;}
"{"									{level++; return LBRACE;}
"}"									{level++; return RBRACE;}

{digit}+							{yylval.intval = 21; return INT;}
({digit}+)?"."{digit}+				{yylval.intval = 22; return FLOAT;}
{ichar}+({ichar}|{digit})*			{yylval.strval = (char *)malloc(sizeof(yytext)); strncpy(yylval.strval,yytext,yyleng); return IDENTIFIER;}
{newline}							{}

%%	