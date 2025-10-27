#include <stdio.h>
#include <string.h>

// Production rules:
// E -> iZ
// Z -> +iZ | ε

char inp[100];
int curr = 0;

// Function declarations
int E();
int Z();

int E() {
    int result;
    if (inp[curr] == 'i') {
        curr++;
        result = Z();
        if (result == 1)
            return 1;
        else
            return -1;
    }
    return -1;
}

int Z() {
    int result;
    if (inp[curr] == '+' && inp[curr + 1] == 'i') {
        curr += 2;
        result = Z();
        if (result == 1)
            return 1;
    }
    return 1; // ε-production (empty)
}

int main() {
    printf("Enter input:\n");
    scanf("%s", inp);

    int res = E();
    if (res == 1 && curr == strlen(inp))
        printf("Input has been accepted.\n");
    else
        printf("Input has been rejected.\n");

    return 0;
}
