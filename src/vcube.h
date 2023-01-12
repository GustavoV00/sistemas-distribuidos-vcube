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

#define MAX_TIME 150.0

/*---- declaramos agora o TipoProcesso ----*/
typedef struct
{
    int id; /* identificador de facility SMPL */
            /* variáveis locais do processo são declaradas aqui */
} TipoProcesso;

node_set *obterCISCorrigido(node_set *nodes, int i, int s);