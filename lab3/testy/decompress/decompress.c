#include <stdlib.h>
#include <string.h>
#define max_line_len 200

char* decompress(char** tekst, int len){// funkcja przyjmuje char ** oraz jego długość
	char* result;
	result = malloc(len * max_line_len * sizeof(char));
	int k=0;// indeks tablicy result
	for(int i=0; i < len; i++){// przechodzimy po wszystkich wczytanych liniach
		for(int j=0; j < strlen(tekst[i]); j++){// przechodzimy po charach z danej linijki
			char c = tekst[i][j];
			if (( c != '(') && ( c != '%' ) && (c != ')'))// jeśli to zwykły znak po prostu 'przepisujemy' go
				result[k++]=c;
			if (c == '('){
				int rozmiar=0;
				for(int h=1; j+h < strlen(tekst[i]); h++){
					if (tekst[i][j+h] != ')'){
						rozmiar++;
					}
					else{
						break;
					}
				}
				int licznik=0;// liczba skompresowamnych znaków ASCII
				int pozycja=1;
				while (rozmiar > 0){// konwersja liczby znaków ze stringa do inta
					licznik += pozycja * (tekst[i][j+rozmiar] - '0');
					rozmiar--;
					pozycja*=10;
				}
				int skip=rozmiar;
				while (licznik > 1){
					result[k++]= tekst[i][j-1];
					licznik--;
				}
				j+= skip+2;
			}
			if (c == '%'){
			 	if (tekst[i][j+2] == 8) //  (
					c = '(';
				if (tekst[i][j+2] == 5) //  %
                        		c = '%';
                        	if (tekst[i][j+2] == 9) // )
                        		c = ')';
				int rozmiar=0;
                        	for (int h=1; j+h+3 < strlen(tekst[i]); h++){// zliczamy rząd wielkości liczby 
                                	if( tekst[i][j+h+3] != ')' )
                                        	rozmiar++;
                                	else
                                        	break;
				}
				int skip=rozmiar;// kopia rozmiaru liczby skompresowanych znaków, aby ją później dodać do j
				int licznik=0;// liczba skompresowamnych znaków ASCII
                        	int pozycja=1;// pozycja dziesiętna
                        	while (rozmiar > 0){ // zczytujemy i konwertujemy liczbę skompresowanych znaków do inta
                                	licznik += pozycja * (tekst[i][j+3+rozmiar] - '0');// mnożymy cyfrę razy jej miejsce dziesiętne, zaczynając od liczby jedności
                                	rozmiar--;
                                	pozycja*=10;
                        	}
				while (licznik > 0){// wpisujemy tyle znaków specjalnych ile było podane
		                	if (tekst[i][j+2] == '8') //  (
                                		result[k++] = '(';
                        		if (tekst[i][j+2] == '5') //  %
                                		result[k++] = '%';
                        		if (tekst[i][j+2] == '9') //  )
                                		result[k++] = ')';
                                	licznik--;
                        	}
                        	j+=skip+4; // skip + 4 ( pozostałe 4 znaki do XX( ) ) 
			}			
	
		}
		result[k++]='\n';// na końcu każdej linii wpisujemy \n
	}
	result[k-1]='\0';// na ostatnim miejscu wpisujemy null byte
	return result;
}
