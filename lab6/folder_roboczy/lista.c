#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*
 * Program, który pokazuje jak utworzyć trzyelementową listę jednokierunkową
 * @author Stanisław Polak
 * @version 1.0 22-05-2020
*/
    enum Day{MON,TUE,WED,THU,FRI,SAT,SUN};
    /**********************/
    /* Struktura 'Lesson' */
    /**********************/
    typedef struct Lesson{
        char *className;
        enum Day day;
        int hour;
        int minute;
        int duration;
    }Lesson;
    /********************/
    /* Struktura 'Node' */
    /********************/
    typedef struct Node{
        struct Lesson lesson;
        struct Node *next;
    }Node;
    char *dayNames[] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};

void List__insert(Node *list, Lesson lesson, bool begin){
	if (begin == false){
		if ( list->next == NULL){
			Node *new_node = (Node *)malloc(sizeof(Node));
			list->next = new_node;
			printf("Dodaje przedmiot %s na koniec\n\n",lesson.className);
			if (new_node != NULL)
				new_node->lesson = lesson;
		}
		else
			List__insert(list->next, lesson, begin);
	}
	if ( begin == true ){
		Node *new_node = (Node *)malloc(sizeof(Node));
		printf("Dodaje przedmiot %s na początek\n\n",lesson.className);
		if (new_node != NULL){
			new_node->next = list->next;//dodaje wskaźnik z nowego elementu na oryginalnie drugi element
			list->next = new_node;// dodaje wskaźnik z pierwszego elementu na nowy node
			new_node->lesson = list->lesson;//zamiana lekcji między pierwszym a drugim 
			list->lesson = lesson;
		}
	}
}


void List__remove(Node *list, Lesson lesson){//Usuwa lekcję lesson z listy list, o ile takowa (lekcja) występuje na liście	
	int zmienna=0;
	Node *current = list;
	if(current->lesson.className == lesson.className && current->lesson.day == lesson.day && current->lesson.hour == lesson.hour && current->lesson.minute == lesson.minute && current->lesson.duration == lesson.duration){
		zmienna++;
		printf("Usuwam pierwszy przedmiot %s\n\n",lesson.className);
		//free(list->next);
		list->lesson = list->next->lesson;
		list->next = list->next->next;
	}
	for (current = list; current->next != NULL; current = current->next){
		if(current->next->lesson.className == lesson.className && current->next->lesson.day == lesson.day && current->next->lesson.hour == lesson.hour && current->next->lesson.minute == lesson.minute && current->next->lesson.duration == lesson.duration){
			zmienna++;
			printf("Usuwam przedmiot %s z listy\n\n",lesson.className);
			if ( current->next->next == NULL){// przypade gdy przedmiot jest ostatni
				free(current->next);
				current->next = NULL;
				return;
			}
			else{// gdy przedmiot nie jest ostatni
				//Node *tmp = current->next;
				//free(tmp);
				current->next = current->next->next;
				free(current->next);
			}
		}
	}
	if ( zmienna == 0){
		        printf("Przedmiot: \e[31m%s\e[0m\nDzień tygodnia: \e[31m%s\e[0m\nGodzina rozpoczęcia [Czas trwania]: \e[31m%02d:%02d [%d]\e[0m\nNie występuje na liście!\n\n",lesson.className, dayNames[lesson.day], lesson.hour, lesson.minute, lesson.duration);
	}
}

void List__print(struct Node *list){//Wyświetla zawartość listy list
	for (Node *current = list; current != NULL; current = current->next){
        	printf("%s %s %02d:%02d [%d]\n", current->lesson.className, dayNames[current->lesson.day], current->lesson.hour, current->lesson.minute, current->lesson.duration);
    	}
	printf("\n");
}

void List__destroy(Node** list){
	if(*list == NULL){
        	printf("Lista nie istnieje\n");
                return;
        }
        if((*list)->next != NULL){
        	List__destroy(&((*list)->next));
              	free(*list);
              	*list = NULL;
	}
}


