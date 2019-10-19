#include <string.h>
#include "Leitor.h"

FILE *arq;
char *path;
int main(int qtdArgs, char *args[]) {
    if (qtdArgs > 1) {
        *path = *args[1];
    } else {
        path = "t.txt";
    }
    abrir(&arq, path, "r");
    while(!acabou(arq)) {
        printf("%c", lerChar(arq));
    }
    return 0;
}
