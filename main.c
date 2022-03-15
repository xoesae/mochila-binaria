#include <stdio.h>
#include <time.h>
#include "func.h"

int main()
{
    /*
    int n = 5, W = 15;                                    // quantidade de itens e o peso maximo que a mochila pode suportar
    int p[5] = {12, 1, 4, 1, 2}, v[5] = {4, 2, 10, 1, 2}; // pesos e valores dos itens

    */

    Arquivo data;
    abrir_arquivo("ex1.txt", &data);
    imprimir(data);
    int *sol = (int *)malloc(data.n * sizeof(int)); // vetor solucao
    int *pesos = (int *)malloc(data.n * sizeof(int)), *valores = (int *)malloc(data.n * sizeof(int));
    if (sol == NULL || pesos == NULL || valores == NULL)
    { // verifica se a memoria esta sendo alocada corretamente
        printf("Memória não alocada!");
        exit(1);
    }
    /*
        preenche_vetor(p, n, pesos);
        preenche_vetor(v, n, valores); */

    // ler dados do arquivo txt

    /* imprime_dados(pesos, valores, data.n);

    printf("Solução Forca Bruta: ");
    mochila_forca_bruta(W, pesos, valores, data.n, sol); // chama algoritmo do forca bruta
    sol_imprime(data.n, sol);
    zera_lista(data.n, sol);

    printf("Solução aleatória: ");
    gera_solucoes(W, pesos, valores, data.n, sol, 50000);
    sol_imprime(data.n, sol);
    zera_lista(data.n, sol);

    printf("Maior Beneficio: ");
    mochila_beneficio(W, pesos, valores, data.n, sol);
    sol_imprime(data.n, sol);
    zera_lista(data.n, sol);

    printf("Menor peso: ");
    mochila_menor_peso(W, pesos, valores, data.n, sol);
    sol_imprime(data.n, sol);
    zera_lista(data.n, sol);

    printf("Peso/Beneficio: ");
    mochila_peso_beneficio(W, pesos, valores, data.n, sol);
    sol_imprime(data.n, sol); */

    free(sol);
    free(pesos);
    free(valores);
    libera_memoria(&data);

    return 0;
}