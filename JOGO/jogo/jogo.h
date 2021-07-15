#define MAX 5

struct alunoesse {
    int serateto;
    int seraparque;
};

typedef struct elemento* Pilha;

Pilha * criar();
void destruir(Pilha *);
int tamanho(Pilha *);
int cheia(Pilha *);
int vazia(Pilha *);
int inserir(Pilha *, struct alunoesse);
int inserir_teto(Pilha ***pd, struct alunoesse novosdados,int linha,int coluna);
int inserir_especifico(Pilha ***pd, struct alunoesse novosdados,int linha,int coluna,int opc);
void imprime_Pilha(Pilha* pi);
void imprime_Pilha2(Pilha ***tabuleiro);
int lerChar(char valorChar[],char essechar);
void insere_aleatorio(Pilha ***pd, struct alunoesse novosdados);
int teto_ou_parque(Pilha ***pd,int linha,int coluna);
int inteiro_validado();
int matriz_auxiliar(Pilha ***pd);


