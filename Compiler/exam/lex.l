%option yylineno

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "y.tab.h"

	int lineno = 0;
%}

digit		[0-9]
ichar		[a-z_A-Z]
header		"#include<"{ichar}*".h>"
whitespace	[ \t]+
float 		[[+-]?{digit}+]?\.{digit}*(e?[+-]?{digit}+)?
newline		\n
identifier	{ichar}({digit}|{ichar})*
escquote	[^"]*\\\"[^"]*
strliteral	\"{escquote}*\"
comment 	"/*"[^*]*"*"+"/"
integer 	{digit}+
%%

"if"		{return IF;}
"else"		{return ELSE;}
"int"		{return INT; printf("int");}

"="			{return ASSIGN;}
"=="		{return EQ;}
"("			{return LPAREN;}
")"			{return RPAREN;}
"{"			{return LBRACE;}
"}"			{return RBRACE;}
","			{return COMMA;}
";"			{return SEMI;}
"||"		{return OR;}
"&&"		{return AND;}

"<="		{return LE;}
">="		{return GE;}
"<"			{return LT;}
">"			{return GT;}
"!="		{return NE;}

"+"			{return ADD;}
"*"			{return MULT;}
"/"			{return DIV;}
"-"			{return SUB;}

{float}			{return FLOAT;}
{integer}		{return INTEGER;}
{identifier}	{yylval.name = malloc(sizeof(yytext)); strncpy(yylval.name,yytext,yyleng); insert(yytext,0,lineno); return IDENTIFIER; }
{newline}		{lineno++;}
%%