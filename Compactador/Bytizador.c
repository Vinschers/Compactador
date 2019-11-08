#include <stdlib.h>
#include "Bytizador.h"
#include "Uteis.h"

char paraByte(char *strByte)
{
    char ret = 0;
    char adiUm = 1;
    inteiro tam = strlen(strByte);
    inteiro i;

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
        *str[0] = '\0';
        return;
    }

    {
        char *ret = (char*) malloc((strlen(*str) + 1) * sizeof(char));
        inteiro i = 0;

        for(; (*str)[7 + i] != '\0'; i++)
        {
            ret[i] = (*str)[8 + i];
        }

        strcpy(*str, ret);
        free(ret);
    }
}

char* charsParaString(unsigned char vet[], inteiro tamStr)
{
    inteiro i, move = 0b10000000;
    char *ret = (char*) malloc(sizeof(char) * (tamStr * 8 + 1));

    for(i = 0; i < tamStr; i++)
    {
        inteiro b;

        move = 0b10000000;

        for(b = 0; b < 8; b++)
        {
            if(move & vet[i])
                ret[(i * 8) + b] = '1';
            else
                ret[(i * 8) + b] = '0';
            move = move >> 1;
        }
    }
    ret[tamStr * 8] = '\0';

    return ret;
}
