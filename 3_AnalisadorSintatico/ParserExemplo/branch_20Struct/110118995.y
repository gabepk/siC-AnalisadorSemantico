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
    //union rule *r;
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

program:	program function { rule *r = new_rule(1, new_program(1, $1, $2)); 
                                   $$ = r->program; 
                                   printf("Arvore sintatica\n[\n");
                                   show_tree(r, 1);
                                   printf("\n]\n "); }
		| %empty {$$ = NULL; }
		;

function:	type_struct IDENTIFIER OPEN_PARENT arguments CLOSE_PARENT OPEN_BRACES statements RETURN value SEMICOLON CLOSE_BRACES { 
                         rule *r = new_rule(2, new_function($1, $2, $4, $7, $9));
                         $$ = r->func; }
		;

values:         values COMMA value { rule *r = new_rule(10, new_values(1, $1, $3)); $$ = r->vals; }
		| value { rule *r = new_rule(10, new_values(2, 0, $1)); $$ = r->vals; }
		| %empty { rule *r = new_rule(10, new_values(3, 0, 0)); $$ = r->vals; }
		;

value:          NUM_INT { rule *r = new_rule(11, new_value(1, $1, 0, 0, 0)); $$ = r->val; }
                | NUM_FLOAT { rule *r = new_rule(11, new_value(2, 0, $1, 0, 0)); $$ = r->val; }
                | CARACTERE { rule *r = new_rule(11, new_value(3, 0, 0, $1, 0)); $$ = r->val; }
                | IDENTIFIER { rule *r = new_rule(11, new_value(4, 0, 0, 0, $1)); $$ = r->val; }
                //| IDENTIFIER DOT FIRST // FALTA ESSE
                ;

type_struct:	type_simple { rule *r = new_rule(3, new_typeStr(1, $1, 0)); $$ = r->tst; }
		| QUEUE LT type_simple GT { rule *r = new_rule(3, new_typeStr(2, 0, new_typeQueue($3))); $$ = r->tst; }
		;

type_simple:	VOID  { rule *r = new_rule(4, new_typeSimple("void")); $$ = r->tsp; }
                | FLOAT { rule *r = new_rule(4, new_typeSimple("float")); $$ = r->tsp; }
                | INT { rule *r = new_rule(4, new_typeSimple("int")); $$ = r->tsp; }
                | CHAR { rule *r = new_rule(4, new_typeSimple("char")); $$ = r->tsp; }
		;
		
arguments:	arguments COMMA type_struct IDENTIFIER { 
                    rule *r = new_rule(5, new_arguments(1, $1, $3, $4)); 
                    $$ = r->args; }
		| type_struct IDENTIFIER { 
                    rule *r = new_rule(5, new_arguments(2, 0, $1, $2)); 
                    $$ = r->args; }
		| %empty { 
                    rule *r = new_rule(5, new_arguments(3, 0, 0, 0)); 
                    $$ = r->args; }
		;

statements:	statements statement { rule *r = new_rule(6, new_statements($1, $2)); $$ = r->stmts; }
		| %empty { rule *r = new_rule(6, new_statements(0, 0)); $$ = r->stmts; }
		;

statement:	type_struct IDENTIFIER SEMICOLON { 
                    rule *r = new_rule(7, new_statement(1, new_definition($1, $2), 0,0,0,0,0,0)); 
                    $$ = r->stmt; }
		| IDENTIFIER OPEN_PARENT values CLOSE_PARENT SEMICOLON { 
                    rule *r = new_rule(7, new_statement(2, 0,  new_funcCall($1, $3),0,0,0,0,0)); 
                    $$ = r->stmt; }
		//| IDENTIFIER ASSIGN IDENTIFIER OPEN_PARENT  values CLOSE_PARENT SEMICOLON // FALTA ESSE FUNCALL COM RETORNO
		| IF OPEN_PARENT value compare_assignment value CLOSE_PARENT block { 
                    rule *r = new_rule(7, new_statement(3, 0, 0, new_ifNoElse($3, $4, $5, $7), 0, 0, 0, 0)); 
                    $$ = r->stmt; }
		| IF OPEN_PARENT value compare_assignment value CLOSE_PARENT block ELSE block { 
                    rule *r = new_rule(7, new_statement(4, 0, 0, 0, new_ifWithElse($3, $4, $5, $7, $9), 0, 0, 0)); 
                    $$ = r->stmt; }
		| WHILE OPEN_PARENT value compare_assignment value CLOSE_PARENT block { 
                    rule *r = new_rule(7, new_statement(5, 0, 0, 0, 0, new_whileOp($3, $4, $5, $7), 0, 0)); 
                    $$ = r->stmt; }
		| IDENTIFIER ASSIGN assignment_expression SEMICOLON { 
                    rule *r = new_rule(7, new_statement(6, 0, 0, 0, 0, 0, new_assignment($1, $3), 0)); 
                    $$ = r->stmt; }
		//| identifier_struct_expression SEMICOLON { $$ = new_statement(7, 0, 0, 0, 0, 0, 0, $1)); }
		;
		
// Um bloco pode ser apenas um statment ou vários entre chaves. Serve para if, if-else, while
block:          statement { rule *r = new_rule(15, new_block(1, $1, 0)); $$ = r->bl; }
		| OPEN_BRACES statements CLOSE_BRACES { rule *r = new_rule(15, new_block(2, 0, $2)); $$ = r->bl; }
		;

compare_assignment:	EQ { rule *r = new_rule(16, new_cmpExpression("==")); $$ = r->cmpExp; }
                        | NEQ { rule *r = new_rule(16, new_cmpExpression("!=")); $$ = r->cmpExp; }
                        | LEQ { rule *r = new_rule(16, new_cmpExpression("<=")); $$ = r->cmpExp; }
                        | GEQ { rule *r = new_rule(16, new_cmpExpression(">=")); $$ = r->cmpExp; }
                        | LT { rule *r = new_rule(16, new_cmpExpression("<")); $$ = r->cmpExp; }
                        | GT { rule *r = new_rule(16, new_cmpExpression(">")); $$ = r->cmpExp; }
                        ;

assignment_expression:	assignment_expression PLUS term { 
                            rule *r = new_rule(17, new_assExpression($1, '+', $3)); 
                            $$ = r->assExp; }
			| assignment_expression MINUS term { 
                            rule *r = new_rule(17, new_assExpression($1, '-', $3)); 
                            $$ = r->assExp; }
			| term { 
                            rule *r = new_rule(17, new_assExpression(0, 0, $1)); 
                            $$ = r->assExp; }
			;
			
term:		term MULT factor { 
                    rule *r = new_rule(19, new_term($1, '*', $3));  
                    $$ = r->term; }
		| term DIV factor { 
                    rule *r = new_rule(19, new_term($1, '/', $3)); 
                    $$ = r->term; }
		| factor { 
                    rule *r = new_rule(19, new_term(0, 0, $1)); 
                    $$ = r->term; }
		;
		
factor:		value { 
                    rule *r = new_rule(20, new_factor(1, $1, 0));  
                    $$ = r->factor; }
		| OPEN_PARENT assignment_expression CLOSE_PARENT { 
                    rule *r = new_rule(20, new_factor(2, 0, $2));  
                    $$ = r->factor; }
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
