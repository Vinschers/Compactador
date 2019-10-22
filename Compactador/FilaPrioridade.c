#include <stdlib.h> /* Permite usar "NULL" */
#include "Uteis.h"
#include "FilaPrioridade.h"

NoFila* novaFila()
{
    NoFila* no = (NoFila*) malloc(sizeof(NoFila));

    no -> dado = NULL;
    no -> prox = NULL;
    no -> valida = True;

    return no;
}

/*
NoFila* inserirLeitura(NoFila* raiz, char byte)
{
    NoFila* percorre = raiz;

    while(percorre != NULL)
    {
        if(percorre->dado->byte == byte)
        {
            No* substituir = percorre->dado;
            No* aux = percorre->dado;
            percorre->dado->vezes++;

            while(percorre->prox != NULL && percorre->dado->vezes > percorre->prox->dado->vezes)
                percorre = percorre->prox;

            *percorre->dado = *substituir;
            *substituir = *aux;

            return raiz;
        }

        percorre = percorre->prox;
    }

    {
        NoFila* novaF = novaFila();
        No* novo = novoNo();

        novo->byte = byte;
        novo->vezes = 1;

        novaF->dado = novo;
        novaF->prox = raiz;

        return novaF;
    }

    return NULL;
}

NoFila* inserir(NoFila* raiz, No* novo)
{
    NoFila* novoF = novaFila();
    novoF -> dado = novo;

    if(raiz == NULL)
        return novoF;

    if(raiz->dado->byte != novo->byte && raiz->dado->vezes > novo->vezes)
    {
        novoF->prox = raiz;
        return novoF;
    }

    {
        NoFila* percorre = raiz;
        NoFila* ant = NULL;

        while(percorre != NULL)
        {
            ant = percorre;
            percorre = percorre -> prox;
        }

        if(raiz->valida == True && ant->dado->byte == novo->byte)
        {
            ant->dado->vezes++;

            free(novo);
            free(novoF);

            return raiz;
        }

        novoF->prox = ant->prox;
        ant->prox = novoF;
    }

    return raiz;
}

/*
NoFila* inserir(NoFila* raiz, No* novo)
{
    NoFila noFila = novaFila();
    NoFila r = *raiz;

    noFila.dado = novo;
    noFila.iniciada = True;

    if(raiz -> iniciada == True)
    {
        if(novo -> vezes <= raiz -> dado -> vezes)
        {
            NoFila aux = *raiz;
            *raiz = noFila;

            r = *raiz;

            noFila = aux;
            raiz -> prox = &noFila;
        }
        else
        {
            NoFila* percorre = raiz;

            while(percorre->prox != NULL && novo -> vezes > percorre->dado -> vezes)
                percorre = percorre->prox;

            noFila.prox = percorre->prox;
            percorre->prox = &noFila;
        }
    }
    else
        *raiz = noFila;
}
*/
