%{
#include "structs.h"
#define MAXSTR 50

void yyerror(char *s);
int yylex(void);

%}

%union {
    int i;
    float f;
    char c;
    char *str;
    struct elemento *e;
    //idStructExpression *idsExp;
}

%start program

%token <i> NUM_INT
%token <f> NUM_FLOAT
%token <c> CARACTERE
%token <str> IDENTIFIER

// PRECEDENCIA: http://en.cppreference.com/w/c/language/operator_precedence
%token WHILE IF ELSE RETURN 
%token QUEUE FIRST VOID FLOAT INT CHAR
%token DOT SEMICOLON COMMA OPEN_BRACES CLOSE_BRACES OPEN_PARENT CLOSE_PARENT
%token EQ NEQ LEQ GEQ LT GT ASSIGN PLUS MINUS MULT DIV
%token ARROW SETLAST RMVFIRST

%type <e> program
%type <e> function
%type <e> type_struct
%type <e> type_simple
%type <e> arguments
%type <e> statements
%type <e> statement
%type <e> values
%type <e> value
%type <e> block
%type <e> assignment_expression
%type <e> compare_assignment
%type <e> term
%type <e> factor
//%type <idsExp> identifier_struct_expression

// FOLLOW, LISTA DE FIRSTS, NUM_FIRST, NOME

%%

program:	program function { 
                            elemento *fL = (elemento*) malloc(FIRST_MAX * sizeof(elemento));;
                            elemento *prog = (elemento*) malloc(sizeof(elemento));
                            elemento *func = (elemento*) malloc(sizeof(elemento));
                            fL[0] = *prog;
                            fL[1] = *func;
                            $$ = new_elemento(NULL, &fL, 2, "program"); }
		| %empty {$$ = NULL; }
		;

function:	type_struct IDENTIFIER OPEN_PARENT arguments CLOSE_PARENT OPEN_BRACES statements RETURN value SEMICOLON CLOSE_BRACES { 
                       // $$ = new_element("function");
                        }
		;

values:         values COMMA value {} //$$ = new_element("values"); }
		| value {} //$$ = new_element("values"); }
		| %empty { $$ = NULL; }
		;

value:          NUM_INT {}// $$ = new_element("value"); }
                | NUM_FLOAT {}// $$ = new_element("value"); }
                | CARACTERE {}// $$ = new_element("value"); }
                | IDENTIFIER {}// $$ = new_element("value"); }
                //| IDENTIFIER DOT FIRST // FALTA ESSE
                ;

type_struct:	type_simple {}// $$ = new_element("type_struct"); }
		| QUEUE LT type_simple GT {}// $$ = new_element("type_struct"); }
		;

type_simple:	VOID  {}// $$ = new_element("type_simple"); }
                | FLOAT {}// $$ = new_element("type_simple"); }
                | INT {}// $$ = new_element("type_simple"); }
                | CHAR {}// $$ = new_element("type_simple"); }
		;
		
arguments:	arguments COMMA type_struct IDENTIFIER {}// $$ = new_element("arguments"); }
		| type_struct IDENTIFIER {}// $$ = new_element("arguments"); }
		| %empty { $$ = NULL; }
		;

statements:	statements statement {}// $$ = new_element("statements"); }
		| %empty { $$ = NULL; }
		;

// https://www.gnu.org/software/bison/manual/html_node/Non-Operators.html#Non-Operators (RESOLVE COM ASSOCIATIVIDADE)
statement:	type_struct IDENTIFIER SEMICOLON {} 
                    //$$ =  new_element("statement"); }
		| IDENTIFIER OPEN_PARENT values CLOSE_PARENT SEMICOLON {} 
                    //$$ =  new_element("statement");}
		//| IDENTIFIER ASSIGN IDENTIFIER OPEN_PARENT  values CLOSE_PARENT SEMICOLON // FALTA ESSE FUNCALL COM RETORNO
		| IF OPEN_PARENT value compare_assignment value CLOSE_PARENT block { }
                    //$$ = new_element("statement"); }
		| IF OPEN_PARENT value compare_assignment value CLOSE_PARENT block ELSE block { }
                    //$$ = new_element("statement"); }
		| WHILE OPEN_PARENT value compare_assignment value CLOSE_PARENT block { }
                   // $$ = new_element("statement"); }
		| IDENTIFIER ASSIGN assignment_expression SEMICOLON { }
                   // $$ = new_element("statement"); }
		//| identifier_struct_expression SEMICOLON { $$ = new_element("")); }
		;
		
// Um bloco pode ser apenas um statment ou vários entre chaves. Serve para if, if-else, while
block:          statement {}// $$ = new_element("block"); }
		| OPEN_BRACES statements CLOSE_BRACES {}// $$ = new_element("block"); }
		;

compare_assignment:	EQ {}// $$ = new_element("compare_assignment"); }
                        | NEQ {}// $$ = new_element("compare_assignment"); }
                        | LEQ {}// $$ = new_element("compare_assignment"); }
                        | GEQ {}// $$ = new_element("compare_assignment"); }
                        | LT {}// $$ = new_element("compare_assignment"); }
                        | GT {}// $$ = new_element("compare_assignment"); }
                        ;

assignment_expression:	assignment_expression PLUS term {}// $$ = new_element("assignment_expression"); }
			| assignment_expression MINUS term {}// $$ = new_element("assignment_expression"); }
			| term {}// $$ = new_element(""); }
			;
			
term:		term MULT factor {}// $$ = new_element("term"); }
		| term DIV factor {}// $$ = new_element("term"); }
		| factor {}// $$ = new_element("term"); }
		;
		
factor:		value {}//$$ = new_element("factor"); }
		| OPEN_PARENT assignment_expression CLOSE_PARENT {}//$$ = new_element("factor"); }
		;
		
//identifier_struct_expression:	IDENTIFIER DOT SETLAST ARROW value  //  x.setlast->y (Add fim da fila)
//				| IDENTIFIER ASSIGN IDENTIFIER DOT RMVFIRST // x = y.rmfirst;
//				;

%%

extern int yylineno;

void yyerror(char *s) {
    printf("\t(sin) ERROR near line %d : %s\n", yylineno, s);
}

int main(void) {
  yyparse();
  return 0;
}