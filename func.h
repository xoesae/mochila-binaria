#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void preenche_vetor(int v[], int n, int *p);
void imprime_dados(int *pesos, int *valores, int n);
int *verifica_solucao(int *pesos, int *valores, int n, int *sol);

void sol_imprime(int n, int *s);
void copia_lista(int n, int *copia, int *original);

int maximo(int a, int b);
int maior(int n, int *v);
int menor(int n, int *v);
int iguais(int n, int *v1, int *v2);

void solucao_aleatoria(int W, int *pesos, int *valores, int n, int *sol);
void gera_solucoes(int W, int *pesos, int *valores, int n, int *solucao, int qtd_sol);

int mochila_forca_bruta(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_beneficio(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_menor_peso(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_maior_peso(int W, int *pesos, int *valores, int n, int *solucao);