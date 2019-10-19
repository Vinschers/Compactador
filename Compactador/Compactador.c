#include <string.h>
#include "Leitor.h"
#include "FilaPrioridade.h"

FILE *arq;
char *path;
NoFila *fila;

void montarFila() {
    abrir(&arq, path, "r");
    while(!acabou(arq)) {
        char atual = lerChar(arq);
        printf("%c", atual);
    }
}

void compactar() {
    montarFila();
}
void descompactar() {
    //
}

char *get_path() {
    char *ret;
    printf("Digite o local do arquivo a ser compactado ou descompactado: ");
    scanf("%s", ret);
    return ret;
}
int main(int qtdArgs, char *args[]) {
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
