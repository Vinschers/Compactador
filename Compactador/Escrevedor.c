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

void printarCabecalho(Barra *b, FILE *arq, CodCab *vets, int qtd) //É necessário controlar qtd (-1 e +1)
{
    unsigned char c = ' ';

    fwrite(&c, sizeof(char), 1, arq);
    c = qtd - 1;
    fwrite(&c, sizeof(char), 1, arq); //bits lixo, altura e qtd

    while(strlen(vets->cabecalho) > 0)
    {
        c = paraByte(vets->cabecalho);

        fwrite(&c, sizeof(char), 1, arq);

        if (strlen(vets->cabecalho) <= 8)
                strcpy(vets->cabecalho, "");
        else
            strcpy(vets->cabecalho, &(vets->cabecalho[8]));
    }

    {
        int i;
        for(i = 0; i < qtd; i++)
        {
            c = vets->cods[i].byte;

            fwrite(&c, sizeof(char), 1, arq);
        }
    }
}

void escreverCompactador(Barra *b, char *path, CodCab *vets, int altura, int qtd, char *extensao)
{
    FILE *arqEntrada, *arqSaida;
    unsigned char *flush = (unsigned char*) malloc(10000 * sizeof(char)); //2 * strlen(vets->cods[qtd - 1].cod) *
    unsigned char atual = '\0';

    int bsl = (int)strlen(vets->cabecalho)/8;

    abrir(&arqEntrada, path, "rb");
    abrir(&arqSaida, strcat(path, extensao), "wb");

    strcpy(flush, "");

    printarCabecalho(b, arqSaida, vets, qtd);

    {
        long int i;
        unsigned char *lido, *cod;
        unsigned char c;
        long int qtdLeitura = 0, k = 0;

        fseek(arqEntrada, 0, SEEK_END);
        qtdLeitura = ftell(arqEntrada);
        rewind(arqEntrada);

        lido = (unsigned char*)malloc((qtdLeitura + 1) * sizeof(char));

        fread(lido, sizeof(char), qtdLeitura, arqEntrada);

        fclose(arqEntrada);

        for (i = 0; i < qtdLeitura; i++)
        {
            c = lido[i];
            cod = getCod(vets->cods, c, qtd);
            strcat(flush, cod);
            k += strlen(cod);

            if (k >= 8) {
                atual = paraByte(flush);
                fwrite(&atual, sizeof(char), 1, arqSaida);

                if (k > 8)
                    strcpy(flush, &flush[8]);
                else
                    strcpy(flush, "");
                k -= 8;
                if (k < 0) k = 0;
            }
        }
        if (k > 0)
        {
            atual = paraByte(flush);
            fwrite(&atual, sizeof(char), 1, arqSaida);
        }
    }


    atual = paraByte(flush);
    fwrite(&atual, sizeof(char), 1, arqSaida); //vai ignorar o lixo de memora pq nao importa mesmo

    {
        char qtdBitsLixo = 8 - strlen(flush);
        free(flush);
        char *c = (char*)malloc(sizeof(char));
        *c = (altura - 1) | (qtdBitsLixo << 4);

        fseek(arqSaida, 0, SEEK_SET);

        fwrite(c, sizeof(char), 1, arqSaida);

        free(c);
    }

    fclose(arqSaida);
}

void escreverDescompactador(No *no, char *path, char *extensao, int iniCompact, char qtdLixo, Barra *b)
{
    FILE *arqEntrada = fopen(path, "rb");
    FILE *arqSaida;
    long int qtdLeitura = 0;

    avancarParte(b);

    path[strlen(path) - strlen(extensao)] = '\0';

    arqSaida = fopen(path, "wb");

    fseek(arqEntrada, 0, SEEK_END);
    qtdLeitura = ftell(arqEntrada) - iniCompact;
    rewind(arqEntrada);
    fseek(arqEntrada, iniCompact, SEEK_SET);

    setMaxPorcentagem(b, qtdLeitura);

    {
        No *atual = no;
        unsigned char bitEsquerda = 0b10000000, charAtual;
        unsigned char *lido = (unsigned char*) malloc(sizeof(char) * (qtdLeitura + 1));
        unsigned char *escrito = (unsigned char*)malloc(sizeof(char) * qtdIdeal);
        long int i, j, k = 0;

        fread(lido, sizeof(char), qtdLeitura, arqEntrada);

        strcpy(escrito, "");

        for (j = 0; j < qtdLeitura; j++)
        {
            charAtual = lido[j];
            for(i = 0; !((j == qtdLeitura - 1) && (8 - i == qtdLixo)) && i < 8; i++)
            {
                if((bitEsquerda >> i) & charAtual)
                    atual = (atual) -> dir;
                else
                    atual = (atual) -> esq;

                if((atual)->valido)
                {
                    strcat(escrito, &(atual->byte));
                    escrito[++k] = '\0';
                    if (k >= 1022)
                    {
                        fwrite(escrito, sizeof(char), k, arqSaida);
                        strcpy(escrito, "");
                        k = 0;
                    }
                    atual = no;
                }
            }
            //setPorcentagem(b, j + 1);
        }

        if (k > 0)
        {
            fwrite(escrito, sizeof(char), k, arqSaida);
        }

        fclose(arqEntrada);
        fclose(arqSaida);
        free(escrito);
        free(lido);
    }
}
