#include <stdlib.h>
#include "FilaArvore.h"

NoFilAr* novaFilAr(No* dado)
{
    NoFilAr* ret = (NoFilAr*) malloc(sizeof(NoFilAr));

    ret->cod = "";
    ret->dado = dado;
    ret->prox = NULL;
    ret->indice = 0;
    ret->h = 1;

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


void inverterFila(NoFilAr** fila)
{
    NoFilAr* atual = *fila;
    NoFilAr* antecessor = NULL;
    NoFilAr* aux = NULL;

    while(atual) {
        aux = atual->prox;
        atual->prox = antecessor;

        antecessor = atual;
        atual = aux;
    }
    *fila = antecessor;
}

void destruirFilAr(NoFilAr *no)
{
    NoFilAr *ant = NULL, *atual = no;

    while(atual != NULL)
    {
        if(ant != NULL)
            free(ant);

        ant = atual;
        atual = atual->prox;
    }

    if(ant != NULL)
        free(ant);
}
