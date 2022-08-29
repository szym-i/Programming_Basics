#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void create_array(int t[], int n) // creating array with random integers [-10,10]
{
	for (int i=0; i < n; i++){
                int r = (lrand48() % 21)-10;
                t[i]=r;
        }

}

void print_array(int t[], int n) // printing array
{
	printf("[");
        for (int i=0; i<n; i++){
                printf(" %d",t[i]);
        }
        printf(" ]\n");
}

void stats(int arr[],int n) // calculate the percentage of occurrences of each number
{
	for(int i=-10; i < 11; i++){
		float counter=0;
		for(int j=0; j < n; j++){
			if ( i == arr[j]){
				counter++;
			}	
		}
		printf("Number %d appeared %0.f times (\033[0;31m%.2f%%\033[0m)\n", i ,counter, 100*counter/n);
	}
}

int main(void)
{
	srand48(time(NULL));
	int n;
	printf("Choose the size of array n=");
	scanf("%d",&n);
	int arr[n];
	create_array(arr,n);
	print_array(arr,n);
	printf("\033[0;35mResult of stats(arr,n):\033[0m\n");
	stats(arr,n);
}

