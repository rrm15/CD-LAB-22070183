%{
#include <stdio.h>
#include <stdlib.h>
%}

%token IF ELSE WHILE FOR SWITCH CASE DEFAULT ID NUMBER RELOP
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COLON

%%
program:
    stmt_list
    ;

stmt_list:
    stmt_list stmt
    | stmt
    ;

stmt:
    if_stmt
    | if_else_stmt
    | if_else_if_stmt
    | while_stmt
    | for_stmt
    | switch_stmt
    ;

if_stmt:
    IF LPAREN cond RPAREN block { printf("Valid IF statement\n"); }
    ;

if_else_stmt:
    IF LPAREN cond RPAREN block ELSE block { printf("Valid IF-ELSE statement\n"); }
    ;

if_else_if_stmt:
    IF LPAREN cond RPAREN block elseif_blocks ELSE block { printf("Valid IF-ELSE IF-ELSE chain\n"); }
    ;

elseif_blocks:
    elseif_blocks ELSE IF LPAREN cond RPAREN block
    | ELSE IF LPAREN cond RPAREN block
    ;

while_stmt:
    WHILE LPAREN cond RPAREN block { printf("Valid WHILE loop\n"); }
    ;

for_stmt:
    FOR LPAREN stmt cond SEMICOLON stmt RPAREN block { printf("Valid FOR loop\n"); }
    ;

switch_stmt:
    SWITCH LPAREN ID RPAREN LBRACE case_blocks RBRACE { printf("Valid SWITCH-CASE structure\n"); }
    ;

case_blocks:
    case_blocks CASE NUMBER COLON stmt_list
    | case_blocks DEFAULT COLON stmt_list
    | CASE NUMBER COLON stmt_list
    | DEFAULT COLON stmt_list
    ;

cond:
    ID RELOP ID
    | ID RELOP NUMBER
    ;

block:
    LBRACE stmt_list RBRACE
    ;
%%

int main() {
    printf("Enter C control structure code:\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Syntax Error: %s\n", s);
    return 0;
}
