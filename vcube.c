/* *********HEADER************
 * Gustavo Valente - GRR20182557
 * Bruno Farias - GRR20186715
 * Ultima alteração: 11/01/23
 **************************** */

#include "vcube.h"
#include "cisj.h"
#include "utils.h"

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

int main(int argc, char const *argv[])
{
    TipoProcesso *processo;
    static int N, // número de processos do sistema
        token,    // indica o processo que está sendo executado
        event, r, i;

    static char fa_name[5];

    if (!verifica_argc(argc))
        return 0;

    // Converte para inteiro
    N = atoi(argv[1]);

    inicia_simulacao();

    imprime_cabecalho(MAX_TIME, N);

    /* vamos inicializar os processos */
    printf("Inicializando os [%d] processos...\n", N);
    processo = (TipoProcesso *)malloc(sizeof(TipoProcesso) * N);

    processo = inicializa_processos(fa_name, processo, i, N);
    printf("Processos inicializados com sucesso!\n");

    // vamos fazer o escalonamento inicial de eventos
    printf("\nFazendo escalonamento inicial dos eventos...\n");
    escalonamento_inicial_de_eventos(i, N);
    printf("Escalonamento concluído!\n");

    printf("Criando faults e recoveries");
    schedule(fault, 31.0, 1);
    schedule(recovery, 61.0, 1);
    printf("Finalizado a ação de faults e recoveries");

    node_set *nodes = NULL, *aux = NULL;
    int log2N = floor(log2(N));
    printf("log2(%d) = %d\n", N, log2N);

    int statusTeste;
    while (time() < MAX_TIME)
    {
        cause(&event, &token); // faz o SMPL verificar para cada processo naquele instante de tempo se tem algum evento para ele

        switch (event){
        case test:
            if (status(processo[token].id) != 0){ // processo falho não testa!
                break;
            }
            printf("===================================\n");
            printf("O processo [%d] testando no tempo %4.1f: \n", token, time());

            for (int s = 1; s <= log2N; s++){
                printf("s: [%d] - ", s);

                //obtém os processos que o processo 'token' vai testar no cluster s -> C(i,s)
                nodes = obterCISCorrigido(nodes, token, s);
                for (int j = 0; j < nodes->size; j++){
                    printf("\tj: [%d] - ", j);

                    //obtem C(j,s) 
                    aux = obterCISCorrigido(aux, nodes->nodes[j], s);
                    printf("\taux->nodes[0]: [%d]\n", aux->nodes[0]);
                    // verificando se i é o primeiro nodo sem falha de C(j,s)
                    if (token == aux->nodes[0]){
                        printf("\t[%d] é o primeiro nó sem falha de C(%d, %d)! Vai testar\n", token, nodes->nodes[j], s);

                        //testa j
                        statusTeste = status(processo[nodes->nodes[j]].id);
                        if (statusTeste == 0){
                            printf("(TESTE) O processo [%d] testou o processo [%d] no tempo %4.1f: CORRETO\n", token, nodes->nodes[j], time());

                            if ((processo[token].State[nodes->nodes[j]] % 2) == 1){
                                printf("Incrementando entrada na posição [%d]...\n", nodes->nodes[j]);
                                processo[token].State[nodes->nodes[j]]++;
                            }

                            obter_informacoes_diagnostico(processo, N, token, nodes, j);
                            // falta colocar quantas rodadas demorou para detectar o evento

                            break;
                        }
                        else
                        {
                            printf("(TESTE) O processo [%d] testou o processo [%d] no tempo %4.1f: FALHO\n", token, nodes->nodes[j], time());

                            if ((processo[token].State[nodes->nodes[j]] % 2) == 0){
                                printf("Incrementando entrada na posição [%d]...\n", nodes->nodes[j]);
                                processo[token].State[nodes->nodes[j]]++;
                            }
                        }
                    }
                }
            }

            imprimeVetorState(processo[token].State, N, token);

            schedule(test, 30.0, token); // processo token vai testar novamente daqui 30 unidades de tempo
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

    libera_os_nodos(nodes);
    printf("\n\nFIM DE EXECUÇÃO\n");
    return 0;
}
