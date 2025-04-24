#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char lhs[10], rhs[50];
} TAC;

int main() {
    FILE *fp = fopen("input.txt", "r");
    if (!fp) return 1;
    TAC code[MAX];
    int n = 0;
    while (fscanf(fp, "%s = %[^\n]\n", code[n].lhs, code[n].rhs) == 2) n++;
    fclose(fp);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(code[i].rhs, code[j].lhs) == 0) {
                for (int k = j; k < n; k++) {
                    char *p = strstr(code[k].rhs, code[j].lhs);
                    if (p) {
                        int len = strlen(code[i].rhs);
                        memmove(p + len, p + strlen(code[j].lhs), strlen(p + strlen(code[j].lhs)) + 1);
                        memcpy(p, code[i].rhs, len);
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s = %s\n", code[i].lhs, code[i].rhs);
    }

    return 0;
}
