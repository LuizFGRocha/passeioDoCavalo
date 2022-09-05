#include <stdio.h>
#include <stdlib.h>
#include "movimentos.h"
#include "comandos.h"

#define kCimaDireita 1
#define kDireitaCima 2
#define kDireitaBaixo 3
#define kBaixoDireita 4
#define kBaixoEsquerda 5
#define kEsquerdaBaixo 6
#define kEsquerdaCima 7
#define kCimaEsquerda 8

/* essa identificacao e util pra pegar o movimento inverso, para fazer o
   backtracking                                                              */

typedef struct{
    short int linha, coluna;
} coordenadas;

int main(){

    /* declaracao do tabuleiro e inicializacao da variavel que guarda a 
       posicao atual e do vetor que guarda qual o maior movimento tentado    */
    short int tabuleiro[8][8] = {0};
    tabuleiro[0][0] = 1;
    int nMovs = 0;
    coordenadas pAtual = {0, 0};
    short int* hist = malloc(500 * sizeof(short int));
    int superLim = 500; 

    while(1){
        if(cimaDireita(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs, hist)){
            pAtual.linha -= 2;
            pAtual.coluna += 1;
            hist[nMovs++] = kCimaDireita;
            tabuleiro[pAtual.linha][pAtual.coluna] = nMovs + 1;
        }

        else if(direitaCima(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs, hist)){
            pAtual.linha -= 1;
            pAtual.coluna += 2;
            hist[nMovs++] = kDireitaCima;
            tabuleiro[pAtual.linha][pAtual.coluna] = nMovs + 1;
        }

        else if(direitaBaixo(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs, hist)){
            pAtual.linha += 1;
            pAtual.coluna += 2;
            hist[nMovs++] = kDireitaBaixo;
            tabuleiro[pAtual.linha][pAtual.coluna] = nMovs + 1;
        }

        else if(baixoDireita(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs, hist)){
            pAtual.linha += 2;
            pAtual.coluna += 1;
            hist[nMovs++] = kBaixoDireita;
            tabuleiro[pAtual.linha][pAtual.coluna] = nMovs + 1;
        }

        else if(baixoEsquerda(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs, hist)){
            pAtual.linha += 2;
            pAtual.coluna -= 1;
            hist[nMovs++] = kBaixoEsquerda;
            tabuleiro[pAtual.linha][pAtual.coluna] = nMovs + 1;
        }

        else if(esquerdaBaixo(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs, hist)){
            pAtual.linha += 1;
            pAtual.coluna -= 2;
            hist[nMovs++] = kEsquerdaBaixo;
            tabuleiro[pAtual.linha][pAtual.coluna] = nMovs + 1;
        }

        else if(esquerdaCima(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs, hist)){
            pAtual.linha -= 1;
            pAtual.coluna -= 2;
            hist[nMovs++] = kEsquerdaCima;
            tabuleiro[pAtual.linha][pAtual.coluna] = nMovs + 1;
        }

        else if(cimaEsquerda(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMovs, hist)){
            pAtual.linha -= 2;
            pAtual.coluna -= 1;
            hist[nMovs++] = kCimaEsquerda;
            tabuleiro[pAtual.linha][pAtual.coluna] = nMovs + 1;
        }

        else{
            printf("Fim da linha\n");
            break;

            /* trabalhar nessa parte
               implementar uma mecanica para retornar sem repetir
               trocar a ordem da prioridade?
               sempre estou indo no primeiro de 1 a 8, talvez alguma das
               prioridades necessariamente resolva?
               ==> mas isso nao e backtracking, e exaustao                   */
        }

        
/* 
        imprimeMatriz8x8(tabuleiro);
        puts("");
 */
        if (nMovs == superLim) {
            hist = realloc(hist, 2 * superLim);
            superLim *= 2;
        }
    }

    imprimeMatriz8x8(tabuleiro);
    puts("");

    int i;
    for(i = 0; i < nMovs; ++i){
        printf("%2d || ", hist[i]);
    }
    puts("");

    free(hist);
}

    /* fazer uma matriz em que as colunas guardam a maior posicao tentada e
       as linhas guardam uma sequencia de movimentos                         */