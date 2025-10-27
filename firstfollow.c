/*#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 20

char productions[MAX][MAX];
char first[MAX][MAX];
char follow[MAX][MAX];
int numProductions;

void findFirst(char*, int, int);
void findFollow(char c);
int isTerminal(char c);
int productionIndex(char c);

int visitedFollow[MAX] = {0};

int main() {
    int i;
    char ch;

    printf("Enter number of productions: ");
    scanf("%d", &numProductions);
    printf("Enter productions (e.g., S->AB):\n");

    for (i = 0; i < numProductions; i++) {
        scanf("%s", productions[i]);
    }

    // Compute FIRST sets
    for (i = 0; i < numProductions; i++) {
        char symbol = productions[i][0];
        findFirst(first[i], i, 0);
    }

    // Print FIRST sets
    printf("\nFIRST Sets:\n");
    for (i = 0; i < numProductions; i++) {
        printf("FIRST(%c) = { ", productions[i][0]);
        for (int j = 0; first[i][j] != '\0'; j++) {
            printf("%c ", first[i][j]);
        }
        printf("}\n");
    }

    // Compute FOLLOW sets
    for (i = 0; i < numProductions; i++) {
        if (i == 0) {
            follow[i][0] = '$'; // Start symbol gets $
        }
        findFollow(productions[i][0]);
    }

    // Print FOLLOW sets
    printf("\nFOLLOW Sets:\n");
    for (i = 0; i < numProductions; i++) {
        printf("FOLLOW(%c) = { ", productions[i][0]);
        for (int j = 0; follow[i][j] != '\0'; j++) {
            printf("%c ", follow[i][j]);
        }
        printf("}\n");
    }

    return 0;
}

// Add character to set if not already present
void addToSet(char *set, char val) {
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == val) return;
    }
    int len = strlen(set);
    set[len] = val;
    set[len + 1] = '\0';
}

// Check if a symbol is terminal
int isTerminal(char c) {
    return !(c >= 'A' && c <= 'Z');
}

// Get index of production for non-terminal
int productionIndex(char c) {
    for (int i = 0; i < numProductions; i++) {
        if (productions[i][0] == c) return i;
    }
    return -1;
}

// Compute FIRST of a non-terminal symbol
void findFirst(char *result, int prodIndex, int pos) {
    char symbol = productions[prodIndex][pos + 3];

    if (symbol == '\0') return;

    if (isTerminal(symbol)) {
        addToSet(result, symbol);
    } else {
        for (int i = 0; i < numProductions; i++) {
            if (productions[i][0] == symbol) {
                findFirst(result, i, 0);
            }
        }
    }
}

// Compute FOLLOW of a non-terminal symbol
void findFollow(char c) {
    int i, j;

    int idx = productionIndex(c);
    if (idx == -1) return;

    for (i = 0; i < numProductions; i++) {
        for (j = 3; productions[i][j] != '\0'; j++) {
            if (productions[i][j] == c) {
                if (productions[i][j + 1] != '\0') {
                    char next = productions[i][j + 1];
                    if (isTerminal(next)) {
                        addToSet(follow[idx], next);
                    } else {
                        int ni = productionIndex(next);
                        for (int k = 0; first[ni][k] != '\0'; k++) {
                            if (first[ni][k] != '#') {
                                addToSet(follow[idx], first[ni][k]);
                            }
                        }
                    }
                } else if (productions[i][0] != c) {
                    findFollow(productions[i][0]);
                    int pi = productionIndex(productions[i][0]);
                    for (int k = 0; follow[pi][k] != '\0'; k++) {
                        addToSet(follow[idx], follow[pi][k]);
                    }
                }
            }
        }
    }
}*/

#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
int n, m = 0, p, i = 0, j = 0;
char a[10][10], f[10];
void follow(char c);
void first(char c);
int main() {
int i, z;
char c, ch;
printf("Enter the no of productions : \n");
scanf("%d", & n);
printf("Enter the productions:\n");
for (i = 0; i < n; i++)
scanf("%s%c", a[i], & ch);
do {
m = 0;
printf("Enter a variable whose fisrt & follow is to be found:");
scanf("%c", & c);
first(c);
printf("First(%c)={", c);
for (i = 0; i < m; i++)
printf("%c", f[i]);
printf("}\n");
strcpy(f, " ");
m = 0;
follow(c);
printf("Follow(%c)={", c);
for (i = 0; i < m; i++)
printf("%c", f[i]);
printf("}\n");
printf("Want to continue or not(1/0) ? ");
scanf("%d%c", & z, & ch);
}
while (z == 1);
return (0);
}
void first(char c) {
     int k;
if (!isupper(c))
f[m++] = c;
for (k = 0; k < n; k++) {
if (a[k][0] == c) {
if (a[k][2] == '$')
follow(a[k][0]);
else if (islower(a[k][2]))
f[m++] = a[k][2];
else
first(a[k][2]);
}
}
}
void follow(char c) {
if (a[0][0] == c)
f[m++] = '$';
for (i = 0; i < n; i++) {
for (j = 2; j < strlen(a[i]); j++) {
if (a[i][j] == c) {
if (a[i][j + 1] != '\0')
first(a[i][j + 1]);
if (a[i][j + 1] == '\0' && c != a[i][0])
follow(a[i][0]);
}
}
}
}
