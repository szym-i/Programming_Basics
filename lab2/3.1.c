#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print(int *arr, int n) // print Matrix
{
    for (int i = 0; i < n; i++){
	printf("[");
        for (int j = 0; j < n; j++)
            printf(" %d", *(arr + i * n + j));
        printf(" ]\n");
    }
}

void read(int *arr, int size) // enter your Matrix (nxn)
{
     	for (int i = 0; i < size; i++)
        scanf("%d", arr + i);
}

void check(int *arr, int n) // check if Matrix is Lower Triangular
{
    int ctr=0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (*(arr + n * i + j) != 0) {
                ctr++;
		break;
            }
    if ( ctr == 0 )
	    printf("\033[0;34mLower Triangular Matrix.\033[0m\n");
    else
	printf("\033[0;31mNot Lower Triangular Matrix.\033[0m\n");
}

int main(void)
{
    int n;
    printf("Enter size of your Square Matrix nxn, n=");
    scanf("%d", &n);
    int size = n * n;
    int *arr = malloc(size * sizeof(int));
    printf("Enter Matrix elements:\n");
    read(arr,size);
    printf("Your Matrix:\n");
    print(arr,n);
    check(arr,n);
    free(arr);
    return 0;
}
