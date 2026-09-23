# Lista de Exercícios: Pilhas

## 1. O que é e para que serve uma pilha?

Uma **pilha** é uma estrutura de dados linear que segue o princípio
**LIFO (Last In, First Out)**, ou seja, o **último elemento inserido é o
primeiro elemento a ser removido**.

As operações principais de uma pilha são:

-   **Inserção (`push`):** adiciona um elemento no topo da pilha.
-   **Remoção (`pop`):** remove o elemento que está no topo.
-   **Acesso ao topo (`top`):** consulta o elemento que está no topo sem
    removê-lo.

Exemplo:

``` text
        Topo
         ↓
       [30] ← remove primeiro
       [20]
       [10]
```

Se o elemento `40` for inserido:

``` text
        Topo
         ↓
       [40]
       [30]
       [20]
       [10]
```

Caso seja realizada uma remoção, o `40` será o primeiro elemento
retirado.

Portanto, uma pilha é útil quando precisamos trabalhar com elementos na
ordem **LIFO**.

------------------------------------------------------------------------

## 2. Em que situações uma pilha pode ser utilizada?

Uma pilha pode ser utilizada em diversas situações em que o último
elemento inserido precisa ser o primeiro a ser processado.

Alguns exemplos são:

-   **Desfazer ações:** editores de texto utilizam pilhas para
    implementar operações de `desfazer` e `refazer`.
-   **Histórico de navegação:** páginas visitadas podem ser armazenadas
    para permitir o retorno à página anterior.
-   **Chamadas de funções:** o sistema utiliza uma estrutura semelhante
    a uma pilha para controlar chamadas e retornos de funções.
-   **Avaliação de expressões:** pilhas podem ser utilizadas para
    avaliar expressões matemáticas.
-   **Verificação de parênteses:** uma pilha pode verificar se os
    parênteses de uma expressão estão corretamente abertos e fechados.
-   **Algoritmos de busca:** estruturas de pilha podem ser utilizadas em
    algoritmos como a busca em profundidade (**DFS**).
-   **Inversão de elementos:** como o último elemento inserido é o
    primeiro a sair, uma pilha pode ser usada para inverter sequências.

------------------------------------------------------------------------

## 3. Dadas as operações de pilha insere `I` e remove `R`, escreva a configuração final da pilha após as seguintes operações

``` text
I(10), I(20), R, I(30), I(45), I(21), R, R, I(50), I(60), R, I(70), R
```

### Resolução

Na pilha, a inserção e a remoção acontecem sempre pelo **topo**.

``` text
I(10) → [10]

I(20) → [10, 20]

R     → [10]

I(30) → [10, 30]

I(45) → [10, 30, 45]

I(21) → [10, 30, 45, 21]

R     → [10, 30, 45]

R     → [10, 30]

I(50) → [10, 30, 50]

I(60) → [10, 30, 50, 60]

R     → [10, 30, 50]

I(70) → [10, 30, 50, 70]

R     → [10, 30, 50]
```

### Resposta

A configuração final da pilha é:

``` text
Topo
 ↓
[50]
[30]
[10]
```

Ou, representando da base para o topo:

``` text
[10, 30, 50]
```

------------------------------------------------------------------------

## 4. Escreva um programa que utilize uma pilha para verificar se expressões aritméticas estão com a parentização correta

O programa deve verificar se cada **abre parênteses `(`** possui um
**fecha parênteses `)`** correspondente.

A ideia é utilizar uma pilha da seguinte maneira:

1.  Percorrer a expressão da esquerda para a direita.
2.  Quando encontrar um `(`, colocá-lo na pilha.
3.  Quando encontrar um `)`, verificar se existe um `(` correspondente
    no topo da pilha.
4.  Se existir, remover o `(` da pilha.
5.  Se aparecer um `)` quando a pilha estiver vazia, a expressão está
    incorreta.
6.  Ao terminar a expressão, a pilha precisa estar vazia.

### Exemplo

Expressão correta:

``` text
( ( ) )
```

Processo:

``` text
( → empilha
( → empilha
) → desempilha
) → desempilha

Pilha final → vazia
```

Portanto, a expressão está correta.

### Implementação em C

Considerando uma pilha de caracteres:

``` c
int parenteses_corretos(char expressao[]) {

    Pilha p = criar_pilha();

    for (int i = 0; expressao[i] != '\0'; i++) {

        if (expressao[i] == '(') {

            inserir(p, '(');

        } else if (expressao[i] == ')') {

            if (esta_vazia(p)) {
                destruir(p);
                return 0;
            }

            remover(p);
        }
    }

    int correto = esta_vazia(p);

    destruir(p);

    return correto;
}
```

