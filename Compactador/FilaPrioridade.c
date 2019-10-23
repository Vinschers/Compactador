#include <stdio.h>
#include <stdlib.h> /* Permite usar "NULL" */
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
        printf("char %c (%i): %llu\n", (signed char)per -> dado -> byte,(unsigned char)per -> dado -> byte, (unsigned long long int)per->dado->vezes);
        per = per -> prox;
    }
}

No* pop(NoFila **fila) {
    No *ret = (*fila)->dado;
    *fila = (*fila)->prox;
    return ret;
}

int montarFila(FILE *arq, NoFila **fila) {
    int qtdChars = 1;
    int qtdFila;
    unsigned long long int freq[256];
    int i;
    for (i = 0; i < 256; ++i)
        freq[i] = 0;

    fseek(arq, 0, SEEK_END);
    qtdChars = ftell(arq) / 8;
    fseek(arq, 0, SEEK_SET);

    while(!acabou(arq)) {
       /*char *vet = lerVariosChars(arq, 1);
        for(i = 0; i < qtdChars; i++) {
            //freq[(unsigned char)vet[i]]++;
            printf("%c", (unsigned char)vet[i]);
        }
        free(vet);*/
        char at = lerChar(arq);
        freq[(unsigned char)at]++;
    }
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
    }
    return qtdFila;
}
