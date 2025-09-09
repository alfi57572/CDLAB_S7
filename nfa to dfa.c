#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10
#define MAX_INPUTS 5

int nfa[MAX][MAX_INPUTS][MAX]; // [state][symbol] = set of next states
int nfa_state_count, input_symbol_count;
char states[MAX][5], inputs[MAX_INPUTS][5];

int get_state_index(char *s) {
    for (int i = 0; i < nfa_state_count; i++)
        if (strcmp(states[i], s) == 0) return i;
    return -1;
}

int get_input_index(char *s) {
    for (int i = 0; i < input_symbol_count; i++)
        if (strcmp(inputs[i], s) == 0) return i;
    return -1;
}

// Utility to print a set
void print_state_set(int *set) {
    printf("{");
    int first = 1;
    for (int i = 0; i < nfa_state_count; i++) {
        if (set[i]) {
            if (!first) printf(",");
            printf("%s", states[i]);
            first = 0;
        }
    }
    printf("}");
}

// Check if a state set is already in dfa_states
int state_sets_equal(int *a, int *b) {
    for (int i = 0; i < nfa_state_count; i++)
        if (a[i] != b[i]) return 0;
    return 1;
}

// Copy a state set
void copy_state_set(int *dest, int *src) {
    for (int i = 0; i < nfa_state_count; i++)
        dest[i] = src[i];
}

// Main
int main() {
    int transitions;
    char from[5], input[5], to[5];

    printf("Enter number of NFA states: ");
    scanf("%d", &nfa_state_count);
    printf("Enter state names: ");
    for (int i = 0; i < nfa_state_count; i++)
        scanf("%s", states[i]);

    printf("Enter number of input symbols: ");
    scanf("%d", &input_symbol_count);
    printf("Enter input symbols: \n");
    for (int i = 0; i < input_symbol_count; i++)
        scanf("%s", inputs[i]);

    printf("Enter number of transitions: \n");
    scanf("%d", &transitions);
    printf("Enter transitions (from input to):\n");
    for (int i = 0; i < transitions; i++) {
        scanf("%s %s %s", from, input, to);
        int from_i = get_state_index(from);
        int input_i = get_input_index(input);
        int to_i = get_state_index(to);
        nfa[from_i][input_i][to_i] = 1;
    }

    // Subset construction
    int dfa_states[100][MAX] = {0}; // array of state sets
    int dfa_transitions[100][MAX_INPUTS]; // mapping [dfa_state][input] = next_dfa_state
    int dfa_state_count = 0;

    int queue[100], front = 0, rear = 0;
    int visited[100] = {0};

    // Start with ε-closure of q0 → in this case, just {q0}
    dfa_states[0][0] = 1; // q0
    queue[rear++] = 0;
    dfa_state_count++;

    while (front < rear) {
        int curr_index = queue[front++];
        for (int sym = 0; sym < input_symbol_count; sym++) {
            int new_set[MAX] = {0};

            for (int i = 0; i < nfa_state_count; i++) {
                if (dfa_states[curr_index][i]) {
                    for (int j = 0; j < nfa_state_count; j++) {
                        if (nfa[i][sym][j]) {
                            new_set[j] = 1;
                        }
                    }
                }
            }

            // Check if new_set already exists
            int exists = -1;
            for (int i = 0; i < dfa_state_count; i++) {
                if (state_sets_equal(dfa_states[i], new_set)) {
                    exists = i;
                    break;
                }
            }

            if (exists == -1) {
                // New state
                copy_state_set(dfa_states[dfa_state_count], new_set);
                dfa_transitions[curr_index][sym] = dfa_state_count;
                queue[rear++] = dfa_state_count;
                dfa_state_count++;
            } else {
                dfa_transitions[curr_index][sym] = exists;
            }
        }
    }

    // Print DFA transition table
    printf("\nDFA Transition Table:\n");
    printf("State\t");
    for (int i = 0; i < input_symbol_count; i++)
        printf("%s\t", inputs[i]);
    printf("\n");

    for (int i = 0; i < dfa_state_count; i++) {
        print_state_set(dfa_states[i]);
        printf("\t");
        for (int j = 0; j < input_symbol_count; j++) {
            int dest = dfa_transitions[i][j];
            print_state_set(dfa_states[dest]);
            printf("\t");
        }
        printf("\n");
    }

    return 0;
}
