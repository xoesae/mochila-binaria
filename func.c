#include "func.h"

Itens* its_criar(int n){
    Itens *e = (Itens*)malloc(sizeof(Itens));
    e->qtd_itens = n;
    e->pesos = (int*)malloc(n * sizeof(int));
    e->valores = (int*)malloc(n * sizeof(int));
    return e;
}