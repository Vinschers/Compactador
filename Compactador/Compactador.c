#include <string.h>
#include <stdlib.h>
#include "Uteis.h"
#include "Leitor.h"
#include "FilaPrioridade.h"
#include "Bytizador.h"
#include "Arvore.h"
#include "Escrevedor.h"

char *path;

void compactar() {
    FILE *arqEnt, *arqSai;
    NoFila *fila;
    No *arvore;
    CodByte *cods;
    int qtd;

    abrir(&arqEnt, path, "rb");
    qtd = montarFila(arqEnt, &fila);
    printarFila(fila);
    arvore = montarArvore(fila, qtd);
    cods = arvoreParaVetor(arvore, qtd);
    abrir(&arqSai, strcat(path, ".loli"), "wb");
    escreverCompactador(arqEnt, arqSai, cods, arvore, qtd);

    fclose(arqEnt);
    fclose(arqSai);
}
void descompactar() {
    //
}

char *get_path() {
    char *ret = (char*)malloc(sizeof(char) * 256);
    printf("Digite o local do arquivo a ser compactado ou descompactado: ");
    scanf("%255s", ret);
    return ret;
}
int main(int qtdArgs, char *args[]) {
    path = (char*)malloc(128 * sizeof(char));

    if (qtdArgs > 1) {
        *path = *args[1];
    } else {
        path = get_path();
    }
    if (strstr(path, ".loli")) //extensao passivel de mudanca
        descompactar();
    else
        compactar();

    free(path);

    return 0;
}
