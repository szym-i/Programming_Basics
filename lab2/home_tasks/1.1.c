#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void create_array(int t[], int n){ // creating array with random integers 1-10
for (int i=0; i < n; i++){
                int temp = (lrand48() % 10)+1;
                t[i]=temp;
        }

}

void print_array(int t[], int n){ // printing array
	printf("[");
	for (int i=0; i<n; i++){
		printf(" %d",t[i]);
	}
	printf(" ]\n");
}

void reverse(int t[], int n){ // reversing array 
	int l = n/2; // number of swaps
	for (int i = 0; i < l; i++){
		int temp = t[i];
		t[i]=t[n-1];
		t[n-1]=temp;
		n--;
	}
}

void bubble_sort(int t[], int n){ // sorting array (bubble sort)
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

int one_two(int t1[], int n1, int t2[], int n2, int result[]){ // merging two arrays without duplicates
	int len=1; // result array index
	result[0]=t1[0]; 
	for ( int i=1; i < n1; i++){ // duplicate check for t1 elements 
		int z=0;
        	for (int j=0; j < len; j++){
                	if ( t1[i] == result[j] ){
                        	z++;
                        	break;
                	}
        	}
        	if ( z == 0){
                	result[len]=t1[i];
                	len++;
        	}
	}
	for ( int i=0; i < n2; i++){ // same for  t2
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
	printf("\033[0;35mResult of one_two(t1, n1, t2, n2, result):\033[0m\n");
	print_array(result,len);
	return len;
}

int main(void){
	srand48(time(NULL));
	int n1;
	int n2;
	printf("Enter size of t1, n1=");
	scanf("%d", &n1);
	printf("Enter size of t2, n2=");
	scanf("%d", &n2);
	int t1[n1];
	int t2[n2];
	create_array(t1,n1);
	create_array(t2,n2);
	printf("\033[0;31mArray t1:\033[0m\n");
	print_array(t1,n1);
	printf("\033[0;31mArray t2:\033[0m\n");
	print_array(t2,n2);
	printf("\033[0;35mResult of reverse(t1,n1):\033[0m\n");
	reverse(t1,n1);
	print_array(t1,n1);
	bubble_sort(t1,n1);
	bubble_sort(t2,n2);
	printf("\033[0;36mResult of bubble_sort(t1,n1):\033[0m\n");
	print_array(t1,n1);
	printf("\033[0;36mResult of bubble_sort(t2,n2):\033[0m\n");
	print_array(t2,n2);
	int result[n1+n2];
	one_two(t1, n1, t2, n2, result);
}
