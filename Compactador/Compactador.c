#include <string.h>
#include <stdlib.h>
#include "conio.h"
#include "Uteis.h"
#include "Leitor.h"
#include "FilaPrioridade.h"
#include "Bytizador.h"
#include "Arvore.h"
#include "Escrevedor.h"

char *path;
Barra barra;

/* Compactar */
NoFila *fila = NULL;
No *arvore = NULL;
CodCab *codCab = NULL;
int qtd = 0;

void sairCompactar()
{
    destruirCodCab(codCab, qtd);
    destruirFilPri(fila);
    destruirArv(arvore);
}

void sairDescompactar()
{
    destruirArv(arvore);
}

void compactar() {
    atexit(sairCompactar);

    qtd = montarFila(&barra, path, &fila);

    arvore = montarArvore(&barra, fila, qtd);
    codCab = arvoreParaVetor(&barra, arvore, qtd);

    escreverCompactador(&barra, path, codCab, strlen(codCab->cods[qtd - 1].cod), qtd);
}

void descompactar()
{
    atexit(sairDescompactar);
    arvore = arqParaArvore(path);
    escreverDescompactador(arvore, path);
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
    if (strstr(path, ".loli")) //extensao passivel de mudanca
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
