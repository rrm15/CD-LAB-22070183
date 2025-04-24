#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 100
#define MAX_CODE 100

typedef struct {
    char result[10];
    char arg1[20];
    char op[5];
    char arg2[20];
} TAC;

TAC code[MAX_CODE];
int n = 0;

int isNumber(char* s) {
    for (int i = 0; s[i]; i++)
        if (!isdigit(s[i])) return 0;
    return 1;
}

void constantFolding() {
    for (int i = 0; i < n; i++) {
        if (isNumber(code[i].arg1) && isNumber(code[i].arg2)) {
            int a = atoi(code[i].arg1);
            int b = atoi(code[i].arg2);
            int res = 0;
            if (strcmp(code[i].op, "+") == 0) res = a + b;
            else if (strcmp(code[i].op, "-") == 0) res = a - b;
            else if (strcmp(code[i].op, "*") == 0) res = a * b;
            else if (strcmp(code[i].op, "/") == 0 && b != 0) res = a / b;
            else continue;

            sprintf(code[i].arg1, "%d", res);
            strcpy(code[i].op, "");
            strcpy(code[i].arg2, "");
        }
    }
}

void constantPropagation() {
    for (int i = 0; i < n; i++) {
        if (strcmp(code[i].op, "") == 0 && isNumber(code[i].arg1)) {
            // Store constant assignment
            char var[10];
            strcpy(var, code[i].result);
            for (int j = i + 1; j < n; j++) {
                if (strcmp(code[j].arg1, var) == 0)
                    strcpy(code[j].arg1, code[i].arg1);
                if (strcmp(code[j].arg2, var) == 0)
                    strcpy(code[j].arg2, code[i].arg1);
            }
        }
    }
}

void strengthReduction() {
    for (int i = 0; i < n; i++) {
        if ((strcmp(code[i].op, "*") == 0) && (isNumber(code[i].arg2)) && atoi(code[i].arg2) == 2) {
            strcpy(code[i].op, "+");
            strcpy(code[i].arg2, code[i].arg1);
        }
    }
}

void commonSubexpressionElimination() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(code[i].arg1, code[j].arg1) == 0 &&
                strcmp(code[i].arg2, code[j].arg2) == 0 &&
                strcmp(code[i].op, code[j].op) == 0) {
                // Replace result with the earlier one
                strcpy(code[j].arg1, code[i].result);
                strcpy(code[j].op, "");
                strcpy(code[j].arg2, "");
            }
        }
    }
}

// Print optimized code
void printCode() {
    printf("\nOptimized TAC:\n");
    for (int i = 0; i < n; i++) {
        if (strcmp(code[i].op, "") == 0 && strcmp(code[i].arg2, "") == 0) {
            printf("%s = %s\n", code[i].result, code[i].arg1);
        } else {
            printf("%s = %s %s %s\n", code[i].result, code[i].arg1, code[i].op, code[i].arg2);
        }
    }
}

int main() {
    printf("Enter number of TAC instructions: ");
    scanf("%d", &n);
    getchar();

    printf("Enter TAC instructions (e.g., t1 = a + b):\n");
    for (int i = 0; i < n; i++) {
        char line[50];
        fgets(line, sizeof(line), stdin);

        sscanf(line, "%s = %s %s %s", code[i].result, code[i].arg1, code[i].op, code[i].arg2);
        if (code[i].arg2[0] == '\0') {
            strcpy(code[i].op, "");
        }
    }

    constantFolding();
    constantPropagation();
    strengthReduction();
    commonSubexpressionElimination();

    printCode();

    return 0;
}
