%{
	#include <stdio.h>
	#include <ctype.h>
	
	#define YYSTYPE double
	
	int yylex (void);
	void yyerror (char const *);
%}

%token NUM

%%

input:
	/* empty */
	| input line
;

line:
	'\n'
	| exp '\n'
;

exp:
	NUM
	| exp '+' exp
	| exp '-' exp
	| exp '*' exp
	| exp '/' exp
	| exp '^' exp
;

%%

int yylex (void) {
	int c;
	
	/* Skip white space. */
	while ((c = getchar ()) == ' ' || c == '\t')
		continue;
	
	/* Process numbers. */
	if (c == '.' || isdigit (c))
	{
		ungetc (c, stdin);
		scanf ("%lf", &yylval);
		return NUM;
	}
	
	/* Return end-of-input. */
	if (c == EOF)
		return 0;
	
	/* Return a single char. */
	return c;
}

void yyerror (char const *s) {
	fprintf (stderr, "%s\n", s);
}

int main (void) {
	return yyparse ();
}
