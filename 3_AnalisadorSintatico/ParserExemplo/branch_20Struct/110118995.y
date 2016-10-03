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
    union program *program;
    struct function *func;
    union typeStr *tst;
    struct typeSimple *tsp;
    struct arguments *args;
    struct statements *stmts;
    union statement *stmt;
    struct definition *def;
    struct funcCall *fc;
    struct values *vals;
    union value *val;
    struct ifNoElse *ife;
    struct ifWithElse *iwe;
    struct whileOp *wh;
    union block *bl;
    struct assExpression *assExp;
    struct cmpExpression *cmpExp;
    struct term *term;
    union factor *factor;
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

%type <program> program
%type <func> function
%type <tst> type_struct
%type <tsp> type_simple
%type <args> arguments
%type <stmts> statements
%type <stmt> statement
%type <vals> values
%type <val> value
%type <bl> block
%type <assExp> assignment_expression
%type <cmpExp> compare_assignment
%type <term> term
%type <factor> factor
//%type <idsExp> identifier_struct_expression

%%

program:	program function { $$ = new_program(1, $1, $2); }
		| %empty {$$ = new_program(2, 0, 0); }
		;

function:	type_struct IDENTIFIER OPEN_PARENT arguments CLOSE_PARENT OPEN_BRACES statements RETURN value SEMICOLON CLOSE_BRACES { 
                        $$ = new_function($1, $2, $4, $7, $9); }
		;

values:         values COMMA value { $$ = new_values(1, $1, $3); }
		| value { $$ = new_values(2, 0, $1); }
		| %empty { $$ = new_values(3, 0, 0); }
		;

value:          NUM_INT { $$ = new_value(1, $1, 0, 0, 0); }
                | NUM_FLOAT { $$ = new_value(2, 0, $1, 0, 0); }
                | CARACTERE { $$ = new_value(3, 0, 0, $1, 0); }
                | IDENTIFIER { $$ = new_value(4, 0, 0, 0, $1); }
                //| IDENTIFIER DOT FIRST // FALTA ESSE
                ;

type_struct:	type_simple { $$ = new_typeStr(1, $1, 0); }
		| QUEUE LT type_simple GT { $$ = new_typeStr(2, 0, new_typeQueue($3)); }
		;

type_simple:	VOID  { $$ = new_typeSimple("void"); }
                | FLOAT { $$ = new_typeSimple("float"); }
                | INT { $$ = new_typeSimple("int"); }
                | CHAR { $$ = new_typeSimple("char"); }
		;
		
arguments:	arguments COMMA type_struct IDENTIFIER { $$ = new_arguments(1, $1, $3, $4); }
		| type_struct IDENTIFIER { $$ = new_arguments(2, 0, $1, $2); }
		| %empty { $$ = new_arguments(3, 0, 0, 0); }
		;

statements:	statements statement { $$ = new_statements($1, $2); }
		| %empty { $$ = new_statements(0, 0); }
		;

// https://www.gnu.org/software/bison/manual/html_node/Non-Operators.html#Non-Operators (RESOLVE COM ASSOCIATIVIDADE)
statement:	type_struct IDENTIFIER SEMICOLON { 
                    $$ =  new_statement(1, new_definition($1, $2), 0,0,0,0,0,0); }
		| IDENTIFIER OPEN_PARENT values CLOSE_PARENT SEMICOLON { 
                    $$ =  new_statement(2, 0,  new_funcCall($1, $3),0,0,0,0,0);}
		//| IDENTIFIER ASSIGN IDENTIFIER OPEN_PARENT  values CLOSE_PARENT SEMICOLON // FALTA ESSE FUNCALL COM RETORNO
		| IF OPEN_PARENT value compare_assignment value CLOSE_PARENT block { 
                    $$ = new_statement(3, 0, 0, new_ifNoElse($3, $4, $5, $7), 0, 0, 0, 0); }
		| IF OPEN_PARENT value compare_assignment value CLOSE_PARENT block ELSE block { 
                    $$ = new_statement(4, 0, 0, 0, new_ifWithElse($3, $4, $5, $7, $9), 0, 0, 0); }
		| WHILE OPEN_PARENT value compare_assignment value CLOSE_PARENT block { 
                    $$ = new_statement(5, 0, 0, 0, 0, new_whileOp($3, $4, $5, $7), 0, 0); }
		| IDENTIFIER ASSIGN assignment_expression SEMICOLON { 
                    $$ = new_statement(6, 0, 0, 0, 0, 0, new_assignment($1, $3), 0); }
		//| identifier_struct_expression SEMICOLON { $$ = new_statement(7, 0, 0, 0, 0, 0, 0, $1)); }
		;
		
// Um bloco pode ser apenas um statment ou vários entre chaves. Serve para if, if-else, while
block:          statement { $$ = new_block(1, $1, 0); }
		| OPEN_BRACES statements CLOSE_BRACES { $$ = new_block(2, 0, $2); }
		;

compare_assignment:	EQ { $$ = new_cmpExpression("=="); }
                        | NEQ { $$ = new_cmpExpression("!="); }
                        | LEQ { $$ = new_cmpExpression("<="); }
                        | GEQ { $$ = new_cmpExpression(">="); }
                        | LT { $$ = new_cmpExpression("<"); }
                        | GT { $$ = new_cmpExpression(">"); }
                        ;

assignment_expression:	assignment_expression PLUS term { $$ = new_assExpression($1, '+', $3); }
			| assignment_expression MINUS term { $$ = new_assExpression($1, '-', $3); }
			| term { $$ = new_assExpression(0, 0, $1); }
			;
			
term:		term MULT factor { $$ = new_term($1, '*', $3); }
		| term DIV factor { $$ = new_term($1, '/', $3); }
		| factor { $$ = new_term(0, 0, $1); }
		;
		
factor:		value {$$ = new_factor(1, $1, 0); }
		| OPEN_PARENT assignment_expression CLOSE_PARENT {$$ = new_factor(2, 0, $2); }
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