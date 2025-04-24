%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUMBER
%left '+'      // Lowest precedence
%left '*'      // Higher precedence

%%
expr: expr '+' expr   { $$ = $1 + $3; }
    | expr '*' expr   { $$ = $1 * $3; }
    | '(' expr ')'    { $$ = $2; }
    | NUMBER          { $$ = $1; }
    ;

input: expr '\n' { printf("Result = %d\n", $1); }
     ;
%%

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Error: %s\n", s);
    return 0;
}
