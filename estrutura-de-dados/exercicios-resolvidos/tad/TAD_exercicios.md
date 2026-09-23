# Lista de Exercícios: TAD

## 1. O que é um Tipo Abstrato de Dados (TAD) e qual a característica fundamental na sua utilização?

Um **Tipo Abstrato de Dados (TAD)** é uma forma de organizar uma
estrutura de dados definindo **quais operações podem ser realizadas
sobre os dados**, sem expor necessariamente os detalhes de como essas
operações são implementadas.

A característica fundamental de um TAD é a **separação entre a interface
e a implementação**.

A interface informa ao usuário:

-   quais operações existem;
-   quais parâmetros cada operação recebe;
-   qual resultado cada operação retorna.

Já a implementação contém os detalhes internos de funcionamento.

Por exemplo, um TAD de fila pode disponibilizar:

``` text
criar_fila()
inserir()
remover()
acessar_inicio()
destruir()
```

O programa que utiliza a fila não precisa conhecer os detalhes de como
os elementos são armazenados internamente.

Essa separação permite utilizar a estrutura por meio de uma interface
bem definida, sem depender de sua implementação interna.

------------------------------------------------------------------------

## 2. Quais as vantagens de se programar com TADs?

A utilização de TADs apresenta diversas vantagens:

### Encapsulamento

Os detalhes internos da estrutura podem ser escondidos, permitindo que o
usuário utilize apenas as operações disponibilizadas pelo TAD.

### Organização

O código fica dividido em partes bem definidas, separando a
**interface** da **implementação**.

### Reutilização

Um TAD pode ser utilizado em diferentes programas sem precisar
reescrever toda a estrutura de dados.

### Manutenção

Alterações na implementação interna podem ser realizadas sem
necessariamente modificar os programas que utilizam o TAD.

### Segurança

Como o acesso aos dados é feito por meio das operações definidas pelo
TAD, é possível controlar melhor como os dados são modificados.

### Abstração

O programador pode trabalhar com o comportamento da estrutura sem
precisar conhecer todos os detalhes de sua implementação.

------------------------------------------------------------------------

## 3. Desenvolva um TAD para um cilindro

O TAD deve representar um **cilindro** e disponibilizar operações para:

-   inicializar um cilindro;
-   obter sua altura;
-   obter seu raio;
-   calcular sua área;
-   calcular seu volume;
-   destruir o cilindro.

As fórmulas utilizadas são:

### Área da base

$$
A_b = \pi r^2
$$

### Área total

$$
A = 2\pi r^2 + 2\pi rh
$$

ou:

$$
A = 2\pi r(r+h)
$$

### Volume

$$
V = \pi r^2h
$$

onde:

-   `r` = raio;
-   `h` = altura.

### `cilindro.h`

``` c
#ifndef CILINDRO_H
#define CILINDRO_H

typedef struct cilindro* Cilindro;

Cilindro criar_cilindro(float raio, float altura);

void destruir_cilindro(Cilindro c);

float obter_raio(Cilindro c);
float obter_altura(Cilindro c);

float calcular_area(Cilindro c);
float calcular_volume(Cilindro c);

#endif
```

### `cilindro.c`

``` c
#include <stdlib.h>
#include <math.h>
#include "cilindro.h"

struct cilindro {

    float raio;
    float altura;
};

Cilindro criar_cilindro(float raio, float altura) {

    Cilindro c = malloc(sizeof(struct cilindro));

    if (c != NULL) {

        c->raio = raio;
        c->altura = altura;
    }

    return c;
}

void destruir_cilindro(Cilindro c) {

    free(c);
}

float obter_raio(Cilindro c) {

    return c->raio;
}

float obter_altura(Cilindro c) {

    return c->altura;
}

float calcular_area(Cilindro c) {

    return 2 * M_PI * c->raio * (c->raio + c->altura);
}

float calcular_volume(Cilindro c) {

    return M_PI * c->raio * c->raio * c->altura;
}
```

### Exemplo de utilização

``` c
#include <stdio.h>
#include "cilindro.h"

int main() {

    Cilindro c = criar_cilindro(5.0, 10.0);

    printf("Raio: %.2f\n", obter_raio(c));
    printf("Altura: %.2f\n", obter_altura(c));
    printf("Area: %.2f\n", calcular_area(c));
    printf("Volume: %.2f\n", calcular_volume(c));

    destruir_cilindro(c);

    return 0;
}
```

Nesse exemplo, o cilindro possui:

