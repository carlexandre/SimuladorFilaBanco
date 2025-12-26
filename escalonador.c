#include <stdlib.h>
#include <stdio.h>
#include "escalonador.h"
#include "fila.h"
#include "logtree.h"

// Inicializa o escalonador, alocando e inicializando as 5 filas, que serão atendidas por “caixas” caixas, onde cada
// operação é tratada em “delta_t” minutos por um caixa, e o escalonamento utiliza a Disciplina de Atendimento
// representada por {n_1; n_2; n_2; n_4; n_5}.
void e_inicializar (Escalonador *e, int caixas, int delta_t, int n_1, int n_2, int n_3, int n_4, int n_5){
    f_inicializar(&(e->premium));
    f_inicializar(&(e->ouro));
    f_inicializar(&(e->prata));
    f_inicializar(&(e->bronze));
    f_inicializar(&(e->leezu));

    e->qntd_caixas = caixas;
    e->delta_t = delta_t;
    e->n_1 = n_1;
    e->n_2 = n_2;
    e->n_3 = n_3;
    e->n_4 = n_4;
    e->n_5 = n_5;

    e->tempo_caixas = (int*) calloc(caixas, sizeof(int));

    e->fila_atual = 1;
    e->contagem_atual = 0;
};

// Insere na fila “classe” o cliente de número “num_conta”, que pretende realizar “qtde_operacoes” operações bancárias.
int e_inserir_por_fila (Escalonador *e, int classe, int num_conta, int qtde_operacoes){
    switch (classe) {
        case 1:
            return f_inserir(&(e->premium), num_conta, qtde_operacoes);
        case 2:
            return f_inserir(&(e->ouro), num_conta, qtde_operacoes);
        case 3:
            return f_inserir(&(e->prata), num_conta, qtde_operacoes);
        case 4:
            return f_inserir(&(e->bronze), num_conta, qtde_operacoes);
        case 5:
            return f_inserir(&(e->leezu), num_conta, qtde_operacoes);
        default:
            return 0;
    }
}

// Retorna o número da conta do próximo cliente a ser atendido de acordo com a Disciplina de Atendimento,
// retirando-o da sua respectiva fila.
int e_obter_prox_num_conta(Escalonador *e) {
    int conta = -1;

    if (e_consultar_qtde_clientes(e) == 0) return -1;

    switch (e->fila_atual) {
        case 1:
            if (e->contagem_atual < e->n_1) { // Verifica se ainda pode atender mais clientes dessa fila
                conta = f_obter_proxima_chave(&e->premium);
            }
            if (conta != -1) { // Se conseguiu atender um cliente dessa fila
                e->contagem_atual++;
                return conta;
            } else { // Se a fila estava vazia OU o limite de atendimentos foi atingido
                e->contagem_atual = 0;
                e->fila_atual = 2;
                return e_obter_prox_num_conta(e);
            }

        case 2:
            if (e->contagem_atual < e->n_2) {
                conta = f_obter_proxima_chave(&e->ouro);
            }
            if (conta != -1) {
                e->contagem_atual++;
                return conta;
            } else {
                e->contagem_atual = 0;
                e->fila_atual = 3;
                return e_obter_prox_num_conta(e);
            }

        case 3:
            if (e->contagem_atual < e->n_3) {
                conta = f_obter_proxima_chave(&e->prata);
            }
            if (conta != -1) {
                e->contagem_atual++;
                return conta;
            } else {
                e->contagem_atual = 0;
                e->fila_atual = 4;
                return e_obter_prox_num_conta(e);
            }

        case 4:
            if (e->contagem_atual < e->n_4) {
                conta = f_obter_proxima_chave(&e->bronze);
            }
            if (conta != -1) {
                e->contagem_atual++;
                return conta;
            } else {
                e->contagem_atual = 0;
                e->fila_atual = 5;
                return e_obter_prox_num_conta(e);
            }

        case 5:
            if (e->contagem_atual < e->n_5) {
                conta = f_obter_proxima_chave(&e->leezu);
            }
            if (conta != -1) {
                e->contagem_atual++;
                return conta;
            } else {
                e->contagem_atual = 0;
                e->fila_atual = 1; // volta para o início
                return e_obter_prox_num_conta(e);
            }

        default:
            return -1;
    }
}

