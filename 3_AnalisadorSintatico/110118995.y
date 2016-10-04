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
    struct Variable *v;
}
%start program

%token <i> NUM_INT
%token <f> NUM_FLOAT
%token <c> CARACTERE
%token <str> ID
%token <str> VOID
%token <str> FLOAT 
%token <str> INT 
%token <str> CHAR
%token WHILE IF ELSE RETURN 
%token QUEUE FIRST 
%token EQ NEQ LEQ GEQ LT GT
%token ARROW SETLAST RMVFIRST

%type <v> program
%type <v> function
%type <v> valueList
%type <v> value
%type <v> type_struct
//%type <v> type_simple
%type <v> argList
%type <v> stmtList
%type <v> stmt
%type <v> block
//%type <v> compare_assignment
%type <v> assignment_expression
%type <v> term
%type <v> factor
%type <v> type_struct_expression
%%

// -----------------------------------------------------------------------------------------------------

program:	program function { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($2);
                                   $$ = new_variable(1, 1, &varList, 0); }
                | function { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(1, 2, &varList, 0); }
                ;
                
// -----------------------------------------------------------------------------------------------------

function:	type_struct ID '(' argList ')' '{' stmtList RETURN value ';' '}' { 
                                   Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($4);
                                   varList[2] = *($7);
                                   varList[3] = *($9);
                                   $$ = new_variable(2, 1, &varList, 0); }
                ;
                
// -----------------------------------------------------------------------------------------------------
                
valueList:      valueList ',' value { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(3, 1, &varList, 0); }
                | value { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(3, 2, &varList, 0); }
                | %empty { $$ = NULL; }
                ;

// -----------------------------------------------------------------------------------------------------
                
value:          NUM_INT { $$ = new_variable(4, 1, NULL, $1); }
                | NUM_FLOAT { $$ = new_variable(4, 2, NULL, $1); }
                | CARACTERE { $$ = new_variable(4, 3, NULL, $1); }
                | ID { $$ = new_variable(4, 3, NULL, $1); }
                | ID '.' FIRST { $$ = new_variable(4, 4, NULL, $1); }
                ;

// -----------------------------------------------------------------------------------------------------
                
type_struct:    type_simple { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(5, 1, &varList, 0); }
                | QUEUE LT type_simple GT  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($3);
                                   $$ = new_variable(5, 2, &varList, 0); }
                ;

// -----------------------------------------------------------------------------------------------------                
                
type_simple:    VOID { $$ = new_variable(6, 0, NULL, $1); }
                | FLOAT { $$ = new_variable(6, 0, NULL, $1); }
                | INT { $$ = new_variable(6, 0, NULL, $1); }
                | CHAR { $$ = new_variable(6, 0, NULL, $1); }
                ;
                
// ----------------------------------------------------------------------------------------------------- 
                
argList:        argList ',' type_struct ID { Variable *varList = (Variable *) malloc (3 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   varList[2] = *($4);
                                   $$ = new_variable(7, 1, &varList, 0); }
                | type_struct ID { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($2);
                                   $$ = new_variable(7, 2, &varList, 0); }
                | %empty { $$ = NULL; }
                ;

// ----------------------------------------------------------------------------------------------------- 
                
stmtList:       stmtList stmt { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($2);
                                   $$ = new_variable(8, 1, &varList, 0); }
                | %empty { $$ = NULL; }
                ;

// ----------------------------------------------------------------------------------------------------- 
                
stmt:           type_struct ID ';' 
                                   { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($2);
                                   $$ = new_variable(9, 1, &varList, 0); }
                | ID '(' valueList ')' ';' 
                                  { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(9, 2, &varList, 0); }
                | ID '=' ID '('  valueList ')' ';' 
                                   { Variable *varList = (Variable *) malloc (3 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   varList[2] = *($5);
                                   $$ = new_variable(9, 3, &varList, 0); }
                | IF '(' value compare_assignment value ')' block
                                  { Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($3);
                                   varList[1] = *($4);
                                   varList[2] = *($5);
                                   varList[3] = *($7);
                                   $$ = new_variable(9, 4, &varList, 0); }
                | IF '(' value compare_assignment value ')' block ELSE block
                                  { Variable *varList = (Variable *) malloc (5 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   varList[2] = *($5);
                                   varList[3] = *($7);
                                   varList[4] = *($9);
                                   $$ = new_variable(9, 5, &varList, 0); }
                | WHILE '(' value compare_assignment value ')' block
                                  { Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($3);
                                   varList[1] = *($4);
                                   varList[2] = *($5);
                                   varList[3] = *($7);
                                   $$ = new_variable(9, 6, &varList, 0); }
                | ID '=' assignment_expression ';'
                                  { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(9, 7, &varList, 0); }
                | type_struct_expression ';'
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(9, 8, &varList, 0); }
                ;
            
// ----------------------------------------------------------------------------------------------------- 
            
block:          stmt
                | '{' stmtList '}'
                ;

compare_assignment:	EQ
                        | NEQ
                        | LEQ
                        | GEQ
                        | LT
                        | GT
                        ;

assignment_expression:  assignment_expression '+' term
                        | assignment_expression '-' term
                        | term
                        ;

term:           term '*' factor
                | term '/' factor
                | factor
                ;
                
factor:         value
                | '(' assignment_expression ')'
                ;
            
type_struct_expression:   ID '.' SETLAST ARROW value  //  x.setlast->y (Add fim da fila)
                          | ID '=' ID '.' RMVFIRST // x = y.rmfirst;
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

