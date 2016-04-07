letter [a-zA-Z]  
digit[0-9]
charac ["!""@""#""$""%"]
%{
    #include<stdio.h>
    int opening_multi=0, closing_multi=0;
%}
%%
\n ;
\t ;
"#""include"" "?"<"{letter}*."h>" printf("\n%s\tis a preprocessor compiler directive", yytext); 
"/*"[^*]*"*"+"/" printf("\n%s\tis a MultiLine Comment", yytext);  
"%d"|"%s"|"%c"|"%f"|"%e" printf("\n%s\tis a format specifier",yytext);
["][^"]*["] printf("\n%s\tis a string",yytext);
{digit}+("E"("+"|"-")?{digit}+)? printf("\n%s\tis real number",yytext);  
{digit}+"."{digit}+("E"("+"|"-")?{digit}+)? printf("\n%s\t is floating pt no ",yytext);  
"if"|"else"|"int"|"char"|"scanf"|"printf"|"switch"|"return"|"struct"|"do"|"while"|"void"|"for"|"float"|"main"|"break" printf("\n%s\t is keywords",yytext);  
"\a"|"\\n"|"\\b"|"\t"|"\\t"|"\b"|"\\a" printf("\n%s\tis Escape sequences",yytext);  
({letter}|"_")({letter}|{digit}|"_")* printf("\n%s\tis an identifier",yytext);
({digit}|{charac})({letter}|{digit}|"_")* printf("\n%s\tis not an identifier",yytext);
"&&"|"<"|">"|"<="|">="|"="|"+"|"-"|"?"|"*"|"/"|"%"|"&"|"||" printf("\n%s\toperator ",yytext);  
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
  yyin=fopen(argv[1],"r");  
  yylex();
  if(closing_multi != opening_multi)
    printf("\nThere appears to be an error in multiline comments");
  fclose(yyin);  
  return 0;  
 }
