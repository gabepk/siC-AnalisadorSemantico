%{
#include <stdio.h>
void yyerror(char *s);
int yylex(void);
%}

%union {
    int i;
    float f;
    char *c;
    char *str;
}

%start program

%token <i> NUM_INT
%token <f> NUM_FLOAT
%token <c> CARACTERE
%token <str> IDENTIFIER

// PRECEDENCIA: http://en.cppreference.com/w/c/language/operator_precedence
%token WHILE IF ELSE RETURN QUEUE FIRST VOID FLOAT INT CHAR
%token DOT SEMICOLON COMMA QUOTE 
%token OPEN_BRACES CLOSE_BRACES OPEN_PARENT CLOSE_PARENT
%token PLUS MINUS MULT DIV EQ NEQ LEQ GEQ LT GT ASSIGN
%%

program:	program function
		| function
		;
		
function:	argument OPEN_PARENT arguments CLOSE_PARENT OPEN_BRACES statements RETURN value SEMICOLON CLOSE_BRACES
		;
		
		
// LEFT RECURSION EM VALUES

                
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
		
// LEFT RECURSION EM ARGUMENTS
		
arguments:	arguments COMMA argument
		| argument
		| %empty
		;
		
argument:	type_struct IDENTIFIER
		;

// LEFT RECURSION EM STATEMENTS

statements:	statements statement
		| %empty
		;
		
statement:	argument SEMICOLON // int x;
		| IDENTIFIER OPEN_PARENT values CLOSE_PARENT SEMICOLON // x (y, z); Chamada de função sem retorno
		| IDENTIFIER ASSIGN IDENTIFIER OPEN_PARENT  values CLOSE_PARENT SEMICOLON // x = x (y, z); Chamada de função com retorno
		
                // https://www.gnu.org/software/bison/manual/html_node/Non-Operators.html#Non-Operators (RESOLVE COM ASSOCIATIVIDADE)
		| IF OPEN_PARENT  compare_expression CLOSE_PARENT statements // ========================================== CONFLITO SHIFT/REDUCE
		| IF OPEN_PARENT  compare_expression CLOSE_PARENT statements ELSE statements
		
		| WHILE OPEN_PARENT  compare_expression CLOSE_PARENT statements // while (x == y.FIRST) ...
		| IDENTIFIER ASSIGN assignment_expression SEMICOLON // x = y + z; // Assignment para tipos primitivos
		| identifier_struct_expression // x = y + z; // Assignment para tipo FILA
		| OPEN_BRACES statements CLOSE_BRACES
		;
		
compare_expression:	value compare_assignment value // x.FIRST == y
			;

compare_assignment:	EQ | NEQ | LEQ | GEQ | LT | GT
			;
			
assignment_expression:	assignment_expression PLUS term
			| assignment_expression MINUS term
			| term
			;
			
term:		term MULT factor
		| term DIV factor
		| factor
		;
		
factor:		value
		| OPEN_PARENT assignment_expression CLOSE_PARENT
		;
		
identifier_struct_expression:	IDENTIFIER ASSIGN IDENTIFIER PLUS value SEMICOLON // FILA_INT = FILA_INT + value_int (Adiciona no topo da fila)
				| IDENTIFIER ASSIGN IDENTIFIER MINUS value SEMICOLON // ============================== CONFLITO SHIFT/REDUCE
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