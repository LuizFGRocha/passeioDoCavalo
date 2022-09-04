#include <stdio.h>
#include <stdlib.h>
#include "movimentos.h"

#define kCimaDireita 1
#define kDireitaCima 2
#define kDireitaBaixo 3
#define kBaixoDireita 4
#define kBaixoEsquerda 5
#define kEsquerdaBaixo 6
#define kEsquerdaCima 7
#define kCimaEsquerda 8

typedef struct{
    short int linha, coluna;
} coordenadas;

int main(){

    /* declaracao do tabuleiro e inicializacao da variavel que guarda a 
       posicao atual e do vetor que guarda qual o maior movimento tentado    */
    int tabuleiro[8][8], nMovs = 0;
    coordenadas pAtual = {1, 1};
    short int* hist = malloc(500 * sizeof(short int));

    while(1){
        if(cimaDireita(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs)){
            pAtual.linha -= 2;
            pAtual.coluna += 1;
            hist[nMovs++] = kCimaDireita;
        }

        if(direitaCima(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs)){
            pAtual.linha -= 1;
            pAtual.coluna += 2;
            hist[nMovs++] = kDireitaCima;
        }

        if(direitaBaixo(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs)){
            pAtual.linha += 1;
            pAtual.coluna += 2;
            hist[nMovs++] = kDireitaBaixo;
        }

        if(baixoDireita(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs)){
            pAtual.linha += 2;
            pAtual.coluna += 1;
            hist[nMovs++] = kBaixoDireita;
        }

        if(baixoEsquerda(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs)){
            pAtual.linha += 2;
            pAtual.coluna -= 1;
            hist[nMovs++] = kBaixoEsquerda;
        }

        if(esquerdaBaixo(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs)){
            pAtual.linha += 1;
            pAtual.coluna -= 2;
            hist[nMovs++] = kEsquerdaBaixo;
        }

        if(esquerdaCima(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs)){
            pAtual.linha -= 1;
            pAtual.coluna -= 2;
            hist[nMovs++] = kEsquerdaCima;
        }

        else if(cimaEsquerda(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs)){
            pAtual.linha -= 2;
            pAtual.coluna -= 1;
            hist[nMovs++] = kCimaEsquerda;
        }

        else{
            printf("Fim da linha\n");
            break;

            /* trabalhar nessa parte
               implementar uma mecanica para retornar sem repetir              */
        }
    }

    int i;
    for(i = 0; i < nMovs; ++i){
        printf("%d\n", hist[i]);
    }

    free(hist);
}

    /* fazer uma matriz em que as colunas guardam a maior posicao tentada e
       as linhas guardam uma sequencia de movimentos                         */