#include <stdio.h>
#include <stdlib.h>


typedef struct{
    int qtd_itens;
    int *pesos;
    int *valores;
} Itens;

Itens* its_criar(int n);