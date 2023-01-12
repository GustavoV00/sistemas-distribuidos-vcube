/**********HEADER************
 * Gustavo Valente - GRR20182557
 * Bruno Farias - GRR20186715
 * Ultima alteração: 11/01/23
 *****************************/

#include "vcube.h"
#include "cisj.h"

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
        printf("[%d] ", vetor[j]);
    }
    printf("\n");
}

node_set *obterCISCorrigido(node_set *nodes, int i, int s)
{
    printf("C(%d, %d): ", i, s);

    // faz o cálculo da função C(i,s)
    nodes = cis(i, s);

    // corrige o erro na ordem quando j >= 3
    if ((i % 2) != 0 && s >= 3)
    {
        // printf("Corrigindo erro em j>=3\n");
        node_set *aux;
        int tamVet = POW_2(s - 1);
        aux = set_new(tamVet);

        for (int k = 0; k < tamVet; k++)
        {
            if ((k % 4) == 0)
            {
                aux->nodes[k] = nodes->nodes[k];
                aux->nodes[k + 2] = nodes->nodes[k + 2];

                aux->nodes[k + 1] = nodes->nodes[k + 3];
                aux->nodes[k + 3] = nodes->nodes[k + 1];
            }
        }
        set_free(nodes);
        nodes = aux;
    }

    for (int k = 0; k < nodes->size; k++)
    {
        printf("%i ", nodes->nodes[k]);
    }
    printf("\n");

    return nodes;
}
