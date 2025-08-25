%{
#include "y.tab.h"
%}

%%

for             { return FOR; }
[ \t\n]+        { /* ignore whitespace */ }
[0-9]+          { yylval = atoi(yytext); return NUM; }
"=="|"<="|">="|"!="|"=="|"<"|">"    { return RELOP; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
"="             { return '='; }
"+"             { return '+'; }
";"             { return ';'; }
"("             { return '('; }
")"             { return ')'; }
.               { return yytext[0]; }

%%

int yywrap() {
    return 1;
}
