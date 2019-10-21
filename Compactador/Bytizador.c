#include "Bytizador.h"

char paraByte(char* strByte)
{
    char ret = 0;
    char adiUm = 1;
    int i;

    for(i = 0; i < 8; i++)
    {
        ret = ret << 1;

        if(strByte[i] == '1')
            ret = ret | adiUm;
    }

    return ret;
}
