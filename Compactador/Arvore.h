#ifndef Arvore
#define Arvore
#include <stdio.h>
#include <stdlib.h> /* Permite usar "NULL" */
#include "Uteis.h"
#include "FilaPrioridade.h"

typedef struct
{
    unsigned char* cod;
    unsigned char byte;
} CodByte;

typedef struct
{
    CodByte *cods;
    char *cabecalho;
} CodCab;

extern No* montarArvore(Barra *b, NoFila *fila, inteiro qtdFila);
extern CodByte* novaCodByte(char* cod, char byte);
extern CodCab* arvoreParaVetor(Barra *b, No *no, inteiro qtd);
extern No* arqParaArvore(char *path, inteiro *iniCompact, char *lixo, Barra *b);
#endif
