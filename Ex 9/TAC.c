#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void generate_asm(char *line) {
    char lhs[10], op1[10], op2[10], op[5];
    int scanned = 0;

    // Handle assignment (e.g., a = t1)
    if (sscanf(line, "%s = %s", lhs, op1) == 2 && strchr(op1, '+') == NULL &&
        strchr(op1, '-') == NULL && strchr(op1, '*') == NULL && strchr(op1, '/') == NULL) {
        printf("MOV AX, [%s]\n", op1);
        printf("MOV [%s], AX\n", lhs);
        return;
    }

    // Handle binary operations: +, -, *, /
    if ((scanned = sscanf(line, "%s = %[^+-*/] %s %s", lhs, op1, op, op2)) == 4) {
        if (strcmp(op, "+") == 0) {
            printf("MOV AX, [%s]\n", op1);
            printf("ADD AX, [%s]\n", op2);
            printf("MOV [%s], AX\n", lhs);
        } else if (strcmp(op, "-") == 0) {
            printf("MOV AX, [%s]\n", op1);
            printf("SUB AX, [%s]\n", op2);
            printf("MOV [%s], AX\n", lhs);
        } else if (strcmp(op, "*") == 0) {
            printf("MOV AX, [%s]\n", op1);
            printf("MOV BX, [%s]\n", op2);
            printf("MUL BX\n");
            printf("MOV [%s], AX\n", lhs);
        } else if (strcmp(op, "/") == 0) {
            printf("MOV AX, [%s]\n", op1);
            printf("MOV DX, 0\n");
            printf("MOV BX, [%s]\n", op2);
            printf("DIV BX\n");
            printf("MOV [%s], AX\n", lhs);
        }
    }
}

int main() {
    char tac[100][100];
    int n;

    printf("Enter number of TAC instructions: ");
    scanf("%d", &n);
    getchar(); // clear newline

    printf("Enter TAC instructions:\n");
    for (int i = 0; i < n; i++) {
        fgets(tac[i], sizeof(tac[i]), stdin);
        tac[i][strcspn(tac[i], "\n")] = 0; // remove newline
    }

    printf("\nGenerated 8086 Assembly Code:\n");
    for (int i = 0; i < n; i++) {
        generate_asm(tac[i]);
    }

    return 0;
}
