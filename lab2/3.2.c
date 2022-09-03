#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int **arr, int m, int n) // print Matrix
{
    for(int i = 0; i < n; i++){
	printf("[");
        for(int j = 0; j < m; j++)
            printf(" %d", *(*(arr + i) + j));
        printf(" ]\n");
    }
}

void randomize(int **arr, int m,int n) // create Matrix with random integers [0,9]
{
	for(int i = 0; i < n; i++){
        	for(int j = 0; j < m; j++)
                        *(*(arr + i) +j) = lrand48() % 10;
        }
}

int main(void)
{
	int m,n;
	srand48(time(NULL));
	printf("Create Matrix (mxn) with random integers:\n");
	printf("Enter number of columns m=");
	scanf("%d",&m);
	printf("Enter number of rows n=");
        scanf("%d",&n);
	int** arr = (int**)malloc(n * sizeof(int*)); // zainicjowanie tablicy o rozmiarze n wierszów
    	for(int i = 0; i < n; i++) // zainicjowanie n wierszów o rozmiarze m
        	arr[i] = (int*)malloc(m * sizeof(int));
	randomize(arr,m,n);
	print(arr,m,n);
	for(int i = 0; i < n; i++) // free memory for each of n rows
        	free(arr[i]);
    	free(arr); // free memory
	return 0;
}
