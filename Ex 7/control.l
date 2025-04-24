%{
#include "y.tab.h"
%}

%%
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"switch"        { return SWITCH; }
"case"          { return CASE; }
"default"       { return DEFAULT; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
";"             { return SEMICOLON; }
":"             { return COLON; }
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }
[0-9]+          { return NUMBER; }
"=="|"="|"<"|">" { return RELOP; }
[ \t\n]+        ;  // Skip whitespace
.               { return yytext[0]; }

%%
int yywrap() { return 1; }
