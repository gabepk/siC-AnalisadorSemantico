%{
#include "structs.h"
#define MAXSTR 50
void yyerror(char *s);
int yylex(void);

int id_index[5];

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
                                   $$ = new_variable(0, 1, &varList, 0, 1, id_index); 
                                   printf("\n\t\t[ Arvore Sintatica: ]\n\n"); show_tree($$, 0, 0);}
                ;

program:	program function { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($2);
                                   $$ = new_variable(1, 2, &varList, 0, 1, id_index);  }
                | function { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(1, 1, &varList, 0, 2, id_index); }
                ;

function:	type_struct ID '(' argList ')' '{' stmtList RETURN value ';' '}' {
                                   id_index[0] = add_symbol_on_table($2);
                                   Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($4);
                                   varList[2] = *($7);
                                   varList[3] = *($9);
                                   $$ = new_variable(2, 4, &varList, 0, 1, id_index);
                                   }
                ;
                
// -----------------------------------------------------------------------------------------------------
                
valueList:      valueList ',' value { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(3, 2, &varList, 0, 1, id_index); }
                | value { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(3, 1, &varList, 0, 2, id_index); }
                | %empty { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(3, 0, &varList, 0, 3, id_index); }
                | error ')' {  yyerrok;  yyerror ("Erro nos paramentros da funcao");}
                ;

// -----------------------------------------------------------------------------------------------------
                
value:          NUM_INT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    id_index[0] = add_symbol_on_table($1);
                                    $$ = new_variable(4, 1, &varList, $1, 1, id_index); }
                | NUM_FLOAT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    id_index[0] = add_symbol_on_table($1);
                                    $$ = new_variable(4, 1, &varList, $1, 2, id_index);}
                | CARACTERE { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    id_index[0] = add_symbol_on_table($1);
                                    $$ = new_variable(4, 1, &varList, $1, 3, id_index);}
                | ID { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    id_index[0] = add_symbol_on_table($1);
                                    $$ = new_variable(4, 1, &varList, $1, 4, id_index);}
                | ID '.' FIRST { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    id_index[0] = add_symbol_on_table($1);
                                    $$ = new_variable(4, 1, &varList, $1, 5, id_index);}
                ;

// -----------------------------------------------------------------------------------------------------
                
type_struct:    type_simple { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(5, 1, &varList, 0, 1, id_index); }
                | QUEUE LT type_simple GT  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($3);
                                   $$ = new_variable(5, 1, &varList, 0, 2, id_index); }
                ;

// -----------------------------------------------------------------------------------------------------                
                
type_simple:    VOID { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(6, 0, &varList, "void", 1, id_index); }
                | FLOAT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(6, 0, &varList, "float", 2, id_index); }
                | INT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(6, 0, &varList, "int", 3, id_index); }
                | CHAR { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(6, 0, &varList, "char", 4, id_index); }
                ;
                
// ----------------------------------------------------------------------------------------------------- 
                
argList:        argList ',' type_struct ID { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   id_index[0] = add_symbol_on_table($4);
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(7, 2, &varList, 0, 1, id_index); }
                | type_struct ID { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   id_index[0] =  add_symbol_on_table($2);
                                   varList[0] = *($1);
                                   $$ = new_variable(7, 1, &varList, 0, 2, id_index);}
                | %empty { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(7, 0, &varList, 0, 3, id_index); }
                | error '{' {  yyerrok;  yyerror ("Erro nos argumentos da funcao");}
                ;

// ----------------------------------------------------------------------------------------------------- 
                
stmtList:       stmtList stmt { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                    varList[0] = *($1);
                                    varList[1] = *($2);
                                    $$ = new_variable(8, 2, &varList, 0, 1, id_index); }
                | %empty { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(8, 0, &varList, 0, 2, id_index); }
                ;

// ----------------------------------------------------------------------------------------------------- 
                
