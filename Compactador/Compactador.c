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

void compactar() {
    NoFila *fila;
    No *arvore;
    CodCab *codCab;
    int qtd;

    qtd = montarFila(&barra, path, &fila);
    //printarFila(fila);

    arvore = montarArvore(&barra, fila, qtd);
    codCab = arvoreParaVetor(&barra, arvore, qtd);

    escreverCompactador(&barra, path, codCab, strlen(codCab->cods[qtd - 1].cod), qtd);
    free(codCab);
}
void descompactar() {
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
        printf("Descompactando \"%s\"...\n\n", path);
        barra.y = ++y;
        descompactar();
    }
    else
    {
        printf("Compactando \"%s\"...\n\n", path);
        barra.y = ++y;
        compactar();
    }

    free(path);

    return 0;
}
