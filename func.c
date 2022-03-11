#include "func.h"

void preenche_vetor(int v[], int n, int *p)
{
    for (int i = 0; i < n; i++)
    {
        p[i] = v[i];
    }
}

void imprime_dados(int *pesos, int *valores, int n)
{
    printf("Pesos: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", pesos[i]);
    }
    printf("\nValores: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", valores[i]);
    }
    printf("\n");
}

int *verifica_solucao(int *pesos, int *valores, int n, int *sol)
{
    int *resultado = (int *)malloc(2 * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        if (sol[i] == 1)
        {
            resultado[0] += pesos[i];
            resultado[1] += valores[i];
        }
    }
    return resultado;
}

// funcoes uteis
void sol_imprime(int n, int *s)
{
    printf("Vetor solução: [ ");
    for (int i = 0; i < n; i++)
    {
        if (i == (n - 1))
        {
            printf("%d ", s[i]);
        }
        else
        {
            printf("%d, ", s[i]);
        }
    }
    printf("]\n");
}

void copia_lista(int n, int *copia, int *original)
{
    for (int i = 0; i < n; i++)
    {
        copia[i] = original[i];
    }
}

int maximo(int a, int b) { return (a > b) ? a : b; }

// funcoes mochila 0-1
int mochila_forca_bruta(int W, int *pesos, int *valores, int n, int *solucao)
{
    int i, w;
    int K[n + 1][W + 1]; // cria tabela

    // preenche tabela
    for (i = 0; i <= n; i++)
    { // percorre linhas
        for (w = 0; w <= W; w++)
        { // percorre pesos
            if (i == 0 || w == 0)
            { // primeira posicao d tabela recebe zero
                K[i][w] = 0;
            }
            else if (pesos[i - 1] <= w)
            {                                                          // se posicao i-1 for menor ou igual ao peso
                int usa = valores[i - 1] + K[i - 1][w - pesos[i - 1]]; // somao valor i-1 com a posicao K[i - 1][w - pesos[i - 1]] da tabela
                int nao_usa = K[i - 1][w];                             // pega somente a posicao anterior da tabela
                K[i][w] = maximo(usa, nao_usa);                        // adiciona o maior valor na tabela
            }
            else
            { // se for maior que o peso, so repete o valor da linha de cima
                K[i][w] = K[i - 1][w];
            }
        }
    }

    // armazena resultados da mochila
    // pega o ultimo elemento da tabela que é o melhor caso
    int res = K[n][W];

    w = W; // variavel auxiliar recebe o peso maximo
    for (i = n; i > 0 && res > 0; i--)
    { // percorre ao contrario, de n ate 0, verificando sempre se o res tambem zerou
        if (res == K[i - 1][w])
        { // se res é igual a k[i-1][w], nao fazemos nada
            continue;
        }
        else
        {
            // tem item na posicao i-1
            solucao[i - 1] = 1;

            // remove o valor e peso na posicao i-1
            res = res - valores[i - 1];
            w = w - pesos[i - 1];
        }
    }
}

void solucao_aleatoria(int W, int *pesos, int *valores, int n, int *sol)
{
    // sorteia quantas posicoes vao ser preenchidos
    srand(time(NULL));
    int n_pos = (rand() % n); // numeros de 0 a n-1
    if (n_pos == 0)
    {
        n_pos += 1;
    }

    // sorteia em quais posicoes ira ser escolhido
    srand(time(NULL));
    int *aux = (int *)malloc(n_pos * sizeof(int));
    for (int i = 0; i < n_pos; i++)
    {
        aux[i] = rand() % n;
        if (aux[i] == aux[i - 1] && i != 0)
        {
            aux[i] = rand() % n;
        }
    }

    // preencha as posicoes sorteadas
    for (int i = 0; i < n_pos; i++)
    {
        int pos = aux[i];
        sol[pos] = 1;
    }

    free(aux);
}

