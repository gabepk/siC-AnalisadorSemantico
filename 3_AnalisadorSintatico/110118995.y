%{
#include "structs.h"
#define MAXSTR 50
void yyerror(char *s);
int yylex(void);

int id_corrente = 0;
%}

%union {
    char *str;
    struct Variable *v;
}
%start program

%token <str> NUM_INT NUM_FLOAT CARACTERE ID
%token <str> VOID FLOAT INT CHAR
%token <str> EQ NEQ LEQ GEQ LT GT
%token WHILE IF ELSE RETURN 
%token QUEUE FIRST 
%token ARROW SETLAST RMVFIRST

%type <v> program
%type <v> function
%type <v> valueList
%type <v> value
%type <v> type_struct
%type <v> type_simple
%type <v> argList
%type <v> stmtList
%type <v> stmt
%type <v> block
%type <v> compare_assignment
%type <v> assignment_expression
%type <v> term
%type <v> factor
%type <v> type_struct_expression
%%

// -----------------------------------------------------------------------------------------------------

program:	program function { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($2);
                                   $$ = new_variable(1, 2, &varList, 0); 
                                   printf("\n\n Arvore Sintatica:\n"); show_tree($$, 0, 0); destroy_tree($$, 0); }
                | function { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(1, 1, &varList, 0); 
                                   printf("\n\n Arvore Sintatica:\n"); show_tree($$, 0, 0); destroy_tree($$, 0); }
                ;

function:	type_struct ID '(' argList ')' '{' stmtList RETURN value ';' '}' { 
                                   Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($4);
                                   varList[2] = *($7);
                                   varList[3] = *($9);
                                   
                                   printf(">> >> %s\n", (&varList[0])->variable_name);
                                   printf(">> >> %s\n", (&varList[1])->variable_name);
                                   printf(">> >> %s\n", (&varList[2])->variable_name);
                                   printf(">> >> %s\n", (&varList[3])->variable_name);
                                   $$ = new_variable(2, 4, &varList, 0);
                                   add_symbol_on_table($2); }
                ;
                
// -----------------------------------------------------------------------------------------------------
                
valueList:      valueList ',' value { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(3, 2, &varList, 0); }
                | value { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(3, 1, &varList, 0); }
                | %empty { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(3, 0, &varList, 0); }
                ;

// -----------------------------------------------------------------------------------------------------
                
value:          NUM_INT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(4, 1, &varList, $1);
                                    add_symbol_on_table($1);}
                | NUM_FLOAT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(4, 1, &varList, $1);
                                    add_symbol_on_table($1);}
                | CARACTERE { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(4, 1, &varList, $1);
                                    add_symbol_on_table($1);}
                | ID { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(4, 1, &varList, $1);
                                    add_symbol_on_table($1);}
                | ID '.' FIRST { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(4, 1, &varList, $1);
                                    add_symbol_on_table($1);}
                ;

// -----------------------------------------------------------------------------------------------------
                
type_struct:    type_simple { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(5, 1, &varList, 0); }
                | QUEUE LT type_simple GT  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($3);
                                   $$ = new_variable(5, 1, &varList, 0); }
                ;

// -----------------------------------------------------------------------------------------------------                
                
type_simple:    VOID { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(6, 0, &varList, "void"); }
                | FLOAT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(6, 0, &varList, "float"); }
                | INT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(6, 0, &varList, "int"); }
                | CHAR { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(6, 0, &varList, "char"); }
                ;
                
// ----------------------------------------------------------------------------------------------------- 
                
argList:        argList ',' type_struct ID { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(7, 2, &varList, 0); 
                                   add_symbol_on_table($4);}
                | type_struct ID { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(7, 1, &varList, 0);
                                   add_symbol_on_table($2); }
                | %empty { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(7, 0, &varList, 0); }
                ;

// ----------------------------------------------------------------------------------------------------- 
                
stmtList:       stmtList stmt { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                    //varList[0] = *($1);
                                    //varList[1] = *($2);
                                    $$ = new_variable(8, 2, &varList, 0); }
                | %empty { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(8, 0, &varList, 0); }
                ;

// ----------------------------------------------------------------------------------------------------- 
                
stmt:           type_struct ID ';' 
                                   { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(9, 1, &varList, 0); 
                                   add_symbol_on_table($2);}
                | ID '(' valueList ')' ';' 
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($3);
                                   $$ = new_variable(9, 1, &varList, 0); 
                                   add_symbol_on_table($1); }
                | ID '=' ID '('  valueList ')' ';' 
                                   { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($5);
                                   $$ = new_variable(9, 1, &varList, 0); 
                                   add_symbol_on_table($1);
                                   add_symbol_on_table($3); }
                | IF '(' value compare_assignment value ')' block
                                  { Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($3);
                                   varList[1] = *($4);
                                   varList[2] = *($5);
                                   varList[3] = *($7);
                                   $$ = new_variable(9, 4, &varList, 0); }
                | IF '(' value compare_assignment value ')' block ELSE block
                                  { Variable *varList = (Variable *) malloc (5 * sizeof(Variable));
                                   varList[0] = *($3);
                                   varList[1] = *($4);
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
                                   $$ = new_variable(9, 4, &varList, 0); }
                | ID '=' assignment_expression ';'
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($3);
                                   $$ = new_variable(9, 1, &varList, 0); 
                                   add_symbol_on_table($1);}
                | type_struct_expression ';'
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(9, 1, &varList, 0); }
                ;
            
// ----------------------------------------------------------------------------------------------------- 
            
block:          stmt  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(10, 1, &varList, 0); }
                | '{' stmtList '}'  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($2);
                                   $$ = new_variable(10, 1, &varList, 0); }
                ;

// ----------------------------------------------------------------------------------------------------- 
                
compare_assignment:	EQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "=="); }
                        | NEQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "!="); }
                        | LEQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "<="); }
                        | GEQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, ">="); }
                        | LT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "<"); }
                        | GT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, ">"); }
                        ;

// ----------------------------------------------------------------------------------------------------- 
                        
assignment_expression:  assignment_expression '+' term
                                   { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(12, 2, &varList, 0); } // REDUNDANTE, poderia passar só "+"
                        | assignment_expression '-' term
                                   { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(12, 2, &varList, 0); } // REDUNDANTE, poderia passar só "-'
                        | term  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(12, 1, &varList, 0); }
                        ;
                        
// ----------------------------------------------------------------------------------------------------- 

term:           term '*' factor { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(13, 2, &varList, 0); }  // REDUNDANTE, poderia passar só "*"
                | term '/' factor { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(13, 2, &varList, 0); }  // REDUNDANTE, poderia passar só "/"
                | factor { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(13, 1, &varList, 0); }
                ;
                
// ----------------------------------------------------------------------------------------------------- 
                
factor:         value { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(14, 1, &varList, 0); }
                | '(' assignment_expression ')'
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($2);
                                   $$ = new_variable(14, 1, &varList, 0); }
                ;
                
// ----------------------------------------------------------------------------------------------------- 
            
type_struct_expression:   ID '.' SETLAST ARROW value  //  x.setlast->y (Add fim da fila)
                          | ID '=' ID '.' RMVFIRST // x = y.rmfirst;
                          ;

%%

extern int yylineno;

void yyerror(char *s) {
    printf("\t(sin) ERROR near line %d : %s\n", yylineno, s);
}

int main(void) {
    for (int i=0; i<256; i++) {
        strcpy(symbol_table[i], ".\0");
    }
    yyparse();
    show_symbol_table();
    return 0;
}

