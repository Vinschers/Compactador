#include <stdio.h>
#include "Leitor.h"
#include <errno.h>

void abrir(FILE **arq, char* path, char* modo) {
    *arq = (FILE*)fopen(path, modo);
    if (*arq == 0) {
        printf("NULL POINTER! erro: %s\n", strerror(errno));
        exit(0);
    }
    //return arq;
}

unsigned char lerChar(FILE *arq) {
    unsigned char ret = '\0';
    fread(&ret, sizeof(char), 1, arq);
    return ret;
}

char* lerVariosChars(FILE *arq, int qtdChars) {
    char *vet = (char*)malloc(qtdChars*sizeof(char));
    fread(vet, sizeof(char), qtdChars, arq);
    return vet;
}


boolean acabou(FILE *arq) {
    int atual = ftell(arq);
    fseek(arq, 0, SEEK_END);
    int fim = ftell(arq);
    fseek(arq, atual, SEEK_SET);
    return atual == fim;
}

int qtdBytesArq(FILE *arq)
{
    int atual = ftell(arq);
    fseek(arq, 0, SEEK_END);
    int fim = ftell(arq);
    fseek(arq, atual, SEEK_SET);
    return fim;
}
