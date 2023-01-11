#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cisj.h"

node_set *set_new(ssize_t size)
{
    node_set *new;

    new = (node_set *)malloc(sizeof(node_set));
    new->nodes = (int *)malloc(sizeof(int) * size);
    new->size = size;
    new->offset = 0;
    return new;
}

void set_insert(node_set *nodes, int node)
{
    if (nodes == NULL)
        return;
    //printf("Inserindo na posição %d o valor %d\n", nodes->offset, node);
    nodes->nodes[nodes->offset++] = node;
}

void set_merge(node_set *dest, node_set *source)
{
    if (dest == NULL || source == NULL)
        return;
    //printf("Fazendo merge...\n");
    memcpy(&(dest->nodes[dest->offset]), source->nodes, sizeof(int) * source->size);
    dest->offset += source->size;
}

void set_free(node_set *nodes)
{
    free(nodes->nodes);
    free(nodes);
}

node_set *cis(int i, int s)
{
    node_set *nodes, *other_nodes;
    int xor = i ^ POW_2(s - 1);
    int j;

    //printf("xor = %d, i = %d, POW_2(s-1) = %d\n", xor, i, POW_2(s - 1));

    /* starting node list */
    nodes = set_new(POW_2(s - 1));

    /* inserting the first value (i XOR 2^^(s-1)) */
    set_insert(nodes, xor);

    /* recursion */
    for (j = 1; j <= s - 1; j++)
    {
        other_nodes = cis(xor, j);
        // printf("other_nodes:");
        // for (int k = 0; k < other_nodes->size; k++)
        // {
        //     printf("%i ", other_nodes->nodes[k]);
        // }
        // printf("\n");
        set_merge(nodes, other_nodes);
        set_free(other_nodes);
    }
    return nodes;
}

// int main(int argc, char **argv)
// {
//     int i, s, j = -1;
//     node_set *nodes;

//     if (argc < 3)
//     {
//         printf(" Usage: %s i s [j]\n", argv[0]);
//         return 1;
//     }

//     /* required params */
//     i = atoi(argv[1]);
//     s = atoi(argv[2]);

//     /* have we the third parameter? */
//     if (argc > 3)
//     {
//         j = atoi(argv[3]);
//         if (!VALID_J(j, s))
//         {
//             printf("%d is not a valid node for a cluster size %d.\n", j, s);
//             return 1;
//         }
//     }
//     /* calculating cis */
//     nodes = cis(i, s);

//     /* print all nodes or just one? */
//     if (j != -1)
//         printf("%i\n", nodes->nodes[j - 1]);
//     else
//     {
//         for (i = 0; i < nodes->size; i++)
//             printf("%i ", nodes->nodes[i]);
//         puts("");
//     }
//     set_free(nodes);
//     return 0;
// }
