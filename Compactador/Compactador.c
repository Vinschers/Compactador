#include <string.h>
#include <stdlib.h>
#include "Uteis.h"
#include "Leitor.h"
#include "FilaPrioridade.h"
#include "Bytizador.h"
#include "Arvore.h"

FILE *arq;
char *path;
NoFila *fila;
No *arvore;
CodByte *cods;

void compactar() {
    abrir(&arq, path, "rb");
    int qtd = montarFila(arq, &fila);
    printarFila(fila);
    arvore = montarArvore(fila, qtd);
    cods = arvoreParaVetor(arvore, qtd);
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
    arvore = NULL;
    if (qtdArgs > 1) {
        *path = *args[1];
    } else {
        path = get_path();
    }
    if (strstr(path, ".loli")) //extensao passivel de mudanca
        descompactar();
    else
        compactar();
    return 0;
}
