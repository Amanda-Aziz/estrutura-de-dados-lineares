# TAD Lista Encadeada

## Visão geral

O programa implementa uma **Lista Encadeada (Linked List)** utilizando **alocação dinâmica de memória**. Diferentemente de uma estrutura baseada em vetor, os elementos da lista são armazenados em nós independentes na memória, ligados uns aos outros por meio de ponteiros.

A lista utilizada é uma **lista simplesmente encadeada**, pois cada elemento possui um ponteiro que indica apenas o **próximo elemento** da sequência.

As principais operações implementadas são:

- `criar_lista` — cria e inicializa uma lista;
- `inserir_inicio` — insere um elemento no início;
- `inserir_final` — insere um elemento no final;
- `remover_inicio` — remove o primeiro elemento;
- `remover_final` — remove o último elemento;
- `acessar_inicio` — retorna o primeiro elemento;
- `acessar_final` — retorna o último elemento;
- `buscar_por_valor` — procura um elemento pelo seu valor;
- `buscar_por_posicao` — acessa um elemento através de sua posição;
- `destruir` — libera a memória utilizada pela lista.

A implementação utiliza `malloc()` para criar dinamicamente os nós e `free()` para liberar a memória quando os elementos são removidos ou quando a lista é destruída.

---

## Estrutura da lista

A lista é formada por duas estruturas principais:

```c
struct elem{

    int valor;

    Elem* prox;

};

typedef struct elem* Elem;
```

A estrutura `elem` representa **um nó da lista**.

| Campo | Tipo | Significado |
|---|---|---|
| `valor` | `int` | Valor armazenado naquele nó |
| `prox` | `Elem*` | Ponteiro para o próximo nó da lista |

O campo `prox` é o que permite conectar os elementos.

Por exemplo, uma lista contendo `10`, `20` e `30` pode ser representada conceitualmente assim:

```text
[10 | *] → [20 | *] → [30 | NULL]
```

O último elemento possui `prox = NULL`, indicando que não existe outro elemento depois dele.

---

## Estrutura da lista

Além dos nós, existe uma estrutura responsável por controlar a lista:

```c
struct lista{

    int qtd;

    Elem* inicio;

};

typedef struct lista* Lista;
```

| Campo | Tipo | Significado |
|---|---|---|
| `qtd` | `int` | Quantidade de elementos atualmente armazenados |
| `inicio` | `Elem*` | Ponteiro para o primeiro nó da lista |

Assim, a estrutura `Lista` não armazena diretamente todos os valores. Ela mantém apenas informações de controle e aponta para o primeiro nó.

Por exemplo:

```text
Lista
 ├── qtd = 3
 └── inicio
      ↓
   [10 | *] → [20 | *] → [30 | NULL]
```

A partir de `inicio`, é possível percorrer todos os elementos seguindo os ponteiros `prox`.

---

# Modularização

A ideia da implementação é separar a lista em arquivos diferentes.

## `lista.h`

O arquivo `.h` deve funcionar como a **interface do TAD**, contendo as definições dos tipos e os protótipos das funções disponíveis.

Por exemplo:

```c
typedef struct elem* Elem;

typedef struct lista* Lista;

Lista criar_lista();

int inserir_inicio();
int inserir_final();

int remover_inicio();
void remover_final();

int acessar_inicio();
int acessar_final();

void buscar_por_valor();
void buscar_por_posicao();

void destruir();
```

A ideia é que o código que utiliza a lista não precise conhecer todos os detalhes internos da implementação.

---

## `lista.c`

O arquivo `lista.c` contém a **implementação das operações** da lista.

É nele que estão:

- as estruturas `elem` e `lista`;
- a alocação dos nós;
- a inserção dos elementos;
- a remoção;
- as buscas;
- o acesso aos elementos;
- a liberação da memória.

---

## `main.c`

O `main.c` é responsável pelo programa principal e pela utilização das funções disponibilizadas pelo TAD.

No código fornecido:

```c
#include "pilha.h"
#include <stdio.h>

int main(){

    int valor;

    printf("Valor: ");

    scanf("%d", &valor);

    criar_lista(&valor);

    return 0;
}
```

O programa solicita um valor ao usuário e depois tenta chamar `criar_lista()`.

Entretanto, existem **inconsistências nesse arquivo**, explicadas mais adiante.

---

# Função por função — `lista.c`

## `criar_lista()`

