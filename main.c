#include <stdio.h>
#include "func.h"

int main(){
    Itens *e;
    int n = 5;

    e = its_criar(n);

    if(e == NULL){
        printf("Memória não alocada!");
        exit(1);
    }

    e->pesos[0] = 2;
    e->valores[0] = 10;

    printf("Quantidade de itens: %d.\n", e->qtd_itens);
    printf("O item 1 pesa %dkg e custa %d$.\n", e->pesos[0], e->valores[0]);

    return 0;
}