#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Uteis.h"
#include "Escrevedor.h"
#include "Leitor.h"
#include "Bytizador.h"
#include "Arvore.h"
#include "FilaArvore.h"

char* getCod(CodByte *vet, unsigned char c, int qtd)
{
    int i;
    for (i = 0; i < qtd; ++i)
        if (vet[i].byte == c)
            return vet[i].cod;

    return "";
}

void printarCabecalho(Barra *b, FILE *arq, CodCab *vets, int qtd, int *coutB) //É necessário controlar qtd (-1 e +1)
{
    unsigned char c = ' ';

    fwrite(&c, sizeof(char), 1, arq);
    c = qtd - 1;
    fwrite(&c, sizeof(char), 1, arq); //bits lixo, altura e qtd
    *coutB += 2;
    setPorcentagem(b, *coutB);

    while(strlen(vets->cabecalho) > 0)
    {
        c = paraByte(vets->cabecalho);

        fwrite(&c, sizeof(char), 1, arq);

        removerByte(&vets->cabecalho);
        setPorcentagem(b, (*coutB)++);
    }

    {
        int i;
        for(i = 0; i < qtd; i++)
        {
            c = vets->cods[i].byte;

            printf("\n%i", c);

            fwrite(&c, sizeof(char), 1, arq);
            //setPorcentagem(b, (*coutB)++);
        }
    }
}

void escreverCompactador(Barra *b, char *path, CodCab *vets, int altura, int qtd, char *extensao)
{
    FILE *arqEntrada, *arqSaida;
    unsigned char *flush = (unsigned char*) malloc(10000 * sizeof(char)); //2 * strlen(vets->cods[qtd - 1].cod) *
    unsigned char *atual = (unsigned char*) malloc(sizeof(char));
    int *coutB = (int*)malloc(sizeof(int));

    float bytesStrLouca = (float)strlen(vets->cabecalho)/8;
    int bsl = (int)ceil(bytesStrLouca);

    abrir(&arqEntrada, path, "rb");
    abrir(&arqSaida, strcat(path, extensao), "wb");
    avancarParte(b);

    setMaxPorcentagem(b, 2 + bsl + qtd + qtdBytesArq(arqEntrada));
    *coutB = 0;

    flush[0] = '\0';

    printarCabecalho(b, arqSaida, vets, qtd, coutB);
    fseek(arqEntrada, 0, SEEK_SET);

    {
        int i = 0;
        unsigned char lido, *cod;
        unsigned char c;

        while(!acabou(arqEntrada)) {
            c = lerChar(arqEntrada);
            cod = getCod(vets->cods, c, qtd);
            strcat(flush, cod);

            while (strlen(flush) >= 8) {
                *atual = paraByte(flush);
                fwrite(atual, sizeof(char), 1, arqSaida);
                removerByte(&flush);
            }

            //setPorcentagem(b, (*coutB)++);
        }
    }


    *atual = paraByte(flush);
    fwrite(atual, sizeof(char), 1, arqSaida); //vai ignorar o lixo de memora pq nao importa mesmo
    setPorcentagem(b, (*coutB)++);

    {
        char qtdBitsLixo = strlen(flush)? 8 - strlen(flush) : 0;
        unsigned char *c = (unsigned char*)malloc(sizeof(char));
        *c = (altura - 1) | (qtdBitsLixo << 4);

        fseek(arqSaida, 0, SEEK_SET);

        fwrite(c, sizeof(char), 1, arqSaida);

        free(c);
    }

    free(atual);
    free(coutB);

    fclose(arqEntrada);
    fclose(arqSaida);
}

/*
void escreverChar(unsigned char c, No **atual, No *raiz, FILE *arqEntrada, FILE *arqSaida, char qtdLixo) {
    char bitEsquerda = 0b10000000;
    int i;
    for(i = 0; !(acabou(arqEntrada) && 8 - i == qtdLixo) && i < 8; i++)
    {
        if((bitEsquerda >> i) & c)
            *atual = (*atual) -> dir;
        else
            atual = (*atual) -> esq;

        if((*atual)->valido)
        {
            fwrite(&(*atual)->byte, sizeof(char), 1, arqSaida);
            *atual = raiz;
        }
    }
}*/

void escreverDescompactador(No *no, char *path, char *extensao, int iniCompact, char qtdLixo)
{
    FILE *arqEntrada = fopen(path, "rb");
    FILE *arqSaida;

    path[strlen(path) - strlen(extensao)] = '\0';

    arqSaida = fopen(path, "wb");

    fseek(arqEntrada, iniCompact, SEEK_SET);

    {
        No *atual = no;
        unsigned char bitEsquerda = 0b10000000, charAtual;
        unsigned char *lido = (unsigned char*) malloc(sizeof(char) * (qtdIdeal + 1));
        int i, j;

        while(!acabou(arqEntrada))
        {
                charAtual = lerChar(arqEntrada);
                for(i = 0; !(acabou(arqEntrada) && 8 - i == qtdLixo) && i < 8; i++)
                {
                    if((bitEsquerda >> i) & charAtual)
                        atual = (atual) -> dir;
                    else
                        atual = (atual) -> esq;

                    if((atual)->valido)
                    {
                        fwrite(&(atual)->byte, sizeof(char), 1, arqSaida);
                        atual = no;
                    }
                }
        }

        fclose(arqEntrada);
        fclose(arqSaida);
    }
}
