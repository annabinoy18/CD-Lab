%{
    int vow_count = 0;
    int const_count = 0;
%}

%%

[aeiouAEIOU]                        { vow_count++; }
[b-df-hj-np-tv-zB-DF-HJ-NP-TV-Z]    { const_count++; }
[ \t]                                ;   // ignore spaces and tabs
\n                                   return 0;
.                                    ;   // ignore any other character

%%

int yywrap() {
    return 1;   // indicate end of input
}

int main() {
    printf("Enter a string (press Enter to finish):\n");
    yylex();    // start scanning input
    printf("Number of vowels: %d\n", vow_count);
    printf("Number of consonants: %d\n", const_count);
    return 0;
}
