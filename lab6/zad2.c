#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum day_definition
{
    MON,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUN
} Day;

typedef struct lesson_definition
{
    char *className;
    Day day;
    int hour;
    int minute;
    int duration;
} Lesson;

typedef struct list_element_definition {
    Lesson element;
    void *next;
} L_element;

typedef struct list_definition {
    L_element *head;
    L_element *tail;
} List;

const char days[7][14] = {"Poniedziałek\0", "Wtorek\0", "Środa\0", "Czwartek\0", "Piątek\0", "Sobota\0", "Niedziela\0"};

const char* Day__toString(Day d) {
	return (*days + d * 14);
}

void Lesson__toString(Lesson lesson) {
	printf("%s, %s, %i:%02i [%i]\n", lesson.className, Day__toString(lesson.day), lesson.hour, lesson.minute, lesson.duration);
}

List *List__create() {
    List *l = malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;
    return l;
}

void List__insert(List *l, Lesson element, int begin) {
    if (l == NULL) {
        fprintf(stderr, "Nie udało się dodać elementu do listy - lista nie istnieje.\n");
        exit(EXIT_FAILURE);
    }

    L_element *e = malloc(sizeof(L_element));
    e->element = element;

    if (begin) {
        e->next = l->head;
        l->head = e;
        return;
    }

    e->next = NULL;
    l->tail->next = e;
    l->tail = e;
}

int Lesson__equals(Lesson a, Lesson b) {
    return a.day == b.day && a.duration == b.duration && a.hour == b.hour && a.minute == b.minute && !strcmp(a.className, b.className);
}

void List__remove(List *l, Lesson element) {
    if (l == NULL) {
        fprintf(stderr, "Nie udało się usunąć elementu z listy - lista nie istnieje.\n");
        exit(EXIT_FAILURE);
    }

    L_element *e = l->head;
    L_element *p = NULL;
    do {
        if (!Lesson__equals(e->element, element)) {
            p = e;
            continue;
        }

        if (p == NULL) {
            l->head = e->next;
            free(e);
            break;
        }

        p->next = e->next;
        free(e);
        break;
    } while ((e = e->next) != NULL);
}

void List__print(List *l) {
    if (l == NULL) {
        fprintf(stderr, "Nie udało się dodać elementu do listy - lista nie istnieje.\n");
        exit(EXIT_FAILURE);
    }

    L_element *e = l->head;
    do
        Lesson__toString(e->element);
        while ((e = e->next) != NULL);
}

void List__destroy(List **l) {
    if ((*l) == NULL) {
        fprintf(stderr, "Nie udało się usunąć listy.\n");
        return;
    }

    if ((*l)->head != NULL) 
    {
        L_element *e = (*l)->head;

        while (e != NULL) {
            L_element *ne = e->next;
            free(e);
            e = ne;
        }
    }

    free (*l);
    (*l) = NULL;
}

void main()
{
    List *list = List__create();
    Lesson lesson;

    lesson.className = "Podstawy Programowania";
    lesson.day = WED;
    lesson.hour = 12;
    lesson.minute = 50;
    lesson.duration = 90;
    List__insert(list, lesson, 1);

    lesson.className = "Wychowanie fizyczne";
    lesson.day = MON;
    lesson.hour = 8;
    lesson.minute = 00;
    lesson.duration = 90;
    List__insert(list, lesson, 1);

    List__print(list);
    printf("\n");

    List__remove(list, lesson);
    List__print(list);

    List__destroy(&list);
    List__destroy(&list);
}
