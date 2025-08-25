%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
int yyerror(const char *s);
%}

%token FOR ID NUM RELOP

%%

stmt:
    FOR '(' assign ';' condition ';' increment ')' ';'
        { printf("Valid for loop syntax\n"); }
    ;

assign:
    ID '=' NUM
    ;

condition:
    ID RELOP NUM
    ;

increment:
    ID '=' ID '+' NUM
    ;

%%

int yyerror(const char *s) {
    printf("Syntax Error\n");
    return 0;
}

int main() {
    printf("Enter a 'for' loop statement:\n");
    yyparse();
    return 0;
}
