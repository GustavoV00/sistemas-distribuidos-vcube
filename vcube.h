/* *********HEADER************
 * Gustavo Valente - GRR20182557
 * Bruno Farias - GRR20186715
 * Ultima alteração: 12/01/23
 **************************** */
#ifndef __VCUBE__
#define __VCUBE__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "smpl.h"
#include "cisj.h"

/* cada processo conta seu tempo */

/*---- aqui definimos os eventos ----*/
#define test 1
#define fault 2
#define recovery 3

// estados do vetor de estados
#define unknown -1
#define correto 0
#define falho 1

#define MAX_TIME 300.0
#define INT_TESTES 30.0

/*---- declaramos agora o TipoProcesso ----*/
typedef struct
{
    int id;     /* identificador de facility SMPL */
    int *State; // ponteiro para vetor de estados
    /* variáveis locais do processo são declaradas aqui */
} TipoProcesso;

node_set *obterCISCorrigido(node_set *nodes, int i, int s);

#endif