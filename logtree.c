#include <stdio.h>
#include <stdlib.h>
#include "logtree.h"

// Inicializa o registrador l.
void log_inicializar(Log **l){
    *l = NULL;
}

// Inclui um registro de tempo de atendimento da conta de número “conta”, que faz parte da classe de número
// “classe”, que esperou “timer” minutos para ser atendido pelo caixa de número “caixa”, e levou “tempo”
// minutos sendo atendido.
void log_registrar(Log **l, int conta, int classe, int timer, int caixa){
    Log * node = *l;
    Log * registrar = (Log*) malloc(sizeof(Log));
    Log * pai = NULL;

    registrar->conta = conta;
    registrar->classe = classe;
    registrar->tempo = timer;
    registrar->caixa = caixa;
    registrar->dir = NULL;
    registrar->esq = NULL;

    while(node != NULL){
        pai = node;
        if(conta > node->conta)
            node = node->dir;
        else
            node = node->esq;
    }

    if(pai == NULL)
        *l = registrar;
    else if(conta > pai->conta)
        pai->dir = registrar;
    else
        pai->esq = registrar;
}

// Retorna o tempo médio de espera, em minutos, para a classe de número “classe”.
float log_media_por_classe(Log *l, int classe) {
    float soma = 0.0;
    int qtd = 0;

    // Chama a auxiliar passando os endereços das variáveis
    auxiliar_media(l, classe, &soma, &qtd);

    // Evita divisão por zero se não encontrar nenhum nó daquela classe
    if (qtd == 0) {
        return 0.0;
    }

    return soma / qtd;
}

// Função auxiliar recursiva para percorrer e somar
void auxiliar_media(Log *node, int classe, float *soma, int *qtd) {
    if (node == NULL) {
        return;
    }

    // Se a classe bater, acumula o tempo e incrementa o contador
    if (node->classe == classe) {
        *soma += node->tempo;
        *qtd += 1;
    }

    // Continua percorrendo para esquerda e direita
    auxiliar_media(node->esq, classe, soma, qtd);
    auxiliar_media(node->dir, classe, soma, qtd);
}

// Retorna a soma dos tempos de espera de todos os clientes cujas contas fazem parte da classe de número “classe”.
int log_obter_soma_por_classe(Log **l, int classe);

// Retorna a quantidade de clientes atendidos cujas contas são da categoria de número “classe”.
int log_obter_contagem_por_classe(Log **l, int classe);
