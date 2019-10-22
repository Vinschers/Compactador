#include <stdio.h>
#include <stdlib.h> /* Permite usar "NULL" */
#include <string.h>
#include "Uteis.h"
#include "FilaPrioridade.h"
#include "Arvore.h"

CodByte* novaCodByte(char* cod, char byte)
{
    CodByte* ret = (CodByte*) malloc(sizeof(CodByte));

    ret->byte = byte;
    ret->cod  = cod;

    return ret;
}

No* montarArvore(NoFila *fila, int qtdFila) {
    while(qtdFila >= 2) {
        No *primeiro = pop(&fila);
        No *segundo = pop(&fila);
        No *novo = (No*)malloc(sizeof(No));
        novo->esq = primeiro;
        novo->dir = segundo;
        novo->vezes = primeiro->vezes + segundo->vezes;
        novo->byte = '\0';
        novo->valido = False;
        fila = inserir(fila, novo);
        qtdFila--;
    }

    return pop(&fila);
}

CodByte* arvoreParaVetor(No *no, int qtd)
{
    CodByte *ret = (CodByte*)malloc(qtd * sizeof(CodByte));
    int *i = (int*)malloc(sizeof(int));
    *i = 0;
    char *str = (char*)malloc(sizeof(char));
    strcpy(str, "");
    percorreArvore(str, no, &ret, i);
    return ret;
}

static void percorreArvore(char *codAtual, No *noAtual, CodByte **vet, int* acesso)
{
    if(noAtual->esq == NULL && noAtual->dir == NULL)
        return;
    if (noAtual->valido) {
        *vet[*acesso] = *novaCodByte(codAtual, noAtual->byte);
        *acesso++;
    }
    if (noAtual->esq != NULL) {
        char *novoEsq = (char*)malloc((1 + strlen(codAtual)) * sizeof(char));
        strcpy(novoEsq, codAtual);
        strcat(novoEsq, "0");
        percorreArvore(novoEsq, noAtual->esq, vet, acesso);
        free(novoEsq);
    }
    if (noAtual->dir != NULL) {
        char *novoDir = (char*)malloc((1 + strlen(codAtual)) * sizeof(char));
        strcpy(novoDir, codAtual);
        strcat(novoDir, "1");
        percorreArvore(novoDir, noAtual->dir, vet, acesso);
        free(novoDir);
    }
}
