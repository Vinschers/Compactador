#include <stdio.h>
#include <stdlib.h> /* Permite usar "NULL" */
#include <string.h>
#include <Math.h>
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

No* montarArvore(Barra *b, NoFila *fila, int qtdFila) {
    int qtdOriginal = qtdFila;
    int qtdNos = qtdFila;
    avancarParte(b);
    setMaxPorcentagem(b, qtdFila - 1);
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
        qtdNos++;
        setPorcentagem(b, qtdOriginal - qtdFila);
    }

    setMaxPorcentagem(b, qtdNos);

    return pop(&fila);
}

/*
No* montarArvore(NoFila *fila, int qtdFila) {
    No arv[(int)pow(2, (ceil(log2(qtdFila)) + 1) - 1)];
    int i;

    for(i = 0; qtdFila >= 2; i++) {
        No *primeiro = pop(&fila);
        No *segundo = pop(&fila);
        No *novo = (No*)malloc(sizeof(No));

        novo->vezes = primeiro->vezes + segundo->vezes;
        novo->byte = '\0';
        novo->valido = False;

        arv[i] = *novo;
        arv[2 * i + 1] = *primeiro;
        arv[2 * i + 2] = *segundo;

        free(novo);
        free(primeiro);
        free(segundo);

        qtdFila--;
    }

    return arv;
}
*/

void adicionaNaFila(NoFilAr **filaTudo, NoFilAr **filaValida, NoFilAr *f, char **atual)
{
    *atual = f->cod;
    char novo[strlen(*atual) + 1];
    strcpy(novo, *atual);

    if (f->dado->dir != NULL) {
        NoFilAr *n = novaFilAr(NULL);

        strcat(novo, "1");

        n->dado = f->dado->dir;
        n->cod = (char*) malloc((strlen(*atual) + 1) * sizeof(char));
        n->indice = f->indice * 2 + 2;
        strcpy(n->cod, novo);

        enfileirar(filaTudo, n);
    }

    strcpy(novo, *atual);

    if (f->dado->esq != NULL) {
        NoFilAr *n = novaFilAr(NULL);

        strcat(novo, "0");

        n->dado = f->dado->esq;
        n->cod = (char*) malloc((strlen(*atual) + 1) * sizeof(char));
        n->indice = f->indice * 2 + 1;
        strcpy(n->cod, novo);

        enfileirar(filaTudo, n);
    }

    if (f->dado->valido == False) {
        desenfileirar(filaTudo);
    } else {
        enfileirar(filaValida, desenfileirar(filaTudo));
    }
}

CodCab* arvoreParaVetor(Barra *b, No *no, int qtd)
{
    CodByte *cods = (CodByte*)malloc(qtd * sizeof(CodByte));
    NoFilAr *filaTudo = NULL;
    NoFilAr *filaValida = NULL;
    int i;
    int tamVetor = (int)pow(2, (ceil(log2(qtd)) + 1));
    char *atual = "\0";
    char arvVetor[tamVetor];

    avancarParte(b);

    for(i = 0; i < tamVetor; i++)
        arvVetor[i] = '0';

    arvVetor[tamVetor - 1] = '\0';

    enfileirar(&filaTudo, novaFilAr(no));

    i = 1;

    while(filaTudo)
    {
        NoFilAr *fim = ultimo(filaTudo);

        arvVetor[fim->indice] = fim->dado->valido ? '1' : '0';

        adicionaNaFila(&filaTudo, &filaValida, fim, &atual);

        setPorcentagem(b, i++);
    }

    inverterFila(&filaValida);

    NoFilAr *per = filaValida;

        for(i = 0; per != NULL; i++) {
            cods[i] = *novaCodByte(per->cod, (unsigned char)per->dado->byte);
            per = per->prox;
        }

    {
        CodCab* ret = (CodCab*) malloc(sizeof(CodCab));

        ret->cods = cods;
        ret->cabecalho = (char*)malloc(sizeof(char) * tamVetor);

        strcpy(ret->cabecalho, arvVetor);

        return ret;
    }

    //return ret;
}
