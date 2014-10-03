%{
#include <stdio.h>
%}

%%

[a-z][a-zA-Z]* { printf("token: %s\n", yytext); }
abc { printf("keyword: %s\n", yytext); }

%%

int
main(void) {
    yylex();
    return 0;
}
