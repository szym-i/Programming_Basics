#include <stdio.h>
#include <stdlib.h>

int get_rows(char* filename){
	FILE* fp;
	int n=1;
	char c;
	fp = fopen(filename,"r");
	while(!feof(fp)){
                fread(&c,1,1,fp);
		if ( c == '\n' )
			n++;
		if ( c == '\0' )
			break;
	}
	fclose(fp);
	return n;
}

int get_columns(char* filename){
	FILE* fp;
        int j = 0;
        char c;
        fp = fopen(filename, "r");
        while(!feof(fp)){
                fread(&c,1,1,fp);
		//printf("%d ",c);
                if ( c == '\n' || c == '\0' )
                        break;
		if ( c == ' ' )
                        j++;
        }
	fclose(fp);
        return j;
}

char* file2char(char* filename){
        char* result = malloc(200*sizeof(char));
        FILE* fp;
        char c;
        int k=0;
        fp = fopen(filename,"r");
        while(!feof(fp) && c != '\0'){
                fread(&c,1,1,fp);
                result[k++]=c;
        }
	result[k++]='\0';
	return result;
}

int get(char* filename, int row, int column){
	int actual_row=1;
	int actual_column=1;
	int licznik=0;
	char c;
	char* value_str=malloc(10*sizeof(char));
	FILE* fp2;
	fp2 = fopen(filename,"r");
        while(!feof(fp2)){
                fread(&c,1,1,fp2);
                if ( c == '\n'){
			if( actual_column == column && actual_row == row){
				int value = atoi(value_str);
                                return value; //printf("%d ",value);
			}
                        actual_row++;
                        actual_column=1;
                        continue;
                }
                if (c > 47 && c < 58)
                        value_str[licznik++]=c;
                if( c == ' ' ){
               	        int value = atoi(value_str);
                        for(int i=0; i < licznik; i++)//free(value_str);
                                value_str[i]=0;
                        licznik=0;
			if( actual_column == column && actual_row == row)
                        	return value; //printf("%d ",value);
			actual_column++;
                }
        }
        fclose(fp2);

}

int macierz(char* macierz1,char* macierz2, char* macierz3){// nazwa pliku, liczba rekordów (N elementów) oraz typ pojedynczego elementu / rekordu
	int n = get_rows(macierz1);
        int j=get_columns(macierz1);
        int k=get_columns(macierz2);
	int v=0;
	FILE* fp3 = fopen(macierz3,"w");
	char* str=malloc(10*sizeof(char));
	for( int i=0; i < n; i++){
		for ( int p=0; p < k ; p++){
			v=0;
	       		for(int u=0; u < j; u++){
				v += get(macierz1,i+1,u+1) * get(macierz2,u+1,p+1);
			}
			snprintf(str,7,"%d ",v);
			fputs(str,fp3);
	       	}
		if( i + 1 !=  n)
			putc('\n',fp3);
	}
	putc('\0',fp3);
	fclose(fp3);
        return 0;
}
