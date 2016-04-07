/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OP_SUB = 258,
     OP_ADD = 259,
     OP_DIV = 260,
     OP_MUL = 261,
     OP_GE = 262,
     OP_LE = 263,
     OP_NE = 264,
     OP_EQ = 265,
     OP_LT = 266,
     OP_GT = 267,
     OP_ASSIGN = 268,
     SEMICOLON = 269,
     LBRACE = 270,
     RBRACE = 271,
     LPAREN = 272,
     RPAREN = 273,
     KW_INT = 274,
     KW_FLOAT = 275,
     KW_IF = 276,
     KW_ELSE = 277,
     KW_WHILE = 278,
     INT_CONSTANT = 279,
     FLOAT_CONSTANT = 280,
     IDENTIFIER = 281
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 11 "parser.y"

   int int_const;
   float float_const;

   int type_specifier;
   char *identifier;

   struct ast_node *node;
   struct ast_declaration *declaration;
   struct ast_expression *expression;
   struct ast_statement_list *statement_list;
   struct ast_selection_statement *selection_statement;
   struct ast_while_statement *while_statement;
   struct ast_compound_statement *compound_statement;
   struct ast_translation_unit *translation_unit;



/* Line 2068 of yacc.c  */
#line 95 "parser.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


