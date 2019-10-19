#include <string.h>
#include <stdlib.h>
#include "Uteis.h"
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