#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void create_2d_array(int arr [8][8]) // create matrix with random numbers [0-1] (for easy calculations check)
{
	for (int i=0; i < 8; i++){
		for ( int j=0; j < 8; j++){
                	int temp = (lrand48() % 2);
                	arr[i][j]=temp;
		}
        }

}

void print_2d_array(int arr[8][8]) // printing matrix
{
	for (int j=0; j < 8; j++){
        printf("[");
        	for (int i=0; i < 8; i++){
                	printf(" %d",arr[i][j]);
        	}
        	printf(" ]\n");
	}  
}

void sum_calculator(int arr[8][8]) // calculate the sum of: diagonal (both), each column and all elements
{
	int sum=0;
	printf("Sum of each column:\n ");
	for ( int i = 0; i < 8; i++){
                int each_column_sum=0;
                for ( int j= 0; j < 8;j++){
                        each_column_sum+=arr[i][j];
                }
                printf(" %d", each_column_sum);
		sum += each_column_sum;
        }
	printf("\nSum of all elements is %d\n",sum);
	        int diagonal_sum1=0;
        int diagonal_sum2=0;
        for (int i = 0; i < 8;i++)
                diagonal_sum1+=arr[i][i];
        printf("Diagonal sum is %d \n",diagonal_sum1);
        for ( int i = 7; i >= 0; i--)
                diagonal_sum2+=arr[i][7-i];
        printf("Second diagonal sum is %d \n",diagonal_sum2);
}

void multiplication(int arr1[8][8], int arr2[8][8]) // matrix multiplication
{
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

int main(void)
{
	srand48(time(NULL));
	int arr1[8][8];
	int arr2[8][8];
	create_2d_array(arr1);
	printf("\033[0;31mFirst matrix:\033[0m\n");
	print_2d_array(arr1);
	create_2d_array(arr2);
	printf("\033[0;31mSecond matrix:\033[0m\n");
	print_2d_array(arr2);
	printf("\033[0;35mResult of sum_calculator(arr2):\033[0m\n");
	sum_calculator(arr2);
	printf("\033[0;35mResult of multiplication(arr1,arr2):\033[0m\n");
	multiplication(arr1,arr2);
}
