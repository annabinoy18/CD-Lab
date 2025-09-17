#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

const char *input;
char lookahead;

void error() {
    printf("Input is rejected\n");
    exit(1);
}

void next() {
    lookahead = *input++;
    while (isspace(lookahead)) {
        lookahead = *input++;
    }
}

// NUMBER → [0-9]+
void number() {
    if (!isdigit(lookahead)) {
        error();
    }
    while (isdigit(lookahead)) {
        next();
    }
}

void expr();

// factor → NUMBER | '(' expr ')'
void factor() {
    if (isdigit(lookahead)) {
        number();
    } else if (lookahead == '(') {
        next();  // consume '('
        expr();  // parse inner expression
        if (lookahead == ')') {
            next();  // consume ')'
        } else {
            error();  // missing closing parenthesis
        }
    } else {
        error();
    }
}

// term → factor (('*' | '/') factor)*
void term() {
    factor();
    while (lookahead == '*' || lookahead == '/') {
        next();
        factor();
    }
}

// expr → term (('+' | '-') term)*
void expr() {
    term();
    while (lookahead == '+' || lookahead == '-') {
        next();
        term();
    }
}

int main() {
    char buffer[256];
    printf("Enter an expression: ");
    fgets(buffer, sizeof(buffer), stdin);
    input = buffer;

    next();        // Initialize lookahead
    expr();        // Start parsing

    // If parsing succeeded and no extra characters are left
    if (lookahead == '\0' || lookahead == '\n') {
        printf("Input is accepted\n");
    } else {
        printf("Input is rejected\n");
    }

    return 0;
}
