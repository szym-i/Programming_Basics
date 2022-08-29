#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int **arr, int m, int n){ //funkcja do printowania tablicy
    for(int i = 0; i < n; i++){
	printf("[");
        for(int j = 0; j < m; j++)
            printf(" %d", *(*(arr + i) + j));
        printf(" ]\n");
    }
}

void randomize(int **arr, int m,int n){ //funkcja do wypełniania tablicy randomowymi wartościami
	for(int i = 0; i < n; i++){
        	for(int j = 0; j < m; j++)
                        *(*(arr + i) +j) = lrand48() % 10;
        }
}

int main(void){
	int m,n;
	srand48(time(NULL));
	printf("Stwórz tablicę mxn:\n");
	printf("Podaj liczbę kolumn m=");
	scanf("%d",&m);
	printf("Podaj liczbę wierszy n=");
        scanf("%d",&n);
	int** arr = (int**)malloc(n * sizeof(int*));//zainicjowanie tablicy o rozmiarze n wierszów
    	for(int i = 0; i < n; i++) //zainicjowanie n wierszów o rozmiarze m
        	arr[i] = (int*)malloc(m * sizeof(int));
	randomize(arr,m,n);
	print(arr,m,n);
	for(int i = 0; i < n; i++) //zwolnienie pamięci każdego z n wierszów
        	free(arr[i]);
    	free(arr); //zwolnienie pamięci całej tablicy
	return 0;
}
