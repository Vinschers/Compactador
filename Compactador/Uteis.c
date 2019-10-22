#include <stdlib.h>
#include "Uteis.h"

No* novoNo()
{
    No* ret = (No*) malloc(sizeof(No));

    ret->dir = NULL;
    ret->esq = NULL;
    ret->vezes = 0;
    ret->byte = '\0';
}
