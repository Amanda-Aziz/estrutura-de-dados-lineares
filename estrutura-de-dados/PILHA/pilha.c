// Implementação das funções da pilha

#include <stdlib.h>
#include "pilha.h"

struct pilha{
    int dados[MAX];
    int topo;
};

Pilha criar(){
    Pilha p = malloc(sizeof(struct pilha)); // alocando memória para a pilha
    if(p != NULL){ //Verifica se a alocação deu certo (se não for NULL inica topo com 0)
        p->topo = 0; //O operador '->' acessa o campo {topo} da estrutura apontada por p
    }
    return p;
}

int empilhar(Pilha p, int valor){
    if(p->topo < MAX){
        p->dados[p->topo] = valor;
        p->topo++;
        return 1;
    }
    return 0;
} 

int acessar_topo(Pilha p){
    if(p->topo == 0) // pilha vazia
    return p->dados[p->topo - 1]; // Retorna o último elemento
}

int desempilhar(Pilha p){
    if(p->topo == 0) // pilha vazia
        return 0;
    p->topo--; //diminui o topo (remove o último)
    return 1;
} 

void destruir(Pilha p) { //aqui liberamos a memoria
    if(p != NULL)
        free(p);
}