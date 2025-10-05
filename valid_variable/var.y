%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(const char *s);
%}

%union {
  char* str;
}

%token <str> IDENTIFIER

%%
stmt: IDENTIFIER '\n' {
  printf("Valid identifier: %s\n", $1);
  free($1);
};
%%

int yyerror(const char *s){
  fprintf(stderr,"error: %s\n",s);
  return 0;
}

int main(){
  printf("Enter the input:\n");
  return yyparse();
}
