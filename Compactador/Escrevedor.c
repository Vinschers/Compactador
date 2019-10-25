#include <stdio.h>
#include "Uteis.h"
#include "Escrevedor.h"
#include "Leitor.h"
#include "Bytizador.h"


char* getCod(CodByte *vet, char c, int qtd)
{
    int i;
    for (i = 0; i < qtd; ++i)
        if (vet[i].byte == c)
            return vet[i].cod;

    return "";
}
void printarCabecalho(FILE *arqEntrada, FILE *arqSaida)
{
    //
}

void escreverCompactador(FILE *arqEntrada, FILE *arqSaida, CodByte* vet, int qtd)
{
    char *flush = (char*) malloc(2 * strlen(vet[qtd - 1].cod) * sizeof(char));
    flush[0] = '\0';

    printarCabecalho(arqEntrada, arqSaida);
    fseek(arqEntrada, 0, SEEK_SET);

    while(!acabou(arqEntrada)) {
        char c = lerChar(arqEntrada);
        char *cod = getCod(vet, c, qtd);
        strcat(flush, cod);

        if (strlen(flush) >= 8) {
            char *atual = (char*)malloc(sizeof(char));
            *atual = paraByte(flush);

            fwrite(atual, sizeof(char), 1, arqSaida);
            removerByte(&flush);
            //free(atual);
        }
    }
}
