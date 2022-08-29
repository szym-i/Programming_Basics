#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_rows(char* filename){
	FILE* fp;
	int n=1;
	char c;
	fp = fopen(filename,"r");
	while(!feof(fp)){
                fread(&c,1,1,fp);
		if ( c == '\n' )
			n++;
		if ( c == '\0')
			break;
	}
	fclose(fp);
	return n;
}

int get_columns(char* filename){
	FILE* fp;
        int j=0;
        char c;
        fp = fopen(filename,"r");
        while(!feof(fp)){
                fread(&c,1,1,fp);
                if ( c == '\n' || c == '\0' )
                        break;
		if ( c == ' ')
                        j++;
        }
	fclose(fp);
        return j;

}

int get(char* filename, int row, int column){
	int actual_row=1;
	int actual_column=1;
	int licznik=0;
	char b;
	char* value_str=malloc(10*sizeof(char));
	FILE* fp;
	fp = fopen(filename,"r");
        while(!feof(fp)){
                fread(&b,1,1,fp);
                if ( b == '\n'){
			if( actual_column == column && actual_row == row){
				int value = atoi(value_str);
                                return value; //printf("%d ",value);
			}
                        actual_row++;
                        actual_column=1;
                        continue;
                }
                if (b > 47 && b < 58)
                        value_str[licznik++]=b;
                if( b == ' '){
               	        int value = atoi(value_str);
                        for(int i=0; i < licznik; i++)//free(value_str);
                                value_str[i]=0;
                        licznik=0;
			if( actual_column == column && actual_row == row)
                        	return value; //printf("%d ",value);
			actual_column++;
                }
        }
        fclose(fp);
}

int main(int argc,char* argv[]){
        if (argc != 4){// program przyjmuje dokładnie 3 argumenty
		printf("Wprowadź dokładnie 3 argumenty (MacierzA, MacierzB, MacierzC)\n");
		return 1;
	}
	char* macierz1 = argv[1];
        char* macierz2 = argv[2];
        char* macierz3 = argv[3];
	int n = get_rows(macierz1);
	int j = get_columns(macierz1);
	int k = get_columns(macierz2);
	printf("Wczytałem macierze o wymiarach: %d %d %d",n,k,j);
	int v = 0;
	FILE* fp3 = fopen(macierz3,"w+");
	char* str = malloc(12*sizeof(char));

	for(int i=0; i < n; i++){
		for ( int p=0; p < k ; p++){
			v=0;
	       		for(int u=0; u < j; u++){
				//printf("+%d*%d",get(macierz1,i+1,u+1), get(macierz2,u+1,p+1));
				v += get(macierz1,i+1,u+1) * get(macierz2,u+1,p+1);
			}
			snprintf(str,7,"%d ",v);
			fputs(str,fp3);
	       	}
		putc('\n',fp3);
	}
	fclose(fp3);
        return 0;
}
