#include <stdlib.h>
#include "FilaArvore.h"

NoFilAr* novaFilAr(No* dado)
{
    NoFilAr* ret = (NoFilAr*) malloc(sizeof(NoFilAr));

    ret->cod = "";
    ret->dado = dado;
    ret->prox = NULL;

    return ret;
}

NoFilAr* enfileirar(NoFilAr* fila, NoFilAr* novo)
{
    if(fila == NULL)
        return novo;

    novo->prox = fila;
    return novo;
}

NoFilAr* desenfileirar(NoFilAr* fila)
{
    NoFilAr* ret = fila;

    while(ret->prox->prox != NULL)
        ret = ret->prox;

    NoFilAr *aux = ret->prox;
    ret->prox = NULL;
    return aux;
}

/*
NoPilha* inverterPilha(NoPilha* pilha)
{
    NoPilha* ret = NULL;

    while(pilha)
        ret = empilhar(ret, desempilhar(pilha));

    return ret;
}
*/
