%option yylineno
%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "y.tab.h"

	int lineno=1;
%}

digit			[0-9]
ichar			[a-z_A-Z]
newline 		\n
identifier		{ichar}+({digit}|{ichar})*
float			([+-]?{digit}*)?\.{digit}+(e[+-]?{digit}+)
intliteral		{digit}+
%%

"int"			{return INT; printf("int here");}
"for"			{return FOR;}
"else"			{return ELSE;}
"return"		{return RETURN;}

{newline}		{lineno++;}

"("				{return LPAREN;}
")"				{return RPAREN;}
"{"				{return LBRACE;}
"}"				{return RBRACE;}
";"				{return SEMI;}
","				{return COMMA;}
"="				{return ASSIGN;}
"+"				{return ADD;}

"<"				{return LT;}

{identifier}	{insert(yytext,0,yylineno); return IDENTIFIER;}
{float}			{return FLOAT;}
{intliteral}	{return INTEGER;}
{identifier}"++"	{return INCRE;}
%%
