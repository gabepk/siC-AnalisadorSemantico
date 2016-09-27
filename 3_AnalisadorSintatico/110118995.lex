%{
#include <stdio.h>
#include "110118995.tab.h"
int lines = 1;
int errors = 0;
%} 

%option nounput
%option noinput
%option yylineno

digito [0-9]
letra [a-zA-Z$]
id [a-zA-Z$][a-zA-Z$0-9]*

%% // Inicio das Regras Lexicas

\n 	++lines;
[ \t]+
"//"[^\n]*	printf("Comentario na linha %d\n", lines);

{digito}+{letra}+{digito}*		{++errors;printf("\tERROR on line %d : Invalid suffix on integer \"%s\" \n", lines, yytext);}
{digito}+"."{digito}*{letra}+{digito}*	{++errors;printf("\tERROR on line %d : Invalid suffix on floating \"%s\" \n", lines, yytext);}

{digito}+"."{digito}* 		{   yylval.f = atof(yytext);
                                    return(NUM_FLOAT);
                                }
{digito}+			{   yylval.i = atoi(yytext);
                                    return(NUM_INT);
                                }
"'"({letra}|{digito})"'"	{   yylval.c = yytext[0];
                                    return(CARACTERE);
                                }
                                
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

{id}	{
            yylval.str = malloc(strlen(yytext)); // Aloca espaço para string do tamanho de yytext
            strncpy(yylval.str, yytext, strlen(yytext)); // Copia yytext para yylval.s
            return(IDENTIFIER); // Diz pro bison que o valor lido é IDENTIFIER
        }
        
.	{++errors;printf("\tERROR on line %d : Unknown token '%s' \n", lines, yytext);}

%% 
/*int main (int argc, char **argv) {
    ++argv, --argc;   
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;
    yylex();
    printf("\nErrors: %d\n\n", errors);
    return 0;
}*/