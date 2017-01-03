%{
#include "structs.h"
void yyerror(char *s);
int yylex(void);
%}

%union {
    char *str;
    struct Variable *v;
}
%start program_start

%token <str> NUM_INT NUM_FLOAT CARACTERE ID
%token <str> VOID FLOAT INT CHAR
%token <str> EQ NEQ LEQ GEQ LT GT
%token <str> WHILE IF ELSE RETURN 
%token <str> QUEUE FIRST 
%token <str> ARROW SETLAST RMVFIRST

%type <v> program_start
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


program_start:  program { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(0, 1, &varList, 0, 1, symbol_ids); 
                                   printf("\n\t\t[ Arvore Sintatica: ]\n\n"); show_tree($$, 0, 0);}
                ;

program:	program function { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($2);
                                   $$ = new_variable(1, 2, &varList, 0, 1, symbol_ids);  }
                | function { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   scope++;
                                   func_scope++;
                                   $$ = new_variable(1, 1, &varList, 0, 2, symbol_ids); }
                ;

function:	type_struct ID '(' argList ')' '{' stmtList RETURN value ';' '}' {
                                   strcpy(symbol_ids[0], $2);
                                   add_symbol_on_hash_table($2, ($1)->type_syn, 1, HIGHEST_SCOPE, HIGHEST_SCOPE); // ID recebe tipo herdado de type_struct
                                   Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($4);
                                   varList[2] = *($7);
                                   varList[3] = *($9);
                                   $$ = new_variable(2, 4, &varList, 0, 1, symbol_ids);
                                   }
                ;
                
// -----------------------------------------------------------------------------------------------------
                
valueList:      valueList ',' value { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(3, 2, &varList, 0, 1, symbol_ids); }
                | value { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(3, 1, &varList, 0, 2, symbol_ids); }
                | %empty { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(3, 0, &varList, 0, 3, symbol_ids); }
                | error ')' {  yyerrok;  yyerror ("Erro nos paramentros da funcao");}
                ;

// -----------------------------------------------------------------------------------------------------
                
value:          NUM_INT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    strcpy(symbol_ids[0], $1);
                                    add_symbol_on_hash_table($1, "int", 2, HIGHEST_SCOPE, MAX_SCOPES); // escopo desconhecido
                                    strcpy(varList->type_syn, "int");
                                    $$ = new_variable(4, 1, &varList, $1, 1, symbol_ids); }
                | NUM_FLOAT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    strcpy(symbol_ids[0], $1);
                                    add_symbol_on_hash_table($1, "float", 2, HIGHEST_SCOPE, MAX_SCOPES); // escopo desconhecido
                                    strcpy(varList->type_syn, "float");
                                    $$ = new_variable(4, 1, &varList, $1, 2, symbol_ids);}
                | CARACTERE { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    strcpy(symbol_ids[0], $1);
                                    add_symbol_on_hash_table($1, "char", 2, HIGHEST_SCOPE, MAX_SCOPES); // escopo desconhecido
                                    strcpy(varList->type_syn, "char");
                                    $$ = new_variable(4, 1, &varList, $1, 3, symbol_ids);}
                | ID { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    strcpy(symbol_ids[0], $1);
                                    add_symbol_on_hash_table($1, "?", 0, scope, HIGHEST_SCOPE); // escopo desconhecido
                                    strcpy(varList->type_syn, get_type_hash_table($1, scope, func_scope));
                                    $$ = new_variable(4, 1, &varList, $1, 4, symbol_ids);}
                | ID '.' FIRST { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    strcpy(symbol_ids[0], $1);
                                    add_symbol_on_hash_table($1, "?", 0, scope, HIGHEST_SCOPE); // escopo desconhecido
                                    strcpy(varList->type_syn, get_type_hash_table($1, scope, func_scope));
                                    $$ = new_variable(4, 1, &varList, $1, 5, symbol_ids);}
                ;

// -----------------------------------------------------------------------------------------------------
                
type_struct:    type_simple { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(5, 1, &varList, 0, 1, symbol_ids); }
                | QUEUE LT type_simple GT  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($3);
                                   $$ = new_variable(5, 1, &varList, 0, 2, symbol_ids); }
                ;

// -----------------------------------------------------------------------------------------------------                
                
