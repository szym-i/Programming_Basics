#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void list(int n, int type, char* filename){
	FILE *fp = fopen(filename, "rb"); // use "rb" if you're opening non-text files,
	int c;
	int i=0;
	if (type == 1){// dla char
		while(fread(&c, 1, 1, fp) && (i++ < n))// n elementów, lub max liczbę elementów (aby nie wypisywać ostatniego wyrazu niepotrzebnie dużo razy)
			printf("%c",c);
	}
	else{// dla int
		while(fread(&c, sizeof(int), 1, fp) && (i++ < n))
			printf("%i\n", c);
	}
	fclose(fp);
}

void generate(int n, int type, char* filename) {
	FILE *fp = fopen(filename, "wb");
	int c;
	for (int i = 0; i < n; i++){
		if (type == 1){// dla char
			c = ((rand() - 33) % 94) + 33;
			fwrite(&c, 1, 1, fp);
		}
		else{// dla int
			c = rand();
			fwrite(&c, sizeof(int), 1, fp);
		}
	}	
	fclose(fp);
}

int get(FILE *fp, int index, int n){
	int c;
	fseek(fp, n * index, SEEK_SET);// SEEK_SET – It moves file pointer position to the beginning of the file.
	fread(&c, n, 1, fp);
	return c;
}

void set(FILE *fp, int index, int n, int value){
	fseek(fp, n * index, SEEK_SET);
	fwrite(&value, n, 1, fp);
}

void sort(int n, int type, char* filename){
	FILE* fp = fopen(filename, "rb+");// In r+ mode you can seek, read, and write.
	int s = type ? 1 : sizeof(int);// If Condition is true ? then value X : otherwise value Y
	for (int i = 0; i < n; i++){// przejście po wszystkich znakach/wartościach
		int min = get(fp,i,s);
		int iv = min;
		int imin = i;
		for (int j = i + 1; j < n; j++){
			int a = get(fp,j,s);
			if (a >= min)
				continue;
			min = a;
			imin = j;
		}
		if (imin == i)
			continue;
		set(fp,i,s,min);
		set(fp,imin,s,iv);
	}
	fclose(fp);
}

int main(int argc, char** argv){
	srand(time(NULL));
	if (argc != 5){// program przyjmie dokładnie 4 argumenty
		printf("[plik] [liczba elementów] [char(c)/int(i)] [generate(g)/list(l)/sort(s)]\n");
		return 1;
	}
	int tryb;
	switch (argv[3][0]){// działa zarówno dla dłuższych i krótszych wersji
		case 'i':
			tryb = 0;
			break;
		
		case 'c':
			tryb = 1;
			break;
			
		default:
			printf("Źle wybrałeś typ danych.\n");
			return 1;
	}
	int n = atoi(argv[2]);// konwersja z char* do inta
	switch (argv[4][0]){// tak samo jak powyżej
		case 'g':
			generate(n, tryb, argv[1]);
			break;
		
		case 'l':
			list(n, tryb, argv[1]);
			break;
			
		case 's':
			sort(n, tryb, argv[1]);
			break;
			
		default:
			printf("Wybrałeś nieobsługiwaną operację operacja.\n");
			return 1;
	}
	return 0;
}
