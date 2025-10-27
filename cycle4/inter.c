//interm
#include <stdio.h>
#include <string.h>

char reg = 'Z'; // global register counter
void gen_code(char *expr);

// Generate code for a single operator
void gen_code_for_operator(char *expr, char operator) {
    int i = 0;
    while (expr[i] != '\0') {
        if (expr[i] == operator) {
            if (operator == '=') {
                // Assignment: left operand is destination
                printf("%c\t%c\t%c\t%c\n", operator, expr[i - 1], ' ', expr[i + 1]);
            } else {
                printf("%c\t%c\t%c\t%c\n", operator, reg, expr[i - 1], expr[i + 1]);
                expr[i - 1] = reg; // replace left operand with register
                reg--;             // use next register
            }

            // Remove operator and right operand by shifting left
            int j = i;
            while (expr[j + 2] != '\0') {
                expr[j] = expr[j + 2];
                j++;
            }
            expr[j] = '\0';
            i = -1; // restart scanning from beginning
        }
        i++;
    }
}

// Recursively handle parentheses
void handle_parentheses(char *expr) {
    char temp[100];
    while (strchr(expr, '(')) {
        int start = -1, end = -1;
        for (int i = 0; expr[i] != '\0'; i++) {
            if (expr[i] == '(') start = i;
            if (expr[i] == ')' && start != -1) {
                end = i;
                break;
            }
        }

        if (start != -1 && end != -1) {
            strncpy(temp, expr + start + 1, end - start - 1);
            temp[end - start - 1] = '\0';

            gen_code(temp); // generate code for subexpression

            expr[start] = reg + 1; // last used register
            int j = start + 1;
            for (int i = end + 1; expr[i] != '\0'; i++) {
                expr[j++] = expr[i];
            }
            expr[j] = '\0';
        }
    }
}

// Generate code for the full expression
void gen_code(char *expr) {
    handle_parentheses(expr); // first handle parentheses
    gen_code_for_operator(expr, '/');
    gen_code_for_operator(expr, '*');
    gen_code_for_operator(expr, '+');
    gen_code_for_operator(expr, '-');
    gen_code_for_operator(expr, '=');
}

int main() {
    char expr[100];
    printf("Enter expression:\n");
    scanf("%s", expr);

    printf("Op\tDestn\tArg1\tArg2\n");
    gen_code(expr);

    return 0;
}

/*
Enter expression:
a=b-d*d
Op      Destn   Arg1    Arg2
*       Z       d       d
-       Y       b       Z
=       a               Y
*/