A função tem como objetivo criar uma nova estrutura de lista:

```c
Lista criar_lista(){

    Lista li = malloc(sizeof(struct lista));

    if(li != NULL){

        li->qtd = 0;
        li->inicio = NULL;

    }

    return li;
}
```

A ideia é:

1. Alocar memória para a estrutura `lista`;
2. Verificar se a alocação foi realizada;
3. Inicializar a quantidade de elementos com `0`;
4. Inicializar `inicio` com `NULL`;
5. Retornar o endereço da lista criada.

Uma lista recém-criada possui:

```text
qtd = 0
inicio = NULL
```

Representação:

```text
Lista
 ├── qtd = 0
 └── inicio → NULL
```

Isso significa que a lista está vazia.

### ⚠️ Problema no código fornecido

No código enviado, a função aparece como:

```c
Lista criar_lista(Lista li){

    Lista li = malloc(sizeof(struct lista));

    ...
}
```

Existe uma variável `li` sendo recebida como parâmetro e outra variável `li` sendo declarada dentro da função. Isso gera conflito.

Além disso, o `main` chama:

```c
criar_lista(&valor);
```

O argumento passado é um `int*`, enquanto a função deveria receber nenhum argumento ou, dependendo da implementação escolhida, um ponteiro compatível com `Lista`.

Portanto, a assinatura precisa ser corrigida antes de o programa funcionar.

---

# `inserir_inicio(Lista li, int valor_inserir)`

A função insere um novo elemento **antes do primeiro elemento atual**.

A lógica é:

```c
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
```

O processo acontece da seguinte maneira:

### 1. Alocação do novo nó

```c
Elem* no = malloc(sizeof(Elem));
```

É solicitada memória para armazenar o novo elemento.

### 2. Armazenamento do valor

```c
no->valor = valor_inserir;
```

O valor recebido é colocado dentro do novo nó.

### 3. Ligação com o antigo primeiro elemento

```c
no->prox = li->inicio;
```

O novo nó passa a apontar para o antigo primeiro elemento.

### 4. Atualização do início

```c
li->inicio = no;
```

Agora o novo nó passa a ser o primeiro da lista.

### 5. Atualização da quantidade

```c
li->qtd++;
```

A quantidade de elementos aumenta em uma unidade.

### Exemplo

Antes:

```text
inicio
  ↓
[20] → [30] → NULL
```

Inserindo `10` no início:

```text
inicio
  ↓
[10] → [20] → [30] → NULL
```

A inserção no início é eficiente porque não é necessário percorrer a lista.

**Complexidade:** `O(1)`.

---

# `inserir_final(Lista li, int valor_inserir)`

Essa função adiciona um novo elemento ao **final da lista**.

A ideia é:

```c
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
```

O novo nó recebe:

```c
no->prox = NULL;
```

Isso acontece porque ele será o último elemento.

Depois, caso a lista não esteja vazia, utiliza-se um ponteiro auxiliar:

```c
Elem* aux = li->inicio;
```

Esse ponteiro percorre a lista:

```c
while(aux->prox != NULL){

    aux = aux->prox;
}
```

Quando o laço termina, `aux` aponta para o último nó.

Então:

```c
aux->prox = no;
```

liga o último elemento antigo ao novo elemento.

### Exemplo

Antes:

```text
[10] → [20] → [30] → NULL
```

Inserindo `40`:

```text
[10] → [20] → [30] → [40] → NULL
```

Como é necessário percorrer a lista até o último elemento:

**Complexidade:** `O(n)`.

---

# `remover_inicio(Lista li)`

Remove o primeiro elemento da lista.

A lógica é:

```c
int remover_inicio(Lista li){

    if(li->qtd == 0)
        return 0;

    Elem* aux = li->inicio;

    li->inicio = aux->prox;

    free(aux);

    li->qtd--;

    return 1;
}
```

Primeiro verifica se a lista está vazia:

```c
if(li->qtd == 0)
    return 0;
```

Se houver elementos, `aux` guarda o primeiro nó:

```c
Elem* aux = li->inicio;
```

Depois, o início passa a apontar para o segundo elemento:

```c
li->inicio = aux->prox;
```

Por fim, o antigo primeiro nó é liberado:

```c
free(aux);
```

### Exemplo

Antes:

```text
inicio
  ↓
[10] → [20] → [30] → NULL
```

Depois de remover o início:

```text
inicio
  ↓
[20] → [30] → NULL
```

