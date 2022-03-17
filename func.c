#include "func.h"

// recebe um vetor com valores e calcula o valor total com base no vetor sol
int verifica_solucao(int *vetor, int n, int *sol)
{
    int resultado = 0; // resultado inicia com zero
    for (int i = 0; i < n; i++)
    {
        if (sol[i] == 1) // quando o vetor sol na posicao i for igual a 1
        {
            resultado += vetor[i]; // soma o valor da posicao i no resultado
        }
    }
    return resultado; // retorna resultado
}

// recebe um ponteiro com alocacao
void verifica_alocacao(int *alocc)
{
    if (alocc == NULL) // verifica se ocorreu com sucesso
    {
        printf("Memória não alocada com sucesso!\n");
        exit(EXIT_FAILURE);
    }
}

// imprime solucao
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

// recebe dois ponteiros de vetores e copia uma para a outra
// essa funcao é util pois nao podemos somente atribuir
// copia = original
// pois assim é copiado o endereco de memoria do vetor original
void copia_lista(int n, int *copia, int *original)
{
    for (int i = 0; i < n; i++)
    {
        copia[i] = original[i];
    }
}

// atribui zeros em todas posicoes de um vetor
void zera_lista(int n, int *v)
{
    for (int i = 0; i < n; i++)
    {
        v[i] = 0;
    }
}

// calcula potencia de base elevado a exp
// util para calcular a quantidade de solucoes possíveis
// do forca bruta, que é 2^n
int potencia(int base, int exp)
{
    int permutacao = base;
    for (int i = 0; i < exp; i++)
    {
        permutacao = permutacao * base;
    }

    return permutacao;
}

// pega maior valor de um vetor
int maior(int n, int *v)
{
    int m = v[0];

    for (int i = 1; i < n; i++)
    {
        if (v[i] > m) // se o valor atual é maior que o maior valor
            m = v[i]; // ele é o maior valor
    }
    return m;
}

// pega menor valor de um vetor
int menor(int n, int *v)
{
    int m = v[0];

    for (int i = 1; i < n; i++)
    {
        if (v[i] < m) // se o valor atual é menor que o menor valor
            m = v[i]; // ele é o menor valor
    }
    return m;
}

// pega o maior valor de um array do tipo float
// util para calcular o peso/beneficio
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

// pega o menor valor de um array do tipo float
// util para calcular o peso/beneficio
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

/* --- funcoes mochila 0 --- */

