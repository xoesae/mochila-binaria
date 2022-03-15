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

typedef struct
{          // struct para armazenar os dados
    int n; // tamanho do vetor
    int W;
    int *pesos; // vator que ira ser alocado dinamicamente
    int *beneficios;
} Arquivo;

/*Função que recebe por parâmetro o endereço do arquivo  a ser aberto, contido na variável ”path”
Após o arquivo aberto, os dados são lidos, e salvos e retornado no endereço de memória da variável “ *data”
Se a abertura de arquivo não ocorrer com sucesso, o programa é interrompido*/
void abrir_arquivo(char *path, Arquivo *data);
/*Função básica que recebe como parâmetro uma dado contido em uma struct,
representado pela variável data. Esse dado é impresso na tela.
Repare que a struct contem um vetor interno alocado dinamicamente.*/
void imprimir(Arquivo data);
/*Função básica de alocação de memória, recebe como parâmetro uma dado contido em uma struct, representado pela variável data.
Esse vetor é alocado dinamicamente do tamanho do parâmetro n, e retornado por endereço de memória.
Se a alocação não ocorrer com sucesso, o programa é interrompido*/
void aloca_memoria(Arquivo *data);
/*Função básica de liberar a memória antes alocada.
Recebe como parâmetro um dado contido em uma struct,
representado pela variável data. Esse vetor interno a struct é liberado. */
void libera_memoria(Arquivo *data);