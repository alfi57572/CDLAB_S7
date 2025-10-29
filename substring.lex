%{
#include <stdio.h>
#include <string.h>

char block_substring[5];  // To store the first 4 characters + null terminator

int contains_block_substring(const char *str) {
    return strstr(str, block_substring) != NULL;
}
%}

%%

.*\n    {
        // Remove newline
        yytext[yyleng - 1] = '\0';

        if (contains_block_substring(yytext)) {
            printf("Rejected: Contains '%s'\n", block_substring);
        } else {
            printf("Accepted: %s\n", yytext);
        }
      }

%%

int main() {
    char name[100];

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);

    // Remove newline if present
    name[strcspn(name, "\n")] = '\0';

    // Extract first 4 characters
    strncpy(block_substring, name, 4);
    block_substring[4] = '\0';  // Null terminate

    printf("Blocking substring: '%s'\n", block_substring);
    printf("Enter strings (Ctrl+D to end):\n");

    yylex();
    return 0;
}

lex prg1.l
gcc lex.yy.c -o output -ll
./output


#include <stdio.h>
#include <string.h>

char block_substring[5];  // To store first 4 letters of name

// Function to check if a string contains the block substring
int contains_block_substring(const char *str) {
    return strstr(str, block_substring) != NULL;
}

int main() {
    char name[100], line[200];

    // Step 1: Get the user's name
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove newline

    // Step 2: Store first 4 letters of name as block substring
    strncpy(block_substring, name, 4);
    block_substring[4] = '\0';

    printf("Blocking substring: '%s'\n", block_substring);
    printf("Enter strings (Ctrl+D to end):\n");

    // Step 3: Process each input line
    while (fgets(line, sizeof(line), stdin)) {
        line[strcspn(line, "\n")] = '\0';  // Remove newline

        if (contains_block_substring(line)) {
            printf("Rejected: Contains '%s'\n", block_substring);
        } else {
            printf("Accepted: %s\n", line);
        }
    }

    return 0;
}

