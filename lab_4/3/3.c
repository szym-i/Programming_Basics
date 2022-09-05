#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>

void copyFile(char* old_file ,char* new_file){
    FILE *ptr_old=fopen(old_file,"rb"), *ptr_new = fopen(new_file,"wb");
    if(ptr_old == NULL){
        return;
    }
    if(ptr_new == NULL){
        fclose(ptr_old);
        return;
    }
    flock(fileno(ptr_old),LOCK_EX);
    flock(fileno(ptr_new),LOCK_EX);
    int a;
        while(1){
        	a = fgetc(ptr_old);
        if(!feof(ptr_old))
            fputc(a,ptr_new);
        else
            break;
        }
    fclose(ptr_new);
    fclose(ptr_old);
    flock(fileno(ptr_old),LOCK_UN);
    flock(fileno(ptr_new),LOCK_UN);
}

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

int mnozenie(char* macierz1, char* macierz2, char* macierz3, int mode){
	/*int n = get_rows(macierz1);
	int j = get_columns(macierz1);
	int k = get_columns(macierz2);
	int v = 0;*/
	
	copyFile(macierz3,"tmp.txt");
	FILE* tmp = fopen("tmp.txt","r");
	flock(fileno(tmp),LOCK_EX);
	FILE* fp3 = fopen(macierz3,"w");
	flock(fileno(fp3),LOCK_EX);
	
	int n = get_rows(macierz1);
        int j = get_columns(macierz1);
        int k = get_columns(macierz2);
        int v = 0;


	char* str = malloc(12*sizeof(char));
	char* number = malloc(20* sizeof(char));
	int beg;
	int end;

	if ( mode ==1 ){
		beg = 0;
		end= k/2;
	}
	if ( mode == 2){
		beg = k/2;
		end=k;
	}
	for(int i=0; i < n; i++){
		for ( int p=0; p < k ; p++){
			v=0;
			if ( beg <= p && p < end){
	       			for(int u=0; u < j; u++){
					v += get(macierz1,i+1,u+1) * get(macierz2,u+1,p+1);
				}
				snprintf(str,7,"%d ",v);
				fputs(str,fp3);
				fscanf(tmp,"%s",number);
			}
			else{
                		fscanf(tmp,"%s",number);
                		if(feof(tmp))
                    			strcpy(number,":");
                		if(!strcmp(number,":")){
                    			fprintf(fp3,": ");
                		}
                		else{
                    			fprintf(fp3,"%s ",number);
                		}

            		}	
	       	}
		putc('\n',fp3);
	}
	fclose(fp3);
        fclose(tmp);
	flock(fileno(tmp),LOCK_UN);
	flock(fileno(fp3),LOCK_UN);
	//remove("tmp.txt");
}


void read_list(char* filename, int mode){
        FILE* lista = fopen(filename,"r");
        char* A = (char*) malloc(sizeof(char)*50);
        char* B = (char*) malloc(sizeof(char)*50);
        char* C = (char*) malloc(sizeof(char)*50);
        while(!feof(lista)){
            fscanf(lista,"%s %s %s\n",A,B,C);
            mnozenie(A,B,C,mode);
        }
}	

int main(int argc,char* argv[]){
	if ( argc != 3){
		printf("Wprowadź poprawną liczbę argumentów [lista] [1/2]");
		return 1;
	}
	int mode = atoi(argv[2]);
	if ( mode != 1 && mode != 2){
		printf("Wybrano nieobsługiwaną operację");
		return 1;
	}
	read_list(argv[1],mode);
}
