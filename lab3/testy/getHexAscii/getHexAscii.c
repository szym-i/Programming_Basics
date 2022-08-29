#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getHexAscii(char ch){ //funkcja przyjmuje pojedynczy char i zwraca tablice wskaźników ('stringa') z jego wartością ASCII w systemie HEX
        char* result = malloc(2*sizeof(char)); // %X to wartość HEX chara
        snprintf(result,3,"%X",ch); // snprintf(destination, size + 1 (nullbyte na końcu), format, source) służy do wpisania tej wartości do 'stringa'
        return result;
}
