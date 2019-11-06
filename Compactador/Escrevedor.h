#ifndef Escrevedor
#define Escrevedor
#include "Arvore.h"

extern void escreverCompactador(Barra *b, char *path, CodCab *vets, int altura, int qtd, char *extensao);
extern void escreverDescompactador(No* no, char *path, char *extensao, int iniCompact, char qtdLixo, Barra *b);

#endif // Escrevedor
