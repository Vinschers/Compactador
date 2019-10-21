#include <string.h>
#include <stdlib.h>
#include "Uteis.h"
#include "Leitor.h"
#include "FilaPrioridade.h"
#include "Bytizador.h"

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
    //mainTeste();

    char* byte = (char*) malloc(8*sizeof(char));
    int i;
    char b;

    byte[0] = '0';
    byte[1] = '0';
    byte[2] = '0';
    byte[3] = '1';
    byte[4] = '1';
    byte[5] = '0';
    byte[6] = '1';
    byte[7] = '0';

    printf("%c", byte[0]);

    b = paraByte(byte);

    for (i = 0; i < 8; i++) {
        printf("%d", !!((b << i) & 0x80));
    }

    return 0;
}

/*
void print(NoFila no)
{
    while(no.prox != NULL)
    {
        printf("%i", no.dado->vezes);
        no = *no.prox;
    }

    printf("%i\n", no.dado->vezes);
}

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
