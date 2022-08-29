#include <stdio.h>
#include <string.h>

char* getEncryptedLine(char* string){ //funkcja będzie przyjmować 'stringa' oraz zwracać jego zmodyfikowaną (zaszyfrowaną) wersję
	int s=0; //przesunięcie
	for (int i=0; i < strlen(string); i++){ //mierzymy długość pierwszego wyrazu (przesunięcie)
		if ((string[i] != ' ') && (string[i] != '\n'))
			s++;
		else {
			if (s > 0)
				break;
		}
	}
	for (int i = 0; i < strlen(string); i++){// przechodzimy po wszystkich charach
		int d = string[i]; // wartość chara w systemie dziesiętnym ASCII, można używać też string[i] i działa, ale tak jest czytelniej
		int x = string[i] + s % 26;// char przesunięty o s, modulo 26 aby dla przesunięcia powyżej 25 działało 
		if ((d > 64) && (d < 91)){ // dla dużych liter (65-90)
			x = ((x - 65) % 26) + 65; // gdy x > 90 - przesunięcia są obliczane na zasadzie modulo, w przeciwnym wypadku nie to nic się nie zmieni  
			string[i]=x;	
		}
		if ((d > 96) && (d < 123)){ // dla małych liter (97 -122)
			x = ((x - 97) % 26 ) + 97; // analogicznie jak powyżej
			string[i]=x;
		}
	}
	return string;	
}