void gera_solucoes(int W, int *pesos, int *valores, int n, int *solucao, int qtd_sol)
{
    int *melhor_sol = (int *)malloc(n * sizeof(int)), *aux;
    int *melhor_resultado = verifica_solucao(pesos, valores, n, solucao);

    for (int i = 0; i < qtd_sol; i++)
    {
        solucao_aleatoria(W, pesos, valores, n, solucao);
        aux = verifica_solucao(pesos, valores, n, solucao);

        if (aux[0] <= 9 && aux[1] > melhor_resultado[1])
        {
            copia_lista(n, melhor_sol, solucao);
            melhor_resultado = aux;
        }
    }

    copia_lista(n, solucao, melhor_sol);

    free(melhor_sol);
    free(melhor_resultado);
}

int maior(int n, int *v)
{
    int m = v[0];

    for (int i = 1; i < n; i++)
    {
        if (v[i] > m)
            m = v[i];
    }
    return m;
}

int menor(int n, int *v)
{
    int m = v[0];

    for (int i = 1; i < n; i++)
    {
        if (v[i] < m)
            m = v[i];
    }
    return m;
}

float menor_f(int n, float *v)
{
    float m = v[0];

    for (int i = 1; i < n; i++)
    {
        if (v[i] < m)
            m = v[i];
    }
    return m;
}

int iguais(int n, int *v1, int *v2)
{
    int b = 1;
    for (int i = 0; i < n; i++)
    {
        if (v1[i] != v2[i])
        {
            b = 0;
            break;
        }
    }
    return b;
}

void peso_beneficio(int n, int *p, int *v, float *r)
{
    for (int i = 0; i < n; i++)
    {
        float temp = (float)p[i] / (float)v[i];
        r[i] = temp;
    }
}

void mochila_beneficio(int W, int *pesos, int *valores, int n, int *solucao)
{
    int maior_valor = maior(n, valores);
    int *aux = (int *)malloc(n * sizeof(int)), j;

    for (j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (solucao[i] == 0 && pesos[i] <= W && valores[i] == maior_valor)
            {
                W -= pesos[i];
                valores[i] = -999;
                maior_valor = maior(n, valores);
                solucao[i] = 1;
            }
            if (solucao[i] == 0 && pesos[i] > W && valores[i] == maior_valor)
            {
                valores[i] = -999;
                maior_valor = maior(n, valores);
            }
        }
        copia_lista(n, aux, solucao);
    }
    free(aux);
}

void mochila_menor_peso(int W, int *pesos, int *valores, int n, int *solucao)
{
    int menor_peso = menor(n, pesos);
    int *aux = (int *)malloc(n * sizeof(int)), j;

    for (j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (solucao[i] == 0 && pesos[i] <= W && pesos[i] == menor_peso)
            {
                W -= pesos[i];
                pesos[i] = 10000000;
                menor_peso = menor(n, pesos);
                solucao[i] = 1;
            }
            if (solucao[i] == 0 && pesos[i] > W && pesos[i] == menor_peso)
            {
                pesos[i] = 10000000;
                menor_peso = menor(n, pesos);
            }
        }
        copia_lista(n, aux, solucao);
    }
    free(aux);
}

void mochila_peso_beneficio(int W, int *pesos, int *valores, int n, int *solucao)
{
    int *aux = (int *)malloc(n * sizeof(int)), j;
    float *pb = (float *)malloc(n * sizeof(float));

    peso_beneficio(n, pesos, valores, pb);
    float menor_pb = menor_f(n, pb);

    for (j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (solucao[i] == 0 && pesos[i] <= W && pb[i] == menor_pb)
            {
                W -= pesos[i];
                pb[i] = 10000000;
                menor_pb = menor_f(n, pb);
                solucao[i] = 1;
            }
            if (solucao[i] == 0 && pesos[i] > W && pb[i] == menor_pb)
            {
                pb[i] = 10000000;
                menor_pb = menor_f(n, pb);
            }
        }
    }
    free(aux);
    free(pb);
};