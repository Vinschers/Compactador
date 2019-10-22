#ifndef Uteis
#define Uteis
typedef enum {
    False, True
} boolean;

typedef struct No
{
    struct No *esq, *dir;
    unsigned long long int vezes;
    char byte;
} No;
#endif
