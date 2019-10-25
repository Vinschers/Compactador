#include <stdio.h>
#include <stdlib.h> /* Permite usar "NULL" */
#include <string.h>
#include "Uteis.h"
#include "FilaPrioridade.h"
#include "Arvore.h"
#include "FilaArvore.h"

CodByte* novaCodByte(char* cod, char byte)
{
    CodByte* ret = (CodByte*) malloc(sizeof(CodByte));

    ret->byte = byte;
    ret->cod  = cod;

    return ret;
}

No* montarArvore(NoFila *fila, int qtdFila) {
    while(qtdFila >= 2) {
        No *primeiro = pop(&fila);
        No *segundo = pop(&fila);
        No *novo = (No*)malloc(sizeof(No));
        novo->esq = primeiro;
        novo->dir = segundo;
        novo->vezes = primeiro->vezes + segundo->vezes;
        novo->byte = '\0';
        novo->valido = False;
        fila = inserir(fila, novo);

        qtdFila--;
    }

    return pop(&fila);
}

CodByte* arvoreParaVetor(No *no, int qtd)
{
    CodByte *ret = (CodByte*)malloc(qtd * sizeof(CodByte));
    int acesso = 0;
    NoFilAr *filaTudo = NULL;
    NoFilAr *filaValida = NULL;
    enfileirar(&filaTudo, novaFilAr(no));
    char *atual = "\0";
    while(filaTudo) {
        NoFilAr *f = ultimo(filaTudo);
        atual = f->cod;
        char novo[strlen(atual) + 1];
        strcpy(novo, atual);

        if (f->dado->dir != NULL) {
            strcat(novo, "1");
            NoFilAr *n = novaFilAr(NULL);
            n->dado = f->dado->dir;

            n->cod = (char*) malloc((strlen(atual) + 1) * sizeof(char));
            strcpy(n->cod, novo);

            enfileirar(&filaTudo, n);
        }

        strcpy(novo, atual);

        if (f->dado->esq != NULL) {
            strcat(novo, "0");
            NoFilAr *n = novaFilAr(NULL);
            n->dado = f->dado->esq;

            n->cod = (char*) malloc((strlen(atual) + 1) * sizeof(char));
            strcpy(n->cod, novo);

            enfileirar(&filaTudo, n);
        }

        if (f->dado->valido == False) {
            desenfileirar(&filaTudo);
        } else {
            enfileirar(&filaValida, desenfileirar(&filaTudo));
        }

        {
            NoFilAr* t = filaTudo;

            while(t != NULL)
            {
                printf("%llu(%c) ", t->dado->vezes, t->dado->byte);
                t = t->prox;
            }

            printf("| ");

            t = filaValida;

            while(t != NULL)
            {
                printf("%llu(%c) ", t->dado->vezes, t->dado->byte);
                t = t->prox;
            }

            printf("\n");
        }
    }

    NoFilAr *per = filaValida;

    printf("\n\n");

    while(per != NULL) {
        printf("char %c: %s\n", (unsigned char)per->dado->byte, per->cod);
        per = per->prox;
    }
    //percorreArvore("\0", no, &ret, i);

    return ret;
}

static void percorreArvore(char *codAtual, No *noAtual, CodByte **vet, int* acesso)
{
    if(noAtual->esq == NULL && noAtual->dir == NULL)
        return;

    char codNovo[strlen(codAtual) + 2];
    strncpy(codNovo, codAtual, strlen(codAtual));
    codNovo[strlen(codAtual) + 1] = '\0';

    if (noAtual->valido) {
        *vet[*acesso] = *novaCodByte(codAtual, noAtual->byte);
        *acesso++;
    }
    if (noAtual->esq != NULL) {
        codNovo[strlen(codAtual)] = '0';
        percorreArvore(codNovo, noAtual->esq, vet, acesso);
    }
    if (noAtual->dir != NULL) {
        codNovo[strlen(codAtual)] = '1';
        percorreArvore(codNovo, noAtual->dir, vet, acesso);
    }
}
