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
    zera_lista(n, resultado);
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
    printf("[ ");
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

void zera_lista(int n, int *v)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = 0;
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

    zera_lista(n, melhor_sol);

    for (int i = 0; i < qtd_sol; i++)
    {
        solucao_aleatoria(W, pesos, valores, n, solucao);
        aux = verifica_solucao(pesos, valores, n, solucao);

        if (aux[0] <= W && aux[1] > melhor_resultado[1])
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
    int *p = (int *)malloc(n * sizeof(int)), *v = (int *)malloc(n * sizeof(int));
    copia_lista(n, p, pesos);
    copia_lista(n, v, valores);

    int maior_valor = maior(n, v);

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (solucao[i] == 0 && v[i] == maior_valor)
            {
                if (p[i] <= W)
                {
                    W -= p[i];
                    solucao[i] = 1;

                    if (W == 0)
                        break;
                }
                v[i] = -99999;
                maior_valor = maior(n, v);
            }
        }
    }
}

void mochila_menor_peso(int W, int *pesos, int *valores, int n, int *solucao)
{
    int *p = (int *)malloc(n * sizeof(int)), *v = (int *)malloc(n * sizeof(int));
    copia_lista(n, p, pesos);
    copia_lista(n, v, valores);

    int menor_peso = menor(n, p);

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (solucao[i] == 0 && p[i] == menor_peso)
            {
                if (p[i] <= W)
                {
                    W -= p[i];
                    solucao[i] = 1;

                    if (W == 0)
                        break;
                }
                p[i] = 10000000;
                menor_peso = menor(n, p);
            }
        }
    }
}

void mochila_peso_beneficio(int W, int *pesos, int *valores, int n, int *solucao)
{
    int *p = (int *)malloc(n * sizeof(int)), *v = (int *)malloc(n * sizeof(int));
    copia_lista(n, p, pesos);
    copia_lista(n, v, valores);

    float *pb = (float *)malloc(n * sizeof(float));
    peso_beneficio(n, p, v, pb);
    float menor_pb = menor_f(n, pb);

    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++)
        {
            if (solucao[i] == 0 && pb[i] == menor_pb)
            {
                if (p[i] <= W)
                {
                    W -= p[i];
                    solucao[i] = 1;

                    if (W == 0)
                        break;
                }
                pb[i] = 10000000.0;
                menor_pb = menor_f(n, pb);
            }
        }
    }
    free(pb);
};

/*Função básica de alocação de memória, recebe como parâmetro uma dado contido em uma struct, representado pela variável data.
Esse vetor é alocado dinamicamente do tamanho do parâmetro n, e retornado por endereço de memória.*/
void aloca_memoria(Arquivo *data)
{
    data->pesos = (int *)malloc(data->n * sizeof(int));
    data->beneficios = (int *)malloc(data->n * sizeof(int));
    if (data->pesos == NULL || data->beneficios == NULL)
    {
        printf("Memória não alocada com sucesso!\n");
        exit(EXIT_FAILURE);
    }
}

void libera_memoria(Arquivo *data)
{
    free(data->pesos);
    free(data->beneficios);
}

/*Função básica que recebe como parâmetro uma dado contido em uma struc,
representado pela variável data. Esse dado é impresso na tela.
Repare que a struct contem um vetor interno alocado dinamicamente.*/
void imprimir(Arquivo data)
{
    printf("W = %d\nn = %d\nPesos: ", data.W, data.n);
    for (int i = 0; i < data.n; i++)
        printf("%d ", data.pesos[i]);
    printf("\nBenefícios: ");
    for (int i = 0; i < data.n; i++)
        printf("%d ", data.beneficios[i]);
    printf("\n");
}

/*Função que recebe por parâmetro o endereço do arquivo  a ser aberto, contido na variável ”path”
Após o arquivo aberto, os dados são lidos, e salvos e retornado no endereço de memória da variável “ *data”*/
void abrir_arquivo(char *path, Arquivo *data)
{
    // criando a variável ponteiro para o arquivo
    FILE *pont_arq;
    int valor; // variável para leitura de cada valor

    // abrindo o arquivo para leitura - caminho do arquivo em path e modo read
    pont_arq = fopen(path, "r");

    // verificando se arquivo foi aberto com sucesso
    if (pont_arq == NULL)
    {
        printf("ERRO! O arquivo não foi aberto!\n");
        exit(EXIT_FAILURE);
    }

    // A função fscanf() funciona como a função scanf(). A diferença é que fscanf() lê de um arquivo e não do teclado do computador.
    fscanf(pont_arq, "%d", &valor);
    // o primero valor lido é o valor de "n", logo é o tamanho do vetor a ser alocado
    data->W = valor;

    fscanf(pont_arq, "%d", &valor);
    data->n = valor;

    aloca_memoria(data);

    // se existem n valores, este valores vão ser lidos sequencialmente
    for (int i = 0; i < data->n; i++)
    {
        fscanf(pont_arq, "%d", &valor); // lê os valores sequentemente da linha, um por um
        data->pesos[i] = valor;         // atrivui cada valor lido a posição do vetor que é retornado por endereço de memoria
    }

    for (int i = 0; i < data->n; i++)
    {
        fscanf(pont_arq, "%d", &valor); // lê os valores sequentemente da linha, um por um
        data->beneficios[i] = valor;    // atrivui cada valor lido a posição do vetor que é retornado por endereço de memoria
    }

    // fechando arquivo - Nunca se esqueça!
    fclose(pont_arq);

    // FIM :)
}
