#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preenche_vetor(int v[], int n, int *p);
void imprime_dados(int *pesos, int *valores, int n);
int *verifica_solucao(int *pesos, int *valores, int n, int *sol);

void sol_imprime(int n, int *s);
void copia_lista(int n, int *copia, int *original);
void zera_lista(int n, int *v);

int maximo(int a, int b);
int maior(int n, int *v);
int menor(int n, int *v);
float menor_f(int n, float *v);
void peso_beneficio(int n, int *p, int *v, float *r);

void solucao_aleatoria(int W, int *pesos, int *valores, int n, int *sol);
void gera_solucoes(int W, int *pesos, int *valores, int n, int *solucao, int qtd_sol);

int mochila_forca_bruta(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_beneficio(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_menor_peso(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_peso_beneficio(int W, int *pesos, int *valores, int n, int *solucao);