#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char lhs[10], rhs[50];
    int used;
} TAC;

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) return 1;

    TAC code[MAX];
    int n = 0;

    while (fscanf(fp, "%s = %[^\n]\n", code[n].lhs, code[n].rhs) == 2) {
        code[n].used = 0;
        n++;
    }
    fclose(fp);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(code[i].rhs, code[j].rhs) == 0) {
                for (int k = 0; k < n; k++) {
                    char *p = strstr(code[k].rhs, code[j].lhs);
                    if (p) strncpy(p, code[i].lhs, strlen(code[i].lhs));
                }
                strcpy(code[j].lhs, "");
                strcpy(code[j].rhs, "");
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (strlen(code[i].lhs) == 0) continue;
        for (int j = 0; j < n; j++) {
            if (strstr(code[j].rhs, code[i].lhs)) code[i].used = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (strlen(code[i].lhs) > 0 && code[i].used)
            printf("%s = %s\n", code[i].lhs, code[i].rhs);
    }

    return 0;
}
