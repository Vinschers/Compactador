#include <stdio.h>
#include <math.h>
#include <string.h>
#include "Uteis.h"
#include "Escrevedor.h"
#include "Leitor.h"
#include "Bytizador.h"
#include "Arvore.h"
#include "FilaArvore.h"

char* getCod(CodByte *vet, unsigned char c, inteiro qtd)
{
    inteiro i;

    for (i = 0; i < qtd; ++i)
        if (vet[i].byte == c)
            return vet[i].cod;

    return "";
}

void printarCabecalho(Barra *b, FILE *arq, CodCab *vets, inteiro qtd, inteiro *coutB) //� necess�rio controlar qtd (-1 e +1)
{
    unsigned char c = ' ';

    fwrite(&c, sizeof(char), 1, arq);
    c = qtd - 2;
    fwrite(&c, sizeof(char), 1, arq);
    c = qtd - 1;
    fwrite(&c, sizeof(char), 1, arq);
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
        inteiro i;
        for(i = 0; i < qtd; i++)
        {
            c = vets->cods[i].byte;

            fwrite(&c, sizeof(char), 1, arq);
            setPorcentagem(b, (*coutB)++);
        }
    }
}

void escreverCompactador(Barra *b, char *path, CodCab *vets, inteiro altura, inteiro qtd, char *extensao)
{
    FILE *arqEntrada, *arqSaida;
    unsigned char *flush = (unsigned char*) malloc((1 + pow(2, altura + 1)) * sizeof(char));
    unsigned char *lido;
    inteiro *coutB = (inteiro*)malloc(sizeof(inteiro));
    lInteiro tamArq = 0;
    flutuante bytesStrLouca = (flutuante)strlen(vets->cabecalho)/8;
    inteiro bsl = (inteiro)ceil(bytesStrLouca);
    ullInteiro qtdLeitura = 1;
    inteiro ler = qtdIdeal*qtdIdeal;

    abrir(&arqEntrada, path, "rb");
    abrir(&arqSaida, strcat(path, extensao), "wb");
    avancarParte(b);

    fseek(arqEntrada, 0, SEEK_END);
    tamArq = ftell(arqEntrada);
    rewind(arqEntrada);

    setMaxPorcentagem(b, 3 + bsl + qtd + tamArq);
    *coutB = 0;

    strcpy(flush, "");

    printarCabecalho(b, arqSaida, vets, qtd, coutB);

    lido = (unsigned char*) malloc ((qtdIdeal * qtdIdeal + 1) * sizeof(char));
    strcpy(lido, "");

    {
        inteiro i;
        unsigned char *cod;
        unsigned char c;

        for(; !acabou(arqEntrada); qtdLeitura)
        {
            if(qtdLeitura * qtdIdeal * qtdIdeal > tamArq)
            {
                if(tamArq < qtdIdeal * qtdIdeal)
                    ler = tamArq;
                else
                    ler = tamArq - (qtdLeitura - 1) * qtdIdeal * qtdIdeal;
            }

            fread(lido, sizeof(char), ler, arqEntrada);

            for(i = 0; i < ler; i++)
            {
                c = lido[i];
                cod = getCod(vets->cods, c, qtd);
                strcat(flush, cod);

                while (strlen(flush) >= 8) {
                    c = paraByte(flush);

                    fwrite(&c, sizeof(char), 1, arqSaida);

                    removerByte(&flush);
                }
            }

            *coutB += ler;
            setPorcentagem(b, *coutB);

        }

        if(strlen(flush) > 0)
        {
            c = paraByte(flush);
            fwrite(&c, sizeof(char), 1, arqSaida);
        }

        *coutB += i;

        free(lido);
        setPorcentagem(b, *coutB);
    }

    {
        char qtdBitsLixo = 8 - strlen(flush);

        if(qtdBitsLixo == 8)
            qtdBitsLixo = 0;

        fseek(arqSaida, 0, SEEK_SET);

        fwrite(&qtdBitsLixo, sizeof(char), 1, arqSaida);
        fwrite(&altura, sizeof(char), 1, arqSaida);

        setPorcentagem(b, ++(*coutB));
    }

    free(coutB);

    fclose(arqEntrada);
    fclose(arqSaida);
}

void escreverCharDescompactador(unsigned char charAtual, No *no, No **atual, FILE *arqEntrada, FILE *arqSaida, char qtdLixo, boolean ultimaVez)
{
    inteiro i, bitEsquerda = 0b10000000;

    for(i = 0; !(ultimaVez && 8 - i == qtdLixo) && i < 8; i++)
    {
        if((bitEsquerda >> i) & charAtual)
            *atual = (*atual) -> dir;
        else
            *atual = (*atual) -> esq;

        if((*atual)->valido)
        {
            fwrite(&((*atual)->byte), sizeof(char), 1, arqSaida);
            *atual = no;
        }
    }
}

void escreverDescompactador(No *no, char *path, char *extensao, inteiro iniCompact, char qtdLixo, Barra *b)
{
    FILE *arqEntrada = fopen(path, "rb");
    FILE *arqSaida;
    lInteiro tamArq = 0, cout = 0;
    ullInteiro qtdLeitura = 1;
    inteiro ler = qtdIdeal*qtdIdeal;

    path[strlen(path) - strlen(extensao)] = '\0';

    arqSaida = fopen(path, "wb");

    fseek(arqEntrada, 0, SEEK_END);
    tamArq = ftell(arqEntrada);
    fseek(arqEntrada, iniCompact, SEEK_SET);
    tamArq -= ftell(arqEntrada);

    avancarParte(b);
    setMaxPorcentagem(b, tamArq);

    {
        No *atual = no;
        unsigned char *lido = (unsigned char*) malloc(sizeof(char) * qtdIdeal * qtdIdeal + 1), charAtual;
        inteiro i;

        strcpy(lido, "");

        for(; !acabou(arqEntrada); qtdLeitura)
        {
            if(qtdLeitura * qtdIdeal * qtdIdeal > tamArq)
            {
                if(tamArq < qtdIdeal * qtdIdeal)
                    ler = tamArq;
                else
                    ler = tamArq - (qtdLeitura - 1) * qtdIdeal * qtdIdeal;
            }

            fread(lido, sizeof(char), ler, arqEntrada);

            for (i = 0; i < ler; i++)
            {
                charAtual = lido[i];

                escreverCharDescompactador(charAtual, no, &atual, arqEntrada, arqSaida, qtdLixo, (i == ler - 1 && acabou(arqEntrada)));
            }
            cout += ler;

            setPorcentagem(b, cout);
        }

        setPorcentagem(b, cout + i);

        fclose(arqEntrada);
        fclose(arqSaida);

        free(lido);
    }
}
