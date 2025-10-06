%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'
%left '(' ')'

%%
start:
    expr '\n'     { printf("Valid Expression\n"); exit(0); }
    ;

expr:
      expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | NUMBER
    ;
%%

void yyerror(const char *s) {
    printf("Invalid Expression\n");
}

int main() {
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}
