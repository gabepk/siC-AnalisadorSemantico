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
    int rule_num;
    int id_index[5];
    struct Variable *variable_list[MAX_CHILD_RULES];
} Variable;

// ----------------------------------------------------------------
// ----------------- ADICAO DE NOS NA ARVORE ----------------------
// ----------------------------------------------------------------

Variable *new_variable (int tag_variable, int num_nexts, Variable *list[], char *terminal, int rule_num, int id_index[]) {
    Variable *v = (Variable *) malloc(sizeof(Variable));
    v->variable_num_nexts = num_nexts;
    *(v->variable_list) = *list;
    strcpy(v->token, "END");
    v->rule_num = rule_num;
    *(v->id_index) = *id_index;
    switch (tag_variable) {
            case (0): // Program_start
                strcpy(v->variable_name, "ProgramStart");
                v->variable_tag = 0;
                break;
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
                
            case (4):
                strcpy(v->variable_name, "Value");
                v->variable_tag = 4;
                strcpy(v->token, terminal);
                break;
                
            case (5):
                strcpy(v->variable_name, "TypeStruct");
                v->variable_tag = 5;
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
                
            case (9):
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
                strcpy(v->token, terminal);
                break;
                
            case (13):
                strcpy(v->variable_name, "Term");
                v->variable_tag = 13;
                strcpy(v->token, terminal);
                break;
                
            case (14):
                strcpy(v->variable_name, "Factor");
                v->variable_tag = 14;
                break;
    }
    return v;
}


// ----------------------------------------------------------------
// ----------------- OPERAÇÕES COM A ARVORE -----------------------
// ----------------------------------------------------------------

