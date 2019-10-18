#include <stdio.h>
#include "Leitor.h"
void abrir(FILE *arq, char* path, char* modo) {
    arq = fopen(path, modo);
}

char lerChar(FILE *arq) {
    char ret;
    fread(ret, sizeof(char), 1, arq);
    return ret;
}

boolean acabou(FILE *arq) {
    int atual = ftell(arq);
    fseek(arq, 0, 3);
    int fim = ftell(arq);
    fseek(arq, atual, 1);
    return atual == fim;
}
