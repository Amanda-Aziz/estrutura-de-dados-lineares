#include <stdlib.h>

struct elem{
    int valor;
    struct  elem* prox;
    Elem* prox;
};
typedef struct elem Elem;
struct lista{
    int qtd;
    int inicio;
    Elem* prox; 
};
typedef struct lista* Lista;

Lista criar_lista(){
    Lista li = malloc(sizeof(struct lista));
    if(li != NULL){
        li->qtd=0;
        li->inicio=NULL;        
    }
    return li;
}

int inserir_inicio(Lista li, int valor_inserir){
    Elem* no = malloc(sizeof(Elem));
    if(no != NULL){
        no->valor = valor_inserir;
        no->prox = li->inicio;
        li->inicio =no;
        return 1;
    }
    return 0;
}

int inserir_final(Lista li, int valor_inserir){
    Elem* no = malloc(sizeof(Elem));
    if(no != NULL){
        no->valor = valor_inserir;
        no->prox = NULL;
        Elem* aux = li->inicio;
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        li->qtd++;
        return 1;
    }
    return 0;
}