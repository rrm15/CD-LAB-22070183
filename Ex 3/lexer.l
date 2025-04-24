%{
#include <stdio.h>
%}

IDENT     [a-zA-Z_][a-zA-Z0-9_]*
NUMBER    [0-9]+(\.[0-9]+)?
OPERATOR  (\+|\-|\*|\/|==|!=|<=|>=|=|<|>)
KEYWORD   int|float|char|if|else|return|while|for
COMMENT1  "//".*
COMMENT2  "/\*([^*]|\*+[^*/])*\*+/"
SYMBOL    [\{\}\(\)\[\]\;\,]

%%
{KEYWORD}     { printf("Keyword: %s\n", yytext); }
{IDENT}       { printf("Identifier: %s\n", yytext); }
{NUMBER}      { printf("Constant: %s\n", yytext); }
{OPERATOR}    { printf("Operator: %s\n", yytext); }
{COMMENT1}    { printf("Comment: %s\n", yytext); }
{COMMENT2}    { printf("Comment: %s\n", yytext); }
{SYMBOL}      { printf("Special Symbol: %s\n", yytext); }
[ \t\n]       { /* skip whitespace */ }
.             { printf("Unknown token: %s\n", yytext); }

%%
int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
