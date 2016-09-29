%error-verbose
%debug
%defines
%pure-parser
%locations

%code requires {
#include <stdio.h>

/* Precisamos acessar o arquivo yyin do flex pelo bison! */
extern FILE *yyin;

void yyerror (char const *);
}

%union {
	char str[255];
}

%token <str> ID "id"

%%

input: | input ID { printf("identificador '%s' encontrado em [%d,%d,%d,%d]\n", $2, @2.first_line, @2.first_column, @2.last_line, @2.last_column);}
;

%%

void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[]) {
	yyin = fopen(argv[1], "r");
	return yyparse();
}
