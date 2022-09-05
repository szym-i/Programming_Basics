#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum Day { MON=1, TUE, WED, THU, FRI, SAT, SUN};

typedef enum Day Day;// niezbędne aby używać typu danych Day

char* Day__toString(Day day){// zwracającą pełne nazwy dni tygodnia, tj. dla MON zwraca "Poniedziałek", itd.
	switch (day){
		case 1:
			return "Poniedziałek";
		case 2:
			return "Wtorek";
		case 3:
                        return "Środa";
		case 4:
                        return "Czwartek";
                case 5:
                        return "Piątek";
                case 6:
                        return "Sobota";
                case 7:
                        return "Niedziela";
	}	
}

Day Day__nextDay(Day day){// która dla SAT zwraca SUN, dla SUN zwraca MON, itd.
	return day%7+1;
}

Day Day__prevDay(Day day){// która dla MON zwraca SUN, dla SUN zwraca SAT, itd.
	return (day + 5 )%7 + 1;
}
