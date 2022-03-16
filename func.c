#include "func.h"

void verifica_alocacao(int *alocc)
{
    if (alocc == NULL)
    {
        printf("Memória não alocada com sucesso!\n");
        exit(EXIT_FAILURE);
    }
}

int verifica_solucao(int *vetor, int n, int *sol)
{
    int resultado = 0;
    for (int i = 0; i < n; i++)
    {
        if (sol[i] == 1)
        {
            resultado += vetor[i];
        }
    }
    return resultado;
}

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

int calcula_permutacao(int base, int exp)
{
    int permutacao = base;
    for (int i = 0; i < exp; i++)
    {
        permutacao = permutacao * base;
    }

    return permutacao;
}

// funcoes mochila 0-1
int mochila_forca_bruta(int W, int *pesos, int *valores, int n, int *solucao)
{
    int *melhor_sol = (int *)malloc(n * sizeof(int));
    verifica_alocacao(melhor_sol);
    int melhor_beneficio = verifica_solucao(valores, n, solucao),
        qtd_permutacao = calcula_permutacao(2, n);

    copia_lista(n, melhor_sol, solucao);

    for (int i = 0; i < qtd_permutacao; i++)
    {
        for (int j = 0; j < n; j++) // for que gera solucao
        {
            int aux = i % calcula_permutacao(2, j);
            if (aux == 0)
            {
                if (solucao[j] == 0)
                {
                    solucao[j] = 1;
                }
                else
                {
                    solucao[j] = 0;
                }
            }
        }
        int peso_aux = verifica_solucao(pesos, n, solucao);
        int beneficio_aux = verifica_solucao(valores, n, solucao);

        // peso - beneficio
        if (peso_aux <= W && beneficio_aux > melhor_beneficio)
        {
            melhor_beneficio = beneficio_aux;
            copia_lista(n, melhor_sol, solucao);
        }
    }

    copia_lista(n, solucao, melhor_sol);
    free(melhor_sol);
}

void gera_solucoes(int W, int *pesos, int *valores, int n, int *solucao, int qtd_sol)
{
    int *melhor_sol = (int *)malloc(n * sizeof(int)),
        melhor_beneficio = 0;
    verifica_alocacao(melhor_sol);

    srand(time(NULL));
    for (int i = 0; i < qtd_sol; i++)
    {
        for (int i = 0; i < n; i++)
        {
            int pos = rand() % n;
            solucao[pos] = 1;
        }

        int peso_aux = verifica_solucao(pesos, n, solucao);
        int beneficio_aux = verifica_solucao(valores, n, solucao);

        if (peso_aux <= W && beneficio_aux > melhor_beneficio)
        {
            copia_lista(n, melhor_sol, solucao);
            melhor_beneficio = beneficio_aux;
        }
        zera_lista(n, solucao);
    }

    copia_lista(n, solucao, melhor_sol);
    free(melhor_sol);
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

float maior_f(int n, float *v)
{
    float m = v[0];

    for (int i = 1; i < n; i++)
    {
        if (v[i] > m)
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

void mochila_beneficio(int W, int *pesos, int *valores, int n, int *solucao)
{
    int *p = (int *)malloc(n * sizeof(int)),
        *v = (int *)malloc(n * sizeof(int));

    verifica_alocacao(p);
    verifica_alocacao(v);

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
                v[i] = menor(n, v) - 1;
                maior_valor = maior(n, v);
            }
        }
    }

    free(p);
    free(v);
}

void mochila_menor_peso(int W, int *pesos, int *valores, int n, int *solucao)
{
    int *p = (int *)malloc(n * sizeof(int)),
        *v = (int *)malloc(n * sizeof(int));

    verifica_alocacao(p);
    verifica_alocacao(v);

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
                p[i] = maior(n, p) + 1;
                menor_peso = menor(n, p);
            }
        }
    }
    free(p);
    free(v);
}

void mochila_peso_beneficio(int W, int *pesos, int *valores, int n, int *solucao)
{
    int *p = (int *)malloc(n * sizeof(int)),
        *v = (int *)malloc(n * sizeof(int));
    float *pb = (float *)malloc(n * sizeof(float));

    verifica_alocacao(p);
    verifica_alocacao(v);
    if (pb == NULL)
    {
        printf("Memória não alocada com sucesso!\n");
        exit(EXIT_FAILURE);
    }

    copia_lista(n, p, pesos);
    copia_lista(n, v, valores);

    for (int i = 0; i < n; i++)
    {
        float temp = (float)p[i] / (float)v[i];
        pb[i] = temp;
    }

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
                pb[i] = maior_f(n, pb) + 1;
                menor_pb = menor_f(n, pb);
            }
        }
    }

    free(p);
    free(v);
    free(pb);
};

/*Função básica de alocação de memória, recebe como parâmetro uma dado contido em uma struct, representado pela variável data.
Esse vetor é alocado dinamicamente do tamanho do parâmetro n, e retornado por endereço de memória.*/
void aloca_memoria(Arquivo *data)
{
    data->pesos = (int *)malloc(data->n * sizeof(int));
    data->beneficios = (int *)malloc(data->n * sizeof(int));
    verifica_alocacao(data->pesos);
    verifica_alocacao(data->beneficios);
}

void libera_memoria(Arquivo *data)
{
    free(data->pesos);
    free(data->beneficios);
}

/*Função básica que recebe como parâmetro uma dado contido em uma struc,
representado pela variável data. Esse dado é impresso na tela.
Repare que a struct contem um vetor interno alocado dinamicamente.*/
void imprimir_entrada(Arquivo data)
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
    // o primero valor lido é o valor de "W", que e a capacidade da mochila
    data->W = valor;

    // o segundo valor lido é o valor de "n", logo é o tamanho do vetor a ser alocado
    fscanf(pont_arq, "%d", &valor);
    data->n = valor;

    aloca_memoria(data); // aloca a memoria dos vetores

    // se existem n valores, este valores vão ser lidos sequencialmente
    for (int i = 0; i < data->n; i++)
    {
        fscanf(pont_arq, "%d", &valor); // lê os valores sequentemente da linha, um por um
        // o valor sendo lido nessa linha é o peso
        data->pesos[i] = valor; // atrivui cada valor lido a posição do vetor que é retornado por endereço de memoria
    }

    for (int i = 0; i < data->n; i++)
    {
        fscanf(pont_arq, "%d", &valor); // lê os valores sequentemente da linha, um por um
        // o valor sendo lido nessa linha é o beneficio
        data->beneficios[i] = valor; // atrivui cada valor lido a posição do vetor que é retornado por endereço de memoria
    }

    // fechando arquivo - Nunca se esqueça!
    fclose(pont_arq);

    // FIM :)
}
