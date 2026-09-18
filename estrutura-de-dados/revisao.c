#include <stdio.h>
#include <stdlib.h>

/* ===================================================================
   exemplo_stack()
   Demonstra uma variável LOCAL (stack).
   - x é criada na pilha de execução (stack) quando a função é chamada
   - &x mostra o endereço de memória onde x está guardada
   - Quando a função termina, esse espaço de memória deixa de ser válido
   =================================================================== */
void exemplo_stack(){
    int x = 10;
    printf("exemplo_stack() Valor de x: %d Endereco de x: %p\n", x, &x);
}

/* ===================================================================
   alterar_valor(int x) -> PASSAGEM POR VALOR
   - O parâmetro x é uma CÓPIA do valor passado na chamada
   - Alterar x aqui dentro NÃO afeta a variável original do main
   - Prova: o endereço (&x) impresso aqui é DIFERENTE do endereço
     da variável x lá no main -> são variáveis diferentes, mesmo nome
   =================================================================== */
void alterar_valor(int x){
    x = 20;
    printf("Dentro alterar_valor() Valor de x: %d Endereco de x: %p\n", x, &x);
}

/* ===================================================================
   alterar_ponteiro(int *x) -> PASSAGEM POR REFERÊNCIA
   - x aqui é um PONTEIRO: guarda um endereço de memória
   - *x = 20 significa "vá até o endereço guardado em x e escreva 20 lá"
     (operador de desreferenciação)
   - Como recebemos o ENDEREÇO da variável do main (&x na chamada),
     a alteração é REAL e persiste depois que a função termina
   - Essa técnica é usada o tempo todo em listas/pilhas/filas, quando
     uma função precisa alterar algo "de fora" (ex: o ponteiro cabeça)
   =================================================================== */
void alterar_ponteiro(int *x){
    *x = 20;
    printf("Dentro alterar_ponteiro() Valor de x: %d Endereco de x: %p\n", *x, x);
}

/* ===================================================================
   retorno_incorreto() -> ERRO CLÁSSICO (dangling pointer)
   - x é uma variável LOCAL, vive na stack desta função
   - A função retorna o ENDEREÇO dessa variável local (&x)
   - PROBLEMA: assim que a função termina, x deixa de existir
     (a memória pode ser reaproveitada por outras chamadas)
   - O ponteiro retornado aponta para memória que NÃO é mais garantida
   - Isso é chamado de "dangling pointer" (ponteiro pendurado)
   - Pode até "funcionar" por sorte, mas é COMPORTAMENTO INDEFINIDO
   =================================================================== */
int* retorno_incorreto(){
    int x = 30;
    printf("Dentro retorno_incorreto() Valor de x: %d Endereco de x: %p\n", x, &x);
    return &x;
}

/* ===================================================================
   criar_numero(int valor) -> FORMA CORRETA de retornar um ponteiro
   - Em vez de criar a variável na stack, usamos malloc para reservar
     espaço no HEAP (memória dinâmica)
   - malloc(sizeof(int)) pede espaço suficiente para guardar 1 int
     e devolve um ponteiro para esse espaço
   - *p = valor escreve o valor recebido nesse espaço
   - O HEAP não é destruído quando a função termina (diferente da stack)
     -> o ponteiro retornado continua VÁLIDO depois da função acabar
   - IMPORTANTE: essa memória é responsabilidade do programador.
     Só é liberada quando chamamos free() manualmente.
     Se esquecer -> memory leak (vazamento de memória)
   =================================================================== */
int* criar_numero(int valor){
    int *p = malloc(sizeof(int));
    *p = valor;
    return p;
}

int main(){
    exemplo_stack();

    int x = 10; // variável local usada nos testes de valor/referência

    printf("Antes alterar_valor() Valor de x: %d Endereco de x: %p\n", x, &x);
    alterar_valor(x); // passa CÓPIA de x -> não altera o x do main
    printf("Depois alterar_valor() Valor de x: %d Endereco de x: %p\n", x, &x);
    // x continua 10, pois alterar_valor só mexeu na cópia local dela

    alterar_ponteiro(&x); // passa o ENDEREÇO de x -> altera o x real
    printf("Depois alterar_ponteiro() Valor de x: %d Endereco de x: %p\n", x, &x);
    // agora x é 20, porque a função mexeu diretamente na memória de x

    // p recebe o ponteiro (INVÁLIDO) retornado por retorno_incorreto()
    int *p = retorno_incorreto();
    printf("Depois retorno_incorreto() Valor de p: %d Endereco de p: %p\n", *p, p);
    // *p pode até imprimir 30 "por sorte", mas isso é comportamento
    // indefinido - a memória apontada por p não é mais garantidamente válida

    // q recebe o ponteiro (VÁLIDO) retornado por criar_numero(),
    // alocado dinamicamente no heap
    int *q = criar_numero(50);
    printf("Depois criar_numero() Valor de q: %d Endereco de q: %p\n", *q, q);

    free(q); // libera a memória alocada com malloc - evita memory leak
    // obs: não existe free(p) porque p nunca foi alocado corretamente
    // com malloc, então não seria válido/seguro liberar aquele endereço

    return 0;
}