#include "escalonador.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fila.h"
#include "logtree.h"

// Inicializa o escalonador, alocando e inicializando as 5 filas, que serão atendidas por “caixas” caixas, onde cada
// operação é tratada em “delta_t” minutos por um caixa, e o escalonamento utiliza a Disciplina de Atendimento
// representada por {n_1; n_2; n_2; n_4; n_5}.
void e_inicializar (Escalonador *e, int caixas, int delta_t,int n_1, int n_2, int n_3, int n_4, int n_5){

    f_inicializar(&e->premium);
    f_inicializar(&e->ouro);
    f_inicializar(&e->prata);
    f_inicializar(&e->bronze);
    f_inicializar(&e->leezu);

    e->qntd_caixas = caixas;
    e->delta_t = delta_t;

    e->n_1 = n_1;
    e->n_2 = n_2;
    e->n_3 = n_3;
    e->n_4 = n_4;
    e->n_5 = n_5;

    e->tempo_caixas = calloc(caixas, sizeof(int));

    e->fila_atual = 1;
    e->contagem_atual = 0;
}

// Função para verificar se as filas estão vazias
int e_vazio(Escalonador *e) {
    if (f_num_elementos(e->premium) > 0) return 0;
    if (f_num_elementos(e->ouro)    > 0) return 0;
    if (f_num_elementos(e->prata)   > 0) return 0;
    if (f_num_elementos(e->bronze)  > 0) return 0;
    if (f_num_elementos(e->leezu)   > 0) return 0;

    return 1;
}

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
int e_obter_prox_num_conta (Escalonador *e) {

    if (e_consultar_qtde_clientes(e) == 0)
        return -1;

    while (1) {
        Fila **fila = NULL;
        int limite = 0;

        if(e->fila_atual == 1) {fila = &e->premium; limite = e->n_1;}
        else if(e->fila_atual == 2) {fila = &e->ouro; limite = e->n_2;}
        else if(e->fila_atual == 3) {fila = &e->prata; limite = e->n_3;}
        else if(e->fila_atual == 4) {fila = &e->bronze; limite = e->n_4;}
        else if(e->fila_atual == 5) {fila = &e->leezu; limite = e->n_5;}

        if (e->contagem_atual < limite) {
            int conta = f_obter_proxima_chave(fila);
            if (conta != -1) {
                e->contagem_atual++;
                return conta;
            }
        }

        e->fila_atual++;
        if (e->fila_atual > 5) e->fila_atual = 1;
        e->contagem_atual = 0;
    }
}

// Retorna o número da conta do próximo cliente a ser atendido de acordo com a Disciplina de Atendimento, sem
// retirá-lo da sua respectiva fila.
int e_consultar_prox_num_conta (Escalonador *e) {

    if (e_consultar_qtde_clientes(e) == 0)
        return -1;

    int fila = e->fila_atual;
    int cont = e->contagem_atual;

    while (1) {
        Fila *f = NULL;
        int limite = 0;

        if(fila == 1) {f = e->premium; limite = e->n_1;}
        else if(fila == 2) {f = e->ouro; limite = e->n_2;}
        else if(fila == 3) {f = e->prata; limite = e->n_3;}
        else if(fila == 4) {f = e->bronze; limite = e->n_4;}
        else if(fila == 5) {f = e->leezu; limite = e->n_5;}

        if (cont < limite) {
            int conta = f_consultar_proxima_chave(f);
            if (conta != -1)
                return conta;
        }

        fila++;
        if (fila > 5) fila = 1;
        cont = 0;
    }
}

// Retorna a quantidade de operações bancárias que o próximo cliente das filas pretende realizar com o caixa,
// sem retirá-lo da sua respectiva fila.
int e_consultar_prox_qtde_oper (Escalonador *e) {

    if (e_consultar_qtde_clientes(e) == 0)
        return -1;

    int fila = e->fila_atual;
    int cont = e->contagem_atual;

    while (1) {
        Fila *f = NULL;
        int limite = 0;

        if(fila == 1) {f = e->premium; limite = e->n_1;}
        else if(fila == 2) {f = e->ouro; limite = e->n_2;}
        else if(fila == 3) {f = e->prata; limite = e->n_3;}
        else if(fila == 4) {f = e->bronze; limite = e->n_4;}
        else if(fila == 5) {f = e->leezu; limite = e->n_5;}

        if (cont < limite) {
            int valor = f_consultar_proximo_valor(f);
            if (valor != -1)
                return valor;
        }

        fila++;
        if (fila > 5) fila = 1;
        cont = 0;
    }
}

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
int e_consultar_tempo_prox_cliente (Escalonador *e) {
    int ops = e_consultar_prox_qtde_oper(e);
    return (ops == -1) ? -1 : ops * e->delta_t;
}

