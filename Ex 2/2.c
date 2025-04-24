#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
    "int", "float", "char", "double", "if", "else", "while", "for", "return", "void",
    "break", "continue", "switch", "case", "default", "do", "sizeof", "struct", "union", "typedef",
    "const", "static", "enum", "goto", "long", "short", "unsigned", "signed", "volatile", "extern", "auto"
};

char *operators[] = { "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "++", "--" };

char delimiters[] = { '(', ')', '{', '}', '[', ']', ';', ',', '#', '"', '\'' };

int isKeyword(char *token) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
        if (strcmp(token, keywords[i]) == 0)
            return 1;
    return 0;
}

int isOperator(char *token) {
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++)
        if (strcmp(token, operators[i]) == 0)
            return 1;
    return 0;
}

int isDelimiter(char ch) {
    for (int i = 0; i < sizeof(delimiters); i++)
        if (ch == delimiters[i])
            return 1;
    return 0;
}

int isIdentifier(char *token) {
    if (!isalpha(token[0]) && token[0] != '_')
        return 0;
    for (int i = 1; token[i]; i++)
        if (!isalnum(token[i]) && token[i] != '_')
            return 0;
    return 1;
}

int main() {
    char code[1000], token[100];
    int i = 0, j = 0, ch;

    printf("Enter C code snippet (end input with `):\n");

    while ((ch = getchar()) != '`')  // Use backtick to stop
        code[i++] = ch;
    code[i] = '\0';

    printf("\n--- Token Analysis ---\n");

    for (i = 0; code[i]; i++) {
        if (isspace(code[i]) || isDelimiter(code[i]) || ispunct(code[i])) {
            if (j > 0) {
                token[j] = '\0';

                if (isKeyword(token))
                    printf("[Keyword]      %s\n", token);
                else if (isIdentifier(token))
                    printf("[Identifier]   %s\n", token);
                else if (isOperator(token))
                    printf("[Operator]     %s\n", token);
                else
                    printf("[Unknown]      %s\n", token);
                j = 0;
            }

            if (isDelimiter(code[i]))
                printf("[Symbol]       %c\n", code[i]);
            else if (ispunct(code[i]) && code[i] != '_') {
                token[0] = code[i];
                token[1] = '\0';
                if (isOperator(token))
                    printf("[Operator]     %s\n", token);
            }
        } else {
            token[j++] = code[i];
        }
    }

    return 0;
}
