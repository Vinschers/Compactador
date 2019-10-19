#include <stdio.h>
#include "Uteis.h"
#ifndef Leitor
#define Leitor

extern void abrir(FILE **arq, char* path, char* modo);
extern char lerChar(FILE *arq);
extern boolean acabou(FILE *arq);

#endif
