#include <stdio.h>
#include <time.h>
#include "func.h"

int main(){
    Itens *e;
    int n = 5, W = 9; // quantidade de itens e o peso maximo que a mochila pode suportar
    int p[5] = {1, 3, 5, 6, 2}, v[5] = {3, 7, 1, 9, 3}; // pesos e valores dos itens
    int *sol = (int*)malloc(n * sizeof(int)); // vetor solucao

    srand(time(NULL));

    e = its_criar(n); // cria itens

    if(e == NULL){ // verifica se a memoria esta sendo alocada corretamente
        printf("Memória não alocada!");
        exit(1);
    }

    its_insere(e, p, v); // insere os dados dos ites
    its_imprime(e); // imprime dados dos itens
    /*
    mochila_forca_bruta(W, e->pesos, e->valores, e->qtd_itens, sol); // chama algoritmo do forca bruta
    */

    // solucoes aleatorias
    gera_solucoes(W, e->pesos, e->valores, e->qtd_itens, sol, 5000);

    // imprime resultados
    sol_imprime(n, sol);

    its_libera(e); // libera memoria 

    return 0;
}