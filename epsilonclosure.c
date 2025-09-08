


#include<stdio.h>
#include<string.h>

char result[20][20], current_state[3];

void display(int n) {
    printf("\n  Epsilon closure of %s = {", current_state);
    for(int i=0; i<n; i++) {
        printf(" %s", result[i]);
    }
    printf(" }");
}

int main() {
    FILE *file = fopen("automata.txt", "r");
    int n;
    char state[3], state1[3], input[3], state2[3];
    
    printf("Enter number of states: ");
    scanf("%d", &n);
    
    char states[n][3];
    printf("Enter state names: ");
    for(int i=0; i<n; i++) {
        scanf("%s", states[i]);
    }
    
    for(int i=0; i<n; i++) {
        int count = 0;
        strcpy(state, states[i]);
        strcpy(current_state, state);
        strcpy(result[count++], state);
        
        while(fscanf(file, "%s%s%s", state1, input, state2) != EOF) {
            if(strcmp(state, state1)==0 && strcmp(input, "e")==0) {
                strcpy(result[count++], state2);
                strcpy(state, state2);
            }
        }
        
        display(count);
        rewind(file);
    }
    
    fclose(file);
    return 0;
}
