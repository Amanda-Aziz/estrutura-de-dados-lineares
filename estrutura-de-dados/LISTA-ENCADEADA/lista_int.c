#include<stdlib.h>

struct elem{
    int valor;
    Elem* prox;
};
typedef struct elem Elem;

struct lista{
    int qtd;
    Elem* inicio;
};
typedef struct lista* Lista;

// metodos

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

int remover_inicio(Lista li){
    if(li->qtd == 0) return 0;
    Elem* aux = li->inicio;
    li->inicio = aux->prox;
    free(aux);
    li->qtd--;
    return 1;
}

int acessar_inicio(Lista li){
    if(li->qtd == 0) return 0;
    return li->inicio->valor;
}

void destruir(Lista li){
    if(li == NULL) return;
    Elem* aux = li->inicio;
    while(aux->prox != NULL){
        Elem* atual = aux;
        aux = aux->prox;
        free(atual);
    }
    free(aux);
    free(li);
}

int remover_final(Lista li){
    if(li->qtd == 0) return 0;
    Elem* aux = li->inicio;
    if(aux->prox == NULL){
        free(aux);
        li->inicio = NULL;
        li->qtd--;
        return 1;
    }
    Elem* ant;
    while(aux->prox != NULL){
        ant = aux;
        aux = aux->prox;
    }
    free(aux);
    ant->prox = NULL;
    li->qtd--;
    return 1;
}

int acessar_final(Lista li){
    if(li->qtd == 0){
        return 0;
    }
    Elem* aux = li->inicio;
    
    while(aux->prox != NULL){
        aux = aux->prox;
    }
    return aux->valor;
}

int buscar_por_valor(Lista li, int valor){
    Elem* aux = li->inicio;
    int posicao = 0;

    while(aux != NULL){
         if(aux->valor == valor){
            return posicao;
         }
         aux = aux->prox;
         posicao++;
    }

    return 0;
}

int buscar_por_posicao(Lista li, int posicao){
    if(posicao < 0 || posicao >= li->qtd){
        return 0;
    }
    Elem* aux = li->inicio;

    for(int i=0; i < posicao; i++){
        aux = aux->prox;
    }

    return aux->valor;
}