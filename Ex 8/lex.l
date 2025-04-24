%{
#include "y.tab.h"
#include <string.h>
extern int yylval;
%}

%%
[ 	\n]+             ;
"="                 return ASSIGN;
"+"                 return PLUS;
"-"                 return MINUS;
"*"                 return MUL;
"/"                 return DIV;
"("                 return LPAREN;
")"                 return RPAREN;
[0-9]+              { yylval = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval = strdup(yytext); return ID; }

.                   { return yytext[0]; }
%%

int yywrap() { return 1; }
