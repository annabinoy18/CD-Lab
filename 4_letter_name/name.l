%{
  #include<stdio.h>
  #include<string.h>
  
  char prefix[5];
%}

%%
[a-zA-Z]+{
  if(strstr(yytext,prefix)){
    printf("Rejected:'%s' contains '%s'\n",yytext,prefix);
  }else{
    printf("Accepted:'%s'\n",yytext);
  }
}
  
\n {/* ignore newline */}
. {/*ignore other character*/}
%%

int main(){
  printf("Enter your name:\n");
  scanf("%4s",prefix);
  prefix[4]='\0';
  printf("Enter the word to check:\n");
  yylex();
  return 0;
}
int yywrap(){
  return 1;
}