// forca bruta verifica todas solucoes possiveis
void mochila_forca_bruta(int W, int *pesos, int *valores, int n, int *solucao)
{
    zera_lista(n, solucao); // zera a solucao

    // alloca vetor auxiliar, verifica se alocou corretamente
    int *melhor_sol = (int *)malloc(n * sizeof(int));
    verifica_alocacao(melhor_sol);

    int melhor_beneficio = 0,            // inicia melhor beneficio como sendo 0
        qtd_permutacao = potencia(2, n); // calcula quantas solucoes possiveis

    for (int i = 0; i < qtd_permutacao; i++)
    {
        for (int j = 0; j < n; j++) // for que gera solucao
        {
            int aux = i % potencia(2, j);
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
        int peso_aux = verifica_solucao(pesos, n, solucao);        // calcula peso que a solucao gerou
        int beneficio_aux = verifica_solucao(valores, n, solucao); // calcula beneficio que a solucao gerou

        // se o peso da solucao couber na mochila e o seu beneficio
        // for melhor que o melhor beneficio
        if (peso_aux <= W && beneficio_aux > melhor_beneficio)
        {
            melhor_beneficio = beneficio_aux;    // ele é o melhor beneficio
            copia_lista(n, melhor_sol, solucao); // armazena a solucao
        }
    }

    copia_lista(n, solucao, melhor_sol); // volta a melhor solucao pro vetor original
    free(melhor_sol);                    // libera memoria
}

// gera solucoes aleatorias e pega a melhor
void mochila_aleatoria(int W, int *pesos, int *valores, int n, int *solucao, int qtd_sol)
{
    zera_lista(n, solucao); // zera a solucao

    int *melhor_sol = (int *)malloc(n * sizeof(int)), // alloca vetor auxiliar
        melhor_beneficio = 0;                         // inicia melhor beneficio como zero
    verifica_alocacao(melhor_sol);                    // verifica se a memoria foi alocada

    srand(time(NULL));                // define seed como time(NULL)
    for (int i = 0; i < qtd_sol; i++) // gera solucoes
    {
        for (int i = 0; i < n; i++) // gera uma solucao
        {
            int pos = rand() % n; // sorteia um numero entre 0 e n-1
            solucao[pos] = 1;     // preenche essa posicao sorteada
        }

        int peso_aux = verifica_solucao(pesos, n, solucao);        // calcula peso da solucao
        int beneficio_aux = verifica_solucao(valores, n, solucao); // calcula beneficio da solucao

        // se o peso da solucao couber na mochila e o seu beneficio
        // for melhor que o melhor beneficio
        if (peso_aux <= W && beneficio_aux > melhor_beneficio)
        {
            copia_lista(n, melhor_sol, solucao); // ele é o melhor beneficio
            melhor_beneficio = beneficio_aux;    // armazena a solucao
        }
        zera_lista(n, solucao); // zera o vetor solucao para gerar outro na proxima iteracao
    }

    copia_lista(n, solucao, melhor_sol); // volta a solucao pro vetor original
    free(melhor_sol);                    // libera memoria
}

// gera solucoes pegando os maiores beneficio, heuristica "gulosa"
void mochila_beneficio(int W, int *pesos, int *valores, int n, int *solucao)
{
    zera_lista(n, solucao); // zera a solucao

    // alloca vetores auxiliares
    // como o codigo altera os valores do array, eu faco uma copia deles
    // para trabalhar com eles sem alterar algo fora do escopo dessa funcao
    int *p = (int *)malloc(n * sizeof(int)),
        *v = (int *)malloc(n * sizeof(int));

    // verifica se foram alocados
    verifica_alocacao(p);
    verifica_alocacao(v);

    // faz a copia
    copia_lista(n, p, pesos);
    copia_lista(n, v, valores);

    int maior_valor = maior(n, v); // pega o item de maior beneficio

    // se o vetor tem  n posicoes, temos q rodar esse codigo n vezes
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++) // percorre as posicoes do array
        {
            // se a posicao i da solucao ainda nao foi preeenchido
            // e ele é o maior beneficio
            if (solucao[i] == 0 && v[i] == maior_valor)
            {
                if (p[i] <= W)      // verifica se ele cabe na mochila
                {                   // se couber
                    W -= p[i];      // desconta o peso dele na mochila
                    solucao[i] = 1; // preenche a posicao dele na solucao
                }
                // agora q utilizamos esse item, vamos substituir
                // o valor dele para ser o menor
                // e pegar novamente o maior beneficio
                v[i] = menor(n, v) - 1;
                maior_valor = maior(n, v);

                break; // se ja achamos o maior valor, podemos encerrar o loop de percorrer o array
            }
        }
        // se a mochila tem capacidade maxima
        // encerra o loop para economizar computacao
        if (W == 0)
            break;
    }

    // libera memorias
    free(p);
    free(v);
}

// heuristica para gerar uma solucao comecando pelos menores pesos
void mochila_menor_peso(int W, int *pesos, int *valores, int n, int *solucao)
{
    zera_lista(n, solucao); // zera solucao

    // alloca vetores auxiliares
    // como o codigo altera os valores do array, eu faco uma copia deles
    // para trabalhar com eles sem alterar algo fora do escopo dessa funcao
    int *p = (int *)malloc(n * sizeof(int)),
        *v = (int *)malloc(n * sizeof(int));

    // verifica se foram alocados
    verifica_alocacao(p);
    verifica_alocacao(v);

    // faz a copia
    copia_lista(n, p, pesos);
    copia_lista(n, v, valores);

    int menor_peso = menor(n, p); // pega o menor peso do vetor

    // se o vetor tem  n posicoes, temos q rodar esse codigo n vezes
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++) // percorre posicoes do array
        {
            // se a posicao i da solucao ainda nao foi preeenchido
            // e ele é o menor peso
            if (solucao[i] == 0 && p[i] == menor_peso)
            {
                if (p[i] <= W) // verifica se ele cabe na mochila
                {
                    W -= p[i];      // desconta o peso dele na mochila
                    solucao[i] = 1; // preenche a posicao dele na solucao
                }
                // agora q utilizamos esse item, vamos substituir
                // o valor dele para ser o maior
                // e pegar novamente o menor peso
                p[i] = maior(n, p) + 1;
                menor_peso = menor(n, p);

                break; // se ja achamos o maior valor, podemos encerrar o loop de percorrer o array
            }
        }
        // se a mochila tem capacidade maxima
        // encerra o loop para economizar computacao
        if (W == 0)
            break;
    }

    // libera memoria
    free(p);
    free(v);
}

