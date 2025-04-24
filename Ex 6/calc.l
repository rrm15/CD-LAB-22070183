%{
#include "y.tab.h"
%}

%%
[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[+\n*()]    { return *yytext; }
[ \t]       ;  // Ignore whitespace
.           { return 0; }

%%
int yywrap() { return 1; }
