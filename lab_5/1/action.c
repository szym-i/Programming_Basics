#include <stdio.h>
#include <stdlib.h>
#include <string.h>


enum Day { Mon=1, Tue, Wed, Thu, Fri, Sat, Sun};

typedef enum Day Day; // data typ Day


Day Day__nextDay(Day day)
{
        return day%7+1;
}

Day Day__prevDay(Day day)
{
	return (day + 5 )%7 + 1;
}


enum Action{ DAY_EARLIER=1, DAY_LATER=2, TIME_EARLIER=3, TIME_LATER=4 };

typedef enum Action Action;

Action* parse(int rozmiarTablicy, char* tablica[])
{
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

char* Day__toString(Day day)
{
        switch (day){
                case 1:
                        return "Monday";
                case 2:
                        return "Tuesday";
                case 3:
                        return "Wednesday";
                case 4:
                        return "Thursday";
                case 5:
                        return "Friday";
                case 6:
                        return "Saturday";
                case 7:
                        return "Sunday";
        }
}

Day returnDay(char* string)
{
	Day day;
	if(!strcmp(string,"Mon"))
		day = Mon;
	if(!strcmp(string,"Tue"))
		day = Tue;
	if(!strcmp(string,"Wed"))
		day = Wed;
	if(!strcmp(string,"Thu"))
		day = Thu;
	if(!strcmp(string,"Fri"))
		day = Fri;
	if(!strcmp(string,"Sat"))
		day = Sat;
	if(!strcmp(string,"Sun"))
		day = Sun;
	return day;
}

char* go(Day day,int size,Action* array)
{
	for(int i=0; i < size; i++){
		if (array[i] == DAY_EARLIER){
			day = Day__prevDay(day);
		}
		if ( array[i] == DAY_LATER){
			day = Day__nextDay(day);
		}

	}
	return Day__toString(day);
}

char* action(int len,char* arguments[])
{
	char* string = arguments[0];
	Day day = returnDay(string);
	int n = len - 1;
	char** array = malloc(n * sizeof(char*));
	for(int i=0; i < n; i++){
		array[i] = malloc(3 * sizeof(char));
		array[i] = arguments[i+1];
	}
	return go(day,n,parse(n,array));
}
