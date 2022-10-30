#ifndef PASSEIO_H
#define PASSEIO_H

#include <stdio.h>
#include "comandos.h"

typedef struct {
    short int linha, coluna;
} coordenadas;

typedef struct {
    short int proximosPossiveis, maiorTentado;
    coordenadas posicao;
} casa;

#define kNaoMovimentado -1

/**
 * @brief essas constantes definem os modos de movimento. existem para facilitar
 * a escolha de um modo e a realizacao do movimento inverso a um anterior (para
 * o backtracking)
 */

#define kCimaDireita 1
#define kDireitaCima 2
#define kDireitaBaixo 3
#define kBaixoDireita 4
#define kBaixoEsquerda 5
#define kEsquerdaBaixo 6
#define kEsquerdaCima 7
#define kCimaEsquerda 8

#define kCima 1
#define kDireita 2
#define kBaixo 3
#define kEsquerda 4

int cMovimento(int modo);

void moveFrente(int modo);

void moveTras();

int ladoMaisProximo(int linha, int coluna);

int seletorDePrioridade(short int a);

short int prioridade[] = {
    kCimaEsquerda,
    kCimaDireita, 
    kEsquerdaCima,      
    kDireitaCima,   
    kEsquerdaBaixo, 
    kDireitaBaixo, 
    kBaixoEsquerda, 
    kBaixoDireita,
};

int itrPrioridade = 0;
int itrItrPrioridade = 1;

short int tabuleiro[8][8] = {0};
int headerI, headerJ, nPosAtual = 0;
coordenadas pAtual;
long long int nMovParcial = 1, nMovTotal = 1, nMovBackTotal = 0;
short int hist[64];

