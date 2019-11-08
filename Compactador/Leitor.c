#include <stdio.h>
#include "Leitor.h"
#include <errno.h>

void abrir(FILE **arq, char* path, char* modo) {
    *arq = (FILE*)fopen(path, modo);

    if (*arq == 0) {
        printf("NULL POINTER! erro: %s\n", strerror(errno));
        exit(0);
    }
}

unsigned char lerChar(FILE *arq) {
    unsigned char ret = '\0';

    fread(&ret, sizeof(char), 1, arq);

    return ret;
}

char* lerVariosChars(FILE *arq, inteiro qtdChars) {
    char *vet = (char*) malloc(sizeof(char) * (qtdChars + 1));

    fread(vet, sizeof(char), qtdChars, arq);
    vet[qtdChars] = '\0';

    return vet;
}


boolean acabou(FILE *arq) {
    inteiro atual = ftell(arq);
    inteiro fim;

    fseek(arq, 0, SEEK_END);

    fim = ftell(arq);

    fseek(arq, atual, SEEK_SET);

    return atual == fim;
}

inteiro qtdBytesArq(FILE *arq)
{
    inteiro atual = ftell(arq);
    inteiro fim;

    fseek(arq, 0, SEEK_END);

    fim = ftell(arq);

    fseek(arq, atual, SEEK_SET);

    return fim;
}
