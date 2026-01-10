#include "fila.h"
#include <stdlib.h>
#include <stdio.h>

// inicializa a fila.
void f_inicializar (Fila **f){
    *f = NULL;
};

// Insere um determinado valor inteiro indexado por um valor de chave na fila. Retorna 1 se a inserção for bem 
// sucedida e 0 se houver algum problema (duplicação de chave ou falta de memória).
int f_inserir(Fila **f, int chave, int valor) {
    if (chaveExistente(*f, chave))
        return 0;

    Fila *novo = malloc(sizeof(Fila));
    if (!novo)
        return 0;

    novo->chave = chave;
    novo->valor = valor;

    // Caso 1: fila vazia
    if (*f == NULL) {
        novo->prox = novo;
        novo->ant  = novo;
        *f = novo;
        return 1;
    }

    // Caso 2: fila com elementos
    Fila *ultimo = (*f)->ant;

    novo->prox = *f;
    novo->ant  = ultimo;

    ultimo->prox = novo;
    (*f)->ant   = novo;

    return 1;
}

// Verifica se existe uma chave com o valor que deseja adicionar na Fila.
int chaveExistente(Fila *f, int chave) {
    if (f == NULL) return 0;

    Fila *aux = f;

    do {
        if (aux->chave == chave)
            return 1;
        aux = aux->prox;
    } while (aux != f);

    return 0;
}


// Retorna o número de chave do próximo elemento da fila, retirando-o da fila. Retorna -1 se a fila estiver vazia.
int f_obter_proxima_chave(Fila **f) {
    if (*f == NULL)
        return -1;

    Fila *inicio = *f;
    int chave = inicio->chave;

    // Caso 1: apenas um elemento
    if (inicio->prox == inicio) {
        free(inicio);
        *f = NULL;
        return chave;
    }

    // Caso 2: mais de um elemento
    Fila *ultimo = inicio->ant;
    Fila *novo_inicio = inicio->prox;

    ultimo->prox = novo_inicio;
    novo_inicio->ant = ultimo;

    *f = novo_inicio;
    free(inicio);

    return chave;
}


// Retorna a chave do elemento que está na cabeça da fila, sem retirá-lo da fila.
int f_consultar_proxima_chave(Fila *f) {
    if (f == NULL)
        return -1;

    return f->chave;
}

// Retorna o valor armazenado no elemento que está na cabeça da fila, sem retirá-lo da fila.
int f_consultar_proximo_valor(Fila *f) {
    if (f == NULL)
        return -1;

    return f->valor;
}


// Retorna o número de elementos presentes na fila.
int f_num_elementos(Fila *f) {
    if (f == NULL)
        return 0;

    int count = 0;
    Fila *aux = f;

    do {
        count++;
        aux = aux->prox;
    } while (aux != f);

    return count;
}

// Retorna a chave do posicao-ésimo elemento da fila. Caso não exista a posição desejada, retornar -1. 
// A posição se inicia em 1.
int f_consultar_chave_por_posicao(Fila *f, int posicao) {
    if (f == NULL || posicao <= 0)
        return -1;

    Fila *aux = f;
    int cont = 1;

    do {
        if (cont == posicao)
            return aux->chave;

        aux = aux->prox;
        cont++;
    } while (aux != f);

    return -1;
}


// Retorna o valor do posicao-ésimo elemento da fila. Caso não exista a posição desejada, retornar -1. 
// A posição se inicia em 1.
int f_consultar_valor_por_posicao(Fila *f, int posicao) {
    if (f == NULL || posicao <= 0)
        return -1;

    Fila *aux = f;
    int cont = 1;

    do {
        if (cont == posicao)
            return aux->valor;

        aux = aux->prox;
        cont++;
    } while (aux != f);

    return -1;
}
