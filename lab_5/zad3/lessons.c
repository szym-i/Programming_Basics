#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../zad1/action.c"

struct Term{
        int hour;
        int minute;
        int duration;// w minutach
	Day day;
};

typedef struct Term Term;

void Term__init(Term* term, int hour, int minute, int duration, int day){// przypisuje polom struktury podane wartości (bez alokacji pamięci)
        term->duration = duration;
        term->hour = hour%24;
        term->minute = minute%60;
	term->day = day;
}

Term* Term__create(int hour, int minute, int duration, int day){// przydziela pamięć dla "obiektu" Term oraz inicjalizuje go (korzystając z Term__init())
        Term *term= malloc(sizeof(struct Term));
        Term__init(term, hour, minute, duration, day);
}

void Term__destroy(Term* term){// zwalnia pamięć dla podanego (istniejącego) "obiektu"
        free(term);
}

char* Term1__toString(Term* term){// zwraca napis postaci "godzina:minuta [czas trwania]"
        char* result = malloc(15*sizeof(char));
        if( term->minute < 10)
                snprintf(result,15,"%d:0%d [%d]", term->hour,term->minute,term->duration);
        else
                snprintf(result,15,"%d:%d [%d]", term->hour,term->minute,term->duration);
        return result;
}

char* Term__toString(Term* term){// zwraca napis postaci "Dzień godzina:minuta [czas trwania]"
        char* result = malloc(25*sizeof(char));
        if( term->minute < 10)
                snprintf(result,25,"%s %d:0%d [%d]",Day__toString(term->day), term->hour,term->minute,term->duration);
        else
                snprintf(result,25,"%s %d:%d [%d]",Day__toString(term->day), term->hour,term->minute,term->duration);
        return result;
}

struct Lesson{
        Term* term;
        char* subject;
};

typedef struct Lesson Lesson;

void Lesson__init(Lesson *lesson, char *subject, Term *term){// przypisuje polom struktury podane wartości (bez alokacji pamięci)
        lesson->subject = subject;
        lesson->term = term;
}

Lesson* Lesson__create(char* subject, Term* term){// przydziela pamięć dla "obiektu" Term oraz inicjalizuje go (korzystając z Term__init())
        Lesson *lesson= malloc(sizeof(struct Lesson));
        Lesson__init(lesson, subject, term);
}

void Lesson__destroy(Lesson *lesson){// zwalnia pamięć dla podanego (istniejącego) "obiektu"
        free(lesson);
}

char* Lesson__toString(Lesson* lesson){// zwraca napisową reprezentację zajęć — napis postaci "Podstawy programowania, Środa 12:50 [90]"
	char* result = malloc(55*sizeof(char));
	snprintf(result,55,"%s, %s",lesson->subject,Term__toString(lesson->term));
	return result;
}

bool lessons_rules(int begin_hour, int end_hour, int end_minute, int end_day){// tutaj uzupełniamy warunki pod jakimi moga odbywać się zajęcia
        if (end_day == 6 || end_day == 7)
                return false;
        if ( end_hour > 20 || (end_hour == 20 && end_minute != 0))
                return false;
        if ( end_day == 5 && (end_hour > 17 || end_hour == 17 && end_minute != 0))
                return false;
        if ( begin_hour < 8 || end_hour < 8 )
                return false;
        return true;
}

void Lesson__earlierDay(Lesson* lesson){//przesuwa zajęcia o jeden dzień do tyłu
	int end_day = Day__prevDay(lesson->term->day);
        int end_hour = (lesson->term->hour + lesson->term->duration/60 + (lesson->term->minute + lesson->term-> duration%60)/60)%24;
        int end_minute = (lesson->term->minute + lesson->term-> duration%60)%60;
	if ( !lessons_rules(lesson->term->hour, end_hour, end_minute, end_day))
		printf("\033[0;33m Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s %s\" \n \033[0m",lesson->subject,Day__toString(end_day),Term1__toString(lesson->term));
	else{
		lesson->term->day = end_day;
	}
}


void Lesson__laterDay(Lesson* lesson){// przesuwa zajęcia o jeden dzień do przodu
	int end_day = Day__nextDay(lesson->term->day);
	int end_hour = (lesson->term->hour + lesson->term->duration/60 + (lesson->term->minute + lesson->term-> duration%60)/60)%24;
        int end_minute = (lesson->term->minute + (lesson->term->duration)%60)%60;
	if ( !lessons_rules(lesson->term->hour, end_hour, end_minute, end_day))
		printf("\033[0;33m Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s %s\"\n\033[0m",lesson->subject,Day__toString(end_day),Term1__toString(lesson->term));
	else{
		lesson->term->day = end_day;
	}

}

void Lesson__earlierTime(Lesson* lesson){// przesuwa zajęcia o jeden termin w tył, czyli o 'duration'
	int begin_minute = lesson->term->minute - lesson->term->duration % 60;
	int begin_hour = lesson->term->hour - lesson->term->duration/60;
	if( begin_minute < 0){
		begin_minute = 60 + begin_minute;
		begin_hour -= 1;
	}
	if (!lessons_rules(begin_hour,lesson->term->hour, lesson->term->minute, lesson->term->day)){
		printf("\033[0;33m Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s %d:%d [%d]\"\n\033[0m",lesson->subject,Day__toString(lesson->term->day),begin_hour,begin_minute, lesson->term->duration);
	}
	else{
                //printf("Termin w tył\n");
                lesson->term->hour = begin_hour;
                lesson->term->minute = begin_minute;
	}
}

void Lesson__laterTime(Lesson* lesson){//przesuwa zajęcia o jeden termin w przód, czy o 'duration'
	int begin_hour = (lesson->term->hour + lesson->term->duration/60 + (lesson->term->minute + lesson->term-> duration%60)/60)%24;
	int begin_minute = (lesson->term->minute + (lesson->term->duration)%60)%60;
	int end_minute = (lesson->term->minute + (2*lesson->term->duration)%60)%60;
	int end_hour = (lesson->term->hour + 2*lesson->term->duration/60 + (lesson->term->minute + 2*lesson->term-> duration%60)/60)%24;
	if(!lessons_rules(begin_hour, end_hour, end_minute, lesson->term->day))
		printf("\033[0;33m Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s %d:%d [%d]\"\n\033[0m",lesson->subject,Day__toString(lesson->term->day),begin_hour,begin_minute, lesson->term->duration);	
	else{
		//printf("Termin w przód\n");
		lesson->term->hour = begin_hour;
		lesson->term->minute = begin_minute;
	}
}

void Lesson_go(Lesson *lesson,int rozmiarTablicy,char** tablica){
	for(int i=0; i < rozmiarTablicy; i++){
		if (!strcmp(tablica[i],"d-")){
			Lesson__earlierDay(lesson);
		}
		if (!strcmp(tablica[i],"d+")){
			Lesson__laterDay(lesson);
		}
		if (!strcmp(tablica[i],"t-"))
                        Lesson__earlierTime(lesson);
		if (!strcmp(tablica[i],"t+"))
                        Lesson__laterTime(lesson);
	}
	//printf("Po uwzględnieniu przesunięć\n\t\"%s\"\n",Lesson__toString(lesson));

}

char* lesson(Lesson *lesson,char* tablica[],int n){
	//Lesson *pp = Lesson__create("Podstawy programowania",Term__create(12,50,90,3));
	//printf("Przed uwzględnieniem przesunięć\n");
        //printf("\t\"%s\"\n",Lesson__toString(pp));
	Lesson_go(lesson,n,tablica);
	return Lesson__toString(lesson);
	//Lesson__destroy(pp);
}
