#include <stdio.h>
#include <stdlib.h>
#define MAX 4 

struct fila{
    int dados[MAX]; //   [0][1][2][3]
    int inicio, final;
};
typedef struct fila* Fila;

Fila criar(){
    Fila f = malloc(sizeof(struct fila)); 
    if(f != NULL){ 
        f->inicio = 0;
        f->final = 0;
    }
    return f;
}

int enfileirar(Fila f,int valor){
    if(f->final < MAX){
        f->dados[f->final] = valor; //comentar...
        f->final++;
        return 1;
    }
    return 0;
}

int desenfileirar(Fila f){
    if(f->final > 0){
        f->inicio++;
        return 1;
    }
    return 0;
}

int acessar_inicio(Fila f){
    if(f->final > 0){
        return f->dados[f->inicio];
    }
    return 0;
}

void destruir(Fila f){
    if(f != NULL)
        free(f);
}

int main(){
    Fila f = criar();

    enfileirar(f, 20);
    enfileirar(f, 40);
    enfileirar(f, 60);
    enfileirar(f, 30);

    printf("\nInicio da fila: %d", acessar_inicio(f));

    desenfileirar(f); //
    printf("\nInicio da fila: %d", acessar_inicio(f));

    if(enfileirar(f, 50)){
        printf("\nEnfileirou\n");
    } else {
        printf("\nNao enfileirou\n");
    }

    return 0;
}