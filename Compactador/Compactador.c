#include <stdlib.h>
#include "Uteis.h"
#include "Leitor.h"
#include "FilaPrioridade.h"

int main() {
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
