/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENT = 258,
    NUMBER = 259,
    ASSIGN = 260,
    PLUS = 261,
    LBRACE = 262,
    RBRACE = 263,
    LPAREN = 264,
    RPAREN = 265,
    SEMI = 266,
    ERROR = 267,
    FLOAT = 268,
    INTEGER = 269,
    IF = 270,
    THEN = 271,
    ELSE = 272,
    WHILE = 273,
    RETURN = 274,
    GOTO = 275,
    READ = 276,
    WRITE = 277,
    VOID = 278,
    CHAR = 279,
    NE = 280,
    EQ = 281,
    LT = 282,
    LE = 283,
    GT = 284,
    GE = 285,
    AND = 286,
    OR = 287,
    MINUS = 288,
    TIMES = 289,
    OVER = 290,
    MOD = 291,
    INT = 292,
    REAL = 293,
    LBRACK = 294,
    RBRACK = 295,
    COMMA = 296,
    CHRLIT = 297,
    STRLIT = 298
  };
#endif
/* Tokens.  */
#define IDENT 258
#define NUMBER 259
#define ASSIGN 260
#define PLUS 261
#define LBRACE 262
#define RBRACE 263
#define LPAREN 264
#define RPAREN 265
#define SEMI 266
#define ERROR 267
#define FLOAT 268
#define INTEGER 269
#define IF 270
#define THEN 271
#define ELSE 272
#define WHILE 273
#define RETURN 274
#define GOTO 275
#define READ 276
#define WRITE 277
#define VOID 278
#define CHAR 279
#define NE 280
#define EQ 281
#define LT 282
#define LE 283
#define GT 284
#define GE 285
#define AND 286
#define OR 287
#define MINUS 288
#define TIMES 289
#define OVER 290
#define MOD 291
#define INT 292
#define REAL 293
#define LBRACK 294
#define RBRACK 295
#define COMMA 296
#define CHRLIT 297
#define STRLIT 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 27 "parse.y" /* yacc.c:1909  */
 int tokid;
         char *tokname;
       

#line 145 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
