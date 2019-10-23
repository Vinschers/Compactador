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

    percorreArvore("\0", no, &ret, i);

    return ret;
}

static void percorreArvore(char *codAtual, No *noAtual, CodByte **vet, int* acesso)
{
    if(noAtual->esq == NULL && noAtual->dir == NULL)
        return;

    char codNovo[strlen(codAtual) + 2];
    strncpy(codNovo, codAtual, strlen(codAtual));
    codNovo[strlen(codAtual) + 1] = '\0';

    if (noAtual->valido) {
        *vet[*acesso] = *novaCodByte(codAtual, noAtual->byte);
        *acesso++;
    }
    if (noAtual->esq != NULL) {
        codNovo[strlen(codAtual)] = '0';
        percorreArvore(codNovo, noAtual->esq, vet, acesso);
    }
    if (noAtual->dir != NULL) {
        codNovo[strlen(codAtual)] = '1';
        percorreArvore(codNovo, noAtual->dir, vet, acesso);
    }
}
