typedef struct node {
    int conta;
    int classe;
    float tempo;
    int caixa;
    struct node* esq;
    struct node* dir;
}Log;

void log_inicializar(Log **l);

void log_registrar(Log **l, int conta, int classe, int timer, int caixa);

float log_media_por_classe(Log **l, int classe);

void auxiliar_media(Log **node, int classe, float *soma, int *qtd);

int log_obter_soma_por_classe(Log **l, int classe);

void auxiliar_soma(Log **node, int classe, int *soma);

int log_obter_contagem_por_classe(Log **l, int classe);

void auxiliar_soma_qtde(Log **node, int classe, int *soma);