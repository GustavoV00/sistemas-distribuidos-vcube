/* *********HEADER************
 * Gustavo Valente - GRR20182557
 * Bruno Farias - GRR20186715
 * Ultima alteração: 12/01/23
 **************************** */
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "vcube.h"
#include "cisj.h"

void imprime_cabecalho(float tempo, int N)
{
    printf("==============================================================================\n");
    printf("2022/2 - TRABALHO 1 SISTEMAS DISTRIBUIDOS\n");
    printf("Bruno Farias - GRR20186715 | Gustavo Valente - GRR20182557\n");
    printf("Tempo máximo: [%4.1f] - N de processos: [%d]\n", tempo, N);
    printf("==============================================================================\n");
}

int verifica_argc(int argc)
{
    if (argc != 2)
    {
        puts("Uso correto: tempo <numero de processos>");
        exit(1);
    }
    return 1;
}

void inicia_simulacao()
{
    smpl(0, "vCube"); // 0 indica que é a primeira simulação, e em seguida o nome dela
    reset();
    stream(1);
}

void resetaVetorState(int *vetor, int N, int idProcessoAtual)
{
    for (int j = 0; j < N; j++)
    {
        if (j == idProcessoAtual)
        {
            vetor[j] = correto;
        }
        else
        {
            vetor[j] = unknown;
        }
    }
}

void imprimeVetorState(int *vetor, int N, int id)
{
    printf("State de [%d]: ", id);
    for (int j = 0; j < N; j++)
    {
        if (vetor[j] >= 0)
        {
            printf("[ %d] ", vetor[j]);
        }
        else
        {
            printf("[%d] ", vetor[j]);
        }
    }
    printf("\n");
}

TipoProcesso *inicializa_processos(char *fa_name, TipoProcesso *processo, int i, int N)
{
    for (i = 0; i < N; i++)
    {
        memset(fa_name, '\0', 5);
        sprintf(fa_name, "%d", i);
        processo[i].id = facility(fa_name, 1);
        printf("fa_name = %s, processo[%d].id = %d\n", fa_name, i, processo[i].id);

        // aloca memória para o vetor de estados
        processo[i].State = malloc(sizeof(int) * N);
        if (processo[i].State == NULL)
        {
            puts("Falha ao alocar espaço para vetor de estados!\n");
            exit(1);
        }

        // inicializa o vetor State com 0 (correto) para o próprio processo
        // e -1 (unknown) para os demais processos
        resetaVetorState(processo[i].State, N, i);

        imprimeVetorState(processo[i].State, N, i);
    }
    return processo;
}

void escalonamento_inicial_de_eventos(int i, int N, int intervalo)
{
    for (i = 0; i < N; i++)
    {
        schedule(test, intervalo, i); // escalona o evento teste no nodo i daqui a 30 unidades de tempo
    }
}

void obter_informacoes_diagnostico(TipoProcesso *processo, int N, int token, node_set *nodes, int j)
{
    // printf("\t\tObtendo informações de diagnóstico...\n");
    for (int k = 0; k < N; k++)
    {
        if (k != token && (processo[nodes->nodes[j]].State[k] > processo[token].State[k]))
        {
            printf("\t\tCopiando entrada ref. ao processo [%d] do State do processo [%d] para o State do processo [%d]...\n", k, nodes->nodes[j], token);
            processo[token].State[k] = processo[nodes->nodes[j]].State[k];
        }
    }
}

void libera_os_nodos(node_set *nodes)
{
    if (nodes != NULL)
    {
        set_free(nodes);
    }
}