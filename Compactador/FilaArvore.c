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

void enfileirar(NoFilAr** fila, NoFilAr* novo)
{
    novo->prox = *fila;
    *fila = novo;
}

NoFilAr* desenfileirar(NoFilAr** fila)
{
    NoFilAr* ret = *fila;

    if(*fila == NULL)
        return fila;
    if((*fila)->prox == NULL)
    {
        *fila = NULL;
        return ret;
    }

    while(ret->prox->prox != NULL)
        ret = ret->prox;

    {
        NoFilAr* aux = ret->prox;
        ret->prox = NULL;
        ret = aux;
    }

    return ret;
}

NoFilAr* ultimo(NoFilAr* fila)
{
    NoFilAr* ret = fila;

    if(fila == NULL)
        return fila;

    while(ret->prox != NULL)
        ret = ret->prox;

    return ret;
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
