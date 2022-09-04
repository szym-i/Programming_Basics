#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate(char* filename, int len, int mode){
	printf("Wybrano funkcje generate\n");
}

void sort(char* filename){
	printf("Wybrano funkcje sort\n");
}

void list(char* filename,int len, int mode){
	printf("Wybrano funkcje list\n");
	FILE* fp;
	char ch;
	if (fp == NULL){
       		printf("file can't be opened \n");
		len=-1;
    	}
	fp = fopen(filename,"rb");
	int b;
	for (int i = 0; i < len; i++)
	{
		if (mode) {
			fread(&b, 1, 1, fp);
			printf("%c", (char)b);
		}
		else {
			fread(&b, sizeof(int), 1, fp);
  			//itoa(i,buffer,b);
 	 		//printf ("binary: %s\n",buffer);
			printf("%i\n", b);
		}
	}	
	fclose(fp);
    	printf("\n");
}


int main(int argc,char* argv[]){// nazwa pliku, liczba rekordów (N elementów) oraz typ pojedynczego elementu / rekordu
	srand(time(NULL));
	int mode;
	char* filename = argv[1];
	char* len_char = argv[2];
        char* type = argv[3];
	if (argc > 3){
        	char* len = argv[2];
        	char* type = argv[3];
		if ((strncmp(type, "int",3)) && (strncmp(type, "char",4))){
			printf("\nWprowadziłeś błędny typ danych\n");
			return 1;
		}
		if (!strncmp(type, "int",3))
			mode = 0;
		if (!strncmp(type, "char",4))
			mode = 1;
	}
	else{
		printf("\nWprowadziłeś za mało argumentów\n");
		return 1;
	}
	char op;// s/g/l
	printf("Wybierz operację (s/l/g) = ");
	scanf("%c",&op);// operacja
	printf("\nmode = %d\n",mode);
	int len = atoi(len_char);
	printf("len = %d\n",len); 
	if ( op != 's' && op != 'g' && op!= 'l'){
		printf("Wybrano niepoprawną operację (s/l/g)");
		return 1;
	}
	else{
		if (op == 's')// sort
			sort(filename);
		if (op == 'g')// generate
		       generate(filename,len,mode);
		if (op == 'l')// list
			list(filename,len,mode);	

	}
	return 0;
}
