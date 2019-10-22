#include <stdio.h>
#include <stdlib.h>
#include "FilaPrioridade.h"
#include "Uteis.h"

NoFila* inserirS(NoFila *raiz, No *novo) {
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
        return raiz;
    } else {
        if (atual->dado->vezes > novo->vezes) {
            nf->prox = atual;
            return nf;
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
            return raiz;
        }
    }
}

NoFila* novaFilaS() {
    NoFila *raiz = (NoFila*)malloc(sizeof(NoFila));
    raiz->dado = NULL;
    raiz->prox = NULL;
    return raiz;
}

void printarFila(NoFila *fila) {
    NoFila* per = fila;
    while(per != NULL)
    {
        printf("char %c: %i\n", (unsigned char)per -> dado -> byte, per->dado->vezes);
        per = per -> prox;
    }
}

No* pop(NoFila *fila) {
    No *ret = fila->dado;
    fila = fila->prox;
    return ret;
}
