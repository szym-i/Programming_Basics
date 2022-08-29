#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Stack {
    int *stack;// stos
    int current_size;// aktualny rozmiar stosu
    int max_size;// maksymalny rozmiar stosu
};

typedef struct Stack Stack;

Stack *Stack__create(int size){// Tworzy stos o rozmiarze size i zwraca go. Jeżeli utworzenie stosu nie powiodło się, to program ma zakończyć działanie
    int *stack = malloc(size*sizeof(int));
    if (stack == NULL){
        fprintf(stderr, "\033[1;33mNie mogę stworzyć stosu o podanym rozmiarze.\n\033[0m");
        exit(EXIT_FAILURE);
    }

    Stack *Stack = malloc(sizeof(Stack));

    Stack->stack = stack;
    Stack->current_size = 0;// bo stworzony stos jest pusty
    Stack->max_size = size;
    printf("Tworzę Stack o wielkości %d\n",size);
    return Stack;
}

void Stack__destroy(Stack **Stack){// Zwalnia pamięć dla stosu stack, o ile stos istnieje. Jeżeli nie istnieje, to wypisuje stosowny komunikat
    if ((*Stack) == NULL) {
        fprintf(stderr, "\033[1;33mStos nie istnieje.\n\033[0m");
	return;
    }
    printf("\033[1;31mUsuwam stos\033[0m\n");
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

int Stack__pop(Stack *s){// Zdejmuje element (liczbę) ze szczytu stosu stack i zwraca go
    if (s == NULL){// jeśli stos nie isntieje
        fprintf(stderr, "\033[1;33mNie udało się zdjąć liczby ze stosu - stos nie istnieje.\n\033[0m");
        exit(EXIT_FAILURE);
    }
    if (s->current_size == 0){
        fprintf(stderr, "\033[1;33mNie udało się zdjąć liczby ze stosu - stos jest pusty.\n\033[0m");
        return INT_MIN;
    }
    return s->stack[--(s->current_size)];
}

void Stack__print(Stack *s){// Wypisuje zawartość stosu stack
    if (s == NULL) {
        fprintf(stderr, "\033[1;33mNie udało się wyświetlić zawartości stosu - stos nie istnieje.\n\033[0m");
        //exit(EXIT_FAILURE);
	return;
    }
    printf("\033[1;36mStack__print():\n");
    if ( s->current_size == 0){
	printf("Stos istnieje, ale jest pusty\n");
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
