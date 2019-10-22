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
extern NoFila *novaFilaS();
extern NoFila *inserirS(NoFila* raiz, No* novo);
extern void printarFila(NoFila *fila);
extern No* pop(NoFila **fila);

#endif
