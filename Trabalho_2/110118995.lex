%{
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>

int lines = 1;
int errors = 0, warnings = 0;
%} 
digito [0-9]
letra [a-zA-Z$]
id [a-zA-Z$][a-zA-Z$0-9]*

%% // Inicio das Regras Lexicas

\n 	++lines;
[ \t]+

{digito}+{letra}+		{++errors;printf("\tERROR on line %d : Invalid suffix on integer \"%s\" \n", lines, yytext);}
{digito}+"."{letra}+		{++errors;printf("\tERROR on line %d : Invalid suffix on floating \"%s\" \n", lines, yytext);}
{digito}+"."{digito}* 		printf("Float number: %s\n", yytext);
{digito}+			printf("Integer number: %s\n", yytext);

"'"({letra}|{digito})"'"	printf("Char value: %s\n", yytext);
"''"				{++errors;printf("\tERROR on line %d : Empty character constant \"%s\" \n", lines, yytext);}

"("	printf("Open parenthesis: %s\n", yytext);
")"	printf("Close  parenthesis: %s\n", yytext);
"{"	printf("Open braces: %s\n", yytext);
"}"	printf("Close braces: %s\n", yytext);
"=="	printf("Equal: %s\n", yytext);
"!="	printf("Different: %s\n", yytext);
"<="	printf("Less or equal than: %s\n", yytext);
">="	printf("Greater or equal than: %s\n", yytext);
"<"	printf("Less than: %s\n", yytext);
">"	printf("Greater than: %s\n", yytext);
"="	printf("Assignment: %s\n", yytext);
"."	printf("Dot: %s\n", yytext);
";"	printf("Semicolon: %s\n", yytext);
","	printf("Comma: %s\n", yytext);
"'"	printf("Single quotes: %s\n", yytext);
"+"	printf("Addition: %s\n", yytext);
"-"	printf("Subtraction: %s\n", yytext);
"*"	printf("Multiplication: %s\n", yytext);
"/"	printf("Division: %s\n", yytext);

(?i:"VOID")	printf("Keyword: %s\n", yytext);
(?i:"FLOAT")	printf("Keyword: %s\n", yytext);
(?i:"INT")	printf("Keyword: %s\n", yytext);
(?i:"CHAR")	printf("Keyword: %s\n", yytext);
(?i:"QUEUE")	printf("Keyword: %s\n", yytext);
(?i:"FIRST")	printf("Keyword: %s\n", yytext);
(?i:"IF")	printf("Keyword: %s\n", yytext);
(?i:"ELSE")	printf("Keyword: %s\n", yytext);
(?i:"WHILE")	printf("Keyword: %s\n", yytext);
(?i:"RETURN")	printf("Keyword: %s\n", yytext);

{id}	printf("Identifier: %s\n", yytext);
.	{++errors;printf("\tERROR on line %d : Unknown token '%s' \n", lines, yytext);}

%% 
int main (int argc, char **argv) {
    ++argv, --argc;   
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;
    yylex();
    printf("\nErrors: %d, Warnings: %d\n\n", errors, warnings);
    return 0;
}