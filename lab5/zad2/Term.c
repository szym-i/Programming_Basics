#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Term{ 
	int hour;
	int minute;
	int duration;// w minutach
};

typedef struct Term Term;

void Term__init(Term* term, int hour, int minute, int duration){// przypisuje polom struktury podane wartości (bez alokacji pamięci)
	term->duration = duration;
	term->hour = hour;
	term->minute = minute;
}

Term* Term__create(int hour, int minute, int duration){// przydziela pamięć dla "obiektu" Term oraz inicjalizuje go (korzystając z Term__init())
	Term *term= malloc(sizeof(struct Term));
	Term__init(term, hour, minute, duration);
}

void Term__destroy(Term* term){// zwalnia pamięć dla podanego (istniejącego) "obiektu"
	free(term);
}

char* Term__toString(Term* term){// zwraca napis postaci "godzina:minuta [czas trwania]"
	char* result = malloc(12*sizeof(char));
	if( term->minute < 10)
		snprintf(result,12,"%d:0%d [%d]",term->hour,term->minute,term->duration);
	else
		snprintf(result,12,"%d:%d [%d]",term->hour,term->minute,term->duration);
	return result;
}

bool Term__earlierThan(Term* term1, Term *term2){//zwraca wartość true, jeżeli term1 jest wcześniejszy niż term2
	int end_hour = (term1->hour + term1->duration/60 + (term1->minute + term1-> duration%60)/60)%24;
	int end_minute = (term1->minute + term1-> duration%60)%60;
	if(( end_hour < term2->hour) || (end_hour == term2->hour && end_minute < term2->minute)){
		return true;
	}
	else
		return false;
}

bool Term__laterThan(Term* term1, Term *term2){// zwraca wartość true, jeżeli term1 jest późniejszy niż term2	
	int end_hour = (term2 -> hour + term2 -> duration/60 + (term2 -> minute + term2 -> duration%60)/60)%24;
        int end_minute = (term2 -> minute + term2 -> duration%60)%60;
        if(( end_hour < term1->hour) || (end_hour == term1->hour && end_minute < term1->minute)){
		return true;
	}
	else
		return false;
}

bool Term__equals(Term* term1, Term *term2){// zwraca wartość true, jeżeli godzina i minuta rozpoczęcia oraz czas trwania są jednakowe
	char *string1 = Term__toString(term1);
	char *string2 = Term__toString(term2); 
	if(!strcmp(string1,string2))
		return true;// 1
	else
		return false;// 0	
}

Term* Term__endTerm(Term* term1, Term *term2){// tworzy termin, którego godzina oraz minuta rozpoczęcia jest taka sama jak term1, natomiast czas trwania to różnica pomiędzy godziną i minutą rozpoczęcia term2, a term1
	int duration = (term2->hour - term1->hour)*60 - term1->minute + term2->minute;
	Term *end_term = Term__create(term1->hour, term1->minute, duration);
	return end_term;
}
