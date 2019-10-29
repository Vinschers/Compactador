#include "Bytizador.h"

char paraByte(char *strByte)
{
    char ret = 0;
    char adiUm = 1;
    int tam = strlen(strByte);
    int i;

    for(i = 0; i < 8; i++)
    {
        ret = ret << 1;

        if(i < tam && strByte[i] == '1')
            ret = ret | adiUm;
    }

    return ret;
}

void removerByte(char **str)
{
    if (strlen(*str) < 8)
    {
        *str = "";
        return;
    }
    char *ret = (char*) malloc((strlen(*str) - 8) * sizeof(char));
    int i = 0;

    for(; (*str)[7 + i] != '\0'; i++)
        ret[i] = (*str)[8 + i];

    //free(*str);
    *str = ret;
}

char* charsParaString(char vet[])
{
    char *ret = (char*) malloc(sizeof(char) * sizeof(vet) * 8);



    return ret;
}
