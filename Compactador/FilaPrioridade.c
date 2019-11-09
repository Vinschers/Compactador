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
    }

    else {
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
        printf("char %i: %llu\n", per -> dado -> byte, (ullInteiro)per->dado->vezes);
        per = per -> prox;
    }
}

No* pop(NoFila **fila) {
    No *ret = (*fila)->dado;

    *fila = (*fila)->prox;

    return ret;
}

inteiro montarFila(Barra *b, char *path, NoFila **fila) {
    FILE* arq;
    ullInteiro qtdChars = 1;
    inteiro qtdFila;
    ullInteiro freq[256];
    lInteiro i, porcent = 0;
    char *lido;

    abrir(&arq, path, "rb");

    if (qtdBytesArq(arq) == 0)
    {
        printf("\n\nArquivo vazio!\n");
        exit(0);
    }

    avancarParte(b);

    for (i = 0; i < 256; ++i)
        freq[i] = 0;

    fseek(arq, 0, SEEK_END);
    qtdChars = ftell(arq);
    rewind(arq);

    porcent = (lInteiro) qtdChars / 100;

    setMaxPorcentagem(b, qtdChars);

    lido = (char*)malloc((qtdChars + 1) * sizeof(char));

    fread(lido, qtdChars, 1, arq);

    for (i = 0; i < qtdChars; i++)
    {
        unsigned char at = lido[i];
        freq[(unsigned char)at]++;
        if ( porcent == 0 || i % porcent == 0)
            setPorcentagem(b, i);
    }
    setPorcentagem(b, qtdChars);    //pra ficar 100% no fim
    free(lido);

    fclose(arq);

    setPorcentagem(b, i);
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
