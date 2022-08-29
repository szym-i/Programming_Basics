#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

void create_array(int t[], int n){ //funkcja do towrzenia tablicy z losowymi liczbami z przedzialu [-10,10]
	for (int i=0; i < n; i++){
                int r = (lrand48() % 21)-10;
                t[i]=r;
        }

}

void print_array(int t[], int n){ //funkcja do printowania tablicy
        printf("[");
        for (int i=0; i<n; i++){
                printf(" %d",t[i]);
        }
        printf(" ]\n");
}

void stats(int arr[],int n){ // funkcja do obliczenia statystyki wystąpień każdej z liczb
	for(int i=-10; i < 11; i++){
		float licznik=0; // liczba wystąpień liczby
		for(int j=0; j < n; j++){
			if ( i == arr[j]){
				licznik++;
			}	
		}
		printf("Wartość %d wystąpiła %0.f razy (\033[0;31m%.2f%%\033[0m)\n", i ,licznik, 100*licznik/n);
	}
}

int main(void){
	srand48(time(NULL));
	int n;
	printf("Wybierz długość tablicy n=");
	scanf("%d",&n);
	int arr[n];
	create_array(arr,n);
	print_array(arr,n);
	printf("\033[0;35mWynik funkcji stats(arr,n):\033[0m\n");
	stats(arr,n);
}

