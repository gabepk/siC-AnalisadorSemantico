%{
#include "structs.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSTR 50

void yyerror(char *s);
int yylex(void);
%}

%union {
    int i;
    float f;
    char *c;
    char *str;
    struct Node *n;
}

%start program

%token <i> NUM_INT
%token <f> NUM_FLOAT
%token <c> CARACTERE
%token <str> IDENTIFIER

// PRECEDENCIA: http://en.cppreference.com/w/c/language/operator_precedence
%token <n> WHILE
%token <n> IF 
%token <n> ELSE 
%token <n> RETURN 
%token <n> QUEUE
%token <n> FIRST
%token <n> VOID
%token <n> FLOAT
%token <n> INT
%token <n> CHAR
%token <n> DOT 
%token <n> SEMICOLON 
%token <n> COMMA
%token OPEN_BRACES
%token CLOSE_BRACES 
%token OPEN_PARENT 
%token CLOSE_PARENT
%token EQ
%token NEQ
%token LEQ
%token GEQ
%token LT
%token GT
%token ASSIGN
%token ARROW
%token SETLAST
%token RMVFIRST
%token PLUS MINUS
%token MULT DIV
%%

program:	program function
		| function
		;

function:	argument OPEN_PARENT arguments CLOSE_PARENT OPEN_BRACES statements RETURN value SEMICOLON CLOSE_BRACES
		;

values:         values COMMA value
		| value
		| %empty
		;

value:          NUM_INT
                | NUM_FLOAT
                | CARACTERE
                | IDENTIFIER
                | IDENTIFIER DOT FIRST
                ;

type_struct:	type_simple
		| type_queue
		;

type_simple:	VOID | FLOAT | INT | CHAR
		;

type_queue:	QUEUE LT type_simple GT
		;

arguments:	arguments COMMA argument
		| argument
		| %empty
		;

argument:	type_struct IDENTIFIER
                ;

statements:	statements statement
		| %empty
		;
		
		
// Adicão de mais de um "statement" no corpo de IF, IF-ELSE e WHILE geram muitos conflitos

statement:	argument SEMICOLON// int x;
		| IDENTIFIER OPEN_PARENT values CLOSE_PARENT SEMICOLON // x (y, z); Chamada de função sem retorno
		| IDENTIFIER ASSIGN IDENTIFIER OPEN_PARENT  values CLOSE_PARENT SEMICOLON // x = x (y, z); Chamada de função com retorno
                // https://www.gnu.org/software/bison/manual/html_node/Non-Operators.html#Non-Operators (RESOLVE COM ASSOCIATIVIDADE)
		| IF OPEN_PARENT  compare_expression CLOSE_PARENT block  // ========================================== CONFLITO SHIFT/REDUCE
		| IF OPEN_PARENT  compare_expression CLOSE_PARENT block ELSE block
		| WHILE OPEN_PARENT  compare_expression CLOSE_PARENT block // while (x == y.FIRST) ...
		| IDENTIFIER ASSIGN assignment_expression SEMICOLON // x = y + z; // Assignment para tipos primitivos
		| identifier_struct_expression SEMICOLON // x = x - z; // Assignment para tipo FILA
		;
		
// Um bloco pode ser apenas um statment ou vários entre chaves. Serve para if, if-else, while
block:          statement
		| OPEN_BRACES statements CLOSE_BRACES
		;
		
compare_expression:	value compare_assignment value // x.FIRST == y
			;

compare_assignment:	EQ | NEQ | LEQ | GEQ | LT | GT
			;
		
		
// PRECEDENCIA de +, -, *, / DEFINIDA COM "%left" não tem parentesis

/*expression:     expression PLUS term
                | expression MINUS term
                | expression MULT term
                | expression DIV term
                | value
                | ;*/

assignment_expression:	assignment_expression PLUS term
			| assignment_expression MINUS term
			| term
			;
			
term:		term MULT factor {  }
		| term DIV factor
		| factor
		;
		
factor:		value
		| OPEN_PARENT assignment_expression CLOSE_PARENT
		;
		
identifier_struct_expression:	IDENTIFIER DOT SETLAST ARROW value  //  x.setlast->y (Add fim da fila)
				| IDENTIFIER ASSIGN IDENTIFIER DOT RMVFIRST // x = y.rmfirst;
				;

%%

extern int yylineno;

void yyerror(char *s) {
    printf("\t(sin) ERROR near line %d : %s\n", yylineno, s);
}

int main(void) {
  yyparse();
  return 0;
}