void passeio(int linhaInicial, int colunaInicial){

    //printf("Linha inicial: %d\nColuna inicial: %d\n", linhaInicial, colunaInicial);

    for (headerI = 0; headerI < 8; ++headerI) {
        for (headerJ = 0; headerJ < 8; ++headerJ) {
            tabuleiro[headerI][headerJ] = 0;
        }
    }
    nPosAtual = 0;
    nMovParcial = 1, nMovTotal = 1, nMovBackTotal = 0;

    switch(ladoMaisProximo(linhaInicial, colunaInicial)) {
        case kCima:
            prioridade[0] = kCimaEsquerda;
            prioridade[1] = kCimaDireita;
            prioridade[2] = kEsquerdaCima;
            prioridade[3] = kDireitaCima;
            prioridade[4] = kEsquerdaBaixo;
            prioridade[5] = kDireitaBaixo;
            prioridade[6] = kBaixoEsquerda;
            prioridade[7] = kBaixoDireita;
            break;
        case kDireita:
            prioridade[0] = kDireitaCima;
            prioridade[1] = kDireitaBaixo; 
            prioridade[2] = kCimaDireita; 
            prioridade[3] = kBaixoDireita;
            prioridade[4] = kCimaEsquerda;
            prioridade[5] = kBaixoEsquerda; 
            prioridade[6] = kEsquerdaCima;  
            prioridade[7] = kEsquerdaBaixo; 
            break;
        case kBaixo:
            prioridade[0] = kBaixoDireita;
            prioridade[1] = kBaixoEsquerda;
            prioridade[2] = kDireitaBaixo; 
            prioridade[3] = kEsquerdaBaixo; 
            prioridade[4] = kDireitaCima;   
            prioridade[5] = kEsquerdaCima;  
            prioridade[6] = kCimaDireita; 
            prioridade[7] = kCimaEsquerda;
        case kEsquerda:
            prioridade[0] = kEsquerdaBaixo; 
            prioridade[1] = kEsquerdaCima;  
            prioridade[2] = kBaixoEsquerda; 
            prioridade[3] = kCimaEsquerda;
            prioridade[4] = kBaixoDireita;
            prioridade[5] = kCimaDireita; 
            prioridade[6] = kDireitaBaixo;
            prioridade[7] = kDireitaCima;   
            break;
    }

    /**
     * @brief inicializacao do tabuleiro com todos os valores em 0 e das variaveis
     * que guardarao as coordenadas. as constantes foram decrementadas porque a
     * posicao da primeira linha e da primeira coluna e 0
     */

    tabuleiro[linhaInicial - 1][colunaInicial - 1] = 1;
    pAtual.linha = linhaInicial - 1;
    pAtual.coluna = colunaInicial - 1;

    nPosAtual = 0;


    /**
     * @brief inicializacao dos contadores. o "headerI" sera usado nos loops. "nPosAtual" conta
     * a quantidade de movimentos com sucesso. e decrementado nos backtrackings.
     * "nMovTotal" conta o total de movimentos, tanto "para frente" quanto "para tras".
     * ele nunca e decrementado. "nMovBackTotal" conta a quantidade de backtrackings
     */

    
    /**
     * @brief inicializacao do vetor "hist". ele guardara o movimento realizado para cada
     * incremento do "nPosAtual". caso um backtracking seja realizado, a ultima posicao escrita
     * do vetor sera apagada. ele e inicializado com -1 para indicar que nenhum dos
     * movimentos do vetor de movimentos foi realizado
     */

    for (headerI = 0; headerI < 64; ++headerI) {
        hist[headerI] = kNaoMovimentado;
    }

    /**
     * o while e executado ate que um caminho seja encontrado. nesse caso, o loop
     * sera quebrado
     */

    while (1) {

        /**
         * @brief o for atribui ao "headerI" o valor correspondente ao primeiro movimento
         * ainda nao utilizado na ordem de prioridade. comecando do -1, o for
         * atribui 0 ao "headerI", que corresponde a primeira posicao no vetor de prioridades.
         */

        for (int modo = hist[nPosAtual] + 1; ; ++modo) {

            /**
             * se o "headerI" for igual a 8, nao ha mais movimentos disponiveis. nesse caso, o
             * programa realiza o backtracking
             */

            if (modo == 8) {
                moveTras();
                break;
                
            /**
             * caso contrario, ainda ha movimentos disponiveis. dai, o programa checa a
             * possibilidade do proximo e o realiza se disponivel. senao, o for incrementa
             * o "headerI" e o proximo movimento e analisado
             */

            } else if (cMovimento(pAtual.linha, pAtual.coluna, modo)) {
                moveFrente(modo);
                break;
            }
        }
        
        /**
         * se foram dados 63 passos a partir da segunda casa, todas as casas foram visitadas,
         * ou seja, um caminho foi encontrado
         */


        if (nPosAtual == 63)
            break;  

        /**
         * imprime a matriz a cada loop do while. ajuda a debugar e permite ver o programa
         * funcionar, mas deixa ele significativamente mais lento
         */

        //imprimeMatriz8x8(tabuleiro);
        //puts("");
        // if (nMovTotal % 5000 == 0) {
        //    printf("%lld", nMovTotal);
        //}
    }

    /**
     * imprime os resultados do caminho encontrado
     */

    FILE* saida = fopen("saida.txt", "a");

    for (headerI = 0; headerI < 8; ++headerI) {
        for (headerJ = 0; headerJ < 7; ++headerJ) {
            fprintf(saida, "%d ", tabuleiro[headerI][headerJ]);
        }
        fprintf(saida, "%d\n", tabuleiro[headerI][7]);
    }
    fprintf(saida, "%lld %lld\n", nMovTotal, nMovBackTotal);

    fclose(saida);

    return;
}

