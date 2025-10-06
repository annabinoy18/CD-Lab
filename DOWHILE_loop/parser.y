%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
%}

%token DO WHILE ID NUM RELOP

%left '+' '-'
%left '*' '/'

%%

stmt:
      DO '{' body '}' WHILE '(' cond ')' ';'   { printf("✅ Valid DO-WHILE statement\n"); }
    ;

body:
      /* empty */ 
    | body stmt_line
    ;

stmt_line:
      ID '=' expr ';' 
    ;

expr:
      expr '+' expr 
    | expr '-' expr 
    | expr '*' expr 
    | expr '/' expr 
    | ID
    | NUM
    ;

cond:
      ID RELOP ID
    | ID RELOP NUM
    | NUM RELOP ID
    ;

%%

int main() {
    printf("Enter a DO-WHILE statement:\n");
    if (yyparse() == 0)
        printf("✅ Parsing completed successfully.\n");
    return 0;
}

int yyerror(const char *s) {
    printf("❌ Error: %s\n", s);
    return 0;
}
