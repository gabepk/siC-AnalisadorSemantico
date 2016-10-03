#ifndef structs_h
#define structs_h

#define FIRST_MAX 5

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------------------

typedef struct elemento {
    struct elemento *followOnRule;
    struct elemento *first[FIRST_MAX];
    int num_firsts;
    char *nome;
} elemento;

// ---------------------------------------------------------------

elemento* new_elemento(elemento *follow, elemento *firsts_var[FIRST_MAX], int num_firsts, char *nome) {
	elemento *e = (elemento*) malloc(sizeof(elemento));
	e->nome = nome;
	e->followOnRule = follow;
        e->num_firsts = num_firsts;
        
        int i;
        for (i = 0; i < num_firsts; i++) {
            e->first[i] = firsts_var[i];
        }
        
	return e;
}

// ---------------------------------------------------

#endif /* structs_h */