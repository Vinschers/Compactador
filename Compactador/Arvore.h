#ifndef Arvore
#define Arvore
#include <stdio.h>
#include <stdlib.h> /* Permite usar "NULL" */
#include "Uteis.h"
#include "FilaPrioridade.h"

typedef struct
{
    char* cod;
    char byte;
} CodByte;

extern No* montarArvore(NoFila *fila, int qtdFila);
extern CodByte* novaCodByte(char* cod, char byte);
extern CodByte* arvoreParaVetor(No *no, int qtd);
static void percorreArvore(char *codAtual, No *noAtual, CodByte **vet, int* acesso);
#endif
