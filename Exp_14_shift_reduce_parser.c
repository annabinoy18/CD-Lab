#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

char input[MAX], stack[MAX];
int top = -1, i = 0;

// Function to print the current stack and remaining input
void printState(const char *action) {
    printf("$");
    for (int j = 0; j <= top; j++) {
        printf("%c", stack[j]);
    }
    printf("\t%-15s\t%s\n", action, &input[i]);
}

// Function to reduce based on grammar rules
int reduce() {
    // E → E + E
    if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'E') {
        top -= 2;
        stack[top] = 'E';
        printState("REDUCE E→E+E");
        return 1;
    }
    // E → E * E
    if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '*' && stack[top] == 'E') {
        top -= 2;
        stack[top] = 'E';
        printState("REDUCE E→E*E");
        return 1;
    }
    // E → ( E )
    if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')') {
        top -= 2;
        stack[top] = 'E';
        printState("REDUCE E→(E)");
        return 1;
    }
    // E → id  (we use 'i' to represent id)
    if (top >= 0 && stack[top] == 'i') {
        stack[top] = 'E';
        printState("REDUCE E→id");
        return 1;
    }
    return 0;
}

int main() {
    printf("Grammar:\n");
    printf("E → E+E | E*E | (E) | id\n\n");
    printf("Enter the input string (use space between tokens like: id + id * id):\n");

    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = '\0';  // remove newline

    printf("\nStack\tAction\t\t\tInput\n");
    printf("-----\t------\t\t\t-----\n");

    while (input[i] != '\0') {
        // Skip whitespace
        if (input[i] == ' ') {
            i++;
            continue;
        }

        // SHIFT id as 'i'
        if (input[i] == 'i' && input[i + 1] == 'd') {
            stack[++top] = 'i';
            i += 2;
            printState("SHIFT id");
        }
        // SHIFT operators and parentheses
        else if (input[i] == '+' || input[i] == '*' || input[i] == '(' || input[i] == ')') {
            stack[++top] = input[i++];
            printState("SHIFT");
        }
        // Invalid character
        else {
            printf("Invalid character in input: %c\n", input[i]);
            return 1;
        }

        // Try to reduce after each shift
        while (reduce());
    }

    // Final reduction if possible
    while (reduce());

    // Accept if the final stack has only 'E'
    if (top == 0 && stack[top] == 'E') {
        printf("\nInput is accepted.\n");
    } else {
        printf("\nInput is rejected.\n");
    }

    return 0;
}
