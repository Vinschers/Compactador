#ifndef FilaPrioridade
#define FilaPrioridade

typedef struct NoFila
{
    struct NoFila* prox;
    No* no;
} NoFila;

extern void Inserir(No novo);

typedef struct
{

} FilaPri;

#endif /* FilaPrioridade 57 */
