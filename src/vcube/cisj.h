/**********HEADER************
 * Gustavo Valente - GRR20182557
 * Bruno Farias - GRR20186715
 * Ultima alteração: 11/01/23
 *****************************/

#ifndef __CISJ__
#define __CISJ__
typedef struct node_set
{
    int *nodes;
    ssize_t size;
    ssize_t offset;
} node_set;

#define POW_2(num) (1 << (num))
#define VALID_J(j, s) ((POW_2(s - 1)) >= j)

node_set *set_new(ssize_t size);
void set_insert(node_set *nodes, int node);
void set_merge(node_set *dest, node_set *source);
void set_free(node_set *nodes);
node_set *cis(int i, int s);

#endif