type_simple:    VOID { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    strcpy(varList->type_syn, "void");
                                    $$ = new_variable(6, 0, &varList, "void", 1, symbol_ids); }
                | FLOAT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    strcpy(varList->type_syn, "float");
                                    $$ = new_variable(6, 0, &varList, "float", 2, symbol_ids); }
                | INT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    strcpy(varList->type_syn, "int");
                                    $$ = new_variable(6, 0, &varList, "int", 3, symbol_ids); }
                | CHAR { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    strcpy(varList->type_syn, "char");
                                    $$ = new_variable(6, 0, &varList, "char", 4, symbol_ids); }
                ;
                
// ----------------------------------------------------------------------------------------------------- 
                
argList:        argList ',' type_struct ID { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   strcpy(symbol_ids[0], $4);
                                   add_symbol_on_hash_table($4, ($3)->type_syn, 0, scope, HIGHEST_SCOPE); // ID recebe tipo herdado de type_struct
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(7, 2, &varList, 0, 1, symbol_ids); }
                | type_struct ID { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   strcpy(symbol_ids[0], $2);
                                   add_symbol_on_hash_table($2, ($1)->type_syn, 0, scope, HIGHEST_SCOPE); // ID recebe tipo herdado de type_struct
                                   varList[0] = *($1);
                                   $$ = new_variable(7, 1, &varList, 0, 2, symbol_ids);}
                | %empty { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(7, 0, &varList, 0, 3, symbol_ids); }
                | error '{' {  yyerrok;  yyerror ("Erro nos argumentos da funcao");}
                ;

// ----------------------------------------------------------------------------------------------------- 
                
stmtList:       stmtList stmt { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                    varList[0] = *($1);
                                    varList[1] = *($2);
                                    $$ = new_variable(8, 2, &varList, 0, 1, symbol_ids);}
                | %empty { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(8, 0, &varList, 0, 2, symbol_ids); }
                ;

// ----------------------------------------------------------------------------------------------------- 
                
stmt:           type_struct ID ';' 
                                   { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   strcpy(symbol_ids[0], $2);
                                   add_symbol_on_hash_table($2, ($1)->type_syn, 0, scope, higher_scope); // ID recebe tipo herdado de type_struct
                                   varList[0] = *($1);
                                   $$ = new_variable(9, 1, &varList, 0, 1, symbol_ids);}
                | ID '(' valueList ')' ';' 
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   strcpy(symbol_ids[0], $1);
                                   add_symbol_on_hash_table($1, "?", 1, 0, higher_scope); // escopo desconhecido
                                   varList[0] = *($3);
                                   $$ = new_variable(9, 1, &varList, 0, 2, symbol_ids); }
                | ID '=' ID '('  valueList ')' ';' 
                                   { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   strcpy(symbol_ids[0], $1);
                                   strcpy(symbol_ids[1], $3);
                                   add_symbol_on_hash_table($1, "?", 0, 0, higher_scope); // escopo desconhecido
                                   add_symbol_on_hash_table($3, "?", 1, 0, higher_scope); // escopo desconhecido
                                   varList[0] = *($5);
                                   $$ = new_variable(9, 1, &varList, 0, 3, symbol_ids); }
                | IF '(' value compare_assignment value ')' block
                                  { Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($3);
                                   varList[1] = *($4);
                                   varList[2] = *($5);
                                   varList[3] = *($7);
                                   $$ = new_variable(9, 4, &varList, 0, 4, symbol_ids); }
                | IF '(' value compare_assignment value ')' block ELSE block
                                  { Variable *varList = (Variable *) malloc (5 * sizeof(Variable));
                                   varList[0] = *($3);
                                   varList[1] = *($4);
                                   varList[2] = *($5);
                                   varList[3] = *($7);
                                   varList[4] = *($9);
                                   $$ = new_variable(9, 5, &varList, 0, 5, symbol_ids); }
                | WHILE '(' value compare_assignment value ')' block
                                  { Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($3);
                                   varList[1] = *($4);
                                   varList[2] = *($5);
                                   varList[3] = *($7);
                                   $$ = new_variable(9, 4, &varList, 0, 6, symbol_ids); }
                | ID '=' assignment_expression ';'
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   strcpy(symbol_ids[0], $1);
                                   add_symbol_on_hash_table($1, "?", 0, 0, higher_scope);
                                   varList[0] = *($3);
                                   $$ = new_variable(9, 1, &varList, 0, 7, symbol_ids); }
                | type_struct_expression ';'
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(9, 1, &varList, 0, 8, symbol_ids); }
                ;
            
// ----------------------------------------------------------------------------------------------------- 
            