// Realiza a configuração de inicialização do escalonador através da leitura do arquivo de configuração de nome
// “nome_arq_conf”, retornando 1 em caso de sucesso e 0 caso contrário.
int e_conf_por_arquivo (Escalonador *e, char *nome_arq_conf){
    FILE *file = fopen(nome_arq_conf, "r");
    if (file == NULL) {
        return 0; // Falha ao abrir o arquivo
    }

    int caixas, delta_t, n_1, n_2, n_3, n_4, n_5;

    // O fscanf precisa incluir o texto exato que está no arquivo para ignorá-lo e pegar só os %d
    if (fscanf(file, "qtde de caixas = %d\n", &caixas) != 1) { fclose(file); return 0; }

    if (fscanf(file, "delta t = %d\n", &delta_t) != 1) { fclose(file); return 0; }
    
    if (fscanf(file, "disciplina de escalonamento = {%d,%d,%d,%d,%d}\n", 
               &n_1, &n_2, &n_3, &n_4, &n_5) != 5) { fclose(file); return 0; }

    e_inicializar(e, caixas, delta_t, n_1, n_2, n_3, n_4, n_5);

    // Formato: Premium - conta 755816 - 3 operacao(oes)
    char classe_str[20];
    int conta, ops;

    // O loop continua enquanto conseguir ler o padrão de linha dos clientes
    while (fscanf(file, "%19s - conta %d - %d operacao(oes)\n", classe_str, &conta, &ops) == 3) {
        int classe_id = 0;

        // Converte a string da classe para o número correspondente
        if (strcmp(classe_str, "Premium") == 0) classe_id = 1;
        else if (strcmp(classe_str, "Ouro") == 0) classe_id = 2;
        else if (strcmp(classe_str, "Prata") == 0) classe_id = 3;
        else if (strcmp(classe_str, "Bronze") == 0) classe_id = 4;
        else if (strcmp(classe_str, "Leezu") == 0) classe_id = 5;

        // Se identificou uma classe válida, insere na fila
        if (classe_id > 0) {
            e_inserir_por_fila(e, classe_id, conta, ops);
        }
    }

    fclose(file);
    return 1;
}

// Função auxiliar para marcar o menor tempo
int indice_menor_tempo(int *tempos, int n) {
    int i, menor = 0;
    for (i = 1; i < n; i++) {
        if (tempos[i] < tempos[menor])
            menor = i;
    }
    return menor;
}

// Função auxiliar para indicar o nome da classe pela numeração
char *e_nome_classe(int classe) {
    switch (classe) {
        case 1: return "Premium";
        case 2: return "Ouro";
        case 3: return "Prata";
        case 4: return "Bronze";
        case 5: return "Leezu";
        default: return "Desconhecida";
    }
}

// Executar a simulação do atendimento, lendo o arquivo de configuração de nome “nome_arq_in” e escrevendo
// o resultado do processamento para arquivo de nome “nome_arq_out”.
void e_rodar (Escalonador *e, char *nome_arq_in, char *nome_arq_out) {

    /* 1. Configura o escalonador a partir do arquivo */
    if (!e_conf_por_arquivo(e, nome_arq_in)) {
        return;
    }

    /* 2. Abre o arquivo de saída */
    FILE *out = fopen(nome_arq_out, "w");
    if (!out) {
        return;
    }

    int i;

    int n_caixas = e->qntd_caixas;
    int delta_t  = e->delta_t;

    int tempo_caixa[n_caixas];
    int atendidos_caixa[n_caixas];

    for (i = 0; i < n_caixas; i++) {
        tempo_caixa[i] = 0;
        atendidos_caixa[i] = 0;
    }

    /* estatísticas por classe */
    int qtd_classe[6] = {0};
    int soma_operacoes[6] = {0};
    float soma_espera[6] = {0};

    /* 3. Simulação */
    while (!e_vazio(e)) {

        /* escolhe o caixa que ficará livre primeiro */
        int cx = 0;
        for (i = 1; i < n_caixas; i++) {
            if (tempo_caixa[i] < tempo_caixa[cx])
                cx = i;
        }

        /* obtém próximo cliente */
        int classe = e_consultar_prox_fila(e);
        int conta  = e_consultar_prox_num_conta(e);
        int ops    = e_consultar_prox_qtde_oper(e);

        /* escreve evento */
        fprintf(
            out,
            "T = %d min: Caixa %d chama da categoria %s cliente da conta %d para realizar %d operacao(oes).\n",
            tempo_caixa[cx],
            cx + 1,
            e_nome_classe(classe),
            conta,
            ops
        );

        /* atualiza estatísticas */
        qtd_classe[classe]++;
        soma_operacoes[classe] += ops;
        soma_espera[classe] += tempo_caixa[cx];

        tempo_caixa[cx] += ops * delta_t;
        atendidos_caixa[cx]++;

        e_obter_prox_num_conta(e);
    }

    /* 4. Estatísticas finais */
    int tempo_total = tempo_caixa[0];
    for (i = 1; i < n_caixas; i++)
        if (tempo_caixa[i] > tempo_total)
            tempo_total = tempo_caixa[i];

    fprintf(out, "Tempo total de atendimento: %d minutos.\n", tempo_total);

    for (i = 1; i <= 4; i++) { // Do Premium até o Bronze
        if (qtd_classe[i] > 0) {
            fprintf(
                out,
                "Tempo medio de espera dos %d clientes %s: %.2f\n",
                qtd_classe[i],
                e_nome_classe(i),
                soma_espera[i] / qtd_classe[i]
            );
        }
    }

    if (qtd_classe[5] > 0) { // Tempo dos clientes COMUNS (vide arquivo original)
            fprintf(
                out,
                "Tempo medio de espera dos %d clientes Comuns: %.2f\n",
                qtd_classe[5],
                soma_espera[5] / qtd_classe[5]
            );
    }

    for (i = 1; i <= 5; i++) {
        if (qtd_classe[i] > 0) {
            fprintf(
                out,
                "Quantidade media de operacoes por cliente %s = %.2f\n",
                e_nome_classe(i),
                (float)soma_operacoes[i] / qtd_classe[i]
            );
        }
    }

    for (i = 0; i < n_caixas; i++) {
        fprintf(
            out,
            "O caixa de número %d atendeu %d clientes.\n",
            i + 1,
            atendidos_caixa[i]
        );
    }

    fclose(out);
}

