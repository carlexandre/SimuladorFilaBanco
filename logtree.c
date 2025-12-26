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

    Log * node = *l;    // Nó que será usado para percorrer a árvore
    Log * registrar = (Log*) malloc(sizeof(Log));   // Nó que será usado para o novo registro
    Log * pai = NULL;   // Nó para referenciar o pai do novo registro na hora da inserção

    // Atribuições necessárias
    registrar->conta = conta;
    registrar->classe = classe;
    registrar->tempo = timer;
    registrar->caixa = caixa;
    registrar->dir = NULL;
    registrar->esq = NULL;

    // Percorre a árvore procurando onde inserir esse novo registro
    while(node != NULL){
        pai = node;
        if(conta > node->conta)
            node = node->dir;
        else
            node = node->esq;
    }

    // Se o pai é nulo, então a árvore é nula. Portanto, 'l' será o novo registro
    if(pai == NULL)
        *l = registrar;
    
    /* Se o pai não for nulo mas o nó for nulo, veremos se o novo registro 
    será inserido na esquerda ou na direita do pai.*/
    else if(conta > pai->conta)
        pai->dir = registrar;
    else
        pai->esq = registrar;
}

// Retorna o tempo médio de espera, em minutos, para a classe de número “classe”.
float log_media_por_classe(Log **l, int classe) {
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
void auxiliar_media(Log **node, int classe, float *soma, int *qtd) {
    if (*node == NULL) {
        return;
    }

    // Se a classe bater, acumula o tempo e incrementa o contador
    if ((*node)->classe == classe) {
        *soma += (*node)->tempo;
        *qtd += 1;
    }

    // Continua percorrendo para esquerda e direita
    auxiliar_media((*node)->esq, classe, soma, qtd);
    auxiliar_media((*node)->dir, classe, soma, qtd);
}

// Retorna a soma dos tempos de espera de todos os clientes cujas contas fazem parte da classe de número “classe”.
int log_obter_soma_por_classe(Log **l, int classe) {
    int soma = 0;

    // Chama a auxiliar passando os endereços das variáveis
    auxiliar_soma(l, classe, &soma);

    return soma;
}

// Função auxiliar recursiva para percorrer e somar os tempos
void auxiliar_soma(Log **node, int classe, int *soma) {
    if (node == NULL) {
        return;
    }

    // Se a classe bater, acumula o tempo e incrementa o contador
    if ((*node)->classe == classe) {
        *soma += (*node)->tempo;
    }

    // Continua percorrendo para esquerda e direita
    auxiliar_soma((*node)->esq, classe, soma);
    auxiliar_soma((*node)->dir, classe, soma);
}

// Retorna a quantidade de clientes atendidos cujas contas são da categoria de número “classe”.
int log_obter_contagem_por_classe(Log **l, int classe) {
    int soma=0;
    auxiliar_soma_qtde(l, classe, &soma);
    return soma;
}

// Função auxiliar recursiva para percorrer e somar a quantidade de clientes da classe "classe"
void auxiliar_soma_qtde(Log **node, int classe, int *soma) {
    if (node == NULL) {
        return;
    }

    // Se a classe bater, acumula o tempo e incrementa o contador
    if ((*node)->classe == classe) {
        *soma += 1;
    }

    // Continua percorrendo para esquerda e direita
    auxiliar_soma((*node)->esq, classe, soma);
    auxiliar_soma((*node)->dir, classe, soma);
}
