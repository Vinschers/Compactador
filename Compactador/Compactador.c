#include <string.h>
#include <stdlib.h>
#include "Uteis.h"
#include "Leitor.h"
#include "FilaPrioridade.h"
#include "Bytizador.h"

FILE *arq;
char *path;
NoFila *fila;
No *arvore;
unsigned short int qtdFila;

void montarFila() {
    abrir(&arq, path, "rb");
    int freq[256];
    int i;
    for (i = 0; i < 256; ++i)
        freq[i] = 0;
    qtdFila = 0;
    while(!acabou(arq)) {
        unsigned char atual = lerChar(arq);
        freq[(int)atual]++;
    }
    fila = novaFilaS();
    for (i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            No *n = (No*)malloc(sizeof(No));
            unsigned char c = (unsigned char)i;
            n->byte = c;
            n->vezes = freq[i];
            fila = inserirS(fila, n);
            qtdFila++;
            free(n);
        }
    }
}

void montarArvore() {
    while(qtdFila >= 2) {
        No *primeiro = pop(&fila);
        No *segundo = pop(&fila);
        No *novo = (No*)malloc(sizeof(No));
        novo->esq = primeiro;
        novo->dir = segundo;
        novo->vezes = primeiro->vezes + segundo->vezes;
        novo->byte = '\0';
        fila = inserirS(fila, novo);
        qtdFila--;
    }
    arvore = pop(&fila);
}

void compactar() {
    montarFila();
    montarArvore();
}
void descompactar() {
    //
}

char *get_path() {
    char *ret = (char*)malloc(sizeof(char) * 256);
    printf("Digite o local do arquivo a ser compactado ou descompactado: ");
    scanf("%255s", ret);
    return ret;
}
int main(int qtdArgs, char *args[]) {
    if (qtdArgs > 1) {
        *path = *args[1];
    } else {
        path = get_path();
    }
    if (strstr(path, ".loli")) //extensao passivel de mudanca
        descompactar();
    else
        compactar();
    return 0;
}
