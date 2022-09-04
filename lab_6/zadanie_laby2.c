#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

    enum Day{MON,TUE,WED,THU,FRI,SAT,SUN};
    
    typedef struct Lesson{
        char *className;
        enum Day day;
        int hour;
        int minute;
        int duration;
    }Lesson;
    
    typedef struct Node{
        struct Lesson lesson;
        struct Node *next;
    }Node;
    
    char *dayNames[] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};

void List__destroy(Node** list){
        if(*list == NULL){
                printf("Lista już nie istnieje\n");
                return;
        }
        if((*list)->next != NULL){
                List__destroy(&((*list)->next));
                free(*list);
                *list = NULL;
        }
        else{
                free(*list);
                *list=NULL;
        }
	printf("\033[1;31mUsuwam listę\033[0m\n\n");
}


void List__remove(Node **list, Lesson lesson){//Usuwa lekcję lesson z listy list, o ile takowa (lekcja) występuje na liście      
        if ( *list == NULL){// przypade gdy lista nie istnieje
		fprintf(stderr,"\033[1;31mNie można usunąć przedmiotu %s bo lista nie istnieje\033[0m\n",lesson.className);
		//exit(EXIT_FAILURE);
		return;
	}
	if ( (*list)->next == NULL && (*list)->lesson.className == lesson.className && (*list)->lesson.day == lesson.day && (*list)->lesson.hour == lesson.hour && (*list)->lesson.minute == lesson.minute){// przypadek gdy usuwamy ostatni element z listy jaki został
		printf("\033[1;31mUsuwam przedmiot \033[9;31m%s\033[0;1;31m oraz listę\033[0m\n\n",lesson.className);
		List__destroy(list);
		return;
	}
	else{
		int zmienna=0;
        	Node *current = *list;
        	if(current->lesson.className == lesson.className && current->lesson.day == lesson.day && current->lesson.hour == lesson.hour && current->lesson.minute == lesson.minute && current->lesson.duration == lesson.duration){// przypadek gdy element jest pierwszy
                	zmienna++;
                	printf("\033[1;31mUsuwam pierwszy przedmiot \033[9;31m%s\033[0;1;31m z listy\n\n\033[0m",lesson.className);
                	(*list)->lesson = (*list)->next->lesson;
			free((*list)->next);// zwalniam pamięć
                	(*list)->next = (*list)->next->next;
			return;
        	}
        	for (current = *list; current->next != NULL; current = current->next){// przechodzimy po wszystkich nodach
                	if(current->next->lesson.className == lesson.className && current->next->lesson.day == lesson.day && current->next->lesson.hour == lesson.hour && current->next->lesson.minute == lesson.minute && current->next->lesson.duration == lesson.duration){
                        	zmienna++;
				printf("\033[1;31mUsuwam przedmiot \033[9;31m%s\033[0;1;31m z listy\n\n\033[0m",lesson.className);
                        	if ( current->next->next == NULL){// przypadek gdy przedmiot jest ostatni
                                	free(current->next);//zwalniam pamięć
                                	current->next = NULL;
					zmienna++;
                                	return;
                        	}
                        	else{// gdy przedmiot nie jest ostatni
                                	Node *tmp = current->next->next;
					free(current->next);//zwalniam pamięć
					current->next = tmp;
					free(tmp);//zwalniam pamięć
					zmienna++;
                        	}
                	}
        	}
        	if ( zmienna == 0){// przypadek gdy przedmiot nie zostanie znaleziony 
                       printf("\033[1;31mPrzedmiot %s nie znajduje się na liście, więc nie mogę go usunąć\033[0m\n\n", lesson.className);
		}
	}
}

void List__print(Node *list){//Wyświetla zawartość listy list
	if ( list == NULL){
		fprintf(stderr,"Lista nie istnieje, nie ma czego printować\n\n");
		//exit(EXIT_FAILURE);
		return;
	}
        for (Node *current = list; current != NULL; current = current->next){
                printf("%s %s %02d:%02d [%d]\n", current->lesson.className, dayNames[current->lesson.day], current->lesson.hour, current->lesson.minute, current->lesson.duration);
        }
        printf("\n");
}


void List__insert(Node **list, Lesson lesson, bool begin){
	if ( *list == NULL){// przypadek gdy lista jest pusta
		printf("\033[34mTworzę listę i dodaje przedmiot \033[1;3;36m%s\033[0m\n\n",lesson.className);
		*list = (Node *)malloc(sizeof(Node));
		(*list)->lesson = lesson;
		(*list)->next = NULL;
		return;
	}
	else{
        	if (begin == false){// element na koniec
			for(Node *current = *list; current != NULL; current = current->next){//przechodzimy po węzłach aż ktoryś nie będzie ostatni i dodajemy node na koniec	
                		if ( current->next == NULL){
                       			Node *new_node = (Node *)malloc(sizeof(Node));
                       			current->next = new_node;
					new_node->next = NULL;
                       			printf("\033[34mDodaje przedmiot \033[1;3;36m%s\033[0;34m na koniec\033[0m\n\n",lesson.className);
                       			if (new_node != NULL)// jeśli new_node się utworzy, przypisujemy mu lesson
                               			new_node->lesson = lesson;
					return;
               			}
			}
		}
        	if ( begin == true ){// element na początek 
                	Node *new_node = (Node *)malloc(sizeof(Node));
                	printf("\033[34mDodaje przedmiot \033[1;3;36m%s\033[0;34m na początek\033[0m\n\n",lesson.className);
                	if (new_node != NULL){
                        	new_node->next = (*list)->next;//dodaje wskaźnik z nowego elementu na oryginalnie drugi element
                        	(*list)->next = new_node;// dodaje wskaźnik z pierwszego elementu na nowy node
                        	new_node->lesson = (*list)->lesson;//zamiana lekcji między pierwszym a drugim
                        	(*list)->lesson = lesson;
                	}
        	}
	}
}



int main(void){
    Node *list = NULL;
    Lesson lesson1;

    lesson1.className = "Podstawy Programowania";
    lesson1.day = WED;
    lesson1.hour = 12;
    lesson1.minute = 50;
    lesson1.duration = 90;

    List__print(list);
    List__insert(&list, lesson1, true);
    List__print(list);
    
    Lesson lesson2;
    lesson2.className = "Wychowanie fizyczne";
    lesson2.day = MON;
    lesson2.hour = 8;
    lesson2.minute = 0;
    lesson2.duration = 90;

    List__insert(&list, lesson2, true);
    List__print(list);

    Lesson lesson3;
    lesson3.className = "Wykrywanie incydentów";
    lesson3.day = THU;
    lesson3.hour = 16;
    lesson3.minute = 15;
    lesson3.duration = 90;

    //List__insert(&list, lesson3, true);	
    //List__print(list);
    //List__remove(&list,lesson3);
    //List__print(list);
    List__remove(&list,lesson2);

    List__print(list); // Funkcja powinna wypisać:
                       // Wychowanie fizyczne, Poniedziałek 8:00 [90]
                       // Podstawy programowania, Środa 12:50 [90]
    //List__remove(&list, lesson1);
    //List__print(list); // Funkcja powinna wypisać:
                       // Podstawy programowania, Środa 12:50 [90]
    List__destroy(&list); // Likwidacja listy
    //List__remove(&list,lesson1);
    List__destroy(&list); // Wypisuje: "Lista nie istnieje"

    return 0;
}
