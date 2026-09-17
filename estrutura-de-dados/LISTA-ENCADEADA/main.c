#include"pilha.h"
#include<stdio.h>

int main(){
    int valor;
    printf("Valor: ");
    scanf("%d", &valor);
    criar_lista(&valor);
    return 0;
}