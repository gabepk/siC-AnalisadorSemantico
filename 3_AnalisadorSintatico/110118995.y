%{
#include <stdio.h>
void yyerror(char *s);
int yylex(void);
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

%union {
    int i;
    float f;
    char c;
    char *str;
}

%start program

%token <int> NUM_INT
%token <float> NUM_FLOAT
%token <c> CARACTERE
%token <str> IDENTIFIER

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

// PRECEDENCIA: http://en.cppreference.com/w/c/language/operator_precedence

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

program:	program function
		| function
		;
		
function:	argument OPEN_PARENT arguments CLOSE_PARENT OPEN_BRACES statement RETURN IDENTIFIER SEMICOLON CLOSE_BRACES
		;

// LEFT RECURSION EM IDENTIFIERS
		
identifiers:	identifiers COMMA IDENTIFIER
		| IDENTIFIER
		| %empty
		;
		
/*identifier:	letra(letra | digito)*
		;
		
caractere:	letra | DIGITO
		;
		
letra:		a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | w | x | y | z
		| A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | W | X | Y | Z
		| $
		;

digito:		0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
		;
*/

identifier_struct:	IDENTIFIER
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


// if-else não ambiguo

// LEFT RECURSION EM STATEMENTS

statements:	statements statement
		| %empty
		;
		
statement:	argument SEMICOLON
		| IDENTIFIER OPEN_PARENT identifiers CLOSE_PARENT SEMICOLON
		| IDENTIFIER ASSIGN IDENTIFIER OPEN_PARENT  identifiers CLOSE_PARENT SEMICOLON
		
                // https://www.gnu.org/software/bison/manual/html_node/Non-Operators.html#Non-Operators (RESOLVE COM ASSOCIATIVIDADE)
		| IF OPEN_PARENT  compare_expression CLOSE_PARENT statement // ========================================== CONFLITO SHIFT/REDUCE
		| IF OPEN_PARENT  compare_expression CLOSE_PARENT statement ELSE statement
		
		| WHILE OPEN_PARENT  compare_expression CLOSE_PARENT statement
		| IDENTIFIER ASSIGN assignment_expression SEMICOLON
		| identifier_struct_expression
		| OPEN_BRACES statements CLOSE_BRACES
		;
		
compare_expression:	identifier_struct compare_assignment identifier_struct
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
		
factor:		identifier_struct
		| QUOTE CARACTERE QUOTE
		| OPEN_PARENT assignment_expression CLOSE_PARENT
		;
		
identifier_struct_expression:	IDENTIFIER ASSIGN IDENTIFIER PLUS IDENTIFIER SEMICOLON
				| IDENTIFIER ASSIGN IDENTIFIER MINUS IDENTIFIER SEMICOLON // ============================== CONFLITO SHIFT/REDUCE
				;

%%

void yyerror(char *s) {
    printf("yyerror : %s\n",s);
}

int main(void) {
  yyparse();
  return 0;
}