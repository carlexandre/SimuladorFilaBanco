typedef struct node {
    int chave;
    int valor;
    struct node* prox;
    struct node* ant;
}Fila;

void f_inicializar (Fila **f);

int f_inserir (Fila **f, int chave, int valor);

int chaveExistente(Fila *f, int chave);

int f_obter_proxima_chave (Fila **f);

int f_consultar_proxima_chave (Fila *f);

int f_consultar_proximo_valor (Fila *f);

int f_num_elementos (Fila *f);

int f_consultar_chave_por_posicao (Fila **f, int posicao);

int f_consultar_valor_por_posicao (Fila **f, int posicao);