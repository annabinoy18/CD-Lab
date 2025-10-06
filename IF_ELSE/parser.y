%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
%}

%token IF ELSE ID NUM RELOP

%left '+' '-'
%left '*' '/'
%left '<' '>' LE GE EQ NE
%left AND OR
%right '='
%right UMINUS

%%

S   : ST { printf("✅ Valid IF-ELSE statement\n"); exit(0); }
    ;

ST  : IF '(' COND ')' ST ELSE ST
    | IF '(' COND ')' ST
    | '{' BODY '}'
    | E ';'
    ;

BODY:
      BODY BODY
    | ST
    | E ';'
    |
    ;

COND:
      E RELOP E
    | E
    ;

E   : ID '=' E
    | E '+' E
    | E '-' E
    | E '*' E
    | E '/' E
    | '(' E ')'
    | ID
    | NUM
    ;

%%

int main() {
    printf("Enter an if-else statement:\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("❌ Syntax Error: %s\n", s);
    exit(1);
}
