#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int n;           // tamanho do vetor
    int W;           // peso maximo da mochila
    int *pesos;      // ponteiro para o vetor de pesos
    int *beneficios; // ponteiro para o vetor de beneficios
} Arquivo;           // struct para armazenar os dados

void abrir_arquivo(char *path, Arquivo *data); // funcao que abre arquivo txt e le seus dados
void imprimir_entrada(Arquivo data);           // imprime valores lidos da entrada
void aloca_memoria(Arquivo *data);             // aloca memoria dos vetores do struct
void libera_memoria(Arquivo *data);            // libera memoria do struct

int verifica_solucao(int *vetor, int n, int *sol);  // recebe um vetor(peso ou beneficio) e uma solucao e retorna qual o peso ou beneficio da solucao
void verifica_alocacao(int *alocc);                 // verifica se a alocacao ocorreu de maneira correta
void sol_imprime(int n, int *s);                    // imprime vetor solucao
void copia_lista(int n, int *copia, int *original); // copia valores de um vetor para outro
void zera_lista(int n, int *v);                     // coloca 0 em todas as posicoes de um vetor

int potencia(int base, int exp); // calcula quantidades possiveis do forca bruta
int maior(int n, int *v);        // retorna maior valor de um vetor de inteiros
int menor(int n, int *v);        // retorna menor valor de um vetor de inteiros
float maior_f(int n, float *v);  // retorna maior valor de um vetor de float
float menor_f(int n, float *v);  // retorna menor valor de um vetor de float

// heuristicas para gerar solucoes
void mochila_forca_bruta(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_aleatoria(int W, int *pesos, int *valores, int n, int *solucao, int qtd_sol);
void mochila_beneficio(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_menor_peso(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_peso_beneficio(int W, int *pesos, int *valores, int n, int *solucao);