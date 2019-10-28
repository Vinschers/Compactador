#include <stdlib.h>
#include <string.h>
#include "Uteis.h"

No* novoNo()
{
    No* ret = (No*) malloc(sizeof(No));

    ret->dir = NULL;
    ret->esq = NULL;
    ret->vezes = 0;
    ret->byte = '\0';
}

void avancarSimboloBarra(Barra *b)
{
    char a = b->atual;
    switch(a)
    {
        case '|':
            b->atual = '/';
            break;

        case '/':
            b->atual = '-';
            break;

        case '-':
            b->atual = '\\';
            break;

        case '\\':
            b->atual = '|';
            break;
    }
}

void setMaxPorcentagem(Barra *b, unsigned int m)
{
    b->porcentagem[1] = m;
}

void setPorcentagem(Barra *b, unsigned int p)
{
    int d = b->porcentagem[1];
    float f = (float)p / d;
    f *= 100;
    b->porcentagem[0] = (unsigned int)f;
    printarStatus(*b);
    avancarSimboloBarra(b);
}

void printarStatus(Barra b)
{
    static char status[5][16] = {"LENDO", "MONTANDO FILA", "MONTANDO ARVORE", "OBTENDO CODIGOS", "ESCREVENDO"};
    char *barra = (char*)malloc(150 * sizeof(char));
    char *parte = (char*)malloc((strlen(status[b.parteAtual]) + 3) * sizeof(char));
    int i;
    strcpy(barra, "\0");
    strcpy(parte, "[");
    strcat(parte, status[b.parteAtual]);
    strcat(parte, "]");
    for (i = 0; i < b.porcentagem[0]/10; i++)
        strcat(barra, "X");
    limparLinha();

    printf("%-18s %c %d%% |%-10s|", parte, b.atual, b.porcentagem[0], barra);

    free(barra);
    free(parte);
}

void avancarParte(Barra *b)
{
    b->parteAtual++;
    printf("\n\nParte %i/5:\n\n", b->parteAtual + 1);
    b->y++;
}

void limparLinha()
{
    printf("\r");
}
