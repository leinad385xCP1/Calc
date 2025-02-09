#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define STACK_SIZE 8

typedef struct {
    double data[STACK_SIZE];
    int top;
} Stack;

void initialize_stack(Stack *s) {
    s->top = -1;
    for (int i = 0; i < STACK_SIZE; i++) {
        s->data[i] = 0.0;
    }
}

void display_stack(Stack *s) {
    printf("\\////// CALCULADORA RPN //////\\\n");
    for (int i = STACK_SIZE - 1; i >= 0; i--) {
        printf("%d. %.6f\n", i + 1, s->data[i]);
    }
}

void push(Stack *s, double value) {
    if (s->top < STACK_SIZE - 1) {
        s->data[++s->top] = value;
    } else {
        for (int i = 1; i < STACK_SIZE; i++) {
            s->data[i - 1] = s->data[i];
        }
        s->data[s->top] = value;
    }
}

double pop(Stack *s) {
    if (s->top >= 0) {
        double value = s->data[s->top];
        s->data[s->top--] = 0.0;
        return value;
    }
    return 0.0;
}

void perform_operation(Stack *s, char op) {
    if (op == 's' || op == 'c' || op == 't' || op == 'r') {
        if (s->top < 0) {
            printf("Error: No hay suficientes operandos\n");
            return;
        }
        double a = pop(s);
        switch (op) {
            case 's': push(s, sin(a)); break;
            case 'c': push(s, cos(a)); break;
            case 't': push(s, tan(a)); break;
            case 'r':
                if (a < 0) {
                    printf("Error: Raíz cuadrada de número negativo\n");
                    push(s, a);
                    return;
                }
                push(s, sqrt(a));
                break;
        }
    } else {
        if (s->top < 1) {
            printf("Error: No hay suficientes operandos\n");
            return;
        }
        double b = pop(s);
        double a = pop(s);
        switch (op) {
            case '+': push(s, a + b); break;
            case '-': push(s, a - b); break;
            case '*': push(s, a * b); break;
            case '/':
                if (b == 0) {
                    printf("Error: División por cero\n");
                    push(s, a);
                    push(s, b);
                    return;
                }
                push(s, a / b);
                break;
            case '^': push(s, pow(a, b)); break;
            default:
                printf("Error: Operador desconocido\n");
                push(s, a);
                push(s, b);
        }
    }
}

int main() {
    Stack stack;
    initialize_stack(&stack);
    int choice;
    double number;
    char op;

    while (1) {
        display_stack(&stack);
        printf("\nQue desea hacer?\n");
        printf("1. Ingresar número  2. Seleccionar operación  3. Limpiar último\n");
        printf("4. Limpiar todo  5. Salir\n");
        printf("Opción: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Ingrese un número: ");
                scanf("%lf", &number);
                push(&stack, number);
                break;
            case 2:
                printf("Ingrese operación (+, -, *, /, ^, s(sen), c(cos), t(tan), r(sqrt)): ");
                scanf(" %c", &op);
                perform_operation(&stack, op);
                break;
            case 3:
                pop(&stack);
                break;
            case 4:
                initialize_stack(&stack);
                break;
            case 5:
                return 0;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    }
    return 0;
}
