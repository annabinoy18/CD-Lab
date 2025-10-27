#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default",
                             "do", "double", "else", "enum", "extern", "float", "for", "goto",
                             "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef", "union",
                             "unsigned", "void", "volatile", "while"};

    for (int i = 0; i < 32; i++)
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    return 0;
}

int isOperator(char c) {
    char operators[] = "+-*%/=";
    for (int i = 0; i < strlen(operators); i++)
        if (c == operators[i])
            return 1;
    return 0;
}

int isSeparator(char c) {
    char separators[] = "(){}[];#,";
    for (int i = 0; i < strlen(separators); i++)
        if (c == separators[i])
            return 1;
    return 0;
}

int main() {
    char filename[50], buffer[100];
    printf("Enter file name: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found!\n");
        return 1;
    }

    char c;
    int j = 0;   //next empty index

    while ((c = fgetc(fp)) != EOF) {
        // Handle single-line comments
        if (c == '/') {
            char next = fgetc(fp);
            if (next == '/') {
                printf("//");
                while ((c = fgetc(fp)) != '\n' && c != EOF)
                    printf("%c", c);
                printf("\n");
                j = 0;
                continue;
            } else {
                // Put back the next char if not comment
                ungetc(next, fp);
                if (j > 0) {
                    buffer[j] = '\0';
                    if (isKeyword(buffer))
                        printf("%s is a keyword.\n", buffer);
                    else if (isdigit(buffer[0]))
                        printf("%s is a number.\n", buffer);
                    else
                        printf("%s is an identifier.\n", buffer);
                    j = 0;
                }
                printf("/ is an operator.\n");
                continue;
            }
        }

        // End of token
        if ((isspace(c) || isSeparator(c) || isOperator(c)) && j > 0) {
            buffer[j] = '\0';
            if (isKeyword(buffer))
                printf("%s is a keyword.\n", buffer);
            else if (isdigit(buffer[0]))
                printf("%s is a number.\n", buffer);
            else
                printf("%s is an identifier.\n", buffer);
            j = 0;
        }

        // Operators
        if (isOperator(c)) {
            printf("%c is an operator.\n", c);
            continue;
        }

        // Separators
        if (isSeparator(c)) {
            printf("%c is a separator.\n", c);
            continue;
        }

        // Collect token characters
        if (!isspace(c)) {
            buffer[j++] = c;
        }
    }

    // Print last buffer if any
    if (j > 0) {
        buffer[j] = '\0';
        if (isKeyword(buffer))
            printf("%s is a keyword.\n", buffer);
        else if (isdigit(buffer[0]))
            printf("%s is a number.\n", buffer);
        else
            printf("%s is an identifier.\n", buffer);
    }

    fclose(fp);
    return 0;
}



/*  INPUT.txt
int main() {
    int a = 5;
    a = a + 1;
    // This is a comment
}
*/
