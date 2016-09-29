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

#ifndef YY_YY_110118995_TAB_H_INCLUDED
# define YY_YY_110118995_TAB_H_INCLUDED
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
    NUM_INT = 258,
    NUM_FLOAT = 259,
    CARACTERE = 260,
    IDENTIFIER = 261,
    WHILE = 262,
    IF = 263,
    ELSE = 264,
    RETURN = 265,
    QUEUE = 266,
    FIRST = 267,
    VOID = 268,
    FLOAT = 269,
    INT = 270,
    CHAR = 271,
    DOT = 272,
    SEMICOLON = 273,
    COMMA = 274,
    OPEN_BRACES = 275,
    CLOSE_BRACES = 276,
    OPEN_PARENT = 277,
    CLOSE_PARENT = 278,
    PLUS = 279,
    MINUS = 280,
    MULT = 281,
    DIV = 282,
    EQ = 283,
    NEQ = 284,
    LEQ = 285,
    GEQ = 286,
    LT = 287,
    GT = 288,
    ASSIGN = 289,
    ARROW = 290,
    SETLAST = 291,
    RMVFIRST = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 7 "110118995.y" /* yacc.c:1909  */

    int i;
    float f;
    char *c;
    char *str;

#line 99 "110118995.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_110118995_TAB_H_INCLUDED  */
