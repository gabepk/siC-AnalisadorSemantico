#ifndef structs_h
#define structs_h

#define HIGHEST_SCOPE 0
#define MAX_SCOPES 20
#define MAX_SYMBOLS_FOR_RULE 3
#define MAX_CHILD_RULES 5
#define MAX_WORD 64

#include "lib/uthash.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
char symbol_ids[MAX_SYMBOLS_FOR_RULE][MAX_WORD];
struct symbol_hash_table *symbols = NULL;

int scope_matrix[MAX_SCOPES][MAX_SCOPES];
int scope = 1; // Soh incrementa
int func_scope = 0;
int higher_scope = 0; // incrementa e decrementa

// ----------------------------------------------------------------
// -------------------- TABELA DE SIMBOLOS ------------------------
// ----------------------------------------------------------------

typedef struct symbol_hash_table {
    char key[MAX_WORD+4];
    char str_id[MAX_WORD];
    char type[MAX_WORD];
    int scope;
    int higher_scope;
    int func_scope;
    UT_hash_handle hh;
} symbol_hash_table;

// ----------------------------------------------------------------
// -------------------- VARIAVEL ESCOLHIDA ------------------------
// ----------------------------------------------------------------

typedef struct Variable {
    char variable_name[MAX_WORD];
    int variable_tag;
    int variable_num_nexts;
    char token[MAX_WORD];
    int rule_num;
    char symbol_ids[MAX_SYMBOLS_FOR_RULE][MAX_WORD];
    struct Variable *variable_list[MAX_CHILD_RULES];
    
    // Analizador semantico: tipo sintetizado
    char type_syn[MAX_WORD];
} Variable;

// ----------------------------------------------------------------
// ----------------- ADICAO DE NOS NA ARVORE ----------------------
// ----------------------------------------------------------------

