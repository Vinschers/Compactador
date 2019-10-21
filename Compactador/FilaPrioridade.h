#ifndef FilaPrioridade
#define FilaPrioridade
#include "Uteis.h"

typedef struct NoFila
{
    struct NoFila* prox;
    No* dado;
    boolean iniciada;
} NoFila;

extern NoFila novaFila();
extern void inserir(NoFila* raiz, No* novo);

//FILA DO SCHERER
extern NoFila novaFilaS();
extern void inserirS(NoFila* raiz, No* novo);

#endif
