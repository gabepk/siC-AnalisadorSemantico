%{
	#include "arvore.tab.h"
%}

%option noyywrap
%option bison-bridge

D   [0-9]
EOL "\n"|"\r"|"\r\n"
WS  [ \t\v\f]

%%

{D}+ 			{ yylval->num = atoi(yytext); return NUM; }
"-"				{ return '-'; }
"+"				{ return '+'; }
"*"				{ return '*'; }
"/"				{ return '/'; }
{EOL}			{ return '\n'; }
{WS}+			{ BEGIN(INITIAL); }
.				{ return *yytext; }

%%
