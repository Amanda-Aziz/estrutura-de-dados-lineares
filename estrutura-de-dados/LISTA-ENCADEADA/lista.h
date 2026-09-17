#include "lista_int.c"
typedef struct elem Elem;
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