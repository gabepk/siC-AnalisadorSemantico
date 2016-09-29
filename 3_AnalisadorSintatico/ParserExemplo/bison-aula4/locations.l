%{
	#include "locations.tab.h"
	#include "string.h"
	
	/* variaveis auxiliares */
	int start_col = 1, start_line = 1;
	int col = 1, line = 1;
	
	/* Reinicia todas as posicoes com a posicao dada. */
	void reset_loc(int line, int col);
	
	/* Define os valores de yylloc com as posicoes inicial e final (menos 1) atuais e reinicia as posicoes. */
	void set_loc(YYLTYPE *yylloc);
%}

%option noyywrap
%option bison-bridge bison-locations

L [_a-zA-Z]
D [0-9]
WS  [ \t\v\f]
EOL "\n"|"\r"|"\r\n"

%%

{L}({L}|{D})*	{ col += yyleng; set_loc(yylloc); strcpy(yylval->str, yytext); return ID; }
{WS}+			{ reset_loc(line, col + yyleng); BEGIN(INITIAL); }
{EOL}			{ reset_loc(line + 1, 1); BEGIN(INITIAL); }
.				{ ++col; set_loc(yylloc); return *yytext; }

%%

void reset_loc(int l, int c) {
	start_line = line = l;
	start_col = col = c;
}

void set_loc(YYLTYPE *yylloc) {
	yylloc->first_line = start_line;
	yylloc->first_column = start_col;
	/* Atencao, nao tratamos a ultima linha porque nenhum token dessa linguagem pode ocupar mais de uma linha! */
	yylloc->last_line = line;
	yylloc->last_column = col - 1;
	
	reset_loc(line, col);
}
