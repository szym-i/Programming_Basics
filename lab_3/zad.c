#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define NEWLINE '\n'
#define IN_WORD 1

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2

#define MAX_LINE 128

char** getData(int* line_count){
    char** main_array = calloc(3, sizeof(char*)); // alokacja pamięci dla tablicy wskaźników
    char* line = NULL;
    (*line_count) = 0;
    size_t size;

    for (;;)
    {
        int length = getline(&line, &size, stdin);
        if (length == -1){// przerwanie pętli na końcu pliku
            break;
        }

        if (*line_count > 2){// jeśli jest więcej niż 3 wiersze, realokujemy pamięc
            char** new_array = realloc(main_array, (*line_count + 1) * sizeof(char*));// bezpieczna realokacja pamięci

            if (new_array != NULL){
                main_array = new_array;
            }
            else
            {
                free(main_array);
                free(new_array);
                return NULL;
            }
        }

        if (line[length - 1] != '\n')// wczytywanie do końca linii
        {
            length++;
        }

        line[length - 1] = 0;// dodawanie linii na główną tablicę
        main_array[*line_count] = malloc(length * sizeof(char));
        memcpy(main_array[*line_count], line, length * sizeof(char));
        (*line_count)++;
    }

    return main_array;
}

int read_line(){
    char line[MAX_LINE];
    int n;
    fgets(line, MAX_LINE, stdin); // to get the whole line
    sscanf(line, "%d", &n);
    return n;
}

// count number of lines (nl), number of words (nw) and number of characters
// (nc) in the text read from stdin
void wc(int* nl, int *nw, int *nc)
{	
	int len;
	int k=1;
	int g=0;
	char* result = malloc(len*200*sizeof(char));
	char** input = getData(&len);	
	* nl = len;
	for(int i=0; i < len; i++){
		if (input[i][0] != ' '&& input[i][0]!='\0' )
			k++;
		for (int j=0; j < strlen(input[i]); j++){
			g++;
			if( j!=0 && input[i][j-1] == ' ' && input[i][j] != ' ')
				k++;
		}
	}
	*nw = k-1;
	*nc = g + *nl;
	
}
// Count block and line comments in the text read from stdin. Set
// line_comment_counter and block_comment_counter accordingly
void find_comments(int *line_comment_counter, int *block_comment_counter)
{
	int len;
	int l=0;
	int b=0;
}
/******************************************************/
int main(void)
{
    int to_do;
    int nl, nw, nc;
    int line_comment_counter, block_comment_counter;
    to_do = read_line();
    switch (to_do)
    {
    case 1: // wc()
        wc(&nl, &nw, &nc);
        printf("\n%d %d %d\n", nl, nw, nc);
        break;
    case 4:
        find_comments(&line_comment_counter, &block_comment_counter);
        printf("%d %d\n", block_comment_counter, line_comment_counter);
        break;
    default:
        printf("NOTHING TO DO FOR %d\n", to_do);
        break;
    }
    return 0;
}
