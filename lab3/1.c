#include <stdio.h>
#include <string.h>

char* getEncryptedLine(char* string) // Caesar Cipher, where shift/key = len of first word in input
{
	int s=0;
	for(int i=0; i < strlen(string); i++){
		if((string[i] != ' ') && (string[i] != '\0') && (string[i] != '\n')){
			s++;
		}
		else{
			if ( s > 0)
				break;
		}
	}
	char c;
	int x;
	int d;
	for(int i = 0; i < strlen(string); i++){
		if((string[i] != ' ') && (string[i] != '\0') && (string[i] != '\n')){
			d = string[i];
			c = string[i];
			x = c + s % 26;// % 26 in case shift is over 25
			if (( d > 64 ) && ( d < 91)){  // for upper case letters
				if ( x > 90)
					x = x - 26;
				string[i]=x;	
			}
			if (( d > 96) && ( d < 123)){ // for lower case letters
				if ( x > 122)
					x = x - 26;
				string[i]=x;
			}
		}	
	}
	return string;	
}

void* main(void)
{
	char string[100];
	do{
		if (fgets(string, sizeof(string), stdin) != NULL ){
                	char* result = getEncryptedLine(string);
			printf("%s",result);
		}
		else
			return NULL;
	}while(1);

}