void show_tree(Variable *root, int tabs, int index) {
    int i;
    for (i = 0; i < tabs; ++i) printf("|  ");
    if (strcmp(root->token, "END") == 0 || 
        strcmp(root->token, "+") == 0 ||
        strcmp(root->token, "-") == 0 || 
        strcmp(root->token, "*") == 0 || 
        strcmp(root->token, "/") == 0) {
        
        printf("[%s] \n", root->variable_name);

        switch (root->variable_tag) {
            case (2): // Function
                show_tree((*root->variable_list+0), tabs+1, 0);
                for (i = 0; i < tabs; ++i) printf("|  ");
                printf("%s\n", symbol_table[root->id_index[0]]); // Encontrar ID
                for (i = 0; i < tabs; ++i) printf("|  ");
                printf("(\n");
                show_tree((*root->variable_list+1), tabs+1, 1);
                for (i = 0; i < tabs; ++i) printf("|  ");
                printf(")\n");
                for (i = 0; i < tabs; ++i) printf("|  ");
                printf("{\n");
                show_tree((*root->variable_list+2), tabs+1, 2);
                for (i = 0; i < tabs; ++i) printf("|  ");
                printf("RETURN\n");
                show_tree((*root->variable_list+3), tabs+1, 3);
                for (i = 0; i < tabs; ++i) printf("|  ");
                printf(";\n");
                for (i = 0; i < tabs; ++i) printf("|  ");
                printf("}\n");
                break;
                
            case (3): // ValueList
                if (root->rule_num != 3) { // != empty
                    show_tree((*root->variable_list+0), tabs+1, 0);
                    if (root->rule_num == 1) {
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(",\n");
                        show_tree((*root->variable_list+1), tabs+1, 1);
                    }
                }
                break;
                
            case (5): // TypeStruct
                if (root->rule_num == 2) {
                    for (i = 0; i < tabs; ++i) printf("|  ");
                    printf("QUEUE\n");
                    for (i = 0; i < tabs; ++i) printf("|  ");
                    printf("<\n");
                }
                show_tree((*root->variable_list+0), tabs+1, 0);
                if (root->rule_num == 2) {
                    for (i = 0; i < tabs; ++i) printf("|  ");
                    printf(">\n");
                }
                break;
                
            case (7): // ArgList
                if (root->rule_num != 3) { // != empty
                    show_tree((*root->variable_list+0), tabs+1, 0);
                    if (root->rule_num == 1) {
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(",\n");
                        show_tree((*root->variable_list+1), tabs+1, 1);
                    }
                    for (i = 0; i < tabs; ++i) printf("|  ");
                    printf("%s\n", symbol_table[root->id_index[0]]);
                }
                break;
                
            case (9):// Stmt
                switch(root->rule_num) {
                    case(1):
                        show_tree((*root->variable_list+0), tabs+1, 0);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("%s\n", symbol_table[root->id_index[0]]);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(";\n");
                        break;
                        
                    case(2):
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("%s\n", symbol_table[root->id_index[0]]);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("(\n");
                        show_tree((*root->variable_list+0), tabs+1, 0);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(")\n");
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(";\n");
                        break;
                        
                    case(3):
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("%s\n", symbol_table[root->id_index[0]]);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("=\n");
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("%s\n", symbol_table[root->id_index[1]]);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("(\n");
                        show_tree((*root->variable_list+0), tabs+1, 0);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(")\n");
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(";\n");
                        break;
                    case(4):
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("IF\n");
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("(\n");
                        show_tree((*root->variable_list+0), tabs+1, 0);
                        show_tree((*root->variable_list+1), tabs+1, 1);
                        show_tree((*root->variable_list+2), tabs+1, 2);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(")\n");
                        show_tree((*root->variable_list+3), tabs+1, 3);
                        break;
                    case(5):
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("IF\n");
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("(\n");
                        show_tree((*root->variable_list+0), tabs+1, 0);
                        show_tree((*root->variable_list+1), tabs+1, 1);
                        show_tree((*root->variable_list+2), tabs+1, 2);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(")\n");
                        show_tree((*root->variable_list+3), tabs+1, 3);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("ELSE\n");
                        show_tree((*root->variable_list+3), tabs+1, 4);
                        break;
                    case(6):
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("WHILE\n");
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("(\n");
                        show_tree((*root->variable_list+0), tabs+1, 0);
                        show_tree((*root->variable_list+1), tabs+1, 1);
                        show_tree((*root->variable_list+2), tabs+1, 2);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(")\n");
                        show_tree((*root->variable_list+3), tabs+1, 3);
                        break;
                    case(7):
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("%s\n", symbol_table[root->id_index[0]]);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("=\n");
                        show_tree((*root->variable_list+0), tabs+1, 0);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(";\n");
                        break;
                    case(8):
                        show_tree((*root->variable_list+0), tabs+1, 0);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(";\n");
                        break;
                }
                break;
                
            case (10):
                if (root->rule_num == 2) {
                    for (i = 0; i < tabs; ++i) printf("|  ");
                    printf("{\n");
                }
                show_tree((*root->variable_list+0), tabs+1, 0);
                if (root->rule_num == 2) {
                    for (i = 0; i < tabs; ++i) printf("|  ");
                    printf("}\n");
                }
                break;
                
            case (12):
            case (13):
                show_tree((*root->variable_list+0), tabs+1, 0);
                if (root->rule_num != 3) {
                    for (i = 0; i < tabs; ++i) printf("|  ");
                    printf("%s\n", root->token);
                    show_tree((*root->variable_list+1), tabs+1, 1);
                }
                break;
                
            case (14):
                if (root->rule_num == 2) {
                    for (i = 0; i < tabs; ++i) printf("|  ");
                    printf("(\n");
                }
                show_tree((*root->variable_list+0), tabs+1, 0);
                if (root->rule_num == 2) {
                    for (i = 0; i < tabs; ++i) printf("|  ");
                    printf(")\n");
                }
                break;
                
            default:
                for (int j = 0; j < root->variable_num_nexts; j++) {
                    show_tree((*root->variable_list+j), tabs+1, j);
                }
                break;
        }
    }
    else {
        printf("%s: %s\n", root->variable_name, root->token);
    }
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