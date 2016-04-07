letter [a-zA-Z]  
digit[0-9]
charac ["!""@""#""$""%"]
%{
    #include<stdio.h>
	#include<string.h>
    int opening_multi=0, closing_multi=0, count[7];
    char str[7][100]={"Directive","Specifier", "Keywords", "Real nos ", "Identifiers", "Float nos ", "Operators"};
	char tok[7][50][50];
%}
%%
\n ;
\t ;
"#""include"" "?"<"{letter}*."h>" { printf("\n%s\tis a preprocessor compiler directive", yytext); count[0]++; strcpy(tok[0][count[0]-1],yytext);}
"/*"[^*]*"*"+"/" printf("\n%s\tis a MultiLine Comment", yytext);  
"%d"|"%s"|"%c"|"%f"|"%e" { printf("\n%s\tis a format specifier",yytext); count[1]++; strcpy(tok[1][count[1]-1],yytext);}
["][^"]*["] printf("\n%s\tis a string",yytext);
{digit}+("E"("+"|"-")?{digit}+)? { printf("\n%s\t is real number",yytext);  count[3]++; strcpy(tok[3][count[3]-1],yytext);}
{digit}+"."{digit}+("E"("+"|"-")?{digit}+)? { printf("\n%s\t is floating pt no ",yytext);  count[5]++; strcpy(tok[5][count[5]-1],yytext);}
"if"|"else"|"int"|"char"|"scanf"|"printf"|"switch"|"return"|"struct"|"do"|"while"|"void"|"for"|"float"|"main"|"break" {printf("\n%s\t is keywords",yytext);  count[2]++; strcpy(tok[2][count[2]-1],yytext);}
"\a"|"\\n"|"\\b"|"\t"|"\\t"|"\b"|"\\a" printf("\n%s\tis Escape sequences",yytext);  
({letter}|"_")({letter}|{digit}|"_")* {printf("\n%s\t is an identifier",yytext); count[4]++; strcpy(tok[4][count[4]-1],yytext);}
({digit}|{charac})({letter}|{digit}|"_")* printf("\n%s\tis not an identifier",yytext);
"&&"|"<"|">"|"<="|">="|"="|"+"|"-"|"?"|"*"|"/"|"%"|"&"|"||" { printf("\n%s\t is an operator ",yytext); count[6]++; strcpy(tok[6][count[6]-1],yytext);} 
"{"|"}"|"["|"]"|"("|")"|"#"|"'"|"."|"\""|"\\"|";"|","|"==" printf("\n%s\t is a special character",yytext);
"//".* printf("\n\"%s\"\tis a single line comment", yytext);
"/*" {opening_multi++; printf("\n%s\tis the opening of a multiline comment", yytext); }
"*/" {closing_multi++;  printf("\n%s\tis the closing of a multiline comment", yytext); }
%%  
 
int yywrap()  
 {  
  return 1;  
 }  
int main(int argc,char *argv[])  
 {  
  int i,j;
  yyin=fopen(argv[1],"r");  
  for(j=0;j<120;j++)
	printf("*");
  printf("\n");
  printf("\n\nLexical Analysis of C Program\n\n");
  for(j=0;j<120;j++)
	printf("*");
  printf("\n");
  yylex();
  if(closing_multi != opening_multi)
    printf("\n\nError\n\nThere is an error in multiline comment\n");
  fclose(yyin);
  printf("\n\n");
  printf("Symbol Table\n");
  for(j=0;j<15;j++)
	printf("*");
  printf("\n");
  printf("\n\n");
  printf("\t\tTokens\t\t\t\t\tFrequency\t\t\tValues\n\n");
  for(j=0;j<120;j++)
	printf("*");
  printf("\n");
  j=0;
  for(i=0;i<7;i++)
   {
	printf("\t\t%s\t\t",str[i]);
    printf("\t\t%d\t\t", count[i]);
	printf("\n");
	for(j=0;j<count[i];j++)
	 printf("\t\t\t\t\t\t\t\t\t\t\t%s\n",tok[i][j]);
    for(j=0;j<120;j++)
	  printf("-");
    printf("\n");
	j=0;
   }

  printf("\n\nConstant Table\n\n");
  for(j=0;j<120;j++)
	printf("*");
  printf("\n");
  for(i=3;i<6;i+=2)
   {
	printf("\t\t%s\t\t",str[i]);
    printf("\t\t%d\t\t", count[i]);
	printf("\n");
	for(j=0;j<count[i];j++)
	 printf("\t\t\t\t\t\t\t\t\t\t\t%s\n",tok[i][j]);
    for(j=0;j<120;j++)
	  printf("-");
    printf("\n");
	j=0;
   }
  return 0;  
 }
