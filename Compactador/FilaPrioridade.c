#include <stdlib.h> /* Permite usar "NULL" */
#include "Uteis.h"
#include "FilaPrioridade.h"

NoFila novaFila()
{
    NoFila* no = (NoFila*) malloc(sizeof(NoFila));

    no -> dado = NULL;
    no -> prox = NULL;
    no -> iniciada = False;

    return *no;
}

void inserir(NoFila* raiz, No* novo)
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
