#include <stdio.h>
#include "func.h"

int main(){
    Itens *e;
    int n = 5;
    int p[5] = {1, 2, 3, 4, 5};
    int v[5] = {10, 15, 20, 25, 30};

    e = its_criar(n);

    if(e == NULL){
        printf("Memória não alocada!");
        exit(1);
    }

    its_insere(e, p, v);

    printf("Quantidade de itens: %d.\n", e->qtd_itens);
    printf("O item 1 pesa %dkg e custa %d$.\n", e->pesos[0], e->valores[0]);

    return 0;
}