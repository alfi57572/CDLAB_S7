%{
#include "y.tab.h"
%}

%%
[0-9]+             { yylval = atoi(yytext); return NUMBER; }
[\t ]+             ;        // Ignore spaces and tabs
\n                 return '\n';
.                  return yytext[0];   // For operators like +, -, *, /
%%
int yywrap() {
    return 1;
}
