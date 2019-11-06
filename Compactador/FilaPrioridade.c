#include <stdio.h>
#include <stdlib.h> /* Permite usar "NULL" */
#include <conio.h>
#include "Uteis.h"
#include "FilaPrioridade.h"
#include "Leitor.h"

NoFila* inserir(NoFila *raiz, No *novo) {
    NoFila *atual = raiz;
    NoFila *nf = (NoFila*)malloc(sizeof(NoFila));
    No *novoNo = (No*)malloc(sizeof(No));
    novoNo->byte = novo->byte;
    novoNo->vezes = novo->vezes;
    novoNo->esq = novo->esq;
    novoNo->dir = novo->dir;
    novoNo->valido = novo->valido;
    nf->dado = novoNo;
    nf->valida = True;

    if (atual == NULL)
        atual = novaFila();
    if(atual->dado == NULL) {
        atual->dado = novoNo;
        atual->valida = True;
        return atual;
    } else {
        if (atual->dado->vezes > novo->vezes) {
            nf->prox = atual;
            return nf;
        } else {
            while(atual->prox != NULL) {
                if (atual->prox->dado == NULL)
                    break;
                if (atual->prox->dado->vezes > novoNo->vezes)
                    break;
                atual = atual-> prox;
            }
            nf->prox = atual->prox;
            atual->prox = nf;
            return raiz;
        }
    }
}

NoFila* novaFila() {
    NoFila *raiz = (NoFila*)malloc(sizeof(NoFila));
    raiz->dado = NULL;
    raiz->prox = NULL;
    return raiz;
}

void printarFila(NoFila *fila) {
    NoFila* per = fila;
    while(per != NULL)
    {
        printf("char %i: %llu\n", per -> dado -> byte, (unsigned long long int)per->dado->vezes);
        per = per -> prox;
    }
}

No* pop(NoFila **fila) {
    No *ret = (*fila)->dado;
    *fila = (*fila)->prox;
    return ret;
}

int montarFila(Barra *b, char *path, NoFila **fila) {
    FILE* arq;
    int qtdChars = 1;
    int qtdFila;
    unsigned long long int freq[256];
    int i, porcent = 0;

    abrir(&arq, path, "rb");

    avancarParte(b);

    for (i = 0; i < 256; ++i)
        freq[i] = 0;

    fseek(arq, 0, SEEK_END);
    qtdChars = ftell(arq);
    fseek(arq, 0, SEEK_SET);
    setMaxPorcentagem(b, qtdChars);

    i = 0;

    while(!acabou(arq)) {
        unsigned char at = lerChar(arq);
        freq[(unsigned char)at]++;
        i++;
        setPorcentagem(b, ++i);
    }
    avancarParte(b);
    setMaxPorcentagem(b, 255);
    qtdFila = 0;
    *fila = novaFila();
    for (i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            No *n = (No*)malloc(sizeof(No));
            unsigned char c = (unsigned char)i;
            n->byte = c;
            n->vezes = freq[i];
            n->valido = True;
            n->dir = NULL;
            n->esq = NULL;
            *fila = inserir(*fila, n);
            qtdFila++;
            free(n);
        }
        setPorcentagem(b, i);
    }

    fclose(arq);

    return qtdFila;
}

void destruirFilPri(NoFila *no)
{
    NoFila *ant = NULL, *atual = no;

    while(atual != NULL)
    {
        if(ant != NULL)
            free(ant);

        ant = atual;
        atual = atual->prox;
    }

    if(ant != NULL)
        free(ant);
}
