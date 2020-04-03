/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
    T_INT = 258,
    T_FLOAT = 259,
    T_S_BINARY_OPERATOR = 260,
    T_F_BINARY_OPERATOR = 261,
    T_ASSIGN_OPERATOR = 262,
    T_UNARY_OPERATOR = 263,
    T_RELATIONAL_OPERATOR = 264,
    T_LOGICAL_OPERATOR = 265,
    T_COLON = 266,
    T_SEMI_COLON = 267,
    T_CLOSE_PARAN = 268,
    T_OPEN_PARAN = 269,
    T_CLOSE_SCOPE = 270,
    T_OPEN_SCOPE = 271,
    T_IDENTIFIER = 272,
    T_WHILE = 273,
    T_SWITCH = 274,
    T_CASE = 275,
    T_DEFAULT = 276,
    T_RETURN = 277,
    T_BREAK = 278,
    T_STRING = 279,
    T_CHARACTER = 280,
    T_PRINT = 281,
    T_MAIN = 282,
    T_DEF = 283,
    T_CONTINUE = 284,
    T_TYPE_NAME = 285,
    T_ASSIGN_INITIALIZE = 286,
    T_PRINT_BODY = 287,
    T_COMMA = 288,
    T_TINT = 289,
    LOL = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 233 "parserpp.y" /* yacc.c:1909  */

    char* str;
    struct SymbolTableTree * stt;

#line 95 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
