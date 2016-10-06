#ifndef structs_h
#define structs_h

#define MAX_CHILD_RULES 5
#define MAX_SIMBOLS 256
#define MAX_WORD 64

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char symbol_table[MAX_SIMBOLS][MAX_WORD];

// ----------------------------------------------------------------
// -------------------- VARIAVEL ESCOLHIDA ------------------------
// ----------------------------------------------------------------

typedef struct Variable {
    // union ChosenVariable *variable;
    char *variable_name;
    int variable_tag;
    int variable_num_nexts;
    char *token;
    struct Variable *variable_list[MAX_CHILD_RULES];
} Variable;
/*
typedef union ChosenVariable {
    union Program *program;         // tag 01  2 rules
    struct Function *function;      // tag 02  1 rule
    union ValueList *valueList;     // tag 03  3 rules
    union Value *value;             // tag 04  5 rules
    union TypeStruct *typeStruct;   // tag 05  2 rules 
    char *typeSimple;               // tag 06  1 simple type // MUDEI PARA TIPO V
    union ArgList *argList;         // tag 07  3 rules
    union StmtList *stmtList;       // tag 08  2 rules
    union Stmt *stmt;               // tag 09  8 rules
    union Block *block;             // tag 10  2 rules
    char *cmpAss;                   // tag 11  1 comparison string // MUDEI PARA TIPO V
    union AssignmentExp *assExp;    // tag 12  3 rules
    union Term *term;               // tag 13  3 rules
    union Factor *factor;           // tag 14  2 rules
} ChosenVariable;


// ----------------------------------------------------------------
// -------------------------- VARIAVEIS ---------------------------
// ----------------------------------------------------------------

typedef union Program {
    int tag;
} Program;

typedef struct Function {} Function;

typedef union ValueList {} ValueList;

typedef union Value {} Value;

typedef union TypeStruct {} TypeStruct;

typedef union ArgList {} ArgList;

typedef union StmtList {} StmtList;

typedef union Stmt {} Stmt;

typedef union Block {} Block;

typedef union AssignmentExp {} AssignmentExp;

typedef union Term {} Term;

typedef union Factor {} Factor;
*/

// ----------------------------------------------------------------
// ----------------- ADICAO DE NOS NA ARVORE ----------------------
// ----------------------------------------------------------------

Variable *new_variable (int tag_variable, int num_nexts, Variable *variable_list[], char *terminal) {
    Variable *v = (Variable *) malloc(sizeof(Variable));
    switch (tag_variable) {
            case (1): // Program
                v->variable_name = "Program";
                printf("%s\n", v->variable_name);
                v->variable_tag = 1;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
                break;
                
            case (2): // Function
                v->variable_name = "Function\n";
                printf("%s\n", v->variable_name);
                v->variable_tag = 2;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
               // for (int i = 0; i < num_nexts; i++) {
                   // if(v->variable_list[i])
                        //printf("<<%s>>\n", v->variable_list[i]->variable_name);
                //}
                break;
                
            case (3): // ValueList
                v->variable_name = "ValueList";
                printf("%s\n", v->variable_name);
                v->variable_tag = 3;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
                break;
                
            case (4): // Value - FAZER VARIAVEL COM ESSE NOME
                /*switch (tag_rule) {
                    case (1): // NUM_INT
                        //printf("%s\n", terminal);
                        break;
                    case (2): // NUM_FLOAT
                        //printf("%s\n", terminal);
                        break;
                    case (3): // CARACTERE
                        //printf("%s\n", terminal);
                        break;
                    case (4): // ID
                        //printf("%s\n", terminal);
                        break;
                    case (5): // ID '.' FIRST
                        //printf("%s.FIRST\n", terminal);
                        break;
                }*/
                v->variable_name = "Value";
                printf("%s\n", v->variable_name);
                v->variable_tag = 4;
                v->variable_num_nexts = num_nexts;
                v->token = terminal;
                *(v->variable_list) = NULL;
                printf("%s\n", terminal);
                break;
                
            case (5):
                v->variable_name = "TypeStruct";
                printf("%s\n", v->variable_name);
                v->variable_tag = 5;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
                break;
                
            case (6): // type_simple
                v->variable_name = "TypeSimple";
                printf("%s\n", v->variable_name);
                v->variable_tag = 6;
                v->variable_num_nexts = num_nexts;
                v->token = terminal;
                *(v->variable_list) = NULL;
                break;
                
            case (7):
                v->variable_name = "ArgList";
                printf("%s\n", v->variable_name);
                v->variable_tag = 7;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
                break;
                
            case (8):
                v->variable_name = "StmtList";
                printf("%s\n", v->variable_name);
                v->variable_tag = 8;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
                break;
                
            case (9): // Stmt
                /*switch (tag_rule) {
                    case (1): // declaração de variavel
                        break;
                    case (2): // chamada de função
                        break;
                    case (3): // chamada de função com retorno
                        break;
                    case (4): // if sem else
                        break;
                    case (5): // if com else
                        break;
                    case (6): // loop while
                        break;
                    case (7): // atribuicao qualquer
                        break;
                    case (8): // atribuicao com tipo fila
                        break;
                }*/
                v->variable_name = "Stmt";
                printf("%s\n", v->variable_name);
                v->variable_tag = 9;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
                break;
                
            case (10):
                v->variable_name = "Block";
                printf("%s\n", v->variable_name);
                v->variable_tag = 10;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
                break;
                
            case (11): // compare_assignemnt
                v->variable_name = "CompareAssignment";
                printf("%s\n", v->variable_name);
                v->variable_tag = 11;
                v->variable_num_nexts = num_nexts;
                v->token = terminal;
                *(v->variable_list) = NULL;
                break;
                
            case (12):
                v->variable_name = "AssignmentExp";
                printf("%s\n", v->variable_name);
                v->variable_tag = 12;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
                break;
                
            case (13):
                v->variable_name = "Term";
                printf("%s\n", v->variable_name);
                v->variable_tag = 13;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
                break;
                
            case (14):
                v->variable_name = "Factor";
                printf("%s\n", v->variable_name);
                v->variable_tag = 12;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *variable_list;
                break;
    }
    return v;
}


