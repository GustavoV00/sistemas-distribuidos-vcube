/* *********HEADER************
 * Gustavo Valente - GRR20182557
 * Bruno Farias - GRR20186715
 * Ultima alteração: 12/01/23
 **************************** */
#ifndef __UTILS__
#define __UTILS__

#include "vcube.h"

void imprime_cabecalho(float tempo, int N);
int verifica_argc(int argc);
void inicia_simulacao();
void resetaVetorState(int *vetor, int N, int idProcessoAtual);
void imprimeVetorState(int *vetor, int N, int id);
TipoProcesso *inicializa_processos(char *fa_name, TipoProcesso *processo, int i, int N);
void escalonamento_inicial_de_eventos(int i, int N, int intervalo);
void caso_de_processo_fault(TipoProcesso *processo, int token, int r);
void caso_de_processo_recovery(TipoProcesso *processo, int token, int r);
void libera_os_nodos(node_set *nodes);
void obter_informacoes_diagnostico(TipoProcesso *processo, int N, int token, node_set *nodes, int j);
int verifica_se_statusTeste_eh_zero(int statusTeste, TipoProcesso *processo, int N, int token, node_set *nodes, int j);
int caso_statusTeste_nao_eh_zero(int statusTeste, TipoProcesso *processo, int N, int token, node_set *nodes, int j);

#endif