#include <stdio.h>
#include <time.h>
#include "func.h"

int main()
{
    int n = 5, W = 9;                                   // quantidade de itens e o peso maximo que a mochila pode suportar
    int p[5] = {1, 3, 5, 6, 2}, v[5] = {3, 7, 1, 9, 3}; // pesos e valores dos itens
    int *sol = (int *)malloc(n * sizeof(int));          // vetor solucao
    int *pesos = (int *)malloc(n * sizeof(int)), *valores = (int *)malloc(n * sizeof(int));

    preenche_vetor(p, n, pesos);
    preenche_vetor(v, n, valores);

    if (sol == NULL || pesos == NULL || valores == NULL)
    { // verifica se a memoria esta sendo alocada corretamente
        printf("Memória não alocada!");
        exit(1);
    }

    /*
    mochila_forca_bruta(W, pesos, valores, qtd_itens, sol); // chama algoritmo do forca bruta
    */

    // solucoes aleatorias
    // gera_solucoes(W, pesos, valores, n, sol, 5000);

    // imprime resultados
    imprime_dados(pesos, valores, n);
    mochila_peso_beneficio(W, pesos, valores, n, sol);
    sol_imprime(n, sol);

    /*  float *pb = (float *)malloc(n * sizeof(float));

     peso_beneficio(n, pesos, valores, pb);

     for (int i = 0; i < n; i++)
     {
         printf("%f ", pb[i]);
     } */

    return 0;
}