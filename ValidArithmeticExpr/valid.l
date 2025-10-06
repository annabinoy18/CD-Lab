%{
#include "y.tab.h"
%}

%%
[0-9]+      { return NUMBER; }
[ \t]       ;           // ignore spaces and tabs
\n          { return '\n'; }
.           { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
