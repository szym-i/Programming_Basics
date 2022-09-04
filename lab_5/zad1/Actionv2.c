#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Day.c"


enum Action{ DAY_EARLIER=1, DAY_LATER=2, TIME_EARLIER=3, TIME_LATER=4 };

typedef enum Action Action;

Action* parse(int rozmiarTablicy, char* tablica[]){
	Action* result=malloc(rozmiarTablicy * sizeof(Action));
	for(int i=0; i < rozmiarTablicy; i++){
		if(!strcmp(tablica[i],"d-"))
			result[i] = DAY_EARLIER;
		if(!strcmp(tablica[i],"d+"))
                        result[i] = DAY_LATER;
		if(!strcmp(tablica[i],"t-"))
                        result[i] = TIME_EARLIER;
		if(!strcmp(tablica[i],"t+"))
                        result[i] = TIME_LATER;
	}
	return result;
}


Day returnDay(char* string){
	Day day;
	if(!strcmp(string,"Mon"))
		day = MON;
	if(!strcmp(string,"Tue"))
		day = TUE;
	if(!strcmp(string,"Wed"))
		day = WED;
	if(!strcmp(string,"Thu"))
		day = THU;
	if(!strcmp(string,"Fri"))
		day = FRI;
	if(!strcmp(string,"Sat"))
		day = SAT;
	if(!strcmp(string,"Sun"))
		day = SUN;
	return day;
}

void go(Day day,int rozmiarTablicy,Action* tablica){
	for(int i=0; i < rozmiarTablicy; i++){
		if (tablica[i] == DAY_EARLIER){
			day = Day__prevDay(day);
			printf("Dzień w tył\n");
		}
		if ( tablica[i] == DAY_LATER){
			day = Day__nextDay(day);
			printf("Dzień w przód\n");
		}
		if (tablica[i] == TIME_EARLIER)
                        printf("Termin w tył\n");
		if (tablica[i] == TIME_LATER)
                        printf("Termin w przód\n");
	}
	printf("Wynik przesunięcia: \"%s\"\n", Day__toString(day));
	
}

int main(int argc, char* argv[]){
	if ( argc < 2 ){
		printf("Wprowadź więcej argumentów [dzień] [dowolna ilość operacji]\n");
		return 1;
	}
	char* string= argv[1];
	Day day = returnDay(string);
	int n = argc - 2;
	char** tablica = malloc(n * sizeof(char*));
	for(int i=0; i < n; i++){
		tablica[i] = malloc(3*sizeof(char));
		tablica[i] = argv[i+2];
	}
	go(day,n,parse(n,tablica));
}
