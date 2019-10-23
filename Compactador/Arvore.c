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
    NoPilha *pilha = NULL;
    pilha = empilhar(pilha, novaPilha(no));
    char *atual = "\0";
    while(pilha) {
        NoPilha *p = pilha;
        atual = p->cod;
        char *novo = (char*)malloc(strlen(atual) * sizeof(char) + 1);
        strcpy(novo, atual);
        if (p->dado->esq != NULL) {
            strcat(novo, "0");
            NoPilha *n = novaPilha(NULL);
            n->dado = pilha->dado->esq;
            n->cod = novo;
            pilha = empilhar(pilha, n);
        }
        if (p->dado->dir != NULL) {
            strcat(novo, "1");
            NoPilha *n = novaPilha(NULL);
            n->dado = pilha->dado->dir;
            n->cod = "";
            pilha = empilhar(pilha, n);
        }
        if (!pilha->dado->valido) {
            pilha = desempilhar(pilha);
        }
    }
    //pilha = inverterPilha(pilha);
    NoPilha *per = pilha;
    while(per != NULL) {
        printf("char %d: %s", (unsigned char)per->dado->byte, per->cod);
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
