#ifndef FilaPrioridade
#define FilaPrioridade
#include "Uteis.h"

typedef struct NoFila
{
    struct NoFila* prox;
    No* dado;
    boolean valida;
} NoFila;

extern NoFila *novaFila();
extern NoFila *inserir(NoFila* raiz, No* novo);
extern void printarFila(NoFila *fila);
extern No* pop(NoFila **fila);
extern int montarFila(FILE *arq, NoFila **fila);

#endif
