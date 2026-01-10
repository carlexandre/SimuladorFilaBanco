#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "escalonador.h"
#include "logtree.h"

// ALUNOS
// Carlos Alexandre - 564967
// Caio Emanuel - 568591

int main(int argc, char *argv[]) {

    if (argc != 2) {
        return 1;
    }

    int x = atoi(argv[1]);

    if (x < 1 || x > 9999) {
        return 1;
    }

    char nome_entrada[50];
    char nome_saida[50];

    /* Arquivos de entrada ficam em casosdeteste/ */
    sprintf(nome_entrada, "casosdeteste/entrada-%04d.txt", x);

    /* Arquivo de saída fica no diretório do programa */
    sprintf(nome_saida, "saida-%04d.txt", x);

    Escalonador escalonador;

    e_rodar(&escalonador, nome_entrada, nome_saida);

    return 0;
}
