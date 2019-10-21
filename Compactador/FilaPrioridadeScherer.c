#include <stdio.h>
#include <stdlib.h>
#include "FilaPrioridade.h"
#include "Uteis.h"

void inserirS(NoFila *raiz, No *novo) {
    NoFila *atual = raiz;
    NoFila *nf = (NoFila*)malloc(sizeof(NoFila));
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->byte = novo->byte;
    novoNo->vezes = novo->vezes;
    novoNo->esq = novo->esq;
    novoNo->dir = novo->dir;
    nf->dado = novoNo;

    if(atual->dado == NULL) {
        atual->dado = novoNo;
    } else {
        while(atual->prox != NULL) {
            if (atual->prox->dado == NULL)
                break;
            if (atual->prox->dado->vezes > novoNo->vezes)
                break;
            atual = atual-> prox;
        }
        nf->prox = atual->prox;
        atual->prox = nf;
    }
}

NoFila novaFilaS() {
    NoFila raiz;
    raiz.dado = NULL;
    raiz.prox = NULL;
    return raiz;
}

void printarFila(NoFila *fila) {
    NoFila* per = fila;
    while(per != NULL)
    {
        printf("char %i: %i\n", (unsigned char)per -> dado -> byte, per->dado->vezes);
        per = per -> prox;
    }
}

No* pop(NoFila *fila) {
    No *ret = fila->dado;
    fila = fila->prox;
    return ret;
}
