%{
#include <stdio.h>
int lines = 1;
int errors = 0;
%} 
digito [0-9]
letra [a-zA-Z$]
comparison (==|!=|<=|>=|<|>)
mark ("."|";"|","|"'"|"{"|"}"|"("|")")
operator ("+"|"-"|"*"|"/")
id [a-zA-Z$][a-zA-Z$0-9]*

%% // Inicio das Regras Lexicas

\n 	++lines;
[ \t]+
"//"[^\n]*	printf("Comentario na linha %d\n", lines);

{digito}+{letra}+{digito}*		{++errors;printf("\tERROR on line %d : Invalid suffix on integer \"%s\" \n", lines, yytext);}
{digito}+"."{digito}*{letra}+{digito}*	{++errors;printf("\tERROR on line %d : Invalid suffix on floating \"%s\" \n", lines, yytext);}
{digito}+"."{digito}* 		printf("Float number: %s\n", yytext);
{digito}+			printf("Integer number: %s\n", yytext);

"'"({letra}|{digito})"'"	printf("Char value: %s\n", yytext);
"''"				{++errors;printf("\tERROR on line %d : Empty character constant \"%s\" \n", lines, yytext);}

{comparison} 	printf("Comparison: %s\n", yytext);
{mark}		printf("Mark: %s\n", yytext);
{operator}	printf("Operator: %s\n", yytext);
"="		printf("Assignment: %s\n", yytext);

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
    printf("\nErrors: %d\n\n", errors);
    return 0;
}