#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    int n;      // tamanho do vetor
    int W;      // peso maximo da mochila
    int *pesos; // ponteiro
    int *beneficios;
} Arquivo; // struct para armazenar os dados

/*Função que recebe por parâmetro o endereço do arquivo  a ser aberto, contido na variável ”path”
Após o arquivo aberto, os dados são lidos, e salvos e retornado no endereço de memória da variável “ *data”
Se a abertura de arquivo não ocorrer com sucesso, o programa é interrompido*/
void abrir_arquivo(char *path, Arquivo *data);
/*Função básica que recebe como parâmetro uma dado contido em uma struct,
representado pela variável data. Esse dado é impresso na tela.
Repare que a struct contem um vetor interno alocado dinamicamente.*/
void imprimir_entrada(Arquivo data);
/*Função básica de alocação de memória, recebe como parâmetro uma dado contido em uma struct, representado pela variável data.
Esse vetor é alocado dinamicamente do tamanho do parâmetro n, e retornado por endereço de memória.
Se a alocação não ocorrer com sucesso, o programa é interrompido*/
void aloca_memoria(Arquivo *data);
/*Função básica de liberar a memória antes alocada.
Recebe como parâmetro um dado contido em uma struct,
representado pela variável data. Esse vetor interno a struct é liberado. */
void libera_memoria(Arquivo *data);

int verifica_solucao(int *vetor, int n, int *sol);
void verifica_alocacao(int *alocc);
void sol_imprime(int n, int *s);
void copia_lista(int n, int *copia, int *original);
void zera_lista(int n, int *v);

int calcula_permutacao(int base, int exp);
int maior(int n, int *v);
int menor(int n, int *v);
float maior_f(int n, float *v);
float menor_f(int n, float *v);

void gera_solucoes(int W, int *pesos, int *valores, int n, int *solucao, int qtd_sol);
int mochila_forca_bruta(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_beneficio(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_menor_peso(int W, int *pesos, int *valores, int n, int *solucao);
void mochila_peso_beneficio(int W, int *pesos, int *valores, int n, int *solucao);