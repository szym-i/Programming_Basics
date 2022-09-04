#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char** getData(int len)
{
	char** a = calloc(3, sizeof(char*));
	char *buffer = NULL;
	(len) = 0;
	
	int l; // int
	
	while (1){
		int r = getline(&buffer, &l, stdin);
		
		if (r == -1)
			break;
		
		if (len > 2) // realloc memory if more than 3 lines are entered
			a = realloc(a, (len + 1) * sizeof(char*));
		
		if (buffer[r - 1] != '\n')
			r++;
		buffer[r - 1] = 0;
		a[len] = malloc(r * sizeof(char));
		memcpy(a[len], buffer, r * sizeof(char));
		
		(len)++;
	}
	return a;
}
int main(void)
{
	char** a = getData(3);
	int i=0;
	do{
		if( a[i] == NULL){
			break;
		}
		else{
			printf("\n%c",a[i][1]);
                        i++;
		}
	}while(1);	
}