block:          {higher_scope++; scope++;}  stmt  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($2);
                                   higher_scope--;
                                   $$ = new_variable(10, 1, &varList, 0, 1, symbol_ids); }
                | '{'  {higher_scope++; scope++; } stmtList '}'  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($3);
                                   higher_scope--;
                                   $$ = new_variable(10, 1, &varList, 0, 2, symbol_ids); }
                ;

// ----------------------------------------------------------------------------------------------------- 
                
compare_assignment:	EQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "==", 1, symbol_ids); }
                        | NEQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "!=", 2, symbol_ids); }
                        | LEQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "<=", 3, symbol_ids); }
                        | GEQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, ">=", 4, symbol_ids); }
                        | LT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "<", 5, symbol_ids); }
                        | GT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, ">", 6, symbol_ids); }
                        ;

// ----------------------------------------------------------------------------------------------------- 
                        
assignment_expression:  assignment_expression '+' term
                                   { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   strcpy(varList->type_syn, decide_type_operation(($1)->type_syn, ($3)->type_syn));
                                   $$ = new_variable(12, 2, &varList, "+", 1, symbol_ids); } // REDUNDANTE, poderia passar só "+"
                        | assignment_expression '-' term
                                   { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   strcpy(varList->type_syn, decide_type_operation(($1)->type_syn, ($3)->type_syn));
                                   $$ = new_variable(12, 2, &varList, "-", 2, symbol_ids); } // REDUNDANTE, poderia passar só "-'
                        | term  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   strcpy(varList->type_syn, ($1)->type_syn);
                                   $$ = new_variable(12, 1, &varList, "END", 3, symbol_ids); }
                        | error ';' { yyerrok;  yyerror ("Erro na operacao matematica");}
                        ;
                        
// ----------------------------------------------------------------------------------------------------- 

term:           term '*' factor { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   //printf("TIPO 1: _%c_\n TIPO 2: _%c_\n", ($1)->type_syn[0], ($3)->type_syn[0]);
                                   strcpy(varList->type_syn, decide_type_operation(($1)->type_syn, ($3)->type_syn));
                                   $$ = new_variable(13, 2, &varList, "*", 1, symbol_ids); }  // REDUNDANTE, poderia passar só "*"
                | term '/' factor { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   strcpy(varList->type_syn, decide_type_operation(($1)->type_syn, ($3)->type_syn));
                                   $$ = new_variable(13, 2, &varList, "/", 2, symbol_ids); }  // REDUNDANTE, poderia passar só "/"
                | factor { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   strcpy(varList->type_syn, ($1)->type_syn);
                                   $$ = new_variable(13, 1, &varList, "END", 3, symbol_ids); }
                | error ';' { yyerrok;  yyerror ("Erro na operacao matematica");}
                ;
                
// ----------------------------------------------------------------------------------------------------- 
                
factor:         value { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   strcpy(varList->type_syn, ($1)->type_syn);
                                   $$ = new_variable(14, 1, &varList, 0, 1, symbol_ids); }
                | '(' assignment_expression ')'
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($2);
                                   strcpy(varList->type_syn, ($2)->type_syn);
                                   $$ = new_variable(14, 1, &varList, 0, 2, symbol_ids); }
                ;
                
// ----------------------------------------------------------------------------------------------------- 
            
type_struct_expression:   ID '.' SETLAST ARROW value
                                   { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   strcpy(symbol_ids[0], $1);
                                   add_symbol_on_hash_table($1, "?", 0, 0, higher_scope); // ID deve ser FILA
                                   varList[0] = *($5);
                                   $$ = new_variable(15, 1, &varList, 0, 1, symbol_ids); }
                          | ID '=' ID '.' RMVFIRST 
                                   { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   strcpy(symbol_ids[0], $1); // ID deve ser o TIPO DA FILA
                                   strcpy(symbol_ids[0], $3); // ID deve ser FILA
                                   add_symbol_on_hash_table($1, "?", 0, 0, higher_scope);
                                   add_symbol_on_hash_table($3, "?", 0, 0, higher_scope);
                                   $$ = new_variable(15, 1, &varList, 0, 2, symbol_ids); }
                          ;

%%

void yyerror(char *s) {
    printf("\t(sin) ERROR near line %d : %s\n", yylineno, s);
}

int main(void) {
    int i, j;
    for (i=0; i<MAX_SYMBOLS_FOR_RULE; i++)
        strcpy(symbol_ids[i], ".");
   
    for (i=0; i<MAX_SCOPES; i++)
        for (j=0; j<MAX_SCOPES; j++)
            scope_matrix[i][j] = 0;
    
    yyparse();
    show_symbol_table();
    show_scope_matrix();
    return 0;
}


