%{
#include <stdio.h>

// 👇 Declare yylex and yyerror to avoid implicit declaration warnings
int yylex();
int yyerror(const char *msg);
%}

%token VARIABLE INVALID              //Defines tokens that the lexer will return:

%%

input:
    VARIABLE    { printf("Valid variable name\n"); }
  | INVALID     { printf("Invalid variable name\n"); }
  ;

%%

int main() {
    printf("Enter a variable name: ");
    yyparse();
    return 0;
}

int yyerror(const char *msg) {
    // Optional error message (won't be used in this small example)
    return 0;
}

lex prg2.l
yacc -d prg2.y
gcc lex.yy.c y.tab.c -o output
./output
