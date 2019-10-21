#include <string.h>
#include <stdlib.h>
#include "Uteis.h"
#include "Leitor.h"
#include "FilaPrioridade.h"

FILE *arq;
char *path;
NoFila fila;

void montarFila() {
    abrir(&arq, path, "r");
    int freq[256];
    int i;
    for (i = 0; i < 256; ++i)
        freq[i] = 0;
    while(!acabou(arq)) {
        char atual = lerChar(arq);
        freq[(int)atual]++;
        printf("%c", atual);
    }
    fila = novaFilaS();
    for (i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            No *n = (No*)malloc(sizeof(No));
            char c = (char)i;
            n->byte = c;
            n->vezes = freq[i];
            inserirS(&fila, n);
            free(n);
        }
    }
    NoFila* per = &fila;
    while(per != NULL)
    {
        printf("%c: %i\n", per -> dado -> byte, per->dado->vezes);
        per = per -> prox;
    }
}

void compactar() {
    montarFila();
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

int mainTeste() {
    NoFila n = novaFila();
    NoFila* per = &n;
    No n1, n2, n3, n4, n5;

    n1.vezes = 5;
    n2.vezes = 2;
    n3.vezes = 1;
    n4.vezes = 2;
    n5.vezes = 3;

    inserir(&n, &n1);
    printf("%i", n.dado->vezes);
    inserir(&n, &n2);
    printf("%i", n.dado->vezes);
    inserir(&n, &n3);
    printf("%i", n.dado->vezes);
    inserir(&n, &n4);
    printf("%i", n.dado->vezes);
    inserir(&n, &n5);
    printf("%i\n", n.dado->vezes);

    do
    {
        printf("%i ", per -> dado -> vezes);
        per = per -> prox;
    }
    while(per -> prox != NULL);

    return 0;
}