Variable *new_variable (int tag_variable, int num_nexts, Variable *list[], char *terminal, int rule_num, char sym_ids[MAX_SYMBOLS_FOR_RULE][MAX_WORD]) {
    Variable *v = (Variable *) malloc(sizeof(Variable));
    v->variable_num_nexts = num_nexts;
    *(v->variable_list) = *list;
    strcpy(v->token, "END");
    v->rule_num = rule_num;
    //v->symbol_ids = sym_ids;
    
    memcpy(v->symbol_ids, sym_ids, sizeof(symbol_ids));

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
                strcpy(v->type_syn, (v->variable_list)[0]->type_syn); // Sintetiza tipo da função
                break;
                
            case (3): // ValueList
                strcpy(v->variable_name, "ValueList");
                v->variable_tag = 3;
                break;
                
            case (4):
                strcpy(v->variable_name, "Value");
                v->variable_tag = 4;
                strcpy(v->token, terminal);
                if ((rule_num == 1) || (rule_num == 2) || (rule_num == 3)) // Como saber tipo de ID? - att hierarquizado
                    strcpy(v->type_syn, (v->variable_list)[0]->type_syn);
                
                break;
                
            case (5):
                strcpy(v->variable_name, "TypeStruct");
                v->variable_tag = 5;
                
                if (rule_num == 1)
                    strcpy(v->type_syn, (v->variable_list)[0]->type_syn); // Sintetiza tipo da variavel tipo simples
                else { // rule_num == 2
                    char type_queue[MAX_WORD];
                    strcpy(type_queue, "queue<");
                    strcat(type_queue, (v->variable_list)[0]->type_syn);
                    strcat(type_queue, ">");
                    strcpy(v->type_syn, type_queue); // Sintetiza tipo da variavel tipo fila
                }
                break;
                
            case (6):
                strcpy(v->variable_name, "TypeSimple");
                v->variable_tag = 6;
                strcpy(v->token, terminal);
                strcpy(v->type_syn, (v->variable_list)[0]->type_syn); // Sintetiza tipo da variavel
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
                printf("%s\n", root->symbol_ids[0]);
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
                    printf("%s\n", root->symbol_ids[0]);
                }
                break;
                
            case (9):// Stmt
                switch(root->rule_num) {
                    case(1):
                        show_tree((*root->variable_list+0), tabs+1, 0);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("%s\n", root->symbol_ids[0]);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf(";\n");
                        break;
                        
                    case(2):
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("%s\n", root->symbol_ids[0]);
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
                        printf("%s\n", root->symbol_ids[0]);
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("=\n");
                        for (i = 0; i < tabs; ++i) printf("|  ");
                        printf("%s\n", root->symbol_ids[1]);
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
                        printf("%s\n", root->symbol_ids[0]);
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
// --------------------- MATRIZ DE ESCOPO -------------------------
// ----------------------------------------------------------------

void include_higher_scopes(int line_matrix, int this_higher_scope, int this_scope) {
    int j;
    scope_matrix[this_scope][this_scope] = 1;
    for (j = this_higher_scope; j >= 0; j--)
        scope_matrix[this_scope][j] = 1;
    return;
}

void show_scope_matrix() {
    printf("\n\n=============================================================\n");
    printf("===================== MATRIZ DE ESCOPO ======================\n");
    printf("=============================================================\n");
    int i, j;
    
    printf("Escopos: \t");
    for(i=0; i<=scope; i++) {
        printf("%d  ", i);
    }
    printf("\n\n");
    for(i=0; i<=scope; i++) {
        printf("Escopo %d:\t", i);
        for(j=0; j<=scope; j++)
            printf("%d  ", scope_matrix[i][j]);
        printf("\n");
    }
    printf("\n=============================================================\n");
    printf("=============================================================\n");
    return;    
}

// ----------------------------------------------------------------
// ---------------------- TABELA DE SIMBOLOS ----------------------
// ----------------------------------------------------------------


int on_reachable_escope(char *s, int scope) {
    symbol_hash_table *symbol;
    int i;
    
    char key[MAX_WORD+4];
    char str_scope[2];
    char str_func_scope[2];
    
    sprintf(str_func_scope, "%d", func_scope);
    
    for (i=0; i<MAX_SCOPES; i++) {
        if (scope_matrix[scope][i] == 1) {
            strcpy(key, s);
            sprintf(str_scope, "%d", i);
            strcat(key, str_scope);
            strcat(key, str_func_scope);
            
            HASH_FIND_STR(symbols, key, symbol);
            if (symbol != NULL) return 1;
        }
    }
    return 0;
}

/*
 VARIAVEL NAO PODE SER VOID
 FUNCAO PODE SER VOID
 */
// if var_or_func == 0 (var), var_or_func == 1 (func)
void add_symbol_on_hash_table (char *s, char type_s[], int var_or_func, int scope, int higher_scope) {
    symbol_hash_table *symbol;
    
    char key[MAX_WORD+4];
    char str_scope[2];
    char str_func_scope[2];
    
    strcpy(key, s);
    sprintf(str_scope, "%d", scope);
    strcat(key, str_scope);
    
    sprintf(str_func_scope, "%d", func_scope);
    strcat(key, str_func_scope);
    
    
    HASH_FIND_STR(symbols, key, symbol);
    printf("\n\n");
    printf("key: %s\n", key);
    printf("s: %s\n", s);
    printf("type_s: %s\n", type_s);
    printf("var_or_func: %d\n", var_or_func);
    printf("scope: %d\n", scope);
    printf("higher_scope: %d\n", higher_scope);
    printf("\n\n");
    
    
    if (symbol != NULL) {} // eSTA NA TABELA DE SIMBOLOS. VERIFICAR ESCOPO
    /*
     Problema: eu quero o mesmo nome de variavel em dois escopos diferentes.
     ID da hash tabel não pode ser o nome da variavel, entao
     Tem que ser nome+scopo+funcao
     
     */
    
    else {
        if ((strcmp(type_s, "?") == 0) && (on_reachable_escope(s, scope) == 0)) {
            printf("(sem) ERROR on line %d : '%s' undeclared\n", yylineno, s);
            return;
        }
        if ((strcmp(type_s, "void") == 0) && (var_or_func == 0)) { // Variavel do tipo void
            printf("(sem) ERROR on line %d : variable or field '%s' declared void\n", yylineno, s);
            return;
        }
        
        symbol = (symbol_hash_table*)malloc(sizeof(symbol_hash_table));
        strcpy(symbol->str_id, s);
        strcpy(symbol->type, type_s);
        symbol->scope = scope;
        symbol->higher_scope = higher_scope;
        symbol->func_scope = func_scope;
        
        include_higher_scopes(scope, higher_scope, scope);
        
        HASH_ADD_STR(symbols, key, symbol);
    }
}

char* get_type_hash_table(char *s, int scope, int func_scope) {
    symbol_hash_table *symbol;
    
    char key[MAX_WORD+4];
    char str_scope[2];
    char str_func_scope[2];
    
    strcpy(key, s);
    sprintf(str_scope, "%d", scope);
    strcat(key, str_scope);
    
    sprintf(str_func_scope, "%d", func_scope);
    strcat(key, str_func_scope);
    
    HASH_FIND_STR(symbols, key, symbol);
    if (symbol != NULL)
        return symbol->type;
    return "?";
}

char *decide_type_operation(char *s1, char *s2) {

    if ((strcmp(s1, "void") == 0) || (strcmp(s2, "void") == 0)) { // Serve para qualquer chamada de funcao void
        printf("(sem) ERROR on line %d : void value not ignored as it ought to be\n", yylineno);
        return "?";
    }
    
    // EM C EH POSSIVEL FAZER OPERACAO COM INT E VETOR DE INT, MAS EM siC NAO EH. SE ALGUM TIPO FOR QUEUE, JA DAH ERRO
    if ((s1[0] == 'q') || (s2[0] == 'q')) { // Operacao com dois elementos do tipo fila
        printf("(sem) ERROR on line %d : invalid operands to binary + (have '%s' and '%s')", yylineno, s1, s2);
        return "?";
    }        
    
    if (strcmp(s1, s2))
        return s1;
    
    if (((strcmp(s1, "int") == 0) && (strcmp(s2, "float") == 0))  || 
        ((strcmp(s1, "float") == 0) && (strcmp(s2, "int") == 0))  ||
        ((strcmp(s1, "char") == 0) && (strcmp(s2, "float") == 0)) || 
        ((strcmp(s1, "float") == 0) && (strcmp(s2, "char") == 0)))
        return "float";
    
    if (((strcmp(s1, "int") == 0) && (strcmp(s2, "char") == 0)) || 
        ((strcmp(s1, "char") == 0) && (strcmp(s2, "int") == 0)))
        return "int";
        
    return "?";
}

void show_symbol_table() {
    printf("\n=============================================================\n");
    printf("===================== TABELA DE SIMBOLOS ====================\n");
    printf("=============================================================\n");
    printf("\tFunc\tHiScope\tScope\tType\t\tID\n");
    printf("=============================================================\n");
    int i = 0;
    symbol_hash_table *s;

    for(s = symbols; s != NULL; s = s->hh.next, i++) {
        printf("%d\t%d\t%d\t%d\t%s\t\t%s\n", i, s->func_scope, s->higher_scope, s->scope, s->type, s->str_id);
    }
    return;
}

#endif /* structs_h */