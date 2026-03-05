#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack[top--];
}

char peek() {
    if (top == -1) return -1;
    return stack[top];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char* exp) {
    char result[MAX];
    int k = 0;

    for (int i = 0; exp[i] != '\0'; i++) {
        char c = exp[i];

        if (isalnum(c)) {
            result[k++] = c;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && peek() != '(') {
                result[k++] = pop();
            }
            pop();
        }
        else {
            while (top != -1 && precedence(peek()) >= precedence(c)) {
                result[k++] = pop();
            }
            push(c);
        }
    }

    while (top != -1) {
        result[k++] = pop();
    }

    result[k] = '\0';
    printf("%s\n", result);
}

int main() {
    char expression[MAX];
    scanf("%s", expression);

    infixToPostfix(expression);

    return 0;
}