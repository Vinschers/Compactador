#include <stdlib.h>
#include "Pilha.h"

NoPilha* novaPilha()
{
    NoPilha* ret = (NoPilha*) malloc(sizeof(NoPilha));

    ret->cod = "";
    ret->dado = NULL;
    ret->prox = NULL;

    return ret;
}

NoPilha* empilhar(NoPilha* pilha, NoPilha* novo)
{
    if(pilha == NULL)
        return novo;

    novo->prox = pilha;
    return novo;
}

NoPilha* desempilhar(NoPilha* pilha)
{
    NoPilha* ret = pilha;
    pilha = pilha->prox;

    return ret;
}

NoPilha* inverterPilha(NoPilha* pilha)
{
    NoPilha* ret = NULL;

    while(!pilha)
        ret = empilhar(ret, desempilhar(pilha));

    return ret;
}
