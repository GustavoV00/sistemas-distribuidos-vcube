#ifndef __UTILS__
#define __UTILS__

#include "../vcube/vcube.h"

void imprime_cabecalho(float MAX_TIME, int N);
int verifica_argc(int argc);
void inicia_simulacao();
TipoProcesso *inicializa_processos(char *fa_name, TipoProcesso *processo, int i, int N);
void escalonamento_inicial_de_eventos(int i, int N);
void fake_faults_e_recovery();
void caso_de_processo_fault(TipoProcesso *processo, int token, int r);
void caso_de_processo_recovery(TipoProcesso *processo, int token, int r);
void libera_os_nodos(node_set *nodes);
void obter_informacoes_diagnostico(TipoProcesso *processo, int N, int token, node_set *nodes, int j);
int verifica_se_statusTeste_eh_zero(int statusTeste, TipoProcesso *processo, int N, int token, node_set *nodes, int j);
int caso_statusTeste_nao_eh_zero(int statusTeste, TipoProcesso *processo, int N, int token, node_set *nodes, int j);

#endif