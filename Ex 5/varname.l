%{
#include "y.tab.h"
%}

%option noyywrap

%%
[a-zA-Z_][a-zA-Z0-9_]* {return IDENTIFIER;}
[\t\n] {}
. {return yytext[0];}
%%
