#include <stdio.h>
#include "Uteis.h"
#ifndef Leitor
#define Leitor

extern void abrir(FILE **arq, char* path, char* modo);
extern unsigned char lerChar(FILE *arq);
extern boolean acabou(FILE *arq);
extern char* lerVariosChars(FILE *arq, int qtdChars);
extern ullInteiro qtdBytesArq(FILE *arq);

#endif
