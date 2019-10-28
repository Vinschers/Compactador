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
    boolean valido;
} No;

typedef struct
{
    char atual;
    unsigned int porcentagem[2];
    int y;
    int parteAtual;
} Barra;

extern No* novoNo();
extern void avancarSimboloBarra(Barra *b);
extern void setMaxPorcentagem(Barra *b, unsigned int m);
extern void setPorcentagem(Barra *b, unsigned int p);
extern void avancarParte(Barra *b);
void limparLinha();
#endif
