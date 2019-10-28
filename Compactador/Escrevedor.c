#include <stdio.h>
#include "Uteis.h"
#include "Escrevedor.h"
#include "Leitor.h"
#include "Bytizador.h"
#include "Arvore.h"
#include "FilaArvore.h"

#define juntarLixoAltura(l, a) a&(l<<4)


char* getCod(CodByte *vet, char c, int qtd)
{
    int i;
    for (i = 0; i < qtd; ++i)
        if (vet[i].byte == c)
            return vet[i].cod;

    return "";
}

void printarNoArv(FILE *arq, No* n)
{
    fwrite(n->byte, sizeof(char), 1, arq);
    fwrite(n->vezes, sizeof(unsigned long long int), 1, arq);
    fwrite(&(n->valido), sizeof(boolean), 1, arq);
}

void printarCabecalho(FILE *arq, CodCab *vets, char qtd) //É necessário controlar qtd (-1 e +1)
{
    NoFilAr *filaTudo = NULL;
    int qtdNos = 0;
    int posFimArv = 0;
    char *c = (char*) malloc(sizeof(char));

    *c = qtd;

    fwrite(c, sizeof(char), 1, arq); //bits lixo e altura
    fwrite(c, sizeof(char), 1, arq); //CASO PRINTE 0, VOLTAR NESSA LINHA

    while(strlen(vets->cabecalho) >= 0)
    {
        *c = paraByte(vets->cabecalho);

        fwrite(c, sizeof(char), 1, arq);

        removerByte(&vets->cabecalho);
    }

    {
        int i;

        for(i = 0; i < qtd; i++)
        {
            *c = vets->cods[i].byte;

            fwrite(c, sizeof(char), 1, arq);
        }
    }

    free(c);
}

void escreverCompactador(char *path, CodCab *vets, int altura, int qtd)
{
    FILE *arqEntrada, *arqSaida;
    char *flush = (char*) malloc(sizeof(char)); //2 * strlen(vets->cods[qtd - 1].cod) *
    char *atual = (char*) malloc(sizeof(char));

    abrir(&arqEntrada, path, "rb");
    abrir(&arqSaida, strcat(path, ".loli"), "wb");

    flush[0] = '\0';

    printarCabecalho(arqSaida, vets, qtd);
    fseek(arqEntrada, 0, SEEK_SET);

    while(!acabou(arqEntrada)) {
        char c = lerChar(arqEntrada);
        char *cod = getCod(vets->cods, c, qtd);

        strcat(flush, cod);

        if (strlen(flush) >= 8) {
            *atual = paraByte(flush);

            fwrite(atual, sizeof(char), 1, arqSaida);
            removerByte(&flush);
        }
    }

    *atual = paraByte(flush);
    fwrite(atual, sizeof(char), 1, arqSaida); //vai ignorar o lixo de memora pq nao importa mesmo

    {
        char qtdBitsLixo = 8 - strlen(flush);
        fseek(arqEntrada, 0, SEEK_SET);
        fwrite(juntarLixoAltura(qtdBitsLixo, altura), sizeof(char), 1, arqSaida);
    }

    free(atual);

    fclose(arqEntrada);
    fclose(arqSaida);
}
