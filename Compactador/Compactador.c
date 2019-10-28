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
    NoFila *fila;
    No *arvore;
    CodCab *codCab;
    int qtd;

    qtd = montarFila(path, &fila);
    printarFila(fila);

    arvore = montarArvore(fila, qtd);
    codCab = arvoreParaVetor(arvore, qtd);

    escreverCompactador(path, codCab, strlen(codCab->cods[qtd - 1].cod), qtd);
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
    path = (char*)malloc(256 * sizeof(char));

    if (qtdArgs > 1) {
        path = args[1];
        printf("%s", path);
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
