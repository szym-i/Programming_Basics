#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void create_2d_array(int arr [8][8]){ // funkcja do zapelniania tablicy 2d randomowymi liczbami
	for (int i=0; i < 8; i++){
		for ( int j=0; j < 8; j++){
                	int temp = (lrand48() % 2);
                	arr[i][j]=temp;
		}
        }

}

void print_2d_array(int arr[8][8]){ //funkcja do printowania tablicy 2d
	for (int j=0; j < 8; j++){
        printf("[");
        	for (int i=0; i < 8; i++){
                	printf(" %d",arr[i][j]);
        	}
        	printf(" ]\n");
	}  
}

void sum_calculator(int arr[8][8]){ //kalkulator sumy po przekątnej, w każdej kolumnie i wszystkich elementów
	int sum=0;
	printf("Suma elementów poszczególnych kolumn:\n");
	printf(" ");
	for ( int i = 0; i < 8; i++){
                int each_column_sum=0;
                for ( int j= 0; j < 8;j++){
                        each_column_sum+=arr[i][j];
                }
                printf(" %d", each_column_sum);
		sum += each_column_sum;
        }
	printf("\nSuma wszystkich elementow wynosi %d\n",sum);
	        int diagonal_sum1=0;
        int diagonal_sum2=0;
        for (int i = 0; i < 8;i++)
                diagonal_sum1+=arr[i][i];
        printf("Suma elementów po przekątnej wynosi %d \n",diagonal_sum1);
        for ( int i = 7; i >= 0; i--)
                diagonal_sum2+=arr[i][7-i];
        printf("Suma elementów po drugiej przekątnej wynosi %d \n",diagonal_sum2);
}

void multiplication(int arr1[8][8], int arr2[8][8]){ // mnożenie macierzy (tablic)
	int result[8][8];
	for (int i=0; i < 8; i++){
		for ( int j=0; j < 8; j++){
			int sum=0;
			for ( int k=0; k < 8; k++){
					sum += arr1[k][i] * arr2[j][k];
			}
			result[j][i]=sum;
		}
	}
	print_2d_array(result);
}

int main(void){
	srand48(time(NULL));
	int arr1[8][8];
	int arr2[8][8];
	create_2d_array(arr1);
	printf("\033[0;31mPierwsza tablica:\033[0m\n");
	print_2d_array(arr1);
	create_2d_array(arr2);
	printf("\033[0;31mDruga tablica:\033[0m\n");
	print_2d_array(arr2);
	printf("\033[0;35mWynik działania funkcji sum_calculator(arr2):\033[0m\n");
	sum_calculator(arr2);
	printf("\033[0;35mWynik funkcji multiplication(arr1,arr2):\033[0m\n");
	multiplication(arr1,arr2);
}
