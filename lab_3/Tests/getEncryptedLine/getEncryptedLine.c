#include <stdio.h>
#include <string.h>

char* getEncryptedLine(char* string) // return Caesar Ciphered string
{
	int s=0; // shift
	for (int i=0; i < strlen(string); i++){ // measure the shift
		if ((string[i] != ' ') && (string[i] != '\n'))
			s++;
		else {
			if (s > 0)
				break;
		}
	}
	for (int i = 0; i < strlen(string); i++){
		int d = string[i]; // wartość chara w systemie dziesiętnym ASCII, można używać też string[i] i działa, ale tak jest czytelniej
		int x = string[i] + s % 26;// char shifted by s, % 26 for shift > 25 
		if ((d > 64) && (d < 91)){ // for upper case letters ASCII[65-90]
			x = ((x - 65) % 26) + 65; // special formula, if x > 90 it will be modulo encrypted  
			string[i]=x;	
		}
		if ((d > 96) && (d < 123)){ // for lower case letter ASCII[97 -122]
			x = ((x - 97) % 26 ) + 97;
			string[i]=x;
		}
	}
	return string;	
}
