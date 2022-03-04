#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int qtd_itens;
    int *pesos;
    int *valores;
} Itens;

Itens* its_criar(int n);
void its_insere(Itens *e, int p[], int v[]);
void its_imprime(Itens *e);
void its_libera(Itens *e);

void sol_imprime(int n, int *s);

int max(int a, int b);
int mochila_forca_bruta(int W, int *wt, int *val, int n, int *sol);