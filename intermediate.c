/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char items[MAX][10];  // Store strings instead of chars
    int top;
} Stack;

void push(Stack *s, const char *item) {
    strcpy(s->items[++(s->top)], item);
}

char* pop(Stack *s) {
    return s->items[(s->top)--];
}

char* peek(Stack *s) {
    return s->items[s->top];
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int tempVarCount = 1;

void generateTAC(char postfix[]) {
    Stack s;
    s.top = -1;

    char operand1[10], operand2[10], result[10], temp[10];
    int i = 0;

    while (postfix[i]) {
        if (isalpha(postfix[i])) {
            char op[2] = {postfix[i], '\0'};
            push(&s, op);
        } else if (isOperator(postfix[i])) {
            strcpy(operand2, pop(&s));
            strcpy(operand1, pop(&s));
            sprintf(temp, "t%d", tempVarCount++);
            printf("%s = %s %c %s\n", temp, operand1, postfix[i], operand2);
            push(&s, temp);
        }
        i++;
    }
}

void infixToPostfix(char infix[], char postfix[]) {
    Stack s;
    s.top = -1;
    int i = 0, j = 0;

    while (infix[i]) {
        if (isalpha(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            char temp[2] = {infix[i], '\0'};
            push(&s, temp);
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && peek(&s)[0] != '(') {
                postfix[j++] = pop(&s)[0];
            }
            pop(&s); // Remove '('
        } else if (isOperator(infix[i])) {
            while (!isEmpty(&s) && precedence(peek(&s)[0]) >= precedence(infix[i])) {
                postfix[j++] = pop(&s)[0];
            }
            char temp[2] = {infix[i], '\0'};
            push(&s, temp);
        }
        i++;
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s)[0];
    }

    postfix[j] = '\0';
}

int main() {
    char input[100];
    char infix[100];
    char lhs;
    char postfix[100];

    printf("Enter expression (e.g., a = b + c * d):\n");
    fgets(input, sizeof(input), stdin);

    // Remove whitespace
    int i = 0, j = 0;
    while (input[i]) {
        if (!isspace(input[i])) {
            infix[j++] = input[i];
        }
        i++;
    }
    infix[j] = '\0';

    // Split into LHS and RHS
    lhs = infix[0];
    if (infix[1] != '=') {
        printf("Invalid expression.\n");
        return 1;
    }

    char rhs[100];
    strcpy(rhs, infix + 2);  // Skip a=

    infixToPostfix(rhs, postfix);
    printf("\nIntermediate Code (Three Address Code):\n");
    generateTAC(postfix);
    printf("%c = t%d\n", lhs, tempVarCount - 1);

    return 0;
}*/

#include <stdio.h>
#include <string.h>
#define MAX 100
int tempCount = 1;
// Generate a new temp variable like t1, t2, ...
void newTemp(char *t) {
 sprintf(t, "t%d", tempCount++);
}
// Precedence function
int precedence(char op) {
 if (op == '*' || op == '/') return 2;
 if (op == '+' || op == '-') return 1;
 return 0;
}
int main() {
 char expr[MAX];
 char temp[10];
 int i, j;
 printf("Enter expression: ");
 scanf("%s", expr);
 printf("\nIntermediate Code Generation:\n");
 // Work on a copy of expression tokens
 char tokens[50][10]; // split into symbols
 int n = 0;
 // Split expr into individual tokens (for now: single-char operands and operators)
 for (i = 0; expr[i] != '\0'; i++) {
 char buf[2] = {expr[i], '\0'};
 strcpy(tokens[n++], buf);
 }
 // Process operators by precedence
 for (int p = 2; p > 0; p--) {
 for (i = 0; i < n; i++) {
 if (precedence(tokens[i][0]) == p) {
 char left[10], right[10];
 strcpy(left, tokens[i - 1]);
 strcpy(right, tokens[i + 1]);
 newTemp(temp);
 printf("%s = %s %s %s\n", temp, left, tokens[i], right);
// Replace (left op right) with temp
 strcpy(tokens[i - 1], temp);
 // Shift remaining tokens left
 for (j = i + 2; j < n; j++) {
 strcpy(tokens[j - 2], tokens[j]);
 }
 n -= 2;
 // Restart from beginning for this precedence
 i = -1;
 }
 }
 }
    return 0;
}
