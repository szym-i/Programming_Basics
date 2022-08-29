#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** getData(int* line_count)
{
    // Allocate memory for array of pointers
    // -------------------------------------
    char** master_array = calloc(3, sizeof(char*));
    char* line = NULL;
    (*line_count) = 0;
    size_t size;

    for (;;)
    {
        int length = getline(&line, &size, stdin);

        // Exit on EOF
        // -----------
        if (length == -1)
        {
            break;
        }

        // If there are too many lines, reallocate mem
        // -------------------------------------------
        if (*line_count > 2)
        {
            // Reallocate memory SAFELY, checking for allocation failures
            // ----------------------------------------------------------
            char** new_master_array = realloc(master_array, (*line_count + 1) * sizeof(char*));

            if (new_master_array != NULL)
            {
                master_array = new_master_array
                               ;
            }
            else
            {
                free(master_array);
                free(new_master_array);
                return NULL;
            }
        }

        // Read until end of line
        // ----------------------
        if (line[length - 1] != '\n')
        {
            length++;
        }

        // Copy temp line to master array
        // ------------------------------
        line[length - 1] = 0;
        master_array[*line_count] = malloc(length * sizeof(char));
        memcpy(master_array[*line_count], line, length * sizeof(char));
        (*line_count)++;
    }

    return master_array;
}

char* getHexAscii(char znak){
	char* ch;
	ch = (char*) malloc(1*sizeof(char));
	snprintf(ch,3,"%X",znak); // %X to wartość HEX chara
	return ch;
}

char* compress(char* tekst){
	char* result;
	result = (char*) malloc((strlen(tekst)*sizeof(char)));//rezerwujemy długość tekstu, bo jest skompresowana wersja będzie nie dłuższa od niego
	int k=0;
	for(int i=0; i < strlen(tekst); i++){
		int licznik = 1;
		int ascii_num = tekst[i];	
		char c = tekst[i];
		if(( ascii_num != 41 ) && ( ascii_num != 40 ) && ( ascii_num != 37 )){//jeśli char nie jest (, % ani )
			result[k++]=c;
			for(int j = i + 1 ; j < strlen(tekst); j++){
                        	if(c == tekst[j]){
                                	licznik++;
                        	}
                        	if(c != tekst[j]){
                                	if(licznik > 4){
						result[k++] = '(';
						int zmienna=0;
						int h=1;
						while(h <= licznik){
				                	zmienna++;
                					h*=10;
        					}
        					snprintf(&result[k++],zmienna+2,"%d",licznik);
						k+=zmienna-1;
						result[k++] = ')';
                                        	i += licznik-1;
                                	}
                                	break;
                        	}
                	}
		}
		else{
			for(int j = i + 1 ; j < strlen(tekst); j++){
                        	if ( c == tekst[j]){
                                	licznik++;
                        	}
                        	if( c != tekst[j]){
					result[k++]='%';
					snprintf(&result[k++],3,"%X",c);
					k++;
					result[k++] = '(';
                                        int zmienna=0;
                                        int h=1;
                                        while(h <= licznik){
                                        	zmienna++;
                                                h*=10;
                                        }
                                        snprintf(&result[k++],zmienna+2,"%d",licznik);
                                        k+=zmienna-1;
                                        result[k++] = ')';
                        		i += licznik-1;
                                	break;
                        	}
                	}

		}
	}
	return result;	
}

char* decompress(char* tekst){
	char* result;
	result = (char*) malloc((150*sizeof(char)));
	int k=0;
	int zmienna;
	for(int i=0; i < strlen(tekst); i++){
		char c = tekst[i];
		if(( c != '%' ) && ( c != '(' ) && (c != ')'))
			result[k++]=tekst[i];
		if( c == '(' ){
			int rozmiar=0;
			for(int j=1; i + j < strlen(tekst);j++){
				if( tekst[i+j] != ')' ){
					rozmiar++;
				}
				else{
					break;
				}
			}
			int num=0; //liczba skompresowamnych znaków ASCII
			zmienna=1;
			while( rozmiar > 0){ //konwersja liczby znaków ze stringa do inta
				num += zmienna *(tekst[i+rozmiar] - '0' );
				rozmiar--;
				zmienna*=10;
			}
			int index=rozmiar;
			while (num > 1){
				result[k++]=tekst[i-1];
				num--;
			}
			i+=index+2;
		}
		if( c == '%'){
			if(tekst[i+2] == 8){ //  (
				c = '(';
			}
			if(tekst[i+2] == 5){ //  %
                        	c = '%';
                        }
                        if(tekst[i+2] == 9){ //  )
                        	c = ')';
                        }
			int rozmiar=0;
                        for(int j=1; i + j + 3< strlen(tekst);j++){
                                if( tekst[i+j+3] != ')' )
                                        rozmiar++;
                                else
                                        break;
			}
			int skip=rozmiar;
			int num=0; //liczba skompresowamnych znaków ASCII
                        zmienna=1;
                        while( rozmiar > 0){ //konwersja liczby znaków ze stringa do inta
                                num += zmienna * (tekst[i+3+rozmiar] - '0' );
                                rozmiar--;
                                zmienna*=10;
                        }
			while (num > 0){
		                if(tekst[i+2] == '8'){ //  (
                                	result[k++] = '(';
                        	}
                        	if(tekst[i+2] == '5'){ //  %
                                	result[k++] = '%';
                        	}
                        	if(tekst[i+2] == '9'){ //  )
                                	result[k++] = ')';
                        	}
                                num--;
                        }
                        i+=skip+4;			
	
		}

	}
	//printf("%s",result);
	return result;
}

int main(void){
	char* str;
        str = (char*) malloc(150*sizeof(char)); 
	/*char c;
	printf("Enter char:");
	scanf("%c",&c);
	char* d = getHexAscii(c);
	printf("%s",d);
	*/
	printf("Enter the string:\n");
	fgets(str,150,stdin);
	char* compressed = compress(str);
	printf("%s",compressed);
	compressed = decompress(compressed);
	printf("%s",compressed);
}
//int main(int argc, char* argv[]){
    // Default mode is 0 — compress
    // ----------------------------
    /*int mode = 0;

    // If provided argument is --decompress, set mode to decompression
    // ---------------------------------------------------------------
    if (argc > 1)
    {
        if (!strncmp(argv[1], "--decompress", 12))
        {
            mode = 1;
        }
    }

    // Compress/decompress up to len
    // -----------------------------
    int len;
    char** input = getData(&len);
    char* output;

    if (mode == 0)
    {
        output = compress(input, len);
    }
    else
    {
        output = decompress(input, len);
    }

    printf("\n\n%s", output);
    free(input);
    free(output);*/
    //printf("%s",compress("aaaaaaaa"));

//}