// pega solucao baseado na relacao peso/beneficio
void mochila_peso_beneficio(int W, int *pesos, int *valores, int n, int *solucao)
{
    zera_lista(n, solucao); // zera solucao

    // alloca vetores auxiliares
    // como o codigo altera os valores do array, eu faco uma copia deles
    // para trabalhar com eles sem alterar algo fora do escopo dessa funcao
    int *p = (int *)malloc(n * sizeof(int)),
        *v = (int *)malloc(n * sizeof(int));
    float *pb = (float *)malloc(n * sizeof(float)); // vetor auxiliar de peso/beneficio

    // verifica se foram alocados
    verifica_alocacao(p);
    verifica_alocacao(v);
    if (pb == NULL)
    {
        printf("Memória não alocada com sucesso!\n");
        exit(EXIT_FAILURE);
    }

    // faz a copia
    copia_lista(n, p, pesos);
    copia_lista(n, v, valores);

    for (int i = 0; i < n; i++) // divide peso por beneficio
    {
        float temp = (float)p[i] / (float)v[i];
        pb[i] = temp;
    }

    float menor_pb = menor_f(n, pb); // pega o menor valor

    // se o vetor tem  n posicoes, temos q rodar esse codigo n vezes
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n; i++) // percorre posicoes do array
        {
            // se a posicao i da solucao ainda nao foi preeenchido
            // e ele é o menor peso/beneficio
            if (solucao[i] == 0 && pb[i] == menor_pb)
            {
                if (p[i] <= W) // se couber na mochila
                {
                    W -= p[i];      // desconta o peso dele na mochila
                    solucao[i] = 1; // preenche a posicao dele na solucao
                }
                // agora que utilizamos esse item, vamos substituir
                // o valor dele para ser o maior
                // e pegar novamente o menor peso/beneficio
                pb[i] = maior_f(n, pb) + 1;
                menor_pb = menor_f(n, pb);

                break; // se ja achamos o maior valor, podemos encerrar o loop de percorrer o array
            }
        }
        // se a mochila tem capacidade maxima
        // encerra o loop para economizar computacao
        if (W == 0)
            break;
    }

    // libera memoria
    free(p);
    free(v);
    free(pb);
};

/*
Função básica de alocação de memória, recebe como parâmetro uma dado contido em uma struct, representado pela variável data.
Os vetores sao alocados dinamicamente do tamanho do parâmetro n, e retornados por endereço de memória.
*/
void aloca_memoria(Arquivo *data)
{
    data->pesos = (int *)malloc(data->n * sizeof(int));
    data->beneficios = (int *)malloc(data->n * sizeof(int));
    verifica_alocacao(data->pesos);
    verifica_alocacao(data->beneficios);
}

// funcao que libera memoria dos vetores do struct
void libera_memoria(Arquivo *data)
{
    free(data->pesos);
    free(data->beneficios);
}

/*
Função básica que recebe como parâmetro uma dado contido em uma struc,
representado pela variável data. Esse dado é impresso na tela.
Repare que a struct contem um vetor interno alocado dinamicamente.
*/
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

/*
Função que recebe por parâmetro o endereço do arquivo  a ser aberto, contido na variável ”path”
Após o arquivo aberto, os dados são lidos, e salvos e retornado no endereço de memória da variável “ *data”
*/
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

    // fecha arquivo
    fclose(pont_arq);
}
