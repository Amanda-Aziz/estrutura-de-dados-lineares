// Cabeçalho com declarações

#define MAX 4
typedef struct pilha* Pilha;

Pilha criar();

int empilhar(Pilha p, int valor);

int acessar_topo(Pilha p);

int desempilhar(Pilha p);
// free
void destruir(Pilha p);