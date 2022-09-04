#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char* argv[])
{
       	FILE* fp = fopen(argv[1], "r");	
	char b;
	int i=0;
	char* str = malloc(5 * sizeof(char));
	while(!feof(fp)){
		fread(&b,1,1,fp);
		if ( b == '<' ){
			fgets(str, 4, fp);
			int result = strcmp(str,"ul>");
			//printf("%s %d \n",str,result);
			if (result == 0){
				printf("*");
				        while(!feof(fp)){
                				fread(&b,1,1,fp);
                				if ( b == '<' ){
                        				fgets(str, 4, fp);
                        				int result = strcmp(str,"li>");
                        				do{
								fread(&b,1,1,fp);
								if ( b != '<')
                               						printf("%c",b);
								else
									break;
                       					}while(1);
               					}
        				}

			}
		}
	}
}
