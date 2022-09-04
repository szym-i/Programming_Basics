#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create(int rows, int columns, char* filename) // create random NxM Matrix and write it into file
{
	FILE* fp;
	char* val=malloc(2*sizeof(char));
        fp = fopen(filename,"w");
	for (int i=0; i < rows; i++){
		for (int j=0; j < columns; j++){
			int d = lrand48() % 10;
			snprintf(val,3,"%d ",d);
			fputs(val,fp);
		}
		if( i != rows - 1)
			putc('\n',fp);
	}
	putc('\0',fp);
        fclose(fp);
}

int main(int argc, char* argv[])
{
	if (argc != 3 ){
		printf("Enter exactly 2 arguments! (min and max)");
		return 1;
	}
	srand48(time(NULL));
	int min = atoi(argv[1]);
	int max = atoi(argv[2]);
	int a = lrand48() %(max - min) + min;
	int b = lrand48() %(max - min) + min;
	int c = lrand48() %(max - min) + min;
	printf("I created Matrices of sizes: %d %d %d\n",b,c,a);
	create(b,a,"MatrixA.txt");
	create(a,c,"MatrixB.txt");
	

	
}