int main(void){

    // Zmienna 'head' będzie przechowywać wskazanie na pierwszy element / węzeł listy
    Node *head = NULL; // Na razie nie przechowuje niczego

    //  Utworzenie pierwszego węzła listy
    Node *node1 = (Node *)malloc(sizeof(Node));
    
    List__destroy(&head);

    if (node1 != NULL) // Jeżeli udało się utworzyć węzeł, to wypełnij go danymi
    {
        // Określanie zawartości struktury 'Lesson'
        node1->lesson.className = "Podstawy Programowania";
        node1->lesson.day = WED;
        node1->lesson.hour = 12;
        node1->lesson.minute = 50;
        node1->lesson.duration = 90;

        // Określanie wskazania na następny węzeł listy
        node1->next = NULL; // Wartość NULL oznacza, że dany węzeł nie ma następnika
    }

    /*
    Po wykonaniu tych instrukcji zmienna 'node1' wskazuje na następującą strukturę danych:

                                   Struktura 'Node'
                   +--------------------------------------------------------+
                   |                          Struktura 'Lesson             |
                   |              +---------------------------------------+ |
                   |              | className -> "Podstawy Programowania" | |
                   |              | day:          WED                     | |
                   | lesson :     | hour:         12                      | |
                   |              | minute:       50                      | |
                   |              | duration:     90                      | |
                   |              +---------------------------------------+ |
      node1 -----> +--------------------------------------------------------+
                   | next:        NULL                                      |
                   +--------------------------------------------------------+
        */

    //  Utworzenie drugiego węzła
    Node *node2 = (Node *)malloc(sizeof(Node));
    if (node2 != NULL)
    {
        node2->lesson.className = "Wychowanie fizyczne";
        node2->lesson.day = MON;
        node2->lesson.hour = 8;
        node2->lesson.minute = 00;
        node2->lesson.duration = 90;
        node2->next = NULL;
    }

    //  Utworzenie trzeciego węzła
    Node *node3 = (Node *)malloc(sizeof(Node));
    if (node3 != NULL)
    {
        node3->lesson.className = "Konsultacje";
        node3->lesson.day = THU;
        node3->lesson.hour = 11;
        node3->lesson.minute = 5;
        node3->lesson.duration = 30;
        node3->next = NULL;
    }

    // Wstawianie węzłów do listy — pierwszy sposób
    if (node1 != NULL && node2 != NULL && node3 != NULL)
    {
        head = node1;
        node1->next = node2;
        node2->next = node3;

        /*
        Po wykonaniu tych instrukcji lista wygląda następująco:

                         +--------+         +--------+         +------------+
                         | lesson |         | lesson |         | lesson     |
                   +-->  +--------+    +--> +--------+    +--> +------------+
                   |     |        |    |    |        |    |    |            |
          head ----+     | next   |----+    | next   |----+    | next: NULL |
                         +--------+         +--------+         +------------+
                             ^                  ^                     ^
                             |                  |                     |
                           node1              node2                  node3
    */
    }

    // Wstawianie węzłów do listy — drugi sposób
    if (node1 != NULL && node2 != NULL && node3 != NULL)
    {
        head = node1;
        head->next = node2;
        head->next->next = node3;
    }

    // Wstawianie węzłów do listy — trzeci sposób
    Node *current;

    if (node1 != NULL && node2 != NULL && node3 != NULL)
    {
        current = head = node1; // Ustawienie wskaźników (zmiennych) 'current' oraz 'head' na pierwszy węzęł listy
        current->next = node2;  // Dopięcie drugiego elementu (węzła) do 'current', czyli de facto do pierwszego węzła listy

        current = current->next; // Ustawienie zmiennej 'current' na drugi element listy
        current->next = node3;   // Dopięcie trzeciego elementu do 'current', czyli do drugiego (węzła)

        /*
        Dopinanie, ewentualnych, kolejnych węzłów:

        current = current->next; // Ustawienie zmiennej 'current' na trzeci element listy
        current->next = node4;   // Dopięcie czwartego elementu do 'current', czyli do trzeciego

        current = current->next; // Ustawienie zmiennej 'current' na czwart element listy
        current->next = node5;   // Dopięcie piątego elementu do 'current', czyli do czwartego

        ...
        */
    }

    Lesson lesson1;
    lesson1.className = "Analiza II";
    lesson1.day = TUE;
    lesson1.hour = 17;
    lesson1.minute = 50;
    lesson1.duration = 90;
    
    List__print(head);
    //List__insert(head, lesson1, false);

    Lesson lesson2;
    lesson2.className = "Fizyka";
    lesson2.day = TUE;
    lesson2.hour = 10;
    lesson2.minute = 69;
    lesson2.duration = 69;

    List__print(head);
    //List__insert(head, lesson2, true);
	
    Lesson lesson3;
    lesson3.className = "ZBI";
    lesson3.day = TUE;
    lesson3.hour = 17;
    lesson3.minute = 50;
    lesson3.duration = 90;

    List__print(head);
    //List__remove(head,lesson1);
    List__print(head);
    //List__remove(head,lesson2);
    List__print(head);
    List__destroy(&head);
    List__destroy(&head);

    // Wypisanie informacji o wszystkich lekcjach zawartych na liście
    for (current = head; current != NULL; current = current->next)
    {
        printf("Przedmiot: \e[31m%s\e[0m\nDzień tygodnia: \e[31m%s\e[0m\nGodzina rozpoczęcia [Czas trwania]: \e[31m%02d:%02d [%d]\e[0m\n\n", current->lesson.className, dayNames[current->lesson.day], current->lesson.hour, current->lesson.minute, current->lesson.duration);
    }
}
