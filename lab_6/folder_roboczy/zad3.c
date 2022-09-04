#include <stdio.h>
#include <stdlib.h>

typedef struct queue_element_definition {
    void *element;
    void *next;
} Q_element;

typedef struct queue_definition {
    Q_element *head;
    Q_element *tail;
} Queue;

Queue *Queue__create() {
    Queue *q = malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    return q;
}

void Queue__destroy(Queue **q) {
    if ((*q) == NULL) {
        fprintf(stderr, "Nie udało się usunąć kolejki.\n");
        return;
    }

    if ((*q)->head != NULL) 
    {
        Q_element *e = (*q)->head;

        while (e != NULL) {
            Q_element *ne = e->next;
            free(e->element);
            free(e);
            e = ne;
        }
    }

    free (*q);
    (*q) = NULL;
}

void Queue__enqueue(Queue *q, void *element) {
    if (q == NULL) {
        fprintf(stderr, "Nie udało się dodać liczby do kolejki - kolejka nie istnieje.\n");
        exit(EXIT_FAILURE);
    }

    Q_element *e = malloc(sizeof(Q_element));
    e->element = element;
    e->next = NULL;

    if (q->head == NULL) {
        q->head = e;
        q->tail = e;
        return;
    }

    q->tail->next = e;
    q->tail = e;
}

void Queue__enqueue_int(Queue *q, int element) {
    int *e = malloc(sizeof(int));
    *e = element;
    Queue__enqueue(q, e);
}

void *Queue__dequeue(Queue *q) {
    if (q == NULL) {
        fprintf(stderr, "Nie udało się zdjąć liczby z kolejki - kolejka nie istnieje.\n");
        exit(EXIT_FAILURE);
    }

    if (q->head == NULL) {
        fprintf(stderr, "Nie udało się pobrać liczby z kolejki - kolejka jest pusta.\n");
        return NULL;
    }

    Q_element *e = q->head;
    void *ev = e->element;
    q->head = q->head->next;
    free(e);
    return ev;
}

int Queue__dequeue_int(Queue *q) {
    int *e = (int*)Queue__dequeue(q);
    int ev = *e;
    free(e);
    return ev;
}

void Queue__print(Queue *q) {
    if (q == NULL) {
        fprintf(stderr, "Nie udało się wyświetlić zawartości kolejki - kolejka nie istnieje.\n");
        exit(EXIT_FAILURE);
    }

    Q_element *e = q->head;
    do
        printf("%i\n", *(int*)(e->element));
        while ((e = e->next) != NULL);
}

void main() {
    Queue *queue = NULL;
    Queue__destroy(&queue);
    queue = Queue__create();
    printf("%p\n", Queue__dequeue(queue));

	Queue__enqueue_int(queue, 3);
	Queue__enqueue_int(queue, 5);
    Queue__enqueue_int(queue, 2);

	Queue__print(queue);

	printf("\n%i\n\n", Queue__dequeue_int(queue));

	Queue__print(queue);
    Queue__destroy(&queue);
    Queue__destroy(&queue);
}
