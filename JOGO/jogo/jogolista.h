struct jogador {
    int matricula;
    char nome[30];
    int andar,parque,teto;
};

typedef struct elemento2* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, struct jogador al);
int insere_lista_inicio(Lista* li, struct jogador al);
int insere_lista_ordenada(Lista* li, struct jogador al);
int remove_lista(Lista* li, int mat);
int remove_lista_inicio(Lista* li);
int remove_lista_final(Lista* li);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
int lista_cheia(Lista* li);
void imprime_lista(Lista* li,int atual);
int consulta_lista_mat(Lista* li, int mat, struct jogador *al);
int consulta_lista_pos(Lista* li, int pos, struct jogador *al);
void removerMeio(Lista *ldse, int x, int valor);
int lerVetor(char alfabeto[],char essaletra[]);
int verifica_pecas(Pilha ***pd, Lista* li,int atual,int opc,int linha,int coluna);
int largura_asteriscos(int tamanhodovetor);