// ----------------------------------------------------------------
// ----------------- OPERAÇÕES COM A ARVORE -----------------------
// ----------------------------------------------------------------

void show_tree(Variable *root, int tabs, int index) {
    int i;
    printf(">> index: %d\n", index);
    for (i = 0; i < tabs; ++i) printf("  ");
    if (root->variable_list[index]) {
        printf("%s {\n", root->variable_name);
        
        // Percorre arvore top-down, left-to-right
        for (int j = 0; j < root->variable_num_nexts; j++) {
            printf(" . . . %s[%d] = %s {\n", root->variable_name, j, root->variable_list[j]->variable_name);
            show_tree(root->variable_list[j], tabs+1, j);
        }
        
        for (i = 0; i < tabs; ++i) printf("  ");
        printf("}\n");
    }
    else {
        printf("%s {\n", root->variable_name);
        for (i = 0; i < tabs; ++i) printf("  ");
        printf("  %s\n", root->token);
        for (i = 0; i < tabs; ++i) printf("  ");
        printf("}\n");
    }
    return;
}

void destroy_tree(Variable *root, int index) {
    // Percorre arvore top-down, left-to-right
    for (int j = 0; j < root->variable_num_nexts-1; j++) {
        destroy_tree(root->variable_list[j], j+1);
    }
    printf(":: Destruiu %s\n", root->variable_name);
    free(root);
    return;
}

// ----------------------------------------------------------------
// -------------------- TABELA DE SIMBOLOS ------------------------
// ----------------------------------------------------------------
/**
 * Procura simbolo na tabela de simbolos, que é um vetor de string.
 * Se ele está lá, retorna o indice.
 * Se não esta, adiciona e retorna o indice
 */
int add_symbol_on_table (char *s) {
    int i = 0;
    while (strcmp(symbol_table[i], ".") != 0) {
        if (strcmp(symbol_table[i], s) == 0)
            return i;
        i++;
    }
    strcpy(symbol_table[i], s);
    return i;
}

void show_symbol_table() {
    int i = 0;
    printf("\n=================================\n");
    printf("======= TABELA DE SIMBOLOS ======\n");
    printf("=================================\n");
    while (strcmp(symbol_table[i], ".") != 0) {
        printf("\t%d\t%s\n", i+1, symbol_table[i]);
        i++;
    }
    printf("\n=================================\n");
    printf("=================================\n");
    return;
}

#endif /* structs_h */