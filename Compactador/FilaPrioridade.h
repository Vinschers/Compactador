#ifndef FilaPrioridade
#define FilaPrioridade
#include "Uteis.h"

typedef struct NoFila
{
    struct NoFila* prox;
    No* dado;
    boolean valida;
} NoFila;

NoFila *novaFila();
NoFila *inserir(NoFila* raiz, No* novo);
No* pop(NoFila **fila);
extern void printarFila(NoFila *fila);
extern int montarFila(Barra *b, char* path, NoFila **fila);

#endif
