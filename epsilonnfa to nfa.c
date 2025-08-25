#include <stdio.h>
#include <string.h>

#define MAX 10
#define MAX_SYMBOLS 5

char states[MAX][5], symbols[MAX_SYMBOLS][5];
int n_states, n_symbols;
int transitions[MAX][MAX_SYMBOLS][MAX]; // [from][symbol][to] = 1 if transition exists
int epsilon[MAX][MAX]; // [from][to] = 1 if epsilon transition exists
int epsilon_closure[MAX][MAX]; // epsilon closure of each state

int get_state_index(char s[]) {
    for (int i = 0; i < n_states; i++) {
        if (strcmp(states[i], s) == 0)
            return i;
    }
    return -1;
}

int get_symbol_index(char s[]) {
    for (int i = 0; i < n_symbols; i++) {
        if (strcmp(symbols[i], s) == 0)
            return i;
    }
    return -1;
}

void compute_epsilon_closure() {
    for (int i = 0; i < n_states; i++) {
        epsilon_closure[i][i] = 1; // state is always in its own closure

        // Use DFS to compute closure
        for (int j = 0; j < n_states; j++) {
            if (epsilon[i][j]) {
                epsilon_closure[i][j] = 1;
                // Indirect closure
                for (int k = 0; k < n_states; k++) {
                    if (epsilon_closure[j][k])
                        epsilon_closure[i][k] = 1;
                }
            }
        }
    }
}

void remove_epsilon_transitions() {
    int new_transitions[MAX][MAX_SYMBOLS][MAX] = {0};

    for (int i = 0; i < n_states; i++) {
        for (int s = 0; s < n_symbols; s++) {
            for (int ec = 0; ec < n_states; ec++) {
                if (epsilon_closure[i][ec]) {
                    for (int t = 0; t < n_states; t++) {
                        if (transitions[ec][s][t])
                            new_transitions[i][s][t] = 1;
                    }
                }
            }
        }
    }

    // Copy back to transitions array
    memcpy(transitions, new_transitions, sizeof(transitions));
}

void print_new_transition_table() {
    printf("\nNFA Without Epsilon Transitions:\n");
    printf("State/Input\t");

    for (int i = 0; i < n_symbols; i++) {
        printf("%s\t", symbols[i]);
    }
    printf("\n");

    for (int i = 0; i < n_states; i++) {
        printf("%s\t\t", states[i]);
        for (int j = 0; j < n_symbols; j++) {
            printf("{");
            int first = 1;
            for (int k = 0; k < n_states; k++) {
                if (transitions[i][j][k]) {
                    if (!first) printf(",");
                    printf("%s", states[k]);
                    first = 0;
                }
            }
            printf("}\t");
        }
        printf("\n");
    }
}

int main() {
    int n_trans;
    char from[5], sym[5], to[5];

    printf("Enter number of states: ");
    scanf("%d", &n_states);

    printf("Enter states: ");
    for (int i = 0; i < n_states; i++)
        scanf("%s", states[i]);

    printf("Enter number of input symbols (excluding epsilon): ");
    scanf("%d", &n_symbols);
    printf("Enter input symbols: ");
    for (int i = 0; i < n_symbols; i++)
        scanf("%s", symbols[i]);

    printf("Enter number of transitions: ");
    scanf("%d", &n_trans);

    printf("Enter transitions (format: from input to), use 'e' for epsilon:\n");
    for (int i = 0; i < n_trans; i++) {
        scanf("%s %s %s", from, sym, to);
        int from_idx = get_state_index(from);
        int to_idx = get_state_index(to);

        if (strcmp(sym, "e") == 0) {
            epsilon[from_idx][to_idx] = 1;
        } else {
            int sym_idx = get_symbol_index(sym);
            transitions[from_idx][sym_idx][to_idx] = 1;
        }
    }

    compute_epsilon_closure();
    remove_epsilon_transitions();
    print_new_transition_table();

    return 0;
}
