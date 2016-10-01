%error-verbose
%debug
%defines
%pure-parser

%code requires {
#include <stdlib.h>
#include <stdio.h>

typedef struct Expression Expression;
struct Expression {
	Expression *left;
	Expression *right;
	char op;
	int value;
};

Expression* new_expr(Expression*, Expression*, char op, int);
void show_tree(Expression*, int);
void destroy_tree(Expression*);
void yyerror (char const *);
}

%union {
	int num;
	Expression *expr;
}

%token <num> NUM "number"

%type <expr> expression

%token '-' '+'
%token '*' '/'

%start input

%%

input: | input line;
line: '\n' | expression '\n' { printf("tree:\n"); show_tree($1, 0); destroy_tree($1); printf("\n> "); } ;
expression:
	NUM { $$ = new_expr(0, 0, 0, $1); }
	| expression '+' expression { $$ = new_expr($1, $3, '+', 0); }
	| expression '-' expression { $$ = new_expr($1, $3, '-', 0); }
	| expression '*' expression { $$ = new_expr($1, $3, '*', 0); }
	| expression '/' expression { $$ = new_expr($1, $3, '/', 0); }
;

%%

Expression* new_expr(Expression* l, Expression* r, char op, int value) {
	Expression *e = (Expression*) malloc(sizeof(Expression));
	e->left = l;
	e->right = r;
	e->op = op;
	e->value = value;
	return e;
}

void show_tree(Expression *root, int tabs) {
	int i;
	for (i = 0; i < tabs; ++i) printf("  ");
	if (root->op) {
		printf("%c{\n", root->op);
		show_tree(root->left, tabs + 1);
		show_tree(root->right, tabs + 1);
		for (i = 0; i < tabs; ++i) printf("  ");
		printf("}\n");
	}
	else
		printf("%d\n", root->value);
}

void destroy_tree(Expression *root) {
	if (root->left) destroy_tree(root->left);
	if (root->right) destroy_tree(root->right);
	free(root);
}

void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}

int main (void) {
	return yyparse();
}
