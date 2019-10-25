#ifndef FILAARV
#define FILAARV

#include "Uteis.h"

typedef struct NoFilAr
{
    struct NoFilAr* prox;
    No* dado;
    char* cod;
} NoFilAr;

extern NoFilAr* novaFilAr(No* dado);
extern void enfileirar(NoFilAr** fila, NoFilAr* novo);
extern NoFilAr* desenfileirar(NoFilAr** fila);
extern NoFilAr* ultimo(NoFilAr* fila);

#endif
