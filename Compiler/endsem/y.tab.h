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
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    INTEGER = 259,
    REAL = 260,
    CHAR = 261,
    FLOAT = 262,
    INT = 263,
    RETURN = 264,
    ADD = 265,
    SUB = 266,
    MULT = 267,
    DIV = 268,
    EQ = 269,
    ASSIGN = 270,
    LT = 271,
    LE = 272,
    GT = 273,
    GE = 274,
    NE = 275,
    LPAREN = 276,
    RPAREN = 277,
    LBRACE = 278,
    RBRACE = 279,
    COMMA = 280,
    SEMI = 281
  };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define INTEGER 259
#define REAL 260
#define CHAR 261
#define FLOAT 262
#define INT 263
#define RETURN 264
#define ADD 265
#define SUB 266
#define MULT 267
#define DIV 268
#define EQ 269
#define ASSIGN 270
#define LT 271
#define LE 272
#define GT 273
#define GE 274
#define NE 275
#define LPAREN 276
#define RPAREN 277
#define LBRACE 278
#define RBRACE 279
#define COMMA 280
#define SEMI 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 21 "parse.y" /* yacc.c:1909  */

	int intval;
	char charval;
	char *strval;
	float floatval;

#line 113 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
