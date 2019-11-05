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
        printf("%i\n", (*filaValida)->indice);
    }
}

int getAltura(No *no)
{
    int ret = 0;

    if(no == NULL)
        return ret;

    {
        int alEsq = getAltura(no->esq), alDir = getAltura(no->dir);

        if(alEsq > alDir)
            ret = alEsq + 1;
        else
            ret = alDir + 1;
    }

    return ret;
}

CodCab* arvoreParaVetor(Barra *b, No *no, int qtd)
{
    CodByte *cods = (CodByte*)malloc(qtd * sizeof(CodByte));
    NoFilAr *filaTudo = NULL;
    NoFilAr *filaValida = NULL;
    int i;
    int tamVetor = (int)pow(2, getAltura(no));
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

        //setPorcentagem(b, i++);
    }

    inverterFila(&filaValida);

    NoFilAr *per = filaValida;

    for(i = 0; per != NULL; i++) {
        cods[i] = *novaCodByte(per->cod, (unsigned char)per->dado->byte);
        per = per->prox;
    }

    destruirFilAr(filaTudo);
    destruirFilAr(filaValida);

    {
        CodCab* ret = (CodCab*) malloc(sizeof(CodCab));

        ret->cods = cods;
        ret->cabecalho = (char*)malloc(sizeof(char) * tamVetor);

        strcpy(ret->cabecalho, arvVetor);

        return ret;
    }
}

void printarArv(No *a)
{
    if (a == NULL)
        return;

    printarArv(a->esq);

    printf("%c - %i\n", a->byte, a->valido);

    printarArv(a->dir);
}

No* montarArvoreBalanc(int h, char *arvStr, char *bytes)
{
    No *raiz = novoNo();
    NoFilAr *fila = novaFilAr(raiz);

    while(fila)
    {
        NoFilAr *fim = ultimo(fila);

        if(arvStr[fim->indice] == '1')
        {
            fim->dado->byte = bytes[0];
            fim->dado->valido = True;

            strcpy(bytes, &bytes[1]);
        }

        if(fim->h < h)
        {
            NoFilAr *esq = novaFilAr(novoNo());
            NoFilAr *dir = novaFilAr(novoNo());

            fim->dado->esq = esq->dado;
            fim->dado->dir = dir->dado;

            esq->h = fim->h + 1;
            dir->h = fim->h + 1;
            esq->indice = fim->indice * 2 + 1;
            dir->indice = fim->indice * 2 + 2;

            enfileirar(&fila, dir);
            enfileirar(&fila, esq);
        }

        desenfileirar(&fila);
    }

    destruirFilAr(fila);

    return raiz;
}

No* arqParaArvore(char *path, int *iniCompact, char *lixo)
{
    FILE *arqEntrada = NULL;
    char altura, lixAl;
    char *arvStr;
    short int qtdNos = 0, qtdNosValidos = 0;
    No *arv = NULL;

    abrir(&arqEntrada, path, "rb");

    lixAl = lerChar(arqEntrada);

    *lixo = lixAl >> 4;

    lixAl = lixAl << 4;
    lixAl = lixAl >> 4;
    altura = lixAl + 1;

    qtdNos = (int)(pow(2, altura) - 1);
    qtdNosValidos = (short int) lerChar(arqEntrada) + 1;

    {
        arvStr = (char*)malloc((qtdNos + 1) * sizeof(char));
        char string[(int)ceil(qtdNos/8)]; /* possui lixo */

        arvStr[qtdNos] = '\0';

        fread(string, sizeof(char), sizeof(arvStr), arqEntrada);

        strncpy(arvStr, charsParaString(string), qtdNos);
    }

    {
        char bytes[qtdNosValidos + 1];

        fread(bytes, sizeof(char), qtdNosValidos, arqEntrada);

        bytes[qtdNosValidos] = '\0';

        printf("\n");
        arv = montarArvoreBalanc((int) altura, arvStr, bytes);
    }

    *iniCompact = ftell(arqEntrada);

    fclose(arqEntrada);

    return arv;
}

void destruirArv(No *no)
{
    if(no == NULL)
        return;

    if(no->dir != NULL)
        destruirArv(no->dir);

    if(no->esq != NULL)
        destruirArv(no->esq);

    free(no);
}

void destruirCodCab(CodCab *cc, int qtd)
{
    if(cc == NULL || qtd <= 0)
        return;

    free(cc->cabecalho);

    {
        int i;

        for(i = 0; i < qtd; i++)
            free(cc->cods[i].cod);
    }

    free(cc->cods);
    free(cc);
}
