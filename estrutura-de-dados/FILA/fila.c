#include<stdlib.h>
#include<stdio.h>
#define MAX 4

struct fila{
    int dados[MAX];
    int inicio;
    int final;
    int qtd;
};
typedef struct fila* Fila;

Fila criar(){
    Fila f = malloc(sizeof(struct fila));
    if(f != NULL){
        f->inicio = 0;
        f->final = 0;
        f->qtd = 0;
    }
    return f;
}

int enfileirar(Fila f, int valor){
    if(f->qtd < MAX){
        f->dados[f->final] = valor;
        f->final = (f->final + 1) % MAX;
        f->qtd++;
        return 1;
    }
    return 0;
}

int desenfileirar(Fila f){
    if(f->qtd > 0){
        f->inicio = (f->inicio + 1) % MAX;
        f->qtd--;
        return 1;
    }
    return 0;       
}

int acessar_inicio(Fila f){
    if(f->qtd > 0){
        return f->dados[f->inicio];
    }
    return -1;
}

void destruir(Fila f){
    if(f != NULL) free(f);                      
}

void imprimir_fila(Fila f){
    for(int i = 0; i < MAX; i++){
        printf("[%d]", f->dados[i]);
    }
    printf("\n");
}

int main(){
    Fila f = criar();

    enfileirar(f, 20);
    enfileirar(f, 40);
    enfileirar(f, 60);
    enfileirar(f, 30);

    printf("\nInicio da fila: %d", acessar_inicio(f));

    desenfileirar(f);
    printf("\nInicio da fila: %d\n", acessar_inicio(f));

    if(enfileirar(f, 50)){
        printf("Enfileirou\n");
    } else {
        printf("Nao enfileirou\n");
    }

    return 0;
}