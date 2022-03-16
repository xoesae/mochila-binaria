#include <stdio.h>
#include <time.h>
#include "func.h"

int main()
{
    Arquivo data;
    clock_t tInicio;
    int *resultado, peso, beneficio;
    abrir_arquivo("instancia4.txt", &data);

    int *sol = (int *)malloc(data.n * sizeof(int)); // vetor solucao
    verifica_alocacao(sol);

    imprimir_entrada(data);

    printf("\n");

    zera_lista(data.n, sol);
    printf("Solução Forca Bruta: ");
    tInicio = clock();                                                     // inicia a marcação do tempo
    mochila_forca_bruta(data.W, data.pesos, data.beneficios, data.n, sol); // chama algoritmo do forca bruta
    sol_imprime(data.n, sol);
    peso = verifica_solucao(data.pesos, data.n, sol), beneficio = verifica_solucao(data.beneficios, data.n, sol);
    printf("Peso: %d | Beneficio: %d\n", peso, beneficio);
    printf("Tempo de execução: %.4fms\n", ((double)(clock() - tInicio) / (CLOCKS_PER_SEC / 1000)));

    printf("\n");

    zera_lista(data.n, sol);
    printf("Solução aleatória: ");
    tInicio = clock();
    gera_solucoes(data.W, data.pesos, data.beneficios, data.n, sol, 50000);
    sol_imprime(data.n, sol);
    peso = verifica_solucao(data.pesos, data.n, sol), beneficio = verifica_solucao(data.beneficios, data.n, sol);
    printf("Peso: %d | Beneficio: %d\n", peso, beneficio);
    printf("Tempo de execução: %.4fms\n", ((double)(clock() - tInicio) / (CLOCKS_PER_SEC / 1000)));

    printf("\n");

    zera_lista(data.n, sol);
    printf("Maior Beneficio: ");
    tInicio = clock();
    mochila_beneficio(data.W, data.pesos, data.beneficios, data.n, sol);
    sol_imprime(data.n, sol);
    peso = verifica_solucao(data.pesos, data.n, sol), beneficio = verifica_solucao(data.beneficios, data.n, sol);
    printf("Peso: %d | Beneficio: %d\n", peso, beneficio);
    printf("Tempo de execução: %.4fms\n", ((double)(clock() - tInicio) / (CLOCKS_PER_SEC / 1000)));

    printf("\n");

    zera_lista(data.n, sol);
    printf("Menor peso: ");
    tInicio = clock();
    mochila_menor_peso(data.W, data.pesos, data.beneficios, data.n, sol);
    sol_imprime(data.n, sol);
    peso = verifica_solucao(data.pesos, data.n, sol), beneficio = verifica_solucao(data.beneficios, data.n, sol);
    printf("Peso: %d | Beneficio: %d\n", peso, beneficio);
    printf("Tempo de execução: %.4fms\n", ((double)(clock() - tInicio) / (CLOCKS_PER_SEC / 1000)));

    printf("\n");

    zera_lista(data.n, sol);
    printf("Peso/Beneficio: ");
    tInicio = clock();
    mochila_peso_beneficio(data.W, data.pesos, data.beneficios, data.n, sol);
    sol_imprime(data.n, sol);
    peso = verifica_solucao(data.pesos, data.n, sol), beneficio = verifica_solucao(data.beneficios, data.n, sol);
    printf("Peso: %d | Beneficio: %d\n", peso, beneficio);
    printf("Tempo de execução: %.4fms\n", ((double)(clock() - tInicio) / (CLOCKS_PER_SEC / 1000)));

    free(sol);
    libera_memoria(&data);

    return 0;
}