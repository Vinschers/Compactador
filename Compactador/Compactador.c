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
    char *ret = (char*)malloc(sizeof(char) * 256);
    printf("Digite o local do arquivo a ser compactado ou descompactado: ");
    scanf("%255s", ret);
    return ret;
}
int main(int qtdArgs, char *args[]) {
    /*
    if (qtdArgs > 1) {
        *path = *args[1];
    } else {
        path = get_path();
    }
    if (strstr(path, ".loli")) //extensao passivel de mudanca
        descompactar();
    else
        compactar();
    */
    mainTeste();

    return 0;
}

void print(NoFila no)
{
    while(no.prox != NULL)
    {
        printf("%i", no.dado->vezes);
        no = *no.prox;
    }

    printf("%i\n", no.dado->vezes);
}

/*
int mainTeste() {
    NoFila n = novaFila();
    NoFila* per = &n;
    No n1, n2, n3, n4, n5;

    n1.vezes = 1;
    n2.vezes = 2;
    n3.vezes = 3;
    n4.vezes = 4;
    n5.vezes = 5;

    inserir(&n, &n1);
    printf("%p\n",n);
    inserir(&n, &n2);
    printf("%p\n",n.prox);
    inserir(&n, &n3);
    printf("%p\n",n);
    inserir(&n, &n4);
    printf("%p\n",n);
    inserir(&n, &n5);
    printf("%p\n",n);

    return 0;
}
*/
