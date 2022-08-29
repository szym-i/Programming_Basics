#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void create_array(int t[], int n){ //funkcja do towrzenia tablicy z losowymi liczbami z przedzialu [1,10]
for (int i=0; i < n; i++){
                int temp = (lrand48() % 10)+1;
                t[i]=temp;
        }

}

void print_array(int t[], int n){ //funkcja do printowania tablicy
	printf("[");
	for (int i=0; i<n; i++){
		printf(" %d",t[i]);
	}
	printf(" ]\n");
}

void reverse(int t[], int n){ // funkcja do odwracania tablicy
	int l = n/2; // liczba ile razy ma sie wykonac petla
	for (int i = 0; i < l; i++){
		int temp = t[i];
		t[i]=t[n-1];
		t[n-1]=temp;
		n--;
	}
}

void bubble_sort(int t[], int n){ // funkcja sortująca
	for (int i=0; i < n-1; i++){
		for (int j = 0; j < n -i -1; j++){
			if ( t[j] > t[j+1]){
				int temp=t[j];
				t[j]=t[j+1];
				t[j+1]=temp;
			}

		}

	}
}

int one_two(int t1[], int n1, int t2[], int n2, int result[]){
	int len=1; // indeks tablicy result
	result[0]=t1[0]; // dodanie pierwszego elementu z t1 na tablicę result 
	for ( int i=1; i < n1; i++){ //sprawdzanie czy element z t1, nie jest już w tablicy result 
		int z=0; // zmienna pomocnicza - sprawdza liczbę wystąpień elementu z t1 w tablicy result
        	for (int j=0; j < len; j++){
                	if ( t1[i] == result[j] ){
                        	z++;
                        	break;
                	}
        	}
        	if ( z == 0){ // jeśli elementu nie ma w tablicy result,
                	result[len]=t1[i]; //zostaje on dodany do niej
                	len++;
        	}
	}
	for ( int i=0; i < n2; i++){ // to samo co wyżej, ale dla tablicy t2
                int z=0;
                for (int j=0; j < len; j++){
                        if ( t2[i] == result[j] ){
                                z++;
                                break;
                        }
                }
                if ( z == 0){
                        result[len]=t2[i];
                        len++;
                }
        }
	bubble_sort(result,len);
	printf("\033[0;35mWynik funkcji one_two(t1, n1, t2, n2, result):\033[0m\n");
	print_array(result,len);
	return len; //funkcja zwraca długość tablicy result
}

int main(void){
	srand48(time(NULL));
	int n1;
	int n2;
	printf("Podaj rozmiar tabeli t1, n1=");
	scanf("%d", &n1);
	printf("Podaj rozmiar tabeli t2, n2=");
	scanf("%d", &n2);
	int t1[n1];
	int t2[n2];
	create_array(t1,n1);
	create_array(t2,n2);
	printf("\033[0;31mTablica t1:\033[0m\n");
	print_array(t1,n1);
	printf("\033[0;31mTablica t2:\033[0m\n");
	print_array(t2,n2);
	printf("\033[0;35mWynik funkcji reverse(t1,n1):\033[0m\n");
	reverse(t1,n1);
	print_array(t1,n1);
	bubble_sort(t1,n1);
	bubble_sort(t2,n2);
	printf("\033[0;36mTablica t1 po posortowaniu:\033[0m\n");
	print_array(t1,n1);
	printf("\033[0;36mTablica t2 po posortowaniu:\033[0m\n");
	print_array(t2,n2);
	int result[n1+n2];
	one_two(t1, n1, t2, n2, result);
}
