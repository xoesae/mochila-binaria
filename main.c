#include <stdio.h>
#include <time.h>
#include "func.h"

int main()
{
    Arquivo data;        // arquivo lido
    clock_t tInicio;     // marcacao de tempo
    int peso, beneficio; // variaveis auxiliares
    abrir_arquivo("instancia1.txt", &data);

    int *sol = (int *)malloc(data.n * sizeof(int)); // aloca vetor solucao
    verifica_alocacao(sol);                         // verifica se foi alocada

    imprimir_entrada(data); // imprime dados de entrada

    /*
    As proximas linhas sao execucoes de todas heuristicas, cada heuristica segue a seguinte ordem:
        - imprime nome da heuristica
        - inicia contador
        - chama funcao da heuristica
        - imprime solucao
        - imprime o peso e beneficio que a solucao gerou
        - imprime o tempo de execucao em ms
    */

    printf("\nForca Bruta");
    tInicio = clock();
    mochila_forca_bruta(data.W, data.pesos, data.beneficios, data.n, sol);
    sol_imprime(data.n, sol);
    peso = verifica_solucao(data.pesos, data.n, sol), beneficio = verifica_solucao(data.beneficios, data.n, sol);
    printf("Peso: %d | Beneficio: %d\n", peso, beneficio);
    printf("Tempo de execução: %.4fms\n", ((double)(clock() - tInicio) / (CLOCKS_PER_SEC / 1000)));

    printf("\nAleatório");
    tInicio = clock();
    mochila_aleatoria(data.W, data.pesos, data.beneficios, data.n, sol, 50000);
    sol_imprime(data.n, sol);
    peso = verifica_solucao(data.pesos, data.n, sol), beneficio = verifica_solucao(data.beneficios, data.n, sol);
    printf("Peso: %d | Beneficio: %d\n", peso, beneficio);
    printf("Tempo de execução: %.4fms\n", ((double)(clock() - tInicio) / (CLOCKS_PER_SEC / 1000)));

    printf("\nMaior Beneficio");
    tInicio = clock();
    mochila_beneficio(data.W, data.pesos, data.beneficios, data.n, sol);
    sol_imprime(data.n, sol);
    peso = verifica_solucao(data.pesos, data.n, sol), beneficio = verifica_solucao(data.beneficios, data.n, sol);
    printf("Peso: %d | Beneficio: %d\n", peso, beneficio);
    printf("Tempo de execução: %.4fms\n", ((double)(clock() - tInicio) / (CLOCKS_PER_SEC / 1000)));

    printf("\nMenor peso");
    tInicio = clock();
    mochila_menor_peso(data.W, data.pesos, data.beneficios, data.n, sol);
    sol_imprime(data.n, sol);
    peso = verifica_solucao(data.pesos, data.n, sol), beneficio = verifica_solucao(data.beneficios, data.n, sol);
    printf("Peso: %d | Beneficio: %d\n", peso, beneficio);
    printf("Tempo de execução: %.4fms\n", ((double)(clock() - tInicio) / (CLOCKS_PER_SEC / 1000)));

    printf("\nPeso/Beneficio");
    tInicio = clock();
    mochila_peso_beneficio(data.W, data.pesos, data.beneficios, data.n, sol);
    sol_imprime(data.n, sol);
    peso = verifica_solucao(data.pesos, data.n, sol), beneficio = verifica_solucao(data.beneficios, data.n, sol);
    printf("Peso: %d | Beneficio: %d\n", peso, beneficio);
    printf("Tempo de execução: %.4fms\n", ((double)(clock() - tInicio) / (CLOCKS_PER_SEC / 1000)));

    // libera memoria
    free(sol);
    libera_memoria(&data);

    return 0;
}