``` text
Raio = 5
Altura = 10
```

O programa utiliza apenas as funções disponibilizadas pelo TAD, sem
acessar diretamente os campos internos da estrutura.

> **Observação:** em alguns compiladores, `M_PI` pode não estar
> disponível por padrão. Nesse caso, pode-se definir uma constante para
> π, por exemplo `#define PI 3.14159265358979323846`.

------------------------------------------------------------------------

## 4. Crie um TAD que represente números complexos

Um número complexo possui a forma:

$$
z = x + iy
$$

onde:

-   `x` é a parte real;
-   `y` é a parte imaginária;
-   `i² = -1`.

O TAD deve disponibilizar as seguintes operações:

-   **(a)** criar um número complexo;
-   **(b)** destruir um número complexo;
-   **(c)** somar dois números complexos;
-   **(d)** subtrair dois números complexos;
-   **(e)** multiplicar dois números complexos;
-   **(f)** dividir dois números complexos.

### Operações matemáticas

Considere:

$$
z_1 = a + bi
$$

e:

$$
z_2 = c + di
$$

### Soma

$$
z_1 + z_2 = (a+c) + (b+d)i
$$

### Subtração

$$
z_1 - z_2 = (a-c) + (b-d)i
$$

### Multiplicação

$$
z_1z_2 = (ac-bd) + (ad+bc)i
$$

### Divisão

Para realizar a divisão, multiplicamos o numerador e o denominador pelo conjugado de $z_2$, que é $c-di$.

$$
\frac{z_1}{z_2}
=
\frac{(a+bi)(c-di)}{(c+di)(c-di)}
$$

Como:

$$
(c+di)(c-di)=c^2+d^2
$$

temos:

$$
\frac{z_1}{z_2}
=
\frac{(a+bi)(c-di)}{c^2+d^2}
$$

Resultando em:

$$
\frac{z_1}{z_2}
=
\frac{ac+bd}{c^2+d^2}
+
\frac{bc-ad}{c^2+d^2}i
$$

A divisão só pode ser realizada quando:

$$
c^2+d^2 \neq 0
$$

### `complexo.h`

``` c
#ifndef COMPLEXO_H
#define COMPLEXO_H

typedef struct complexo* Complexo;

Complexo criar_complexo(float real, float imaginaria);

void destruir_complexo(Complexo z);

Complexo somar(Complexo z1, Complexo z2);
Complexo subtrair(Complexo z1, Complexo z2);
Complexo multiplicar(Complexo z1, Complexo z2);
Complexo dividir(Complexo z1, Complexo z2);

#endif
```

### `complexo.c`

``` c
#include <stdlib.h>
#include "complexo.h"

struct complexo {

    float real;
    float imaginaria;
};

Complexo criar_complexo(float real, float imaginaria) {

    Complexo z = malloc(sizeof(struct complexo));

    if (z != NULL) {

        z->real = real;
        z->imaginaria = imaginaria;
    }

    return z;
}

void destruir_complexo(Complexo z) {

    free(z);
}

Complexo somar(Complexo z1, Complexo z2) {

    return criar_complexo(
        z1->real + z2->real,
        z1->imaginaria + z2->imaginaria
    );
}

Complexo subtrair(Complexo z1, Complexo z2) {

    return criar_complexo(
        z1->real - z2->real,
        z1->imaginaria - z2->imaginaria
    );
}

Complexo multiplicar(Complexo z1, Complexo z2) {

    float real =
        z1->real * z2->real -
        z1->imaginaria * z2->imaginaria;

    float imaginaria =
        z1->real * z2->imaginaria +
        z1->imaginaria * z2->real;

    return criar_complexo(real, imaginaria);
}

Complexo dividir(Complexo z1, Complexo z2) {

    float denominador =
        z2->real * z2->real +
        z2->imaginaria * z2->imaginaria;

    if (denominador == 0) {
        return NULL;
    }

    float real =
        (z1->real * z2->real +
         z1->imaginaria * z2->imaginaria)
        / denominador;

    float imaginaria =
        (z1->imaginaria * z2->real -
         z1->real * z2->imaginaria)
        / denominador;

    return criar_complexo(real, imaginaria);
}
```

### Exemplo

Considere:

``` text
z1 = 2 + 3i
z2 = 4 + 5i
```

A soma será:

``` text
z1 + z2 = 6 + 8i
```

A subtração:

``` text
z1 - z2 = -2 - 2i
```

A multiplicação:

