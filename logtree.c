#include <stdio.h>
#include <stdlib.h>
#include "logtree.h"

// Inicializa o registrador l.
void log_inicializar(Log **l);

// Inclui um registro de tempo de atendimento da conta de número “conta”, que faz parte da classe de número
// “classe”, que esperou “timer” minutos para ser atendido pelo caixa de número “caixa”, e levou “tempo”
// minutos sendo atendido.
void log_registrar(Log **l, int conta, int classe, int timer, int caixa);

// Retorna o tempo médio de espera, em minutos, para a classe de número “classe”.
float log_media_por_classe(Log **l, int classe);

// Retorna a soma dos tempos de espera de todos os clientes cujas contas fazem parte da classe de número “classe”.
int log_obter_soma_por_classe(Log **l, int classe);

// Retorna a quantidade de clientes atendidos cujas contas são da categoria de número “classe”.
int log_obter_contagem_por_classe(Log **l, int classe);