O nó contendo `10` é liberado da memória.

**Complexidade:** `O(1)`.

---

# `acessar_inicio(Lista li)`

Retorna o valor armazenado no primeiro elemento.

```c
int acessar_inicio(Lista li){

    if(li->qtd == 0)
        return 0;

    return li->inicio->valor;
}
```

Primeiro verifica se a lista está vazia.

Se não estiver, acessa:

```c
li->inicio->valor
```

Ou seja:

1. `li->inicio` → primeiro nó;
2. `->valor` → valor armazenado nesse nó.

### Exemplo

```text
inicio
  ↓
[50] → [80] → [100] → NULL
```

`acessar_inicio()` retorna:

```text
50
```

**Complexidade:** `O(1)`.

---

# `remover_final(Lista li)`

Remove o último elemento da lista.

A função precisa tratar dois casos:

1. Lista com apenas um elemento;
2. Lista com dois ou mais elementos.

Para uma lista com apenas um elemento:

```text
[10] → NULL
```

o `inicio` precisa ser atualizado para `NULL`.

Para uma lista maior, é necessário encontrar o último nó e também guardar o nó anterior a ele.

A lógica utilizada é:

```c
Elem* aux = li->inicio;
Elem* ant;

while(aux->prox != NULL){

    ant = aux;
    aux = aux->prox;
}
```

Ao final:

```text
ant → penúltimo nó
aux → último nó
```

Depois:

```c
free(aux);
ant->prox = NULL;
```

O último nó é liberado e o penúltimo passa a ser o último.

### Exemplo

Antes:

```text
[10] → [20] → [30] → NULL
```

Depois:

```text
[10] → [20] → NULL
```

**Complexidade:** `O(n)`.

---

# `acessar_final(Lista li)`

Retorna o valor armazenado no último elemento.

```c
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
```

O ponteiro `aux` começa no primeiro elemento e percorre a lista até encontrar um nó cujo `prox` seja `NULL`.

Esse é o último elemento.

### Exemplo

```text
[10] → [20] → [30] → NULL
                         ↑
                       final
```

A função retorna:

```text
30
```

Como precisa percorrer os nós:

**Complexidade:** `O(n)`.

---

# `buscar_por_valor(Lista li, int valor)`

Essa função percorre a lista procurando um determinado valor.

```c
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
```

A variável `posicao` começa em `0`.

Por exemplo:

```text
posição:   0       1       2
          ↓       ↓       ↓
        [10] → [20] → [30] → NULL
```

Se for procurado o valor `20`, a função retorna:

```text
1
```

Se for procurado `30`:

```text
2
```

### ⚠️ Problema importante

O código retorna `0` quando o valor não é encontrado:

```c
return 0;
```

Porém, `0` também é uma posição válida.

Por exemplo, se o valor procurado estiver no primeiro nó:

```text
[10] → [20] → [30]
 ↑
posição 0
```

a função também retorna `0`.

Portanto, não é possível distinguir:

```text
0 → elemento encontrado na posição 0
```

de:

```text
0 → elemento não encontrado
```

Uma solução comum seria retornar `-1` quando o valor não for encontrado:

```c
return -1;
```

Assim:

```text
posição >= 0 → encontrado
-1            → não encontrado
```

**Complexidade:** `O(n)`.

---

# `buscar_por_posicao(Lista li, int posicao)`

Essa função procura um elemento através de sua posição.

Primeiro verifica se a posição é válida:

```c
if(posicao < 0 || posicao >= li->qtd){

    return 0;
}
```

A primeira posição da lista é `0`.

Por exemplo, em uma lista com quatro elementos:

```text
posição:   0      1      2      3
          ↓      ↓      ↓      ↓
        [10] → [20] → [30] → [40]
```

As posições válidas são:

```text
0, 1, 2 e 3
```

Depois, a função percorre a lista:

```c
Elem* aux = li->inicio;

for(int i = 0; i < posicao; i++){

    aux = aux->prox;
}
```

Quando o laço termina, `aux` aponta para o nó correspondente à posição solicitada.

Finalmente:

```c
return aux->valor;
```

retorna seu valor.

### Exemplo

Para:

```c
buscar_por_posicao(li, 2);
```

a função percorre:

```text
[10] → [20] → [30] → [40]
               ↑
             posição 2
```

e retorna:

```text
30
```

**Complexidade:** `O(n)`.

---

# `destruir(Lista li)`

