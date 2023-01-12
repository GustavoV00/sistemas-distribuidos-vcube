/**********HEADER************
 * Gustavo Valente - GRR20182557
 * Bruno Farias - GRR20186715
 * Ultima alteração: 11/01/23
 *****************************/
#include "vcube.h"
#include "cisj.h"

TipoProcesso *processo;

node_set *obterCISCorrigido(node_set *nodes, int i, int s){
    printf("C(%d, %d): ", i, s);

    // faz o cálculo da função C(i,s)
    nodes = cis(i, s);
    
    //corrige o erro na ordem quando j >= 3
    if((i%2) != 0 && s >= 3){
        //printf("Corrigindo erro em j>=3\n");
        node_set *aux;
        int tamVet = POW_2(s - 1);
        aux = set_new(tamVet);

        for(int k = 0; k < tamVet; k++){
            if((k%4) == 0){
                aux->nodes[k] = nodes->nodes[k];
                aux->nodes[k+2] = nodes->nodes[k+2];

                aux->nodes[k+1] = nodes->nodes[k+3];
                aux->nodes[k+3] = nodes->nodes[k+1];
            }
        }
        set_free(nodes);
        nodes = aux;
    }

    for (int k = 0; k < nodes->size; k++){
        printf("%i ", nodes->nodes[k]);
    }
    printf("\n");

    return nodes;
}

int main(int argc, char const *argv[])
{
    static int N, // número de processos do sistema
        token,    // indica o processo que está sendo executado
        event, r, i;
    // static int N, i, r;

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
    printf("Bruno Farias - GRR20186715 | Gustavo Valente - GRR20182557\n");
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

    // vamos fazer o escalonamento inicial de eventos
    printf("\nFazendo escalonamento inicial dos eventos...\n");
    for(i = 0; i < N; i++){
        schedule(test, 30.0, i); //escalona o evento teste no nodo i daqui a 30 unidades de tempo
    }
    printf("Escalonamento concluído!\n");

    node_set *nodes = NULL, *aux = NULL;
    int log2N = floor(log2(N));
    printf("log2(%d) = %d\n", N, log2N);

    int statusTeste;
    while(time() < MAX_TIME){
        cause(&event, &token); //faz o SMPL verificar para cada processo naquele instante de tempo se tem algum evento para ele

        switch(event){
            case test:
                if(status(processo[token].id) != 0) { //processo falho não testa!
                    break;
                }
                printf("===================================\n");
                printf("O processo [%d] testando no tempo %4.1f: \n", token, time());
                
                for(int s = 1; s <= log2N; s++){
                    
                    printf("s: [%d] - ", s);

                    nodes = obterCISCorrigido(nodes, token, s);
                    for (int j = 0; j < nodes->size; j++){
                        printf("\tj: [%d] - ", j);
                        //printf("%i ", nodes->nodes[j]);

                        aux = obterCISCorrigido(aux, nodes->nodes[j], s);
                        printf("\taux->nodes[0]: [%d]\n", aux->nodes[0]);
                        //verificando se i é o primeiro nodo sem falha de C(j,s)
                        if(aux->nodes[0] == token){
                            printf("\t[%d] é o primeiro nó sem falha de C(%d, %d)! Vai testar\n", token, nodes->nodes[j], s);

                            statusTeste = status(processo[nodes->nodes[j]].id);
                            if(statusTeste == 0){
                                printf("(TESTE) O processo [%d] testou o processo [%d] no tempo %4.1f: CORRETO\n", token, nodes->nodes[j], time());
                                break;
                            } else {
                                printf("(TESTE) O processo [%d] testou o processo [%d] no tempo %4.1f: FALHO\n", token, nodes->nodes[j], time());
                            }
                        }
                    }
                }
                
                schedule(test, 30.0, token); //processo token vai testar daqui 30 unidades de tempo
                break;
            case fault:
                r = request(processo[token].id, token, 0);
                printf("---------------------------------------------------------\n");
                printf("\t\tO processo [%d] FALHOU no tempo %4.1f\n", token, time());
                printf("---------------------------------------------------------\n");
                break;
            case recovery:
                release(processo[token].id, token);
                schedule(test, 1.0, token);
                printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                printf("\t\tO processo [%d] RECUPEROU no tempo %4.1f\n", token, time());
                printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
                break;
        }
    }

    if(nodes != NULL){
        set_free(nodes);
    }
    
    printf("\n\nFIM DE EXECUÇÃO\n");
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
