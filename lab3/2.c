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

char* getHexAscii(char c)
{
	char* hex;
	hex = (char*) malloc(1*sizeof(char));
	snprintf(hex,3,"%X",c); // %X for HEX char value
	return hex;
}

char* compress(char* text) // compress "(", "%", ")" with ASCII values, and compress more than 4 same characters ( aaaaa = a(5) ) 
{
	char* result;
	result = (char*) malloc((strlen(text)*sizeof(char)));
	int k=0;
	for(int i=0; i < strlen(text); i++){
		int ctr = 1;
		int ascii_num = text[i];	
		char c = text[i];
		if(( ascii_num != 41 ) && ( ascii_num != 40 ) && ( ascii_num != 37 )){ // if char is not "(","%" and ")"
			result[k++]=c;
			for(int j = i + 1 ; j < strlen(text); j++){
                        	if(c == text[j]){
                                	ctr++;
                        	}
                        	if(c != text[j]){
                                	if(ctr > 4){
						result[k++] = '(';
						int zmienna=0;
						int h=1;
						while(h <= ctr){
				                	zmienna++;
                					h*=10;
        					}
        					snprintf(&result[k++],zmienna+2,"%d",ctr);
						k+=zmienna-1;
						result[k++] = ')';
                                        	i += ctr-1;
                                	}
                                	break;
                        	}
                	}
		}
		else{
			for(int j = i + 1 ; j < strlen(text); j++){
                        	if ( c == text[j]){
                                	ctr++;
                        	}
                        	if( c != text[j]){
					result[k++]='%';
					snprintf(&result[k++],3,"%X",c);
					k++;
					result[k++] = '(';
                                        int zmienna=0;
                                        int h=1;
                                        while(h <= ctr){
                                        	zmienna++;
                                                h*=10;
                                        }
                                        snprintf(&result[k++],zmienna+2,"%d",ctr);
                                        k+=zmienna-1;
                                        result[k++] = ')';
                        		i += ctr-1;
                                	break;
                        	}
                	}

		}
	}
	return result;	
}

char* decompress(char* text) // just decompress text
{
	char* result;
	result = (char*) malloc((150*sizeof(char)));
	int k=0;
	int zmienna;
	for(int i=0; i < strlen(text); i++){
		char c = text[i];
		if(( c != '%' ) && ( c != '(' ) && (c != ')'))
			result[k++]=text[i];
		if( c == '(' ){
			int rozmiar=0;
			for(int j=1; i + j < strlen(text);j++){
				if( text[i+j] != ')' ){
					rozmiar++;
				}
				else{
					break;
				}
			}
			int num=0; // number of compressed ASCII characters
			zmienna=1;
			while( rozmiar > 0){ //konwersja liczby znaków ze stringa do inta
				num += zmienna *(text[i+rozmiar] - '0' );
				rozmiar--;
				zmienna*=10;
			}
			int index=rozmiar;
			while (num > 1){
				result[k++]=text[i-1];
				num--;
			}
			i+=index+2;
		}
		if( c == '%'){
			if(text[i+2] == 8){ // "("
				c = '(';
			}
			if(text[i+2] == 5){ //  "%"
                        	c = '%';
                        }
                        if(text[i+2] == 9){ //  ")"
                        	c = ')';
                        }
			int rozmiar=0;
                        for(int j=1; i + j + 3< strlen(text);j++){
                                if( text[i+j+3] != ')' )
                                        rozmiar++;
                                else
                                        break;
			}
			int skip=rozmiar;
			int num=0; // number of compressed ASCII characters
                        zmienna=1;
                        while( rozmiar > 0){ // konwersja liczby znaków ze stringa do inta
                                num += zmienna * (text[i+3+rozmiar] - '0' );
                                rozmiar--;
                                zmienna*=10;
                        }
			while (num > 0){
		                if(text[i+2] == '8'){ //  (
                                	result[k++] = '(';
                        	}
                        	if(text[i+2] == '5'){ //  %
                                	result[k++] = '%';
                        	}
                        	if(text[i+2] == '9'){ //  )
                                	result[k++] = ')';
                        	}
                                num--;
                        }
                        i+=skip+4;			
	
		}

	}
	return result;
}

int main(void)
{
	char* str;
        str = (char*) malloc(150*sizeof(char)); 
	/*char c;
	printf("Enter char:");
	scanf("%c",&c);
	char* d = getHexAscii(c);
	printf("%s\n",d);*/
	printf("\033[7;36mEnter the string:\033[0m\n");
	fgets(str,150,stdin);
	char* compressed = compress(str);
	printf("\033[2;32mResult of compress(string):\033[0m\n%s",compressed);
	compressed = decompress(compressed);
	printf("\033[2;33mResult of decompress(compressed_string):\033[0m\n%s",compressed);
}