A função `destruir()` tem como objetivo liberar toda a memória utilizada pela lista.

Uma lista encadeada utiliza memória dinâmica para cada nó. Portanto, não basta liberar apenas a estrutura `Lista`: todos os nós também precisam ser liberados.

A ideia do processo é percorrer a lista e liberar cada elemento:

```text
[10] → [20] → [30] → NULL
```

Primeiro libera `10`, depois `20` e finalmente `30`.

Depois de todos os nós serem liberados, a própria estrutura da lista pode ser liberada:

```c
free(li);
```

### ⚠️ Problema no código fornecido

O código apresenta:

```c
Elem* aux = li->inicio;

while(aux->prox != NULL){

    Elem* atual = aux;

    aux = aux->prox;

    free(atual);
}

free(aux);
free(li);
```

A lógica funciona para uma lista não vazia, pois os nós são liberados um por um e o último é liberado depois do `while`.

Entretanto, existe um problema quando a lista está vazia.

Se:

```c
li->inicio == NULL
```

então:

```c
Elem* aux = li->inicio;
```

faz `aux` receber `NULL`.

Logo, a condição:

```c
while(aux->prox != NULL)
```

tenta acessar `prox` através de um ponteiro `NULL`.

Isso pode causar **comportamento indefinido**.

Uma forma mais segura de percorrer seria:

```c
Elem* aux = li->inicio;

while(aux != NULL){

    Elem* atual = aux;
    aux = aux->prox;

    free(atual);
}

free(li);
```

Dessa maneira, o laço termina naturalmente quando `aux` chegar a `NULL`.

---

# Simulação de uma lista

Considere a seguinte sequência de operações:

```text
criar_lista()
inserir_inicio(20)
inserir_inicio(10)
inserir_final(30)
inserir_final(40)
remover_inicio()
```

### 1. `criar_lista()`

```text
qtd = 0

inicio
  ↓
 NULL
```

---

### 2. `inserir_inicio(20)`

```text
qtd = 1

inicio
  ↓
[20] → NULL
```

---

### 3. `inserir_inicio(10)`

O novo nó aponta para o antigo início:

```text
inicio
  ↓
[10] → [20] → NULL
```

`qtd = 2`.

---

### 4. `inserir_final(30)`

O programa percorre a lista até o último elemento e adiciona `30`:

```text
inicio
  ↓
[10] → [20] → [30] → NULL
```

`qtd = 3`.

---

### 5. `inserir_final(40)`

```text
inicio
  ↓
[10] → [20] → [30] → [40] → NULL
```

`qtd = 4`.

---

### 6. `remover_inicio()`

O primeiro nó é removido:

```text
inicio
  ↓
[20] → [30] → [40] → NULL
```

`qtd = 3`.

O nó contendo `10` é liberado com `free()`.

---

# Resumo das operações

| Operação | Função | Complexidade | Descrição |
|---|---|---:|---|
| Criar | `criar_lista()` | `O(1)` | Cria e inicializa a lista |
| Inserir no início | `inserir_inicio()` | `O(1)` | Adiciona um nó antes do primeiro |
| Inserir no final | `inserir_final()` | `O(n)` | Percorre até o último nó e insere |
| Remover início | `remover_inicio()` | `O(1)` | Remove o primeiro nó |
| Remover final | `remover_final()` | `O(n)` | Percorre até o último nó e o remove |
| Acessar início | `acessar_inicio()` | `O(1)` | Retorna o primeiro valor |
| Acessar final | `acessar_final()` | `O(n)` | Percorre até o último e retorna o valor |
| Buscar valor | `buscar_por_valor()` | `O(n)` | Procura um valor na lista |
| Buscar posição | `buscar_por_posicao()` | `O(n)` | Percorre até a posição desejada |
| Destruir | `destruir()` | `O(n)` | Libera todos os nós e a lista |

---

# Problemas encontrados na implementação

Além da lógica da lista, os arquivos fornecidos apresentam algumas inconsistências que precisam ser corrigidas.

## 1. Inclusão do arquivo incorreto

O `lista.h` possui:

```c
#include "lista_int.c"
```

Mas o arquivo apresentado é:

```text
lista.c
```

Além disso, normalmente o `.h` não deve incluir diretamente o arquivo `.c`.

A organização recomendada é:

```text
lista.h
    ↑
lista.c
    ↑
main.c
```

