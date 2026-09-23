# Lista de Exercícios: Filas

## 1. O que é uma estrutura de dados do tipo fila e como ela funciona?

Uma **fila** é uma estrutura de dados linear que segue o princípio
**FIFO (First In, First Out)**, ou seja, o **primeiro elemento que entra
é o primeiro elemento que sai**.

A inserção de elementos acontece no **final da fila**, enquanto a
remoção acontece no **início**.

Exemplo:

``` text
Início                    Final
  ↓                         ↓
[10] → [20] → [30] → [40]
  ↑
remoção
```

Nesse exemplo, o elemento `10` será o primeiro a ser removido.

------------------------------------------------------------------------

## 2. Em que situações uma fila pode ser utilizada?

Uma fila pode ser utilizada em situações nas quais os elementos precisam
ser processados **na ordem em que foram inseridos**.

Alguns exemplos são:

-   **Fila de impressão:** documentos são impressos na ordem em que
    foram enviados.
-   **Fila de atendimento:** as pessoas são atendidas conforme a ordem
    de chegada.
-   **Processos de um sistema operacional:** processos podem aguardar em
    uma fila para serem executados.
-   **Requisições de um servidor:** solicitações podem ser processadas
    na ordem em que chegaram.
-   **Buffers de comunicação:** dados podem ser armazenados
    temporariamente enquanto aguardam processamento.

------------------------------------------------------------------------

## 3. Qual a principal diferença entre uma pilha e uma fila em relação às operações de inserção e remoção de elementos?

A principal diferença está na **ordem em que os elementos são
removidos**.

Uma **fila** utiliza o princípio **FIFO (First In, First Out)**. O
primeiro elemento inserido é o primeiro a ser removido.

Uma **pilha** utiliza o princípio **LIFO (Last In, First Out)**. O
último elemento inserido é o primeiro a ser removido.

  Estrutura   Inserção   Remoção   Princípio
  ----------- ---------- --------- -----------
  **Fila**    Final      Início    FIFO
  **Pilha**   Topo       Topo      LIFO

------------------------------------------------------------------------

## 4. Dadas as operações de fila `I` (insere) e `R` (remove), escreva a configuração final da fila após as seguintes operações

``` text
I(10), I(20), R, I(30), I(45), I(21), R, R, I(50), I(60), R, I(70), R
```

### Resolução

Acompanhando cada operação:

``` text
I(10) → [10]

I(20) → [10, 20]

R     → [20]

I(30) → [20, 30]

I(45) → [20, 30, 45]

I(21) → [20, 30, 45, 21]

R     → [30, 45, 21]

R     → [45, 21]

I(50) → [45, 21, 50]

I(60) → [45, 21, 50, 60]

R     → [21, 50, 60]

I(70) → [21, 50, 60, 70]

R     → [50, 60, 70]
```

### Resposta

A configuração final da fila é:

``` text
[50, 60, 70]
```

------------------------------------------------------------------------

## 5. Implemente uma função `reverso`, que reposiciona os elementos na fila de tal forma que o início da fila torna-se o fim, e vice-versa

A função deve inverter a ordem dos elementos da fila.

Por exemplo:

``` text
Antes:

[10, 20, 30, 40]
```

Após a execução da função:

``` text
[40, 30, 20, 10]
```

Uma forma de realizar essa operação é utilizando uma **pilha auxiliar**:

``` c
void reverso(Fila f) {

    Pilha p = criar_pilha();

    while (!fila_vazia(f)) {
        empilhar(p, remover(f));
    }

    while (!pilha_vazia(p)) {
        inserir(f, desempilhar(p));
    }

    destruir_pilha(p);
}
```

A pilha auxilia na inversão porque segue o princípio **LIFO**.

O processo pode ser representado da seguinte forma:

``` text
Fila:
[10] [20] [30] [40]

        ↓

Pilha:
[40]
[30]
[20]
[10]

        ↓

Fila:
[40] [30] [20] [10]
```

------------------------------------------------------------------------

## 6. Escreva uma função que, dadas duas filas de inteiros `F1` e `F2`, concatene as duas filas. Retorne a fila concatenada em `F1`. A fila `F2` deve ficar vazia após a operação

A concatenação deve colocar todos os elementos de `F2` no final de `F1`.

Por exemplo:

``` text
F1 = [10, 20, 30]

F2 = [40, 50, 60]
```

Após a operação:

``` text
F1 = [10, 20, 30, 40, 50, 60]

F2 = []
```

Uma possível implementação é:

``` c
void concatenar(Fila f1, Fila f2) {

    while (!fila_vazia(f2)) {
        inserir(f1, remover(f2));
    }
}
```

Os elementos são retirados de `F2` e inseridos no final de `F1`. Dessa
forma, ao final da operação, `F2` estará vazia.

------------------------------------------------------------------------

## 7. Escreva uma função que receba três filas `F1`, `F2` e `F3`. As filas `F1` e `F2` já estão ordenadas em ordem crescente. A função deve preencher a fila `F3` com os elementos de `F1` e `F2` também em ordem crescente

A função deve comparar os elementos que estão no início de `F1` e `F2`.
O menor elemento deve ser removido da respectiva fila e inserido em
`F3`.

Por exemplo:

``` text
F1 = [10, 30, 50, 70]

F2 = [20, 40, 60, 80]

F3 = []
```

O resultado será:

``` text
F3 = [10, 20, 30, 40, 50, 60, 70, 80]
```

Uma possível implementação é:

``` c
void intercalar(Fila f1, Fila f2, Fila f3) {

    while (!fila_vazia(f1) && !fila_vazia(f2)) {

        if (acessar_inicio(f1) <= acessar_inicio(f2)) {
            inserir(f3, remover(f1));
        } else {
            inserir(f3, remover(f2));
        }
    }

    while (!fila_vazia(f1)) {
        inserir(f3, remover(f1));
    }

    while (!fila_vazia(f2)) {
        inserir(f3, remover(f2));
    }
}
```

### Exemplo do processo

Considerando:

``` text
F1 = [10, 30, 50]
F2 = [20, 40, 60]
F3 = []
```

Os elementos do início das filas são comparados:

``` text
10 < 20 → F3 recebe 10

30 > 20 → F3 recebe 20

30 < 40 → F3 recebe 30

50 > 40 → F3 recebe 40

50 < 60 → F3 recebe 50

F2 restante → F3 recebe 60
```

Resultado:

``` text
F3 = [10, 20, 30, 40, 50, 60]
```

Dessa forma, `F3` permanece ordenada em **ordem crescente**.
