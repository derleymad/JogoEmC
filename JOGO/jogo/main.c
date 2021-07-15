#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "jogo.h"
#include "jogolista.h"



int main() {
    char teste[2];
    int matriz[MAX][MAX]= {0};
    int valor,opc = 2,atual = 0;
    char valorChar[] = "abcdefghijklmnopqrstuvxzwy";
    char linha_char;
    int coluna = 4,linha = 4;

    struct alunoesse a;
    struct jogador jogador[4] = {{0,"Sul",12,1,2},
        {1,"Oeste",12,1,2},
        {2,"Norte",12,1,2},
        {3,"Leste",12,1,2}
    };

//CRIAR PILHA
    Pilha ***tabuleiro = criar_tabuleiro();
    inserir_especifico(tabuleiro,a,MAX/2,MAX/2,opc);

//CRIA LISTA
    Lista* li = cria_lista();
    for(int i=0; i < 4; i++)
        insere_lista_final(li,jogador[i]);
//INSERE PECAS
    insere_aleatorio(tabuleiro,a);

//TESTE


//////////////////////////////////////////////////// VALIDACOES //////////////////////////////////////////////////////

    // matriz_auxiliar(tabuleiro);
    // printf("%d" , largura_asteriscos(4));

    while (1) {
        if (atual==4) atual = 0;

        //IMPRIME LISTA E TABULEIRO
        imprime_Pilha2(tabuleiro);
        imprime_lista(li,atual);


        scanf("%d",&opc);
        while( getchar() != '\n' );


        switch (opc) {


        case 0:
            matriz_auxiliar(tabuleiro);
            getch();
            break;



        case 1:

            printf("\nDigite agora onde deseja jogar\n->");
            scanf("%s",teste);
            while( getchar() != '\n' );
            coluna = teste[0] - '0';
            linha = lerChar(valorChar,teste[1]) ;


            if (verifica_pecas(tabuleiro,li,atual,opc,linha,coluna)) {
                break;
            } else {

                removerMeio(li,atual,opc);
                inserir_especifico(tabuleiro,a,linha,coluna,opc);
                atual++;
                imprime_lista(li,atual);

                break;
            }

        case 2:
            printf("\nDigite agora onde deseja jogar\n->");
            scanf("%s",teste);
            while( getchar() != '\n' );
            coluna = teste[0] - '0';
            linha = lerChar(valorChar,teste[1]) ;

            if (verifica_pecas(tabuleiro,li,atual,opc,linha,coluna)) {
                break;
            } else {

                removerMeio(li,atual,opc);
                inserir_especifico(tabuleiro,a,linha,coluna,opc);
                atual++;

                break;
            }

        case 3:

            printf("\nDigite agora onde deseja jogar\n->");
            scanf("%s",teste);
            while( getchar() != '\n' );
            coluna = teste[0] - '0';
            linha = lerChar(valorChar,teste[1]) ;


            if (verifica_pecas(tabuleiro,li,atual,opc,linha,coluna)) {
                break;
            } else {

                removerMeio(li,atual,opc);
                inserir_especifico(tabuleiro,a,linha,coluna,opc);
                atual++;

                break;

            }


        default:
            break;
        }

        //getch();
        //  if (x1==0 || x2 == 0 || x3 == 0 || x4 == 0) goto partidafinal;
    }



    // partidafinal:
    //    pardida_final();

    libera_lista(li);
    return 0;

}

