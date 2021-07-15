#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "jogolista.h"
#include <string.h>
#include <time.h>



struct elemento {
    struct alunoesse dados;
    struct elemento *prox;
};

typedef struct elemento Elemento;

Pilha *** criar_tabuleiro() {
    int m = MAX/2;
    Pilha ***tabuleiro;
    tabuleiro = (Pilha ***) malloc (MAX * sizeof(Pilha **));
    if(tabuleiro != NULL) {
        for (int i = 0; i<MAX; i++) {
            tabuleiro[i] = (Pilha **) malloc (MAX * sizeof(Pilha*));
            for (int j=0; j<MAX; j++) {
                tabuleiro[i][j] = NULL;
                tabuleiro[i][j] = criar();
            }
        }
    }
    return tabuleiro;
}


Pilha* criar() {
    Pilha *pd;
    pd = (Pilha*)malloc(sizeof(Pilha));
    if (pd!= NULL) *pd = NULL;
    return pd;

}


int inserir(Pilha *pd, struct alunoesse novosdados) {
    if (pd == NULL) {
        return 0;
        printf("nao alocou");
    } else {
        Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
        if (novo == NULL) {
            printf("nao alocou");
            return 0;
        }
        novo->dados = novosdados;
        *pd= novo;
        return 1;
    }
}


int inserir_teto(Pilha ***pd, struct alunoesse novosdados,int linha,int coluna) {

    for (int i =0; i<MAX; i++) {
        for (int j =0; j<MAX; j++) {
            if (pd[i][j] == NULL)
                return 0;
        }
    }
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));

    if(novo == NULL) return 0;


    novo->dados = novosdados;
    novo->dados.serateto = 1;
    novo->prox = *pd[linha][coluna];
    *pd[linha][coluna] = novo;


    return 1;
}


int inserir_especifico(Pilha ***pd, struct alunoesse novosdados,int linha,int coluna,int opc) {
    for (int i =0; i<MAX; i++) {
        for (int j =0; j<MAX; j++) {
            if (pd[i][j] == NULL)
                return 0;
        }
    }
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    if(novo == NULL) return 0;

    if (opc == 1) { //andar
        novo->dados = novosdados;
        novo->prox = *pd[linha][coluna];
        *pd[linha][coluna] = novo;
    }

    else if (opc == 2) { //parque
        if(tamanho(pd[linha][coluna])==0) {

            novosdados.seraparque = 1;
            novo->dados = novosdados;
            novo->prox = *pd[linha][coluna];
            *pd[linha][coluna] = novo;
        } else {
            printf("Nao pode colocar parque em cima de pecas");
            return 0;

        }

    }

    else if ( opc ==3) { //teto
        novosdados.serateto = 1;
        novo->dados = novosdados;
        novo->prox = *pd[linha][coluna];
        *pd[linha][coluna] = novo;

    }

    return 1;
}

void imprime_Pilha2(Pilha ***tabuleiro) {
    char alfabeto[] = "abcdefghijklmnopqrstuvxzwy";
    for(int x=0; x<MAX; x++)
        printf("\t\t\t");
    printf(" Norte\n");
    for(int i=0; i< MAX; i++) {
        if (i == (MAX/2+1)) printf("\t\t\tOeste\t");
        else printf("\t\t\t\t");
        for(int x=0; x<MAX; x++) {
            printf("+----");
        }
        if(i!=(MAX/2+1))
            printf("+\n\t\t\t\t");
        else printf("+\tLeste\n\t\t\t\t");
        for( int j = 0; j < MAX; j++ ) {


            if (teto_ou_parque(tabuleiro,i,j)==3 || teto_ou_parque(tabuleiro,i,j)==2) {
                printf("|[%d] ",tamanho(tabuleiro[i][j]));
            } else {
                printf("| %d  ",tamanho(tabuleiro[i][j]));
            }

        }
        printf("| %c\n",alfabeto[i]);
    }
    printf("\t\t\t\t");
    for(int x=0; x<MAX; x++)
        printf("+----");
    printf("+\n\t\t\t\t");
    for (int x=0; x<MAX; x++) {
        printf("  %d  ",x);
    }
    printf("\n");
    for(int x=0; x<MAX; x++)
        printf("\t\t\t");
    printf(" Sul\n");
}