``` text
z1 × z2 = -7 + 22i
```

O TAD permite realizar essas operações sem que o programa principal
precise conhecer a estrutura interna utilizada para armazenar as partes
real e imaginária.

------------------------------------------------------------------------

## 5. Crie um TAD que represente o tipo conjunto de inteiros

O TAD deve representar um **conjunto de números inteiros** utilizando um
**vetor de inteiros**.

O conjunto não deve possuir elementos repetidos.

As operações solicitadas são:

-   **(a)** União;
-   **(b)** Criar um conjunto vazio;
-   **(c)** Inserir;
-   **(d)** Remover;
-   **(e)** Interseção;
-   **(f)** Diferença;
-   **(g)** Testar se um número pertence ao conjunto;
-   **(h)** Menor valor;
-   **(i)** Maior valor;
-   **(j)** Testar se os conjuntos são iguais;
-   **(k)** Tamanho;
-   **(l)** Testar se o conjunto é vazio.

### Estrutura do conjunto

Uma possibilidade é armazenar:

-   um vetor de inteiros;
-   a quantidade atual de elementos;
-   a capacidade máxima do vetor.

### `conjunto.h`

``` c
#ifndef CONJUNTO_H
#define CONJUNTO_H

#define MAX 100

typedef struct conjunto* Conjunto;

Conjunto criar_conjunto(void);

void destruir_conjunto(Conjunto c);

int inserir(Conjunto c, int valor);
int remover(Conjunto c, int valor);

Conjunto uniao(Conjunto c1, Conjunto c2);
Conjunto intersecao(Conjunto c1, Conjunto c2);
Conjunto diferenca(Conjunto c1, Conjunto c2);

int pertence(Conjunto c, int valor);

int menor(Conjunto c);
int maior(Conjunto c);

int iguais(Conjunto c1, Conjunto c2);

int tamanho(Conjunto c);

int vazio(Conjunto c);

#endif
```

### `conjunto.c`

``` c
#include <stdlib.h>
#include "conjunto.h"

struct conjunto {

    int dados[MAX];
    int qtd;
};

Conjunto criar_conjunto(void) {

    Conjunto c = malloc(sizeof(struct conjunto));

    if (c != NULL) {
        c->qtd = 0;
    }

    return c;
}

void destruir_conjunto(Conjunto c) {

    free(c);
}

int pertence(Conjunto c, int valor) {

    for (int i = 0; i < c->qtd; i++) {

        if (c->dados[i] == valor) {
            return 1;
        }
    }

    return 0;
}

int inserir(Conjunto c, int valor) {

    if (c->qtd >= MAX) {
        return 0;
    }

    if (pertence(c, valor)) {
        return 0;
    }

    c->dados[c->qtd] = valor;
    c->qtd++;

    return 1;
}

int remover(Conjunto c, int valor) {

    for (int i = 0; i < c->qtd; i++) {

        if (c->dados[i] == valor) {

            for (int j = i; j < c->qtd - 1; j++) {
                c->dados[j] = c->dados[j + 1];
            }

            c->qtd--;

            return 1;
        }
    }

    return 0;
}

Conjunto uniao(Conjunto c1, Conjunto c2) {

    Conjunto resultado = criar_conjunto();

    if (resultado == NULL) {
        return NULL;
    }

    for (int i = 0; i < c1->qtd; i++) {
        inserir(resultado, c1->dados[i]);
    }

    for (int i = 0; i < c2->qtd; i++) {
        inserir(resultado, c2->dados[i]);
    }

    return resultado;
}

Conjunto intersecao(Conjunto c1, Conjunto c2) {

    Conjunto resultado = criar_conjunto();

    if (resultado == NULL) {
        return NULL;
    }

    for (int i = 0; i < c1->qtd; i++) {

        if (pertence(c2, c1->dados[i])) {
            inserir(resultado, c1->dados[i]);
        }
    }

    return resultado;
}

Conjunto diferenca(Conjunto c1, Conjunto c2) {

    Conjunto resultado = criar_conjunto();

    if (resultado == NULL) {
        return NULL;
    }

    for (int i = 0; i < c1->qtd; i++) {

        if (!pertence(c2, c1->dados[i])) {
            inserir(resultado, c1->dados[i]);
        }
    }

    return resultado;
}

int menor(Conjunto c) {

    if (c->qtd == 0) {
        return 0;
    }

    int menor_valor = c->dados[0];

    for (int i = 1; i < c->qtd; i++) {

        if (c->dados[i] < menor_valor) {
            menor_valor = c->dados[i];
        }
    }

    return menor_valor;
}

int maior(Conjunto c) {

    if (c->qtd == 0) {
        return 0;
    }

    int maior_valor = c->dados[0];

    for (int i = 1; i < c->qtd; i++) {

        if (c->dados[i] > maior_valor) {
            maior_valor = c->dados[i];
        }
    }

    return maior_valor;
}

int iguais(Conjunto c1, Conjunto c2) {

    if (c1->qtd != c2->qtd) {
        return 0;
    }

    for (int i = 0; i < c1->qtd; i++) {

        if (!pertence(c2, c1->dados[i])) {
            return 0;
        }
    }

    return 1;
}

int tamanho(Conjunto c) {

    return c->qtd;
}

int vazio(Conjunto c) {

    return c->qtd == 0;
}
```

