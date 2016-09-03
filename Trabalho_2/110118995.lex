%{
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>

int lines = 1;
int errors = 0, warnings = 0;
%} 

letra [a-zA-Z]
digito [0-9]

%% // Inicio das Regras Lexicas

\n 		++lines;
[ \t]+

"("
")"
"{"
"}"
"'"

"<="
">="
"<"
">"
"=="
"!="
"="

"."
";"
","

"+"
"-"
"*"
"/"

(?i:"VOID")
(?i:"FLOAT")
(?i:"INT")
(?i:"CHAR")
(?i:"QUEUE")
(?i:"FIRST")
(?i:"IF")
(?i:"ELSE")
(?i:"WHILE")
(?i:"RETURN")

{digito}+{letra}+	{++errors;printf("\tERROR on line %d : Identifier starting with digit '%s' \n", lines, yytext);}

{digito}+"."{digito}* 		printf("float: %s\n", yytext);
{digito}+ 			printf("digito: %s\n", yytext);
{letra}+({digito}|{letra})* 	printf("id: %s\n", yytext);

.			{++errors;printf("\tERROR on line %d : Unknown token '%s' \n", lines, yytext);}


%% 

int main (int argc, char **argv) {
    ++argv, --argc;   
    if (argc > 0) {
        yyin = fopen(argv[0], "r");
    }
    else {
        yyin = stdin;
    }
    
    printf("\n");
    yylex();
    
    printf("\nErrors: %d, Warnings: %d\n", errors, warnings);
    
    return 0;
}