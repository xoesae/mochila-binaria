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

int* its_verifica_solucao(int *pesos, int *valores, int n, int *sol){
    int *resultado = (int*)malloc(2 * sizeof(int));
    for(int i=0; i<n; i++){
        if(sol[i] == 1){
            resultado[0] += pesos[i];
            resultado[1] += valores[i];
        }  
    }
    return resultado;
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

void copia_lista(int n, int *copia, int *original){
    for (int i = 0; i < n; i++){
        copia[i] = original[i];
    }
}

// funcoes mochila 0-1
int maximo(int a, int b) { return (a > b) ? a : b; }

int mochila_forca_bruta(int W, int *pesos, int *valores, int n, int *solucao)
{
    int i, w;
    int K[n + 1][W + 1];
 
    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0){
                K[i][w] = 0;
            } 
            else if (pesos[i - 1] <= w){
                int usa = valores[i - 1] + K[i - 1][w - pesos[i - 1]];
                int nao_usa = K[i - 1][w];
                K[i][w] = maximo(usa, nao_usa);
            }
            else{
                K[i][w] = K[i - 1][w];
            }
        }
    }
 
    // armazena resultados da mochila
    int res = K[n][W];  
     
    w = W;
    for (i = n; i > 0 && res > 0; i--) {
        // either the result comes from the top
        // (K[i-1][w]) or from (valores[i-1] + K[i-1]
        // [w-pesos[i-1]]) as in Knapsack table. If
        // it comes from the latter one/ it means
        // the item is included.
        if (res == K[i - 1][w]){
            continue;   
        }    
        else {
            // tem item na posicao i-1
            solucao[i -1] = 1;
             
            // remove o valor e peso na posicao i-1
            res = res - valores[i - 1];
            w = w - pesos[i - 1];
        }
    }
}

void solucao_aleatoria(int W, int *pesos, int *valores, int n, int *sol){
    // sorteia quantas posicoes vao ser preenchidos
    srand(time(NULL));
    int n_pos = (rand() % n); // numeros de 0 a n-1
    if(n_pos == 0){
        n_pos += 1;
    }

    // sorteia em quais posicoes ira ser escolhido
    srand(time(NULL));
    int *aux = (int*)malloc(n_pos * sizeof(int));
    for(int i=0; i < n_pos; i++){
        aux[i] = rand() % n;
        if(aux[i] == aux[i-1] && i != 0){
            aux[i] = rand() % n;
        }
    }

    // preencha as posicoes sorteadas
    for(int i=0; i<n_pos; i++){
        int pos = aux[i];
        sol[pos] = 1;
    }
}

void gera_solucoes(int W, int *pesos, int *valores, int n, int *solucao, int qtd_sol){
    int *melhor_sol = (int*)malloc(n * sizeof(int)), *aux;
    int *melhor_resultado = its_verifica_solucao(pesos, valores, n, solucao);

    srand(time(NULL));
    printf("peso %d\n", W);
    for (int i=0; i < qtd_sol; i++){
        solucao_aleatoria(W, pesos, valores, n, solucao);
        aux = its_verifica_solucao(pesos, valores, n, solucao);

        if(aux[0] <= 9 && aux[1] > melhor_resultado[1]){
            copia_lista(n, melhor_sol, solucao);
            melhor_resultado = aux;
        }
    }

    copia_lista(n, solucao, melhor_sol);
}