### Exemplos das operações

Considere:

``` text
A = {1, 2, 3, 4}
B = {3, 4, 5, 6}
```

#### União

A união reúne todos os elementos dos dois conjuntos sem repetir valores:

``` text
A ∪ B = {1, 2, 3, 4, 5, 6}
```

No código:

``` c
Conjunto C = uniao(A, B);
```

#### Interseção

A interseção contém apenas os elementos presentes nos dois conjuntos:

``` text
A ∩ B = {3, 4}
```

No código:

``` c
Conjunto C = intersecao(A, B);
```

#### Diferença

A diferença `A - B` contém os elementos que estão em `A`, mas não estão
em `B`:

``` text
A - B = {1, 2}
```

No código:

``` c
Conjunto C = diferenca(A, B);
```

#### Pertinência

Para verificar se `3` pertence a `A`:

``` c
if (pertence(A, 3)) {
    printf("Pertence ao conjunto.\n");
}
```

#### Menor valor

Para:

``` text
A = {4, 8, 2, 10}
```

temos:

``` text
menor(A) = 2
```

#### Maior valor

Para o mesmo conjunto:

``` text
maior(A) = 10
```

#### Igualdade

Dois conjuntos são iguais quando possuem a mesma quantidade de elementos
e todos os elementos de um também pertencem ao outro.

Por exemplo:

``` text
A = {1, 2, 3}
B = {3, 1, 2}
```

Mesmo estando em ordens diferentes:

``` text
iguais(A, B) = 1
```

Isso acontece porque **a ordem dos elementos não importa em um
conjunto**.

#### Tamanho

Para:

``` text
A = {10, 20, 30, 40}
```

temos:

``` text
tamanho(A) = 4
```

#### Conjunto vazio

Um conjunto é considerado vazio quando não possui nenhum elemento:

``` text
A = {}
```

Nesse caso:

``` c
vazio(A)
```

retorna:

``` text
1
```

------------------------------------------------------------------------

## Resumo

  -----------------------------------------------------------------------
  Questão                 TAD                     Principais operações
  ----------------------- ----------------------- -----------------------
  **1**                   Conceito de TAD         Abstração e separação
                                                  entre interface e
                                                  implementação

  **2**                   Vantagens               Encapsulamento,
                                                  organização,
                                                  reutilização e
                                                  manutenção

  **3**                   Cilindro                Criar, destruir, obter
                                                  raio/altura, área e
                                                  volume

  **4**                   Número complexo         Criar, destruir, soma,
                                                  subtração,
                                                  multiplicação e divisão

  **5**                   Conjunto de inteiros    União, inserção,
                                                  remoção, interseção,
                                                  diferença e consultas
  -----------------------------------------------------------------------

## Estrutura recomendada dos arquivos

Uma possível organização para implementar os TADs é:

``` text
TAD/
├── README.md
│
├── cilindro.h
├── cilindro.c
│
├── complexo.h
├── complexo.c
│
├── conjunto.h
├── conjunto.c
│
└── main.c
```

A ideia é manter a **interface** nos arquivos `.h` e a **implementação**
nos arquivos `.c`.

``` text
        ┌──────────────┐
        │    main.c    │
        └──────┬───────┘
               │
               ↓
        ┌──────────────┐
        │ arquivo .h  │
        │  Interface   │
        └──────┬───────┘
               │
               ↓
        ┌──────────────┐
        │ arquivo .c  │
        │Implementação │
        └──────────────┘
```

Dessa forma, o programa principal utiliza as operações do TAD sem
precisar conhecer os detalhes internos de cada estrutura.
