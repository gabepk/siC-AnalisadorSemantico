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
    char variable_name[MAX_WORD];
    int variable_tag;
    int variable_num_nexts;
    char token[MAX_WORD];
    struct Variable *variable_list[MAX_CHILD_RULES];
} Variable;

// ----------------------------------------------------------------
// ----------------- ADICAO DE NOS NA ARVORE ----------------------
// ----------------------------------------------------------------

Variable *new_variable (int tag_variable, int num_nexts, Variable *list[], char *terminal) {
    Variable *v = (Variable *) malloc(sizeof(Variable));
    v->variable_num_nexts = num_nexts;
    *(v->variable_list) = *list;
    strcpy(v->token, "-");
    switch (tag_variable) {
            case (1): // Program
                strcpy(v->variable_name, "Program");
                v->variable_tag = 1;
                break;
                
            case (2): // Function
                strcpy(v->variable_name, "Function");
                v->variable_tag = 2;           
                break;
                
            case (3): // ValueList
                strcpy(v->variable_name, "ValueList");
                v->variable_tag = 3;
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
                strcpy(v->variable_name, "Value");
                v->variable_tag = 4;
                strcpy(v->token, terminal);
                break;
                
            case (5):
                strcpy(v->variable_name, "TypeStruct");
                v->variable_tag = 5;
                v->variable_num_nexts = num_nexts;
                *(v->variable_list) = *list;
                break;
                
            case (6): // type_simple
                strcpy(v->variable_name, "TypeSimple");
                v->variable_tag = 6;
                strcpy(v->token, terminal);
                break;
                
            case (7):
                strcpy(v->variable_name, "ArgList");
                v->variable_tag = 7;
                break;
                
            case (8):
                strcpy(v->variable_name, "StmtList");
                v->variable_tag = 8;
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
                strcpy(v->variable_name, "Stmt");
                v->variable_tag = 9;
                break;
                
            case (10):
                strcpy(v->variable_name, "Block");
                v->variable_tag = 10;
                break;
                
            case (11): // compare_assignemnt
                strcpy(v->variable_name, "CompareAssignment");
                v->variable_tag = 11;
                strcpy(v->token, terminal);
                break;
                
            case (12):
                strcpy(v->variable_name, "AssignmentExp");
                v->variable_tag = 12;
                break;
                
            case (13):
                strcpy(v->variable_name, "Term");
                v->variable_tag = 13;
                break;
                
            case (14):
                strcpy(v->variable_name, "Factor");
                v->variable_tag = 12;
                break;
    }
    return v;
}


// ----------------------------------------------------------------
// ----------------- OPERAÇÕES COM A ARVORE -----------------------
// ----------------------------------------------------------------

void show_tree(Variable *root, int tabs, int index) {
    int i;
    //printf(">> index: %d\n", index);
    for (i = 0; i < tabs; ++i) printf("|  ");
    //if ((*root->variable_list+index)) 
    if (strcmp(root->token, "-") == 0){
        printf("1:%s {\n", root->variable_name);
        
        // Percorre arvore top-down, left-to-right
        for (int j = 0; j < root->variable_num_nexts; j++) {
            //printf(" . . . %s[%d] = %s {\n", root->variable_name, j, (*root->variable_list+j)->variable_name);
            show_tree((*root->variable_list+j), tabs+1, j);
        }
        
        for (i = 0; i < tabs; ++i) printf("|  ");
        printf("}\n");
    }
    else {
        printf("%s\n", root->token);
    }
    return;
}
 
void destroy_tree(Variable *root, int index) {
    // Percorre arvore top-down, left-to-right
    for (int j = 0; j < root->variable_num_nexts-1; j++) {
        destroy_tree((*root->variable_list+j), j+1);
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