stmt:           type_struct ID ';' 
                                   { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   id_index[0] = add_symbol_on_table($2);
                                   varList[0] = *($1);
                                   $$ = new_variable(9, 1, &varList, 0, 1, id_index);}
                | ID '(' valueList ')' ';' 
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   id_index[0] = add_symbol_on_table($1);
                                   varList[0] = *($3);
                                   $$ = new_variable(9, 1, &varList, 0, 2, id_index); }
                | ID '=' ID '('  valueList ')' ';' 
                                   { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   id_index[0] = add_symbol_on_table($1);
                                   id_index[1] = add_symbol_on_table($3);
                                   varList[0] = *($5);
                                   $$ = new_variable(9, 1, &varList, 0, 3, id_index); }
                | IF '(' value compare_assignment value ')' block
                                  { Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($3);
                                   varList[1] = *($4);
                                   varList[2] = *($5);
                                   varList[3] = *($7);
                                   $$ = new_variable(9, 4, &varList, 0, 4, id_index); }
                | IF '(' value compare_assignment value ')' block ELSE block
                                  { Variable *varList = (Variable *) malloc (5 * sizeof(Variable));
                                   varList[0] = *($3);
                                   varList[1] = *($4);
                                   varList[2] = *($5);
                                   varList[3] = *($7);
                                   varList[4] = *($9);
                                   $$ = new_variable(9, 5, &varList, 0, 5, id_index); }
                | WHILE '(' value compare_assignment value ')' block
                                  { Variable *varList = (Variable *) malloc (4 * sizeof(Variable));
                                   varList[0] = *($3);
                                   varList[1] = *($4);
                                   varList[2] = *($5);
                                   varList[3] = *($7);
                                   $$ = new_variable(9, 4, &varList, 0, 6, id_index); }
                | ID '=' assignment_expression ';'
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   id_index[0] = add_symbol_on_table($1);
                                   varList[0] = *($3);
                                   $$ = new_variable(9, 1, &varList, 0, 7, id_index); }
                | type_struct_expression ';'
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(9, 1, &varList, 0, 8, id_index); }
                ;
            
// ----------------------------------------------------------------------------------------------------- 
            
block:          stmt  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(10, 1, &varList, 0, 1, id_index); }
                | '{' stmtList '}'  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($2);
                                   $$ = new_variable(10, 1, &varList, 0, 2, id_index); }
                ;

// ----------------------------------------------------------------------------------------------------- 
                
compare_assignment:	EQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "==", 1, id_index); }
                        | NEQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "!=", 2, id_index); }
                        | LEQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "<=", 3, id_index); }
                        | GEQ { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, ">=", 4, id_index); }
                        | LT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, "<", 5, id_index); }
                        | GT { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                    $$ = new_variable(11, 0, &varList, ">", 6, id_index); }
                        ;

// ----------------------------------------------------------------------------------------------------- 
                        
assignment_expression:  assignment_expression '+' term
                                   { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(12, 2, &varList, "+", 1, id_index); } // REDUNDANTE, poderia passar só "+"
                        | assignment_expression '-' term
                                   { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(12, 2, &varList, "-", 2, id_index); } // REDUNDANTE, poderia passar só "-'
                        | term  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(12, 1, &varList, "END", 3, id_index); }
                        | error ';' { yyerrok;  yyerror ("Erro na operacao matematica");}
                        ;
                        
// ----------------------------------------------------------------------------------------------------- 

term:           term '*' factor { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(13, 2, &varList, "*", 1, id_index); }  // REDUNDANTE, poderia passar só "*"
                | term '/' factor { Variable *varList = (Variable *) malloc (2 * sizeof(Variable));
                                   varList[0] = *($1);
                                   varList[1] = *($3);
                                   $$ = new_variable(13, 2, &varList, "/", 2, id_index); }  // REDUNDANTE, poderia passar só "/"
                | factor { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(13, 1, &varList, "END", 3, id_index); }
                | error ';' { yyerrok;  yyerror ("Erro na operacao matematica");}
                ;
                
// ----------------------------------------------------------------------------------------------------- 
                
factor:         value { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($1);
                                   $$ = new_variable(14, 1, &varList, 0, 1, id_index); }
                | '(' assignment_expression ')'
                                  { Variable *varList = (Variable *) malloc (1 * sizeof(Variable));
                                   varList[0] = *($2);
                                   $$ = new_variable(14, 1, &varList, 0, 2, id_index); }
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
    int i;
    for (i=0; i<256; i++) {
        strcpy(symbol_table[i], ".\0");
    }
    for (i=0; i<5; i++) {
        id_index[i] = 0;
    }
    yyparse();
    show_symbol_table();
    return 0;
}

