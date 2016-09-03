%{
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>

int lines = 1;
int errors = 0, warnings = 0;
%} 
letra [a-zA-Z$]
digito [0-9]
%% // Inicio das Regras Lexicas

\n 	++lines;
[ \t]+

{digito}+{letra}+		{++errors;printf("\tERROR on line %d : Invalid suffix on integer \"%s\" \n", lines, yytext);}
{digito}+"."{letra}+		{++errors;printf("\tERROR on line %d : Invalid suffix on floating \"%s\" \n", lines, yytext);}
[^{letra}{digito}]+{letra}+	{++errors;printf("\tERROR on line %d : Invalid prefix on identifier '%s' \n", lines, yytext);}
{digito}+"."{digito}* 		printf("float: %s\n", yytext);
{digito}+			printf("digito: %s\n", yytext);

"("|")"|"{"|"}"
"<="|">="|"<"|">"|"=="|"!="|"="
"."|";"|","|"'"
"+"|"-"|"*"|"/"

(?i:"VOID")|(?i:"FLOAT")|(?i:"INT")|(?i:"CHAR")
(?i:"QUEUE")|(?i:"FIRST")
(?i:"IF")|(?i:"ELSE")|(?i:"WHILE")
(?i:"RETURN")

{letra}+[^{letra}{digito}]+	{++errors;printf("\tERROR on line %d : Invalid suffix on identifier '%s' \n", lines, yytext);}
{letra}+({digito}|{letra})*	printf("id: %s\n", yytext);
.				{++errors;printf("\tERROR on line %d : Unknown token '%s' \n", lines, yytext);}

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