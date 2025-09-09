#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 50
#define MAX_SYMBOLS 10

int nStates, nSymbols, nFinal;
char alphabet[MAX_SYMBOLS];
int transition[MAX_STATES][MAX_SYMBOLS];
bool isFinal[MAX_STATES];
bool distinguishable[MAX_STATES][MAX_STATES];
int classID[MAX_STATES];  

int symbolIndex(char sym) {
    for (int i = 0; i < nSymbols; i++)
        if (alphabet[i] == sym)
            return i;
    return -1;
}

void inputDFA() {
    printf("Enter number of states: ");
    scanf("%d", &nStates);

    printf("Enter number of symbols: ");
    scanf("%d", &nSymbols);

    printf("Enter symbols (space-separated): ");
    for (int i = 0; i < nSymbols; i++)
        scanf(" %c", &alphabet[i]);

   
    for (int s = 0; s < nStates; s++)
        for (int sym = 0; sym < nSymbols; sym++)
            transition[s][sym] = -1;

    printf("Now enter transitions as: <current_state> <symbol> <next_state>\n");
    printf("Enter total %d * %d = %d transitions:\n", nStates, nSymbols, nStates * nSymbols);

    for (int i = 0; i < nStates * nSymbols; i++) {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);

        int symIdx = symbolIndex(sym);
        if (symIdx == -1) {
            printf("Invalid symbol!\n");
            return;
        }
        transition[from][symIdx] = to;
    }

    printf("Enter number of final states: ");
    scanf("%d", &nFinal);

    for (int i = 0; i < nStates; i++) isFinal[i] = false;
    printf("Enter final states: ");
    for (int i = 0; i < nFinal; i++) {
        int f;
        scanf("%d", &f);
        isFinal[f] = true;
    }
}

void initializeTable() {
    for (int i = 0; i < nStates; i++) {
        for (int j = 0; j < nStates; j++) {
            distinguishable[i][j] = false;
        }
    }


    for (int i = 0; i < nStates; i++) {
        for (int j = 0; j < i; j++) {
            if (isFinal[i] != isFinal[j]) {
                distinguishable[i][j] = true;
            }
        }
    }
}

void minimizeDFA() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < nStates; i++) {
            for (int j = 0; j < i; j++) {
                if (!distinguishable[i][j]) {
                    for (int sym = 0; sym < nSymbols; sym++) {
                        int next1 = transition[i][sym];
                        int next2 = transition[j][sym];

                        int a = next1 > next2 ? next1 : next2;
                        int b = next1 > next2 ? next2 : next1;

                        if (distinguishable[a][b]) {
                            distinguishable[i][j] = true;
                            changed = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}

int buildEquivalenceClassesAndPrint() {
    bool visited[MAX_STATES] = {false};
    int newClassCount = 0;

    printf("\n=== Equivalent (Merged) States ===\n");
    for (int i = 0; i < nStates; i++) {
        if (!visited[i]) {
            printf("{ %d", i);
            classID[i] = newClassCount;

            for (int j = i + 1; j < nStates; j++) {
                int a = i > j ? i : j;
                int b = i > j ? j : i;

                if (!distinguishable[a][b]) {
                    visited[j] = true;
                    classID[j] = newClassCount;
                    printf(", %d", j);
                }
            }

            visited[i] = true;
            printf(" }\n");
            newClassCount++;
        }
    }
    return newClassCount; 
}

void printMinimizedDFA(int minimizedStates) {
    printf("\n=== Minimized DFA ===\n");
    printf("Number of states: %d\n", minimizedStates);

    
    bool newFinal[MAX_STATES] = {false};
    for (int old = 0; old < nStates; old++) {
        if (isFinal[old]) {
            newFinal[classID[old]] = true;
        }
    }


    printf("\nTransition Table:\n");
    for (int c = 0; c < minimizedStates; c++) {
        printf("State %d:", c);

       
        int repOld = -1;
        for (int old = 0; old < nStates; old++) {
            if (classID[old] == c) {
                repOld = old;
                break;
            }
        }

        for (int sym = 0; sym < nSymbols; sym++) {
            int nextOld = transition[repOld][sym];
            int nextNew = classID[nextOld];
            printf(" %c->%d", alphabet[sym], nextNew);
        }
        printf("\n");
    }

    
    printf("\nFinal states in minimized DFA: ");
    for (int c = 0; c < minimizedStates; c++) {
        if (newFinal[c]) printf("%d ", c);
    }
    printf("\n");
}

int main() {
    inputDFA();
    initializeTable();
    minimizeDFA();

    
    int minimizedStates = buildEquivalenceClassesAndPrint();

  
    printMinimizedDFA(minimizedStates);

    return 0;
}
