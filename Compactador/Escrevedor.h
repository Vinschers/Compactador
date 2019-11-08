#ifndef Escrevedor
#define Escrevedor
#include "Arvore.h"

extern void escreverCompactador(Barra *b, char *path, CodCab *vets, inteiro altura, inteiro qtd, char *extensao);
extern void escreverDescompactador(No *no, char *path, char *extensao, inteiro iniCompact, char qtdLixo, Barra *b);

#endif // Escrevedor
