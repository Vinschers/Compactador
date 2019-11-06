#ifndef Uteis
#define qtdIdeal 1024
#define Uteis
typedef enum {
    False, True
} boolean;

typedef struct No
{
    struct No *esq, *dir;
    unsigned long long int vezes;
    unsigned char byte;
    boolean valido;
} No;

typedef struct
{
    char atual;
    unsigned int porcentagem[2];
    int y;
    int parteAtual;
    char modo;
} Barra;

extern No* novoNo();
extern void avancarSimboloBarra(Barra *b);
extern void setMaxPorcentagem(Barra *b, unsigned int m);
extern void setPorcentagem(Barra *b, unsigned int p);
extern void avancarParte(Barra *b);
extern void resetarBarra(Barra *b);
extern void setModo(Barra *b, char modo);
#endif
