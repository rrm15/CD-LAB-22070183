#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int tempCount = 1;
char tempVars[MAX][10];
char stack[MAX];
int top = -1;

void push(char ch) { stack[++top] = ch; }
char pop() { return stack[top--]; }
char peek() { return (top == -1) ? '\0' : stack[top]; }

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    int k = 0;
    for (int i = 0; i < strlen(infix); i++) {
        char ch = infix[i];
        if (isalnum(ch)) postfix[k++] = ch;
        else if (ch == '(') push(ch);
        else if (ch == ')') { while (peek() != '(') postfix[k++] = pop(); pop(); }
        else { while (precedence(ch) <= precedence(peek())) postfix[k++] = pop(); push(ch); }
    }
    while (top != -1) postfix[k++] = pop();
    postfix[k] = '\0';
}

void generateTAC(char* postfix) {
    int n = strlen(postfix), count = 0;
    char temp[10], op1[10], op2[10];
    char* res;

    for (int i = 0; i < n; i++) {
        char ch = postfix[i];
        if (isalnum(ch)) {
            sprintf(tempVars[count++], "%c", ch);
        } else {
            strcpy(op2, tempVars[--count]);
            strcpy(op1, tempVars[--count]);
            res = tempVars[count];
            sprintf(res, "t%d", tempCount++);
            printf("%s = %s %c %s\n", res, op1, ch, op2);
            count++;
        }
    }
}

int main() {
    FILE* fp = fopen("input.txt", "r");
    if (!fp) { printf("File error\n"); return 1; }

    char infix[MAX], postfix[MAX];
    while (fgets(infix, MAX, fp)) {
        infix[strcspn(infix, "\n")] = '\0';
        infixToPostfix(infix, postfix);
        generateTAC(postfix);
        tempCount = 1;
    }
    fclose(fp);
    return 0;
}