A função pode retornar:

``` text
1 → expressão correta
0 → expressão incorreta
```

### Exemplos

#### Expressões corretas

``` text
( ( ) )
( ( )( ) )
( ) ( )
```

#### Expressões incorretas

``` text
)( 
( ( ) (
) ) ( (
```

Por exemplo, para:

``` text
( ( ) (
```

ao final da análise ainda haverá um `(` na pilha. Isso significa que
existe um parêntese aberto sem o respectivo fechamento.

------------------------------------------------------------------------

## 5. Desenvolva uma função para inverter a posição dos elementos de uma pilha P

A função deve fazer com que o elemento que estava no topo passe para a
base e o elemento que estava na base passe para o topo.

Por exemplo:

``` text
Antes:

Topo
 ↓
[40]
[30]
[20]
[10]
```

Depois:

``` text
Topo
 ↓
[10]
[20]
[30]
[40]
```

Uma forma de realizar a inversão é utilizando uma **pilha auxiliar**.

``` c
void reverso(Pilha p) {

    Pilha auxiliar = criar_pilha();

    while (!esta_vazia(p)) {
        inserir(auxiliar, remover(p));
    }

    while (!esta_vazia(auxiliar)) {
        inserir(p, remover(auxiliar));
    }

    destruir(auxiliar);
}
```

### Observação

A primeira etapa retira os elementos da pilha original e coloca-os na
pilha auxiliar.

``` text
Pilha original:

[40]
[30]
[20]
[10]

        ↓

Pilha auxiliar:

[10]
[20]
[30]
[40]
```

Ao transferir os elementos novamente, a ordem é invertida.

> **Observação:** dependendo da implementação da pilha utilizada na
> disciplina, os nomes das funções podem ser diferentes, como `push`,
> `pop`, `empilhar`, `desempilhar`, `inserir` ou `remover`.

------------------------------------------------------------------------

## 6. Considere uma pilha que armazene caracteres. Escreva uma função que verifique se uma palavra é um palíndromo

Um **palíndromo** é uma palavra que permanece igual quando lida da
esquerda para a direita ou da direita para a esquerda.

Exemplos:

``` text
ARARA
RADAR
ANA
OSSO
```

Uma pilha pode ser utilizada porque, ao inserir os caracteres na ordem
original, eles serão retirados na ordem inversa.

### Exemplo

Para a palavra:

``` text
ARARA
```

A pilha será preenchida com:

``` text
Topo
 ↓
[A]
[R]
[A]
[R]
[A]
```

Ao remover os elementos, obteremos:

``` text
A R A R A
```

que é igual à palavra original.

### Implementação em C

``` c
int eh_palindromo(char palavra[]) {

    Pilha p = criar_pilha();

    int tamanho = 0;

    while (palavra[tamanho] != '\0') {
        inserir(p, palavra[tamanho]);
        tamanho++;
    }

    for (int i = 0; i < tamanho; i++) {

        if (palavra[i] != remover(p)) {
            destruir(p);
            return 0;
        }
    }

    destruir(p);

    return 1;
}
```

A função retorna:

``` text
1 → a palavra é um palíndromo
0 → a palavra não é um palíndromo
```

### Exemplos

``` text
ARARA → palíndromo
RADAR → palíndromo
ANA   → palíndromo
OSSO  → palíndromo
```

Exemplos que não são palíndromos:

``` text
CASA
JAVA
PILHA
FILA
```

### Funcionamento

Para verificar `RADAR`:

``` text
Palavra original:

R A D A R
```

Os caracteres são inseridos na pilha e depois removidos na ordem
inversa:

``` text
R A D A R
↑         ↑
igual     igual
```

Como cada caractere retirado da pilha é igual ao caractere
correspondente da palavra original, a função conclui que:

``` text
RADAR → é palíndromo
```

------------------------------------------------------------------------

## Resumo

  -----------------------------------------------------------------------
  Questão                             Conceito principal
  ----------------------------------- -----------------------------------
  **1**                               Pilha é uma estrutura LIFO

  **2**                               Desfazer, histórico, chamadas de
                                      funções, expressões, DFS etc.

  **3**                               Configuração final: `[10, 30, 50]`

  **4**                               Uso de pilha para verificar
                                      parênteses

  **5**                               Uso de uma pilha auxiliar para
                                      inverter

  **6**                               Uso da pilha para comparar a
                                      palavra com sua ordem inversa
  -----------------------------------------------------------------------
