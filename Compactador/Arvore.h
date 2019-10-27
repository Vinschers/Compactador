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

typedef struct
{
    CodByte *cods;
    char *cabecalho;
} CodCab;

extern No* montarArvore(NoFila *fila, int qtdFila);
extern CodByte* novaCodByte(char* cod, char byte);
extern CodCab arvoreParaVetor(No *no, int qtd);
#endif
