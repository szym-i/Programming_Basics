#include <stdlib.h>
#include <string.h>
#define max_line_len 200

int int2arr(char* a, int l){
	int h = l;
	int len;
	for ( len = 0; h != 0; len++)
		h /= 10;
	for (int i = len - 1; i >= 0; i--){
		a[i] = (l % 10) + '0';
		l /= 10;
	}
	return len;// ilośc cyfr inta o którą mamy zwiększyć indeks result
}
char* compress(char** a, int len){ // funkcja przyjmuje char** oraz jego długość (ilość wierszów)
	char* result;
	result = malloc(len * max_line_len * sizeof(char));
	int k = 0;// indeks result
	for (int i = 0; i < len; i++){// przejście po wszystkich wierszach
		int j = 0, licznik = 1;
		do{
			j++;
			if (a[i][j-1] == a[i][j]) {
				licznik++;
				continue;
			}
			char c = a[i][j - 1];
			if (licznik < 5 && !(c == '(' || c == '%' || c == ')'))//jeśli wystąpień znaku było mniej niż 5 oraz jest różny od '(' '%' ')', to wpisujemy go tyle razy ile wystąpił do result
				for (int h = 0; h < licznik; h++)
					result[k++] = c;
			else{
				if (c == '(' || c == '%' || c == ')'){ // jeśli jest jednym ze znaków '(' '%' ')', wpisujemy % i jego wartość HEX
					result[k++] = '%';
					snprintf(&result[k++],3,"%X",c);
					k++;
				}
				else //jeśli jest 'zwyczajnym znakiem' po prostu go wpisujemy
					result[k++] = c;
				result[k++] = '(';
				k += int2arr(&result[k],licznik); //wpisujemy ilość wystąpień w result oraz zwiększamy indeks l o tyle ile miejsca zajmuje ilość wystąpień
				result[k++] = ')';
			}
			licznik = 1;
		}while(a[i][j] != 0);
		result[k++] = '\n';//ostatni znak każdej linii
	}
	result[k-1]='\0';// ostatni znak - nullbyte
	return result;
}  
