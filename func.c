#include "func.h"

// TADs do Itens
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

void its_imprime(Itens *e){
    printf("Pesos: ");
    for(int i=0; i<e->qtd_itens; i++){
        printf("%d ", e->pesos[i]);
    }
    printf("\nValores: ");
    for(int i=0; i<e->qtd_itens; i++){
        printf("%d ", e->valores[i]);
    }
    printf("\n");
}

void its_verifica_solucao(Itens *e, int *sol){
    int w = 0, v = 0;
    for(int i=0; i<e->qtd_itens; i++){
        if(sol[i] == 1)
            w += e->pesos[i];
            v += e->valores[i];
    }
    printf("A solução usa %dkg e gera um valor de %d$.\n", w, v);
}

void its_libera(Itens *e){
    free(e->pesos);
    free(e->valores);
    free(e);
}

// funcoes uteis
void sol_imprime(int n, int *s){
    printf("Vetor solução: [ ");
    for(int i=0; i<n; i++){
        if(i == (n-1)){
            printf("%d ", s[i]);
        } else{
            printf("%d, ", s[i]);
        }
    }
    printf("]\n");
}

// funcoes mochila 0-1
int max(int a, int b) { return (a > b) ? a : b; }

int mochila_forca_bruta(int W, int *wt, int *val, int n, int *sol){
    // Base Case
    if (n == 0 || W == 0){
        return 0; // nao tem solucao
    }
        
    // If weight of the nth item is more than
    // Knapsack capacity W, then this item cannot
    // be included in the optimal solution
    if (wt[n - 1] > W){
        sol[n-1] = 1;
        return mochila_forca_bruta(W, wt, val, n - 1, sol);
    }
        
    // Return the maximum of two cases:
    // (1) nth item included
    // (2) not included
    else{
        int usa = val[n - 1] + mochila_forca_bruta(W - wt[n - 1], wt, val, n - 1, sol);
        int nao_usa = mochila_forca_bruta(W, wt, val, n - 1, sol);
        int maximo = max(usa, nao_usa);

        if(maximo == usa){
            sol[n-1] = 1;
        }

        return maximo;
    }
}