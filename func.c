#include "func.h"

Itens* its_criar(int n){
    Itens *e = (Itens*)malloc(sizeof(Itens));
    e->qtd_itens = n;
    e->pesos = (int*)malloc(n * sizeof(int));
    e->valores = (int*)malloc(n * sizeof(int));
    return e;
}

void its_insere(Itens *e, int p[], int v[]){
    for(int i=0; i<e->qtd_itens; i++){
        e->pesos[i] = p[i];
        e->valores[i] = v[i];
    }
}