#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_EXPR_SIZE 100

struct Node {
    char data;
    struct Node* next;
};

struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(struct Node** top, char data) {
    struct Node* newNode = createNode(data);
    if (!newNode) {
        fprintf(stderr, "bellek ayirma hatasi\n");
        exit(1);
    }
    newNode->next = *top;
    *top = newNode;
}

char pop(struct Node** top) {
    if (*top == NULL) {
        fprintf(stderr, "yigin bos\n");
        exit(1);
    }
    struct Node* temp = *top;
    char data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}

char peek(struct Node* top) {
    if (top == NULL) {
        fprintf(stderr, "yigin bos\n");
        exit(1);
    }
    return top->data;
}

int precedence(char operator) {
    switch (operator) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return -1;
    }
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int empty(struct Node* stack) {
    return stack == NULL;
}

int evaluatePostfix(char* postfix) {
    struct Node* stack = NULL;
    int i, result;

    for (i = 0; postfix[i]; ++i) {
        char token = postfix[i];

        if (isdigit(token)) {
            push(&stack, token - '0');
        } else if (isOperator(token)) {
            int op2 = pop(&stack);
            int op1 = pop(&stack);

            switch (token) {
            case '+':
                push(&stack, op1 + op2);
                break;
            case '-':
                push(&stack, op1 - op2);
                break;
            case '*':
                push(&stack, op1 * op2);
                break;
            case '/':
                push(&stack, op1 / op2);
                break;
            case '^':
                push(&stack, op1 ^ op2);
                break;
            }
        }
    }

    if (!empty(stack)) {
        result = pop(&stack);
    } else {
        fprintf(stderr, "gecersiz postfix ifade\n");
        exit(1);
    }

    return result;
}

void infixToPostfixStepByStep(char infix[], FILE* output) {
    char postfix[MAX_EXPR_SIZE];
    struct Node* stack = NULL;
    int i, j, k;

    for (i = 0, j = 0; infix[i]; ++i) {
        char token = infix[i];

        if (isalnum(token)) {
            postfix[j++] = token;
        } else if (token == '(') {
            push(&stack, token);
        } else if (token == ')') {
            while (!empty(stack) && peek(stack) != '(') {
                postfix[j++] = pop(&stack);
            }
            pop(&stack);
        } else if (isOperator(token)) {
            while (!empty(stack) && precedence(token) <= precedence(peek(stack))) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, token);
        }

        fprintf(output, "Token: %c\n", token);
        fprintf(output, "Postfix: ");
        for (k = 0; k < j; k++) {
            fprintf(output, "%c", postfix[k]);
        }
        fprintf(output, "\nStack: ");
        struct Node* temp = stack;
        while (temp != NULL) {
            fprintf(output, "%c", temp->data);
            temp = temp->next;
        }
        fprintf(output, "\n");

        printf("Token: %c\n", token);
        printf("Postfix: ");
        for (k = 0; k < j; k++) {
            printf("%c", postfix[k]);
        }
        printf("\nStack: ");
        struct Node* temp2 = stack;
        while (temp2 != NULL) {
            printf("%c", temp2->data);
            temp2 = temp2->next;
        }
        printf("\n");
    }

    while (!empty(stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
    fprintf(output, "Son Postfix Ifade: %s\n", postfix);

    printf("Son Postfix Ifade: %s\n", postfix);

    int result = evaluatePostfix(postfix);
    fprintf(output, "Hesaplama sonucu: %d\n", result);
    printf("Hesaplama sonucu: %d\n", result);
}

int main() {
    char infix[MAX_EXPR_SIZE];
    printf("Bir infix ifade giriniz: ");
    scanf("%s", infix);

    FILE* outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Dosya acilamadi\n");
        return 1;
    }


    printf("Girilen infix ifadeyi adim adim postfix e donusturme:\n");
    fprintf(outputFile, "Girilen infix ifadeyi adim adim postfix e donusturme:\n");
    infixToPostfixStepByStep(infix, outputFile);

    fclose(outputFile);
    printf("Cikti ve diger adimlar output.txt ye yazildi\n");

    return 0;
}












