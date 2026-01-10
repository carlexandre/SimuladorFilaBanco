#include "logtree.h"
#include <stdio.h>
#include <stdlib.h>

// Inicializa o registrador l.
void log_inicializar(Log **l) {
    *l = NULL;
}

// Inclui um registro de tempo de atendimento da conta de número “conta”, que faz parte da classe de número
// “classe”, que esperou “timer” minutos para ser atendido pelo caixa de número “caixa”, e levou “tempo”
// minutos sendo atendido.
void log_registrar(Log **l, int conta, int classe, int tempo, int caixa) {
    Log *novo = malloc(sizeof(Log));
    if (!novo) return;

    novo->conta = conta;
    novo->classe = classe;
    novo->tempo = tempo;
    novo->caixa = caixa;
    novo->esq = NULL;
    novo->dir = NULL;

    if (*l == NULL) {
        *l = novo;
        return;
    }

    Log *atual = *l;
    Log *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (conta < atual->conta)
            atual = atual->esq;
        else if (conta > atual->conta)
            atual = atual->dir;
        else {
            free(novo); // evita duplicação
            return;
        }
    }

    if (conta < pai->conta)
        pai->esq = novo;
    else
        pai->dir = novo;
}

// Calcula uma média auxiliar
static void auxiliar_media(Log *node, int classe, float *soma, int *qtd) {
    if (node == NULL) return;

    if (node->classe == classe) {
        *soma += node->tempo;
        (*qtd)++;
    }

    auxiliar_media(node->esq, classe, soma, qtd);
    auxiliar_media(node->dir, classe, soma, qtd);
}

// Retorna o tempo médio de espera, em minutos, para a classe de número “classe”.
float log_media_por_classe(Log *l, int classe) {
    float soma = 0.0f;
    int qtd = 0;

    auxiliar_media(l, classe, &soma, &qtd);

    if (qtd == 0) return 0.0f;
    return soma / qtd;
}

// Calcula uma soma auxiliar
static void auxiliar_soma(Log *node, int classe, int *soma) {
    if (node == NULL) return;

    if (node->classe == classe)
        *soma += node->tempo;

    auxiliar_soma(node->esq, classe, soma);
    auxiliar_soma(node->dir, classe, soma);
}

// Retorna a soma dos tempos de espera de todos os clientes cujas contas fazem parte da classe de número “classe”.
int log_obter_soma_por_classe(Log *l, int classe) {
    int soma = 0;
    auxiliar_soma(l, classe, &soma);
    return soma;
}

// Função auxiliar recursiva para percorrer e somar a quantidade de clientes da classe "classe"
static void auxiliar_contagem(Log *node, int classe, int *qtd) {
    if (node == NULL) return;

    if (node->classe == classe)
        (*qtd)++;

    auxiliar_contagem(node->esq, classe, qtd);
    auxiliar_contagem(node->dir, classe, qtd);
}

// Retorna a quantidade de clientes atendidos cujas contas são da categoria de número “classe”.
int log_obter_contagem_por_classe(Log *l, int classe) {
    int qtd = 0;
    auxiliar_contagem(l, classe, &qtd);
    return qtd;
}