#include <stdio.h>
#include "Leitor.h"
void abrir(char* path, char* modo) {
    arq = fopen(path, modo);
}

char lerChar() {
    char ret;
    fread(ret, sizeof(char), 1, arq);
    return ret;
}

boolean acabou() {
    int atual = ftell(arq);
    fseek(arq, 0, 3);
    int fim = ftell(arq);
    fseek(arq, atual, 1);
    return atual == fim;
}