// Retorna o número da conta do próximo cliente a ser atendido de acordo com a Disciplina de Atendimento, sem
// retirá-lo da sua respectiva fila.
int e_consultar_prox_num_conta (Escalonador *e){

    if (e_consultar_qtde_clientes(e) == 0) return -1;

    int fila_temp = e->fila_atual;
    int contagem_temp = e->contagem_atual;
    
    while (1) {
        int conta = -1;
        int limite_fila = 0;
        void* fila_ponteiro = NULL;

        if(fila_temp == 1){
            limite_fila = e->n_1;
            fila_ponteiro = e->premium;
        } else if(fila_temp == 2){
            limite_fila = e->n_2;
            fila_ponteiro = e->ouro;
        } else if(fila_temp == 3){
            limite_fila = e->n_3;
            fila_ponteiro = e->prata;
        } else if(fila_temp == 4){
            limite_fila = e->n_4;
            fila_ponteiro = e->bronze;
        } else if(fila_temp == 5){
            limite_fila = e->n_5;
            fila_ponteiro = e->leezu;
        }else 
            return -1;

        if (contagem_temp < limite_fila) { // Verifica se ainda pode atender mais clientes dessa fila
            conta = f_consultar_proxima_chave(fila_ponteiro);
            
            // Se conseguiu consultar um cliente dessa fila
            if (conta != -1) {
                return conta;
            }
        }

        // Avança para a próxima fila
        contagem_temp = 0;
        fila_temp++; 
        if (fila_temp > 5) fila_temp = 1; // Volta para 1 se passar de 5
    }
}
// Retorna a quantidade de operações bancárias que o próximo cliente das filas pretende realizar com o caixa,
// sem retirá-lo da sua respectiva fila.
int e_consultar_prox_qtde_oper (Escalonador *e){
    if (e_consultar_qtde_clientes(e) == 0) return -1;

    int fila_temp = e->fila_atual;
    int contagem_temp = e->contagem_atual;
    
    while (1) {
        int qntd_operacoes = -1;
        int limite_fila = 0;
        void* fila_ponteiro = NULL;

        if(fila_temp == 1){
            limite_fila = e->n_1;
            fila_ponteiro = e->premium;
        } else if(fila_temp == 2){
            limite_fila = e->n_2;
            fila_ponteiro = e->ouro;
        } else if(fila_temp == 3){
            limite_fila = e->n_3;
            fila_ponteiro = e->prata;
        } else if(fila_temp == 4){
            limite_fila = e->n_4;
            fila_ponteiro = e->bronze;
        } else if(fila_temp == 5){
            limite_fila = e->n_5;
            fila_ponteiro = e->leezu;
        }else
            return -1;

        if (contagem_temp < limite_fila) { // Verifica se ainda pode atender mais clientes dessa fila
            qntd_operacoes = f_consultar_proxima_valor(fila_ponteiro);
            
            // Se conseguiu consultar um cliente dessa fila
            if (qntd_operacoes != -1) {
                return qntd_operacoes;
            }
        }

        // Avança para a próxima fila
        contagem_temp = 0;
        fila_temp++; 
        if (fila_temp > 5) fila_temp = 1; // Volta para 1 se passar de 5
    }
};

// Retorna a próxima fila que será atendida de acordo com a Disciplina de Atendimento.
int e_consultar_prox_fila (Escalonador *e){
    if (e_consultar_qtde_clientes(e) == 0) return -1;

    int fila = e->fila_atual;
    int disciplina[5] = {e->n_1, e->n_2, e->n_3, e->n_4, e->n_5};
    Fila *f[5] = {e->premium, e->ouro, e->prata, e->bronze, e->leezu};

    // Verifica se a fila atual ainda pode ser retornada
    if (f_num_elementos(f[fila-1]) != 0 && e->contagem_atual < disciplina[fila-1])
        return fila;

    // Caso contrário, procura a próxima fila válida
    int voltas = 0;
    while(voltas < 5){
        fila++;

        if (fila > 5) fila = 1;
        if (f_num_elementos(f[fila-1]) != 0 && disciplina[fila-1] > 0)
            return fila;

        voltas++;
    }

    return -1; // Nenhuma fila encontrada - ERRO
}

// Retorna a quantidade total (soma) de clientes esperando atendimento em todas as filas.
int e_consultar_qtde_clientes (Escalonador *e){
    int total = 0;
    total += f_num_elementos(e->premium);
    total += f_num_elementos(e->ouro);
    total += f_num_elementos(e->prata);
    total += f_num_elementos(e->bronze);
    total += f_num_elementos(e->leezu);
    return total;
};

// Retorna o tempo necessário para que o próximo cliente a ser atendido realize todas as operações financeiras
// que deseja, sem retirá-lo da sua respectiva fila. Retornar -1 caso não tenha nenhum cliente em todas as filas.
int e_consultar_tempo_prox_cliente (Escalonador *e);

// Realiza a configuração de inicialização do escalonador através da leitura do arquivo de configuração de nome
// “nome_arq_conf”, retornando 1 em caso de sucesso e 0 caso contrário.
int e_conf_por_arquivo (Escalonador *e, char *nome_arq_conf);

// Executar a simulação do atendimento, lendo o arquivo de configuração de nome “nome_arq_in” e escrevendo
// o resultado do processamento para arquivo de nome “nome_arq_out”.
void e_rodar (Escalonador *e, char *nome_arq_in, char *nome_arq_out);

