#include <string.h>
#include <stdlib.h>
#include "conio.h"
#include "Uteis.h"
#include "Leitor.h"
#include "FilaPrioridade.h"
#include "Bytizador.h"
#include "Arvore.h"
#include "Escrevedor.h"

#define extensao ".loli"

char *path;
Barra barra;

/* Compactar */
NoFila *fila = NULL;
No *arvore = NULL;
CodCab *codCab = NULL;
int qtd = 0;

/* Descompactar */
int *iniCompact;
char *qtdLixo;

void sairCompactar()
{
    destruirCodCab(codCab, qtd);
    destruirFilPri(fila);
    destruirArv(arvore);
}

void sairDescompactar()
{
    free(iniCompact);
    free(qtdLixo);
    destruirArv(arvore);
}

void compactar() {
    int i;
    atexit(sairCompactar);

    for (i = 0; i < 1; i++) {
        qtd = montarFila(&barra, path, &fila);

        arvore = montarArvore(&barra, fila, qtd);

        codCab = arvoreParaVetor(&barra, arvore, qtd);

        escreverCompactador(&barra, path, codCab, getAltura(arvore), qtd, extensao);
        printf("\n\n");
        resetarBarra(&barra);
    }
}

void descompactar()
{
    iniCompact = (int*) malloc(sizeof(int));
    qtdLixo = (char*) malloc(sizeof(char));

    atexit(sairDescompactar);

    arvore = arqParaArvore(path, iniCompact, qtdLixo);
    escreverDescompactador(arvore, path, extensao, *iniCompact, *qtdLixo);
}

char *get_path() {
    char *ret = (char*)malloc(sizeof(char) * 256);
    printf("Digite o local do arquivo a ser compactado ou descompactado: ");
    scanf("%255s", ret);
    return ret;
}
int main(int qtdArgs, char *args[]) {
    int y = 0;
    path = (char*)malloc(256 * sizeof(char));

    barra.parteAtual = -1;

    if (qtdArgs > 1) {
        path = args[1];
        printf("%s", path);
    } else {
        path = get_path();
        y++;
    }
    if (strstr(path, extensao))
    {
        printf("Descompactando \"%s\"...", path);
        barra.y = ++y;
        descompactar();
    }
    else
    {
        printf("Compactando \"%s\"...", path);
        barra.y = ++y;
        compactar();
    }

    printf("\n");

    free(path);

    return 0;
}