Ou seja, `lista.c` inclui `lista.h`, enquanto `main.c` também inclui `lista.h`.

---

## 2. `main.c` inclui `pilha.h`

O código apresenta:

```c
#include "pilha.h"
```

Porém, o programa implementado é uma lista.

O esperado seria:

```c
#include "lista.h"
```

---

## 3. Protótipos incompletos

No `lista.h` aparecem declarações como:

```c
int inserir_inicio();
int inserir_final();
```

Porém, em `lista.c`, as funções recebem parâmetros.

O cabeçalho deve declarar os parâmetros corretamente, por exemplo:

```c
int inserir_inicio(Lista li, int valor_inserir);
int inserir_final(Lista li, int valor_inserir);
```

Isso permite que o compilador verifique se as chamadas das funções estão sendo feitas corretamente.

---

## 4. Tipos de retorno diferentes

Em `lista.c`:

```c
int remover_final(...)
```

mas em `lista.h`:

```c
void remover_final();
```

Essas declarações são incompatíveis.

O tipo de retorno precisa ser o mesmo nos dois arquivos.

O mesmo problema ocorre com:

```text
buscar_por_valor()
buscar_por_posicao()
```

que retornam `int` na implementação, mas aparecem como `void` no cabeçalho.

---

## 5. Problema na chamada de `criar_lista()`

O `main` faz:

```c
int valor;

scanf("%d", &valor);

criar_lista(&valor);
```

O valor lido pelo usuário não deveria ser passado para a criação da lista, pois criar uma lista e inserir um valor são operações diferentes.

A ideia normalmente seria:

```c
Lista li = criar_lista();
```

e depois:

```c
inserir_inicio(li, valor);
```

Assim:

```text
criar_lista()
      ↓
lista vazia
      ↓
inserir_inicio(li, valor)
      ↓
lista com o valor
```

---

# Fluxo conceitual do programa

A utilização correta do TAD pode ser entendida através do seguinte fluxo:

```text
             criar_lista()
                   ↓
             Lista vazia
                   ↓
        ┌──────────┴──────────┐
        ↓                     ↓
inserir_inicio()       inserir_final()
        ↓                     ↓
        └──────────┬──────────┘
                   ↓
              Lista criada
                   ↓
        ┌──────────┼──────────┐
        ↓          ↓          ↓
     acessar    buscar     remover
        ↓          ↓          ↓
        └──────────┼──────────┘
                   ↓
               destruir()
                   ↓
             Memória liberada
```

---

# Conceitos importantes

## Lista encadeada

Uma lista encadeada é uma estrutura dinâmica formada por nós.

Cada nó contém:

```text
dado + ponteiro
```

No caso desta implementação:

```c
struct elem{

    int valor;
    Elem* prox;

};
```

O `valor` guarda o dado e `prox` permite chegar ao próximo nó.

---

## Alocação dinâmica

Os nós são criados utilizando:

```c
malloc()
```

Isso permite que a lista cresça dinamicamente durante a execução do programa.

Quando um nó não é mais necessário, sua memória deve ser liberada usando:

```c
free()
```

---

## Ponteiro `NULL`

O último elemento da lista possui:

```c
prox = NULL;
```

Isso indica o final da sequência.

Por isso, muitos percursos utilizam:

```c
while(aux != NULL)
```

ou:

```c
while(aux->prox != NULL)
```

dependendo do objetivo do percurso.

---

## Tamanho da lista

A variável:

```c
qtd
```

mantém a quantidade atual de elementos.

Por exemplo:

```text
Lista vazia:

qtd = 0

[NULL]
```

Depois de três inserções:

```text
qtd = 3

[10] → [20] → [30] → NULL
```

Manter `qtd` permite verificar rapidamente se a lista está vazia e validar posições.

---

# Organização esperada dos arquivos

Uma organização adequada para o projeto seria:

```text
projeto/
│
├── lista.h
├── lista.c
└── main.c
```

### `lista.h`

Interface da lista:

```text
Tipos
↓
Protótipos das funções
```

### `lista.c`

Implementação:

```text
Structs
↓
Funções
↓
Manipulação dos nós
↓
Alocação/liberação de memória
```

### `main.c`

Utilização:

```text
Entrada de dados
↓
Criação da lista
↓
Chamadas das operações
↓
Exibição dos resultados
↓
Destruição da lista
```

Essa separação facilita a organização do código e permite que a implementação da lista fique isolada do programa que a utiliza.