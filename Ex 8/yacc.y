%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int temp_count = 0;
char temp[10];

char* new_temp() {
    sprintf(temp, "t%d", temp_count++);
    return strdup(temp);
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
%}

%union {
    int ival;
    char *sval;
}

%token <ival> NUMBER
%token <sval> ID
%token ASSIGN PLUS MINUS MUL DIV LPAREN RPAREN
%type <sval> expr statement

%%

program:
    statement
    ;

statement:
    ID ASSIGN expr {
        printf("%s = %s\n", $1, $3);
    }
    ;

expr:
    expr PLUS expr {
        char *t = new_temp();
        printf("%s = %s + %s\n", t, $1, $3);
        $$ = t;
    }
    | expr MINUS expr {
        char *t = new_temp();
        printf("%s = %s - %s\n", t, $1, $3);
        $$ = t;
    }
    | expr MUL expr {
        char *t = new_temp();
        printf("%s = %s * %s\n", t, $1, $3);
        $$ = t;
    }
    | expr DIV expr {
        char *t = new_temp();
        printf("%s = %s / %s\n", t, $1, $3);
        $$ = t;
    }
    | LPAREN expr RPAREN {
        $$ = $2;
    }
    | NUMBER {
        char buffer[20];
        sprintf(buffer, "%d", $1);
        $$ = strdup(buffer);
    }
    | ID {
        $$ = $1;
    }
    ;

%%

int main() {
    yyparse();
    return 0;
}
