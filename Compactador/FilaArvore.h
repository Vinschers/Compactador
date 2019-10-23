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
extern NoFilAr* enfileirar(NoFilAr* fila, NoFilAr* novo);
extern NoFilAr* desenfileirar(NoFilAr* fila);
//extern NoFilAr* inverterPilha(NoFilAr* fila);
//extern boolean pilhaVazia(NoFilAr* fila);

#endif
