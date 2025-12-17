#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

// inicializa a fila.
void f_inicializar (Fila **f){
    *f = NULL;
};

// Insere um determinado valor inteiro indexado por um valor de chave na fila. Retorna 1 se a inserção for bem 
// sucedida e 0 se houver algum problema (duplicação de chave ou falta de memória).
int f_inserir (Fila **f, int chave, int valor){
    Fila * inicio = *f;
    Fila * adicionar = (Fila*) malloc(sizeof(Fila));

    if(!adicionar) return 0;
    if(chaveExistente(inicio, chave)) return 0;

    adicionar->chave = chave;
    adicionar->valor = valor;

    if(Fila_vazia(inicio)){
        adicionar->ant = adicionar;
        adicionar->prox = adicionar;
        *f = adicionar;
        return 1;
    }

    adicionar->prox = inicio;
    adicionar->ant = inicio->ant;

    inicio->ant->prox = adicionar;
    inicio->ant = adicionar;

    return 1;
}

// Verifica se existe uma chave com o valor que deseja adicionar na Fila.
int chaveExistente(Fila *f, int chave){
    Fila * temp = f;
    while(temp != NULL){
        if (temp->chave == chave)
            return 1;
    }
    return 0;
}

// Retorna o número de chave do próximo elemento da fila, retirando-o da fila. Retorna -1 se a fila estiver vazia.
int f_obter_proxima_chave (Fila **f){
    Fila * inicio = *f;
    Fila * prox = inicio->prox;
    Fila * ant = inicio->ant;
    int chave;

    if (inicio == NULL){
        return -1;
    }

    chave = inicio->chave;

    ant->prox = prox;
    prox->ant = ant;

    *f = prox;

    free(inicio);

    return chave;
}

// Retorna a chave do elemento que está na cabeça da fila, sem retirá-lo da fila.
int f_consultar_proxima_chave (Fila *f){
    Fila * inicio = f;

    if (inicio == NULL)
        return -1;
    
    return inicio->chave;
}

// Retorna o valor armazenado no elemento que está na cabeça da fila, sem retirá-lo da fila.
int f_consultar_proximo_valor (Fila *f){
    Fila * inicio = f;

    if (inicio == NULL)
        return -1;
    
    return inicio->valor;
}

// Retorna o número de elementos presentes na fila.
int f_num_elementos (Fila *f){
    Fila * inicio = f;
    int count = 0;

    while(inicio != NULL){
        count++;
        inicio = inicio->prox;
    }
    
    return count;
};

// Retorna a chave do posicao-ésimo elemento da fila. Caso não exista a posição desejada, retornar -1. 
// A posição se inicia em 1.
int f_consultar_chave_por_posicao (Fila **f, int posicao);

// Retorna o valor do posicao-ésimo elemento da fila. Caso não exista a posição desejada, retornar -1. 
// A posição se inicia em 1.
int f_consultar_valor_por_posicao (Fila **f, int posicao);