#include <stdio.h>
#include "func.h"

int main(){
    Itens *e;
    int n = 3, W = 3; // quantidade de itens e o peso maximo que a mochila pode suportar
    int p[3] = {1, 2, 3}, v[3] = {10, 15, 20}; // pesos e valores dos itens
    int *sol = (int*)malloc(n * sizeof(int)); // vetor solucao

    e = its_criar(n); // cria itens

    if(e == NULL){ // verifica se a memoria esta sendo alocada corretamente
        printf("Memória não alocada!");
        exit(1);
    }

    its_insere(e, p, v); // insere os dados dos ites
    its_imprime(e); // imprime dados dos itens

    int r = mochila_forca_bruta(W, e->pesos, e->valores, e->qtd_itens, sol); // chama algoritmo do forca bruta

    // imprime resultados
    printf("O peso máximo que a mochila pode carregar é de %d.\n", W);
    printf("Vetor solução: ");
    sol_imprime(n, sol);
    printf("Valor máximo carregado: %d\n", r);

    its_libera(e); // libera memoria
    
    return 0;
}