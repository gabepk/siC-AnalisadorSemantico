%{
#include <stdio.h>
%}

// QUE ISSO ????? ACHO QUE SÃO OS TERMINAIS COM A ASSOCIATIVIDADE

/*%union{
  int		int_val;
  string*	op_val;
}

%start	input 

%token	<int_val>	INTEGER_LITERAL
%type	<int_val>	exp
%left	PLUS
%left	MULT
*/


%token WHILE
%token IF
%token ELSE
%token RETURN
%token QUEUE
%token FIRST
%token VOID
%token FLOAT
%token INT
%token CHAR

%token DOT
%token SEMICOLON
%token COMMA
%token QUOTE
%token OPEN_BRACES
%token CLOSE_BRACES
%token OPEN_PARENT
%token CLOSE_PARENT

%token PLUS
%token MINUS
%token MULT
%token DIV
%token EQ
%token NEQ
%token LEQ
%token GEQ
%token LT
%token GT
%token ASSIGN
%%

input:		/* empty */
		| exp	{ cout << "Result: " << $1 << endl; }
		;

exp:		INTEGER_LITERAL	{ $$ = $1; }
		| exp PLUS exp	{ $$ = $1 + $3; }
		| exp MULT exp	{ $$ = $1 * $3; }
		;
		
		
// ===========================		
		
		
		

program:	program function
		| function
		;
		
function:	argument OPEN_PARENT arguments CLOSE_PARENT OPEN_BRACES statement RETURN identifier SEMICOLON CLOSE_BRACES
		;

identifiers:	identifiers COMMA identifier
		| identifier
		| ε
		;
		
identifier:	letra(letra | digito)*
		;
		
caractere:	letra | digito
		;
		
letra:		a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | w | x | y | z
		| A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | W | X | Y | Z
		| $
		;

digito:		0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
		;

identifier_struct:	identifier
			| identifier DOT FIRST
			;

type_struct:	type_simple
		| type_queue IF OPEN_PARENT compare_expression CLOSE_PARENT OPEN_BRACES statement CLOSE_BRACES
                | IF OPEN_PARENT compare_expression CLOSE_PARENT OPEN_BRACES statement CLOSE_BRACES ELSE OPEN_BRACES statement CLOSE_BRACES
		;
		
type_simple:	VOID | FLOAT | INT | CHAR
		;

type_queue:	QUEUE LT type_simple GT
		;
		
arguments:	arguments COMMA argument
		| argument
		| ε
		;
		
argument:	type_struct identifier
		;


// if-else não ambiguo



statements:	statements statement
		| ε
		;
		
statement:	argument SEMICOLON
		| identifier OPEN_PARENT identifiers CLOSE_PARENT SEMICOLON
		| identifier ASSIGN identifier OPEN_PARENT  identifiers CLOSE_PARENT SEMICOLON
		| IF OPEN_PARENT  compare_expression CLOSE_PARENT statement
		| IF OPEN_PARENT  compare_expression CLOSE_PARENT statement ELSE statement
		| WHILE OPEN_PARENT  compare_expression CLOSE_PARENT statement
		| identifier ASSIGN assignment_expression SEMICOLON
		| identifier_struct_expression
		| OPEN_BRACES statements CLOSE_BRACES
		;
		
compare_expression:	identifier_struct compare_assignment identifier_struct
			;

compare_assignment:	EQ | NEQ | LEQ | GEQ | LT | GT
			;
			
assignment_expressions:	assignment_expression PLUS term { $$ = $1 + $3; }
			| assignment_expression MINUS term { $$ = $1 - $3; }
			| term
			;
			
term:		term MULT factor { $$ = $1 * $3; }
		| term DIV factor { $$ = $1 / $3; }
		| factor
		;
		
factor:		identifier_struct
		| QUOTE caractere QUOTE
		| OPEN_PARENT assignment_expression CLOSE_PARENT
		;
		
identifier_struct_expression:	identifier ASSIGN identifier PLUS identifier SEMICOLON
				| identifier ASSIGN identifier MINUS identifier SEMICOLON
				;


		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		


%%

int yyerror(char *s) {
  printf("yyerror : %s\n",s);
}

int main(void) {
  yyparse();
}