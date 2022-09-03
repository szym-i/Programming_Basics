#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_line_len 200

char** getData(int* line_count)
{
    char** input = calloc(3, sizeof(char*)); // alokacja pamięci na tablicę wskaźników
    char* line = NULL; // by default
    (*line_count) = 0;
    size_t size;

    for (;;){ // aka while true
        int length = getline(&line, &size, stdin);
        if (length == -1){ // break at the end of input
            break;
        }
        if (*line_count > 2){ // if more than 3 lines, realloc mem
	    char** new_input = realloc(input, (*line_count + 1) * sizeof(char*)); // safe realloc

            if (new_input != NULL){
                input = new_input;
            }
            else{
                free(input);
                free(new_input);
                return NULL;
            }
        }
        if (line[length - 1] != '\n'){// wczytywanie do końca linii
            length++;
        }
        line[length - 1] = 0;
        input[*line_count] = malloc(length * sizeof(char));
        memcpy(input[*line_count], line, length * sizeof(char));
        (*line_count)++;
    }
    return input;
}

char* getHexAscii(char znak){
	char* result;
	result = (char*) malloc(1*sizeof(char));
	snprintf(result,3,"%X",znak); // %X to wartość HEX chara
	return result;
}                            

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
			 	if (tekst[i][j+2] == 8) //  "("
					c = '(';
				if (tekst[i][j+2] == 5) //  "%"
                        		c = '%';
                        	if (tekst[i][j+2] == 9) // ")"
                        		c = ')';
				int size=0;
                        	for (int h=1; j+h+3 < strlen(tekst[i]); h++){// zliczamy rząd wielkości liczby 
                                	if( tekst[i][j+h+3] != ')' )
                                        	size++;
                                	else
                                        	break;
				}
				int skip=size;// kopia rozmiaru liczby skompresowanych znaków, aby ją później dodać do j
				int licznik=0;// liczba skompresowamnych znaków ASCII
                        	int pozycja=1;// pozycja dziesiętna
                        	while (size > 0){ // zczytujemy i konwertujemy liczbę skompresowanych znaków do inta
                                	licznik += pozycja * (tekst[i][j+3+size] - '0');// mnożymy cyfrę razy jej miejsce dziesiętne, zaczynając od liczby jedności
                                	size--;
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
		result[k++]='\n'; // "\n" at the end of each line
	}
	result[k-1]='\0'; // null byte at the end
	return result;
}

int int2arr(char* arr, int l){
	int h = l;
	int len;
	for (len = 0; h != 0; len++)
		h /= 10;
	for (int i = len - 1; i >= 0; i--){
		arr[i] = (l % 10) + 48;
		l /= 10;
	}
	return len;
}

char* compress(char** a, int len){
	char* result;
	result = malloc(len * max_line_len * sizeof(char));
	int k = 0; // result index
	for (int i = 0; i < len; i++){
		int j = 0, licznik = 1;
		do{
			j++;
			if (a[i][j-1] == a[i][j]) {
				licznik++;
				continue;
			}

			char c = a[i][j - 1];
			if (licznik < 5 && !(c == '(' || c == '%' || c == ')'))// jeśli wystąpień znaku było mniej niż 5 oraz jest różny od '(' '%' ')', to wpisujemy go tyle razy ile wystąpił do result
				for (int h = 0; h < licznik; h++)
					result[k++] = c;
			else {
				if (c == '(' || c == '%' || c == ')'){ // jeśli jest jednym ze znaków '(' '%' ')', wpisujemy % i jego wartość HEX
					result[k++] = '%';
					snprintf(&result[k++],3,"%X",c);
					k++;
				}
				else // if any other character
					result[k++] = c;
				result[k++] = '(';
				k += int2arr(&result[k],licznik);// wpisujemy ilość wystąpień w result oraz zwiększamy indeks l o tyle ile miejsca zajmuje ilość wystąpień
				result[k++] = ')';
			}
			licznik = 1;
		}while (a[i][j] != 0);
		result[k++] = '\n';
	}
	result[k-1]='\0';
	return result;
}


int main(int argc, char* argv[]){
    int mode = 0; // default mode - compress
    if ((argc > 1) && (!strncmp(argv[1], "--decompress",12))) // if used with --decompress, changes mode
        mode = 1;
    int len;
    char** input = getData(&len); // get input and input len
    char* result;
    if (mode == 0){ // compress mode
        result = compress(input, len);
	printf("\nThe result of compression:\n");
    }
    else { // decompress mode
	printf("\nThe result of decompression:\n");
	result=decompress(input,len);
    }
    printf("%s\n",result);
    free(input);
    free(result);
    return 0;
}
