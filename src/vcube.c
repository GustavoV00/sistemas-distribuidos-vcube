/**********HEADER************
 * Gustavo Valente - GRR20182557
 * Bruno Farias - GRR20186715
 * Ultima alteração: 10/01/23
 *****************************/
#include "vcube.h"

TipoProcesso *processo;

int main(int argc, char const *argv[])
{
    static int N, // número de processos do sistema
        token,    // indica o processo que está sendo executado
        event, r, i;

    static char fa_name[5];

    if (argc != 2)
    {
        puts("Uso correto: tempo <numero de processos>");
        exit(1);
    }

    N = atoi(argv[1]);

    smpl(0, "vCube"); // 0 indica que é a primeira simulação, e em seguida o nome dela
    reset();
    stream(1);

    printf("==============================================================================\n");
    printf("2022/2 - TRABALHO 1 SISTEMAS DISTRIBUIDOS\n");
    printf("Bruno Farias - GRR20186715 | Gustavo Valente - GRR20182557");
    printf("Tempo máximo: [%4.1f] - N de processos: [%d]\n", MAX_TIME, N);
    printf("==============================================================================\n");

    /* vamos inicializar os processos */
    printf("Inicializando os [%d] processos...\n", N);
    processo = (TipoProcesso *)malloc(sizeof(TipoProcesso) * N);
    for (i = 0; i < N; i++)
    {
        memset(fa_name, '\0', 5);
        sprintf(fa_name, "%d", i);
        processo[i].id = facility(fa_name, 1);
        printf("fa_name = %s, processo[%d].id = %d\n", fa_name, i, processo[i].id);
    }
    /* code */
    printf("teste\n");
    return 0;
}

/*
repeat
    for j <- 0 to (N-1) except i
        for s <- 1 to log N do
            if i is the first correct process E Cj,s then
                test(j)
                if j is correct then
                    if Statei[j] MOD 2 == 1 then
                        Statei[j]++;
                        obtain state info. from State j
                    else if Statei[j] MOD 2 == 0 then
                        Statei[j]++;
*/

// Algoritmo VCube executado no nodo i
