#include <stdio.h>


int main(void){
	int n=0;
	printf("Wprowadź rozmiar działki n=");
	scanf("%d",&n);
	int arr[n][n];
	for(int i=0; i < n; i++){
                for(int j=0; j < n; j++)
                        scanf("%d", &arr[i][j]);
	}
	for(int i=0; i < n; i++){
		printf("[ ");
                for(int j=0; j < n; j++)
                        printf("%d ", arr[i][j]);
		printf("]\n");
	}
	int max_area=0;
	for(int i=0; i < n; i++){
		int len=0;
	        int h=0;
		for(int j=0; j < n; j++){
			printf("i=%d j=%d \n",i,j);
			int area=0;
			int zmienna=0;
			int x=n;
			if (zmienna == 0){
			for(int l=i; l < n ; l++){
					for(int h=j; h < n && x > h ; h++){
						int each_row=0;
						printf("l=%d h=%d \n",l,h);
						if(arr[l][h]==0)
							area++;
						else{
							x=h;
							zmienna+=1;
							break;
						}
					}
				}
			}
			printf("Area = %d\n",area);
			if(area > max_area){
				max_area=area;	
			}	
		}
	}
	printf("Max area=%d",max_area);
}
