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
    union rule *r;
    /*union program *program;
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
    union factor *factor;*/
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

%type <r> program
%type <r> function
%type <r> type_struct
%type <r> type_simple
%type <r> arguments
%type <r> statements
%type <r> statement
%type <r> values
%type <r> value
%type <r> block
%type <r> assignment_expression
%type <r> compare_assignment
%type <r> term
%type <r> factor
//%type <idsExp> identifier_struct_expression

%%

program:	program function { $$ = new_program(1, 1, $1, $2); // FALTA BOTAR TAGS NAS REGRAS
                                   printf("Arvore sintatica\n[\n");
                                   show_tree($$, 1);
                                   printf("\n]\n "); }
		| %empty { $$ = NULL; }
		;

function:	type_struct IDENTIFIER OPEN_PARENT arguments CLOSE_PARENT OPEN_BRACES statements RETURN value SEMICOLON CLOSE_BRACES { 
                         $$ = new_function(2, $1, $2, $4, $7, $9); }
		;

values:         values COMMA value { $$ = new_values(10, 1, $1, $3);}
		| value { $$ = new_values(10, 2, 0, $1); }
		| %empty { $$ = new_values(10, 3, 0, 0); }
		;

value:          NUM_INT { $$ = new_value(11, 1, $1, 0, 0, 0); }
                | NUM_FLOAT { $$ = new_value(11, 2, 0, $1, 0, 0); }
                | CARACTERE { $$ = new_value(11, 3, 0, 0, $1, 0); }
                | IDENTIFIER { $$ = new_value(11, 4, 0, 0, 0, $1); }
                //| IDENTIFIER DOT FIRST // FALTA ESSE
                ;

type_struct:	type_simple { $$ = new_typeStr(3, 1, $1, 0); }
		| QUEUE LT type_simple GT { $$ = new_typeStr(3, 2, 0, new_typeQueue(0, $3)); }
		;

type_simple:	VOID  { $$ = new_typeSimple(4, "void"); }
                | FLOAT { $$ = new_typeSimple(4, "float"); }
                | INT { $$ = new_typeSimple(4, "int");  }
                | CHAR { $$ = new_typeSimple(4, "char"); }
		;
		
arguments:	arguments COMMA type_struct IDENTIFIER { $$ = new_arguments(5, 1, $1, $3, $4); }
		| type_struct IDENTIFIER { $$ = new_arguments(5, 2, 0, $1, $2); }
		| %empty { $$ = new_arguments(5, 3, 0, 0, 0); }
		;

statements:	statements statement { $$ = new_statements(6, $1, $2); }
		| %empty { $$ = new_statements(6, 0, 0); }
		;

statement:	type_struct IDENTIFIER SEMICOLON { 
                    $$ = new_statement(7, 1, new_definition(8, $1, $2), 0,0,0,0,0,0); }
		| IDENTIFIER OPEN_PARENT values CLOSE_PARENT SEMICOLON { 
                    $$ = new_statement(7, 2, 0,  new_funcCall(9, $1, $3),0,0,0,0,0); }
		//| IDENTIFIER ASSIGN IDENTIFIER OPEN_PARENT  values CLOSE_PARENT SEMICOLON // FALTA ESSE FUNCALL COM RETORNO
		| IF OPEN_PARENT value compare_assignment value CLOSE_PARENT block { 
                    $$ = new_statement(7, 3, 0, 0, new_ifNoElse(12, $3, $4, $5, $7), 0, 0, 0, 0); }
		| IF OPEN_PARENT value compare_assignment value CLOSE_PARENT block ELSE block { 
                    $$ = new_statement(7, 4, 0, 0, 0, new_ifWithElse(14, $3, $4, $5, $7, $9), 0, 0, 0); }
		| WHILE OPEN_PARENT value compare_assignment value CLOSE_PARENT block { 
                    $$ = new_statement(7, 5, 0, 0, 0, 0, new_whileOp(15, $3, $4, $5, $7), 0, 0); }
		| IDENTIFIER ASSIGN assignment_expression SEMICOLON { 
                    $$ = new_statement(7, 6, 0, 0, 0, 0, 0, new_assignment(17, $1, $3), 0); }
		//| identifier_struct_expression SEMICOLON { $$ = new_statement(7, 0, 0, 0, 0, 0, 0, $1)); }
		;
		
// Um bloco pode ser apenas um statment ou vários entre chaves. Serve para if, if-else, while
block:          statement { $$ = new_block(15, 1, $1, 0); }
		| OPEN_BRACES statements CLOSE_BRACES { $$ = new_block(15, 2, 0, $2);  }
		;

compare_assignment:	EQ { $$ = new_cmpExpression(16, "=="); }
                        | NEQ { $$ = new_cmpExpression(16, "!="); }
                        | LEQ { $$ = new_cmpExpression(16, "<="); }
                        | GEQ { $$ = new_cmpExpression(16, ">="); }
                        | LT { $$ = new_cmpExpression(16, "<"); }
                        | GT { $$ = new_cmpExpression(16, ">"); }
                        ;

assignment_expression:	assignment_expression PLUS term { $$ = new_assExpression(17, $1, '+', $3); }
			| assignment_expression MINUS term { $$ = new_assExpression(17, $1, '-', $3); }
			| term { $$ = new_assExpression(17, 0, 0, $1); }
			;
			
term:		term MULT factor { $$ = new_term(19, $1, '*', $3); }
		| term DIV factor { $$ = new_term(19, $1, '/', $3); }
		| factor { $$ = new_term(19, 0, 0, $1); }
		;
		
factor:		value { $$ = new_factor(20, 1, $1, 0); }
		| OPEN_PARENT assignment_expression CLOSE_PARENT { $$ = new_factor(20, 2, 0, $2); }
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
