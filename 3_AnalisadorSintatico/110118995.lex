%{
#include <stdio.h>
#include "bison.h"
int lines = 1;
int errors = 0;
%} 
digito [0-9]
letra [a-zA-Z$]
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


"=="    return(EQ);
"!="    return(NEQ);
"<="    return(LEQ);
">="    return(GEQ);
"<"     return(LT);
">"     return(GT);

"."     return(DOT);
";"     return(SEMICOLON);
","     return(COMMA);
"'"     return(QUOTE);
"{"     return(OPEN_BRACES);
"}"     return(CLOSE_BRACES);
"("     return(OPEN_PARENT);
")"     return(CLOSE_PARENT);

"+"     return(PLUS);
"-"     return(MINUS);
"*"     return(MULT);
"/"     return(DIV);

"="	return(ASSIGN);

(?i:"VOID")	return(VOID);
(?i:"FLOAT")	return(FLOAT);
(?i:"INT")	return(INT);
(?i:"CHAR")	return(CHAR);
(?i:"QUEUE")	return(QUEUE);
(?i:"FIRST")	return(FIRST);
(?i:"IF")	return(IF);
(?i:"ELSE")	return(ELSE);
(?i:"WHILE")	return(WHILE);
(?i:"RETURN")	return(RETURN);

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