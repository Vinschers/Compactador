#ifndef Uteis
#define Uteis
typedef enum {
    False, True
} boolean;
typedef struct No
{
    struct No *esq, *dir;
    int vezes;
    char byte;
} No;
#endif
