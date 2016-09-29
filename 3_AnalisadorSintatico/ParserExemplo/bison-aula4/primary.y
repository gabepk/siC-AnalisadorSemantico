%{
	#include <stdio.h>
	void yyerror (char const *);
%}

%token I_CONSTANT, F_CONSTANT
%token ID

%%

primary_expression:
	ID /* var */
	| constant
	| enumeration_field
;

constant:
	I_CONSTANT
	| F_CONSTANT
;

enumeration_field:
	ID /* field name */
;

%%

void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}

int main (void) {
	return yyparse ();
}
