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

#define kLinhaInicial 1
#define kColunaInicial 8

typedef struct{
    short int linha, coluna;
} coordenadas;

int main(){

    short int tabuleiro[8][8] = {0};
    tabuleiro[kLinhaInicial - 1][kColunaInicial - 1] = 1;
    int nMov = 0, i;
    long long int nMovTotal = 0, nMovBackTotal = 0;
    coordenadas pAtual = {kLinhaInicial - 1, kColunaInicial - 1};
    short int hist[64];
    for (i = 0; i < 64; ++i) {
        hist[i] = 0;
    }

    while (1) {
        for (i = hist[nMov] + 1; ; ++i) { // checa a partir do ultimo movimento usado
            if (i == 9) {
                moveTras(tabuleiro, &pAtual.linha, &pAtual.coluna, &nMov,
                         &nMovTotal, &nMovBackTotal, hist);
                break;
            } else if (cMovimento(tabuleiro, &pAtual.linha, &pAtual.coluna, i)) {
                moveFrente(tabuleiro, &pAtual.linha, &pAtual.coluna, i, &nMov, &nMovTotal, hist);
                break;
            }
        }
        
        if (nMov == 63)
            break;

        // imprimeMatriz8x8(tabuleiro);
        // puts("");
    }

    printf("Caminho encontrado!!\n\n");
    imprimeMatriz8x8(tabuleiro);
    printf("\nNumero de passos total: %lld\n", nMovTotal);
    printf("Numero de retornos: %lld\n\n", nMovBackTotal);

    return 0;
}