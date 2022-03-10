#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    int qtd_itens;
    int *pesos;
    int *valores;
} Itens;

Itens* its_criar(int n);
void its_insere(Itens *e, int p[], int v[]);
void its_imprime(Itens *e);
int* its_verifica_solucao(int *pesos, int *valores, int n, int *sol);
void its_libera(Itens *e);

void sol_imprime(int n, int *s);
void copia_lista(int n, int *copia, int *original);

int maximo(int a, int b);
int mochila_forca_bruta(int W, int *pesos, int *valores, int n, int *solucao);

void solucao_aleatoria(int W, int *pesos, int *valores, int n, int *sol);
void gera_solucoes(int W, int *pesos, int *valores, int n, int *solucao, int qtd_sol);