int tamanho(Pilha *pd) {
    if (vazia(pd)) {
        return 0;
    }
    int cont = 0;
    Elemento *aux = *pd;
    while (aux != NULL) {
        cont++;
        aux = aux->prox;
    }
    return cont;
}

int cheia (Pilha *pd) {
    printf("cheia\n");
    return 0;
}

int vazia(Pilha *pd) {
    if (pd == NULL) {
        return 1;
    } else if(*pd == NULL) {
        return 1;
    } else {
        return 0;
    }
}


/////////////////////////LISSTA//////////////////////////

struct elemento2 {
    struct jogador dados;
    struct elemento2 *prox;
};

typedef struct elemento2 Elem;

Lista* cria_lista() {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li) {
    if(li != NULL) {
        Elem* no;
        while((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int insere_lista_final(Lista* li, struct jogador al) {
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL) { //lista vazia: insere início
        *li = no;
    } else {
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *ant, *no = *li;
    while(no != NULL && no->dados.matricula != mat) {
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int tamanho_lista(Lista* li) {
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li) {
    return 0;
}

int lista_vazia(Lista* li) {
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li,int atual) {

    int i = 0;
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL) {
        if(i==atual) {
            printf("Vez do jogador com vista %s\n",no->dados.nome);
            printf("Escolha qual peca deseja jogar\n\n1 = Andar[%d]\n2 = Parque [%d]\n3 = Teto [%d]\n0 = Sua Vista\n",no->dados.andar,
                   no->dados.parque,
                   no->dados.teto);
            printf("-> ");
            return;
        }
        i++;
        no = no->prox;
    }
}

void removerMeio(Lista *ldse, int x, int valor) {
    if(lista_vazia(ldse)) return 0;
    else {
        Elem *aux = *ldse;
        while (aux != NULL && aux->dados.matricula != x) {
            aux = aux->prox;
        }
        if(aux == NULL) return 0;
        if (valor == 1 && aux->dados.andar>0)
            aux->dados.andar--;
        else if(valor == 2 && aux->dados.parque>0)
            aux->dados.parque--;
        else if(valor == 3 && aux->dados.teto>0)
            aux->dados.teto--;
        else {
            printf("Acabou as pecas.\n");
            //return 1;
        }
        return;
    }
}

int lerChar(char valorChar[],char essechar) {

    for (int i=0; i!=strlen(valorChar); i++) {
        if (valorChar[i]==essechar)
            return (i);
    }

}

void insere_aleatorio(Pilha ***pd,struct alunoesse novosdados) {

    int x,linha,coluna;
    srand(time(NULL));

    for(int i=0; i <6; i++) {
        linha = rand() % MAX;
        coluna = rand() % MAX;

        while  ( ( linha > (MAX/2)+1 || linha < (MAX/2)-1 )    || ( teto_ou_parque(pd,linha,coluna) == 3 )) {
            linha = rand() % MAX;
        }
        while  ( (coluna > (MAX/2)+1 || coluna < (MAX/2)-1 )   || ( teto_ou_parque(pd,linha,coluna) == 3 )) {
            coluna = rand() % MAX;
        }

        inserir_especifico(pd,novosdados,linha,coluna,1);

    }

}

int verifica_pecas(Pilha ***pd,Lista* li,int atual,int opc,int linha,int coluna) {



    int i = 0;
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL) {
        if(i==atual) {
            if (opc==1 && no->dados.andar==0)  {
                printf("Acabou as pecas");
                return 1;
            } else if (opc==2 && no->dados.parque==0) {
                printf("Acabou as pecas");
                return 1;
            } else if (opc==3 && no->dados.teto==0) {
                printf("Acabou as pecas");
                return 1;
            }
        }
        i++;
        no = no->prox;
    }



    if ( teto_ou_parque(pd,linha,coluna) == 3) {
        printf("Nao pode colocar em cima de parque\n");
        return 1;

    } else if( teto_ou_parque(pd,linha,coluna) == 2 ) {
        printf("Nao pode colocar em cima de teto\n");
        return 1;
    } else {
        return 0;
    }

}
int teto_ou_parque(Pilha ***pd,int linha,int coluna) {

    if(vazia(pd[linha][coluna]))
        return 0;
    else {
        if ((*pd[linha][coluna])->dados.serateto == 1)
            return 2;
        else if ((*pd[linha][coluna])->dados.seraparque == 1)
            return 3;
        else
            return 0;

    }
}

int inteiro_validado() {
    int linha,coluna;
    char teste[2];

    gets(teste);//fflush(stdin);

    if(teste[0] >= '0' && teste[0] <= '9') {
        linha = teste[0] - '0';
    } else {
        return NULL;
    }


    return ;
}

int largura_asteriscos(int tamanhodovetor) {
    if (tamanhodovetor == 1)
        return 1;
    else
        return (largura_asteriscos(tamanhodovetor-1) + 2);
}

int matriz_auxiliar(Pilha ***pd) {

    int maior_coluna[MAX] = {0};
    int aux = MAX-1;
    int maior_linha = 0;
    int maior_coluna_sequencial[MAX] = {0};

    int matriz_recebe[MAX][MAX];

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX ; j++) {
            matriz_recebe[i][j] = 0;
        }
    }

    for (int j = 0; j<MAX; j++) {
        for (int i = MAX-1; i >= 0; i--) {
            if ( tamanho(pd[i][j]) > maior_linha ) {
                maior_linha = tamanho(pd[i][j]);
                matriz_recebe[i][j] = maior_linha;
                aux--;
            }
        }

        maior_coluna_sequencial[j] = maior_linha;
        aux = MAX - 1;
        maior_linha = 0;
    }


    for ( int i = 0; i < MAX; i++ ) {
        for ( int j = 0; j < MAX ; j++ ) {
            printf ( "%d\t", matriz_recebe[i][j]) ;
        }
        printf("\n\n");
    }
    int y=0;
        for ( int i = 0; i<MAX; i++ ) {
            for ( int j = 0 ; j<MAX; j++ ) {
                if(matriz_recebe[i][j] != 0 ) {

                    matriz_recebe[i][j]--;


                    // printf("\n");


                    for (int q = 0; q<MAX; q++) {
                        for (int w = MAX-1; w >= 0; w--) {
                            if ( tamanho(pd[w][q]) > maior_linha ) {
                                maior_linha = tamanho(pd[w][q]);
                                matriz_recebe[w][q] = maior_linha;
                                aux--;


                            }

                        }



                        maior_coluna_sequencial[q] = maior_linha;
                        aux = MAX - 1;
                        maior_linha = 0;
                        // printf("\n");


                    }


                if(matriz_recebe[i][j] == 0 )
                    i--;

                    for (int ini = 0; ini<=largura_asteriscos(i); ini++)
                        printf("#");
                    // printf("\n");
                }



                printf("\t\t");
                //  printf("---");

            }
            // i--;
            // printf("\n");
        }
        printf("_________________________________________________");

    //CONTA QUANTOS ELEM CADA COLUNA
    /*

        int cont = 0;
        while (1) {
            for ( int i = MAX-1; i <=0; i-- ) {
                if (matriz_recebe[i][1] != 0) {
                    matriz_recebe[i][1];
                    cont++;
                }
            }
            break;
        }
        printf("\n\n%d",cont);

      // ORDENA


      for (int k=0;k<=MAX-2;k++) {
            for (int i=0;i<=MAX-2;i++) {
                if (maior_coluna_sequencial[i]>maior_coluna_sequencial[i+1]) {
                    aux=maior_coluna_sequencial[i];
                    maior_coluna_sequencial[i] = maior_coluna_sequencial[i+1];
                    maior_coluna_sequencial[i+1] = aux;
                }
            }
        }

        for(int i = 0; i<MAX; i++) {
            printf("%d",maior_coluna_sequencial[i]);
        }

    */
    return 1;
}

