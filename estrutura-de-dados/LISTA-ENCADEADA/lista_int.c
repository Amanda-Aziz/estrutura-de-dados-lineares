#include<stdlib.h>

struct elem{
    int valor;
    struct elem* prox;
};
typedef struct elem Elem;

struct lista{
    int qtd;
    Elem* inicio;
};
typedef struct lista* Lista;

// =================================================== MÉTODOS

Lista criar_lista(Lista li){
    Lista li = malloc(sizeof(struct lista));
    if(li != NULL){
        li->qtd = 0;
        li->inicio = NULL;
    }
    return li;
}

int inserir_inicio(Lista li, int valor_inserir){
    Elem* no = malloc(sizeof(Elem));
    if(no != NULL){
        no->valor = valor_inserir;
        no->prox = li->inicio;
        li->inicio = no;
        li->qtd++;
        return 1;
    } 
    return 0;
}

int inserir_final(Lista li, int valor_inserir){
    Elem* no = malloc(sizeof(Elem));
    if(no != NULL){
        no->valor = valor_inserir;
        no->prox = NULL;
        if(li->inicio == NULL){
            li->inicio = no;
            li->qtd++;
            return 1;
        }
        Elem* aux = li->inicio;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        li->qtd++;
        return 1;
    }
    return 0;
}

int remover_inicio(Lista li){ //acessar lista, acessar inicio, remover inicio
    if(li->qtd == 0){
        return 0;
    }
    Elem* aux = li->inicio;
    li->inicio = aux->prox;
    free(aux);
    li->qtd--;
}

int acessar_inicio(Lista li){
    if(li->qtd == 0){
        return 0;
    }
    return li->inicio->valor;
}

void destruir(Lista li){
    //...
}

void imprimir_lista(Lista li){}
void remover_final(){}
int acessar_final(){}
void buscar_por_valor(){}
void buscar_por_posicao(){}