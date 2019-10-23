#ifndef PILHA
#define PILHA

#include "Uteis.h"

typedef struct NoPilha
{
    struct NoPilha* prox;
    No* dado;
    char* cod;
} NoPilha;

extern NoPilha* novaPilha(No* dado);
extern NoPilha* empilhar(NoPilha* pilha, NoPilha* novo);
extern NoPilha* desempilhar(NoPilha* pilha);
extern NoPilha* inverterPilha(NoPilha* pilha);
extern boolean pilhaVazia(NoPilha* pilha);

#endif
