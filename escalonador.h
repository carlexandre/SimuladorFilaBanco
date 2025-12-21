#include <fila.h>

typedef struct node{
    Fila* premium;
    Fila* ouro;
    Fila* prata;
    Fila* bronze;
    Fila* leezu;

    int* tempo_caixas;
    int qntd_caixas;
    int delta_t;
    int n_1, n_2, n_3, n_4, n_5;

    int fila_atual; //saber qual fila está sendo atendida no momento.
    int contagem_atual; // saber quantos já foram atendidos na rodada atual daquela fila.
}Escalonador;

void e_inicializar (Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5);

int e_inserir_por_fila (Escalonador *e, int classe, int num_conta, int qtde_operacoes);

int e_obter_prox_num_conta(Escalonador *e);

int e_consultar_prox_num_conta (Escalonador *e);

int e_consultar_prox_qtde_oper (Escalonador *e);

int e_consultar_prox_fila (Escalonador *e);

int e_consultar_qtde_clientes (Escalonador *e);

int e_consultar_tempo_prox_cliente (Escalonador *e);

int e_conf_por_arquivo (Escalonador *e, char *nome_arq_conf);

void e_rodar (Escalonador *e, char *nome_arq_in, char *nome_arq_out);