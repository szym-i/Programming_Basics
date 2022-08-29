#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int *arr, int n) {
    for (int i = 0; i < n; i++){
	printf("[");
        for (int j = 0; j < n; j++)
            printf(" %d", *(arr + i * n + j));
        printf(" ]\n");
    }
}

void read(int *arr, int size){
    for (int i = 0; i < size; i++)
        scanf("%d", arr + i);
}

void check(int *arr, int n){
    int licznik=0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (*(arr + n * i + j) != 0) {
                licznik++;
		break;
            }
    if ( licznik == 0 )
	    printf("\033[0;34mMacierz jest trójkątna dolna.\033[0m\n");
    else
	printf("\033[0;31mMacierz nie jest trójkątna dolna.\033[0m\n");
}

int main(void) {
    int n;
    printf("Podaj wymiary tablicy nxn, n=");
    scanf("%d", &n);
    int size = n * n;
    int *arr = malloc(size * sizeof(int));
    printf("Wprowadź elementy tablicy:\n");
    read(arr,size);
    printf("Wprowadzona tablica:\n");
    print(arr,n);
    check(arr,n);
    free(arr);
    return 0;
}
