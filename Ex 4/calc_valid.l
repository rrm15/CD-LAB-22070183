%{
#include <stdio.h>
int valid = 1;
%}

DIGIT      [0-9]
NUM        {DIGIT}+(\.{DIGIT}+)?
OPERATOR   [\+\-\*/]
PAREN      [\(\)]
WHITESPACE [ \t\n]

%%
{NUM}           { /* Valid number */ }
{OPERATOR}      { /* Valid operator */ }
{PAREN}         { /* Valid parenthesis */ }
{WHITESPACE}    { /* Ignore spaces */ }
.               { valid = 0; printf("Invalid token: %s\n", yytext); }

%%
int main() {
    printf("Enter an arithmetic expression:\n");
    yylex();

    if (valid)
        printf("Valid arithmetic expression.\n");
    else
        printf("Invalid arithmetic expression.\n");

    return 0;
}

int yywrap() {
    return 1;
}