int cMovimento(short int linha, short int coluna, int modo) {

    switch(seletorDePrioridade(modo)){

        case kCimaDireita:
            if (tabuleiro[linha - 2][coluna + 1] != 0)
                return 0;

            if (linha - 2 < 0)
                return 0;

            if (coluna + 1 > 7)
                return 0;
    
            return 1;

        case kDireitaCima:
            if (tabuleiro[linha - 1][coluna + 2] != 0)
                return 0;

            if (linha - 1 < 0)
                return 0;

            if (coluna + 2 > 7)
                return 0;

            return 1;   

        case kDireitaBaixo:
            if (tabuleiro[linha + 1][coluna + 2] != 0)
                return 0;

            if (linha + 1 > 7)
                return 0;

            if (coluna + 2 > 7)
               return 0;

            return 1;   

        case kBaixoDireita:
            if (tabuleiro[linha + 2][coluna + 1] != 0)
                return 0;

            if (linha + 2 > 7)
                return 0;

            if (coluna + 1 > 7)
                return 0;

            return 1;   

        case kBaixoEsquerda:
            if (tabuleiro[linha + 2][coluna - 1] != 0)
                return 0;

            if (linha + 2 > 7)
                return 0;

            if (coluna - 1 < 0)
                return 0;

            return 1; 

        case kEsquerdaBaixo:
            if (tabuleiro[linha + 1][coluna - 2] != 0)
                return 0;

            if (linha + 1 > 7)
                return 0;

            if (coluna - 2 < 0)
                return 0;

            return 1;   

        case kEsquerdaCima:
            if (tabuleiro[linha - 1][coluna - 2] != 0)
                return 0;

            if (linha - 1 < 0)
                return 0;

            if (coluna - 2 < 0)
                return 0;

            return 1; 

        case kCimaEsquerda:
            if (tabuleiro[linha - 2][coluna - 1] != 0)
                return 0;

            if (linha - 2 < 0)
                return 0;

            if (coluna - 1 < 0)
                return 0;

            return 1;
    }
}

void moveFrente(int modo) {

    nMovTotal++;
    nMovParcial++;

    hist[(nPosAtual)++] = modo;

    switch(seletorDePrioridade(modo)){
        case kCimaDireita:
            pAtual.linha -= 2;
            pAtual.coluna += 1;
            break;
        case kDireitaCima:
            pAtual.linha -= 1;
            pAtual.coluna += 2;
            break;
        case kDireitaBaixo:
            pAtual.linha += 1;
            pAtual.coluna += 2;
            break;
        case kBaixoDireita:
            pAtual.linha += 2;
            pAtual.coluna += 1;
            break;
        case kBaixoEsquerda:
            pAtual.linha += 2;
            pAtual.coluna -= 1;
            break;
        case kEsquerdaBaixo:
            pAtual.linha += 1;
            pAtual.coluna -= 2;
            break;
        case kEsquerdaCima:
            pAtual.linha -= 1;
            pAtual.coluna -= 2;
            break;
        case kCimaEsquerda:
            pAtual.linha -= 2;
            pAtual.coluna -= 1;
            break;
    }

    tabuleiro[pAtual.linha][pAtual.coluna] = nPosAtual + 1;
    return;
}

void moveTras() {

    nMovBackTotal++;

    tabuleiro[pAtual.linha][pAtual.coluna] = 0;

    switch(seletorDePrioridade(hist[nPosAtual - 1])) {
        case kCimaDireita:
            pAtual.linha += 2;
            pAtual.coluna -= 1;
            break;
        case kDireitaCima:
            pAtual.linha += 1;
            pAtual.coluna -= 2;
            break;
        case kDireitaBaixo:
            pAtual.linha -= 1;
            pAtual.coluna -= 2;
            break;
        case kBaixoDireita:
            pAtual.linha -= 2;
            pAtual.coluna -= 1;
            break;
        case kBaixoEsquerda:
            pAtual.linha -= 2;
            pAtual.coluna += 1;
            break;
        case kEsquerdaBaixo:
            pAtual.linha -= 1;
            pAtual.coluna += 2;
            break;
        case kEsquerdaCima:
            pAtual.linha += 1;
            pAtual.coluna += 2;
            break;
        case kCimaEsquerda:
            pAtual.linha += 2;
            pAtual.coluna += 1;
            break;
    }

    hist[nPosAtual] = -1;
    nPosAtual--;
    return;
}

int seletorDePrioridade(short int modo) {
    return prioridade[((modo + itrPrioridade) * itrItrPrioridade) % 8];
}

int ladoMaisProximo(int linha, int coluna) {
    if (linha < 4) {
        if (linha < coluna && linha < 8 - coluna) {
            return kCima;
        } else if (coluna < 8 - coluna) {
            return kEsquerda;
        } else {
            return kDireita;
        }
    } else {
        if (8 - linha < coluna && 8 - linha < 8 - coluna) {
            return kBaixo;
        } else if (coluna < 8 - coluna) {
            return kEsquerda;
        } else {
            return kDireita;
        }
    }
}

#endif  // PASSEIO_H