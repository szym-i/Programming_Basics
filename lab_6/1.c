#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Stack 
{
    int *stack;
    int current_size;
    int max_size;
};

typedef struct Stack Stack;

Stack *Stack__create(int size) // create Stack, if something went wrong end program working
{
    int *stack = malloc(size*sizeof(int));
    if (stack == NULL){
        fprintf(stderr, "\033[1;33mI can't create stack of this size.\n\033[0m");
        exit(EXIT_FAILURE);
    }

    Stack *Stack = malloc(sizeof(Stack));

    Stack->stack = stack;
    Stack->current_size = 0;
    Stack->max_size = size;
    printf("Tworzę Stack o wielkości %d\n",size);
    return Stack;
}

void Stack__destroy(Stack **Stack) // free memory of Stack, if Stack exists
{
    if ((*Stack) == NULL) {
        fprintf(stderr, "\033[1;33mStack does not exist.\n\033[0m");
	return;
    }
    printf("\033[1;31mI destroy Stack\033[0m\n");
    free((*Stack)->stack);
    free(*Stack);
    (*Stack) = NULL;
}

void Stack__push(Stack *s, int n){// Umieszcza liczbę number na szczycie stosu stack
    printf("\033[1;34mStack__push(%d)\n",n);
    if (s == NULL) {
        fprintf(stderr, "\033[1;33mNie udało się umieścić liczby na stosie - stos nie istnieje.\n\033[0m");
        exit(EXIT_FAILURE);
    }

    if (s->current_size == s->max_size) {
        fprintf(stderr, "\033[1;33mNie udało się umieścić liczby %d na stosie - stos jest pełny.\n\033[0m",n);
        return;
    }
    s->stack[(s->current_size)++] = n;
}

int Stack__pop(Stack *s){ // pop item from Stack and return it
    if (s == NULL){ // if Stack does not exist
        fprintf(stderr, "\033[1;33mCan't pop item from Stack - Stack does not exist.\n\033[0m");
        exit(EXIT_FAILURE);
    }
    if (s->current_size == 0){
        fprintf(stderr, "\033[1;33mCan't pop item from Stack - Stack is empty.\n\033[0m");
        return INT_MIN;
    }
    return s->stack[--(s->current_size)];
}

void Stack__print(Stack *s)
{
    if (s == NULL) {
        fprintf(stderr, "\033[1;33mCan't print Stack - Stack does not exist.\n\033[0m");
        //exit(EXIT_FAILURE);
	return;
    }
    printf("\033[1;36mStack__print():\n");
    if ( s->current_size == 0){
	printf("Stack is empty\n");
	return;
    }
    for (int i = 0; i < s->current_size; i++)
        printf("%i\n", s->stack[i]);
    printf("\033[0m\n");
}

int main() {
    Stack *stack = NULL;

    Stack__destroy(&stack);
    stack = Stack__create(3);
    Stack__push(stack, 3);
    Stack__push(stack, 5);
    Stack__push(stack, 2);
    Stack__push(stack, 4);

    Stack__print(stack);

    printf("\033[1;31mStack__pop():%d\n\n\033[0m", Stack__pop(stack));

    Stack__print(stack);

    printf("\033[1;31mStack__pop():%d\n\n\033[0m", Stack__pop(stack));
    Stack__print(stack);
    Stack__push(stack, 7);
    Stack__print(stack);

    printf("\033[1;31mStack__pop():%d\n\n\033[0m", Stack__pop(stack));
    Stack__print(stack);

    printf("\033[1;31mStack__pop():%d\n\n\033[0m", Stack__pop(stack));
    Stack__print(stack);

    printf("\033[1;31mStack__pop()=(wartość specjalna:INT_MIN):%d\n\n\033[0m", Stack__pop(stack));

    Stack__destroy(&stack);
    Stack__destroy(&stack);
    return 0;
}
