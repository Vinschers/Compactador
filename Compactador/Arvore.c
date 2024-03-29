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

No* montarArvore(Barra *b, NoFila *fila, inteiro qtdFila) {
    inteiro qtdOriginal = qtdFila;
    inteiro qtdNos = qtdFila;
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
    inteiro tamanhoNovo = 2 * strlen(*atual) + 1;
    char novo[tamanhoNovo];
    *atual = f->cod;

    strcpy(novo, *atual);

    if (f->dado->dir != NULL) {
        NoFilAr *n = novaFilAr(NULL);

        strcat(novo, "1");

        n->dado = f->dado->dir;
        n->cod = (char*) malloc(tamanhoNovo * sizeof(char));
        n->indice = f->indice * 2 + 2;
        strcpy(n->cod, novo);

        enfileirar(filaTudo, n);
    }

    strcpy(novo, *atual);

    if (f->dado->esq != NULL) {
        NoFilAr *n = novaFilAr(NULL);

        strcat(novo, "0");

        n->dado = f->dado->esq;
        n->cod = (char*) malloc(tamanhoNovo * sizeof(char));
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

int getAltura(No *no)
{
    inteiro ret = 0;

    if(no == NULL)
        return ret;

    {
        inteiro alEsq = getAltura(no->esq), alDir = getAltura(no->dir);

        if(alEsq > alDir)
            ret = alEsq + 1;
        else
            ret = alDir + 1;
    }

    return ret;
}

CodCab* arvoreParaVetor(Barra *b, No *no, inteiro qtd)
{
    CodByte *cods = (CodByte*)malloc(qtd * sizeof(CodByte));
    NoFilAr *filaTudo = NULL;
    NoFilAr *filaValida = NULL;
    inteiro i;
    inteiro tamVetor = (inteiro)pow(2, getAltura(no));
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

    {
        NoFilAr *per = filaValida;

        for(i = 0; per != NULL; i++) {
            cods[i] = *novaCodByte(per->cod, (unsigned char)per->dado->byte);
            per = per->prox;
        }
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

    printf("%i - %i\n", a->byte, a->valido);

    printarArv(a->dir);
}

No* montarArvoreBalanc(inteiro h, char *arvStr, unsigned char *bytes)
{
    No *raiz = novoNo();
    NoFilAr *fila = novaFilAr(raiz);
    inteiro i = 0;

    while(fila)
    {
        NoFilAr *fim = ultimo(fila);

        if(arvStr[fim->indice] == '1')
        {
            fim->dado->byte = bytes[i++];
            fim->dado->valido = True;
        }

        if(fim->h < h && fim->dado->valido == False)
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

No* arqParaArvore(char *path, inteiro *iniCompact, char *lixo, Barra *b)
{
    FILE *arqEntrada = NULL;
    unsigned char altura, lixAl;
    unsigned char *arvStr;
    inteiro qtdNos = 0;
    sInteiro qtdNosValidos = 0;
    uInteiro *coutB = (inteiro*)malloc(sizeof(inteiro));
    No *arv = NULL;

    avancarParte(b);

    abrir(&arqEntrada, path, "rb");

    *lixo = lerChar(arqEntrada);
    altura = lerChar(arqEntrada);

    qtdNosValidos = (sInteiro) lerChar(arqEntrada) + 1;

    qtdNos = (inteiro)(pow(2, altura) - 1);

    setMaxPorcentagem(b, qtdNos + 2 + qtdNosValidos);

    *coutB = 2;

    setPorcentagem(b, *coutB);

    {
        inteiro tamString = ((inteiro)ceil(qtdNos/8)) + 1, i;
        unsigned char string[tamString + 1]; /* possui lixo */
        arvStr = (char*)malloc((qtdNos + 2) * sizeof(char));

        arvStr[qtdNos] = '\0';

        fread(string, sizeof(char), tamString, arqEntrada);

        *coutB += qtdNos;
        setPorcentagem(b, *coutB);

        strcpy(arvStr, charsParaString(string, tamString));
    }

    {
        unsigned char bytes[qtdNosValidos + 1];

        fread(bytes, sizeof(char), qtdNosValidos, arqEntrada);

        *coutB += qtdNosValidos;
        setPorcentagem(b, *coutB);

        bytes[qtdNosValidos] = '\0';

        arv = montarArvoreBalanc((inteiro) altura, arvStr, bytes);
    }

    *iniCompact = ftell(arqEntrada);

    fclose(arqEntrada);

    free(coutB);

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

void destruirCodCab(CodCab *cc, inteiro qtd)
{
    if(cc == NULL || qtd <= 0)
        return;

    free(cc->cabecalho);

    {
        inteiro i;

        for(i = 0; i < qtd; ++i)
        {
            free(cc->cods[i].cod);
        }
    }

    free(cc->cods);
    free(cc);
}
