#include <stdio.h>
#include "Uteis.h"
#include "Escrevedor.h"
#include "Leitor.h"
#include "Bytizador.h"
#include "Arvore.h"
#include "FilaArvore.h"


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

void printarCabecalho(FILE *arq, No *arv)
{
    NoFilAr *filaTudo = NULL;
    int qtdNos = 0;
    int posFimArv = 0;
    fwrite(' ', sizeof(char), 1, arq); //bits lixo
    fwrite(' ', sizeof(char), 1, arq); //h
    enfileirar(&filaTudo, novaFilAr(arv));
    while(filaTudo) {
        NoFilAr *f = ultimo(filaTudo);

        printarNoArv(arq, f->dado);

        if (f->dado->esq != NULL) {
            NoFilAr *n = novaFilAr(NULL);
            n->dado = f->dado->esq;

            enfileirar(&filaTudo, n);
        }

        if (f->dado->dir != NULL) {
            NoFilAr *n = novaFilAr(NULL);
            n->dado = f->dado->dir;

            enfileirar(&filaTudo, n);
        }

        qtdNos++;
        desenfileirar(&filaTudo);
    }

    posFimArv = ftell(arq);
    fseek(arq, 1, SEEK_SET);
    fwrite(qtdNos, sizeof(char), 1, arq);
    fseek(arq, posFimArv, SEEK_SET);
}

void escreverCompactador(FILE *arqEntrada, FILE *arqSaida, CodByte* vet, No* arv, int qtd)
{
    char *flush = (char*) malloc(2 * strlen(vet[qtd - 1].cod) * sizeof(char));
    char *atual = (char*)malloc(sizeof(char));
    char qtdBitsLixo;
    flush[0] = '\0';

    printarCabecalho(arqSaida, arv);
    fseek(arqEntrada, 0, SEEK_SET);

    while(!acabou(arqEntrada)) {
        char c = lerChar(arqEntrada);
        char *cod = getCod(vet, c, qtd);
        strcat(flush, cod);

        if (strlen(flush) >= 8) {
            *atual = paraByte(flush);

            fwrite(atual, sizeof(char), 1, arqSaida);
            removerByte(&flush);
            //free(atual);
        }
    }

    *atual = paraByte(flush);
    fwrite(atual, sizeof(char), 1, arqSaida); //vai ignorar o lixo de memora pq nao importa mesmo
    qtdBitsLixo = 8 - strlen(flush);
    fseek(arqEntrada, 0, SEEK_SET);
    fwrite(qtdBitsLixo, sizeof(char), 1, arqSaida);

    free(atual);
}
