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

{digito}+{letra}+{digito}*		{++errors;printf("\t(lex) ERROR on line %d : Invalid suffix on integer \"%s\" \n", lines, yytext);}
{digito}+"."{digito}*{letra}+{digito}*	{++errors;printf("\t(lex) ERROR on line %d : Invalid suffix on floating \"%s\" \n", lines, yytext);}

"'"({letra}|{digito})"'"	{   yylval.str[0] = yytext[1];
                                    yylval.str[0] = '\0';
                                    return(CARACTERE);
                                }
{digito}+"."{digito}* 		{   //yylval.f = atof(yytext);
                                    yylval.str = yytext;
                                    return(NUM_FLOAT);
                                }
{digito}+			{   //yylval.i = atoi(yytext);
                                    yylval.str = yytext;
                                    return(NUM_INT);
                                }
                                
"''"				{++errors;printf("\tERROR on line %d : Empty character constant \"%s\" \n", lines, yytext);}


"=="    return(EQ);
"!="    return(NEQ);
"<="    return(LEQ);
">="    return(GEQ);
"<"     return(LT);
">"     return(GT);

"."     return('.');
";"     return(';');
","     return(',');
"{"     return('{');
"}"     return('}');
"("     return('(');
")"     return(')');

"+"     return('+');
"-"     return('-');
"*"     return('*');
"/"     return('/');
"="	return('=');

"->"    return(ARROW);

(?i:SETLAST)    return(SETLAST);
(?i:RMVFIRST)   return(RMVFIRST);

(?i:"QUEUE")	return(QUEUE);
(?i:"VOID")	return(VOID);
(?i:"FLOAT")	return(FLOAT);
(?i:"INT")	return(INT);
(?i:"CHAR")	return(CHAR);
(?i:"FIRST")	return(FIRST);
(?i:"IF")	return(IF);
(?i:"ELSE")	return(ELSE);
(?i:"WHILE")	return(WHILE);
(?i:"RETURN")	return(RETURN);

{id}	{
            //printf("\tIDENTIFIER %s\n", yytext);
            yylval.str = malloc(strlen(yytext)); // Aloca espaço para string do tamanho de yytext
            strncpy(yylval.str, yytext, strlen(yytext)); // Copia yytext para yylval.s
            return(ID); // Diz pro bison que o valor lido é IDENTIFIER
        }
        
.	{++errors;printf("\t(lex) ERROR on line %d : Unknown token '%s' \n", lines, yytext);}

%% 

