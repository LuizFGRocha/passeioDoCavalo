#ifndef PASSEIO_H
#define PASSEIO_H

#include <stdio.h>
#include "movimentos.h"
#include "comandos.h"

typedef struct {
    short int linha, coluna;
} coordenadas;

#define kNaoMovimentado -1

#define kCimaDireita 1
#define kDireitaCima 2
#define kDireitaBaixo 3
#define kBaixoDireita 4
#define kBaixoEsquerda 5
#define kEsquerdaBaixo 6
#define kEsquerdaCima 7
#define kCimaEsquerda 8

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

void fazerPasseio(int linhaInicial, int colunaInicial){

    printf("Linha inicial: %d\nColuna inicial: %d\n", linhaInicial, colunaInicial);

    /**
     * @brief inicializacao do tabuleiro com todos os valores em 0 e das variaveis
     * que guardarao as coordenadas. as constantes foram decrementadas porque a
     * posicao da primeira linha e da primeira coluna e 0
     */

    short int tabuleiro[8][8] = {0};
    tabuleiro[linhaInicial - 1][colunaInicial - 1] = 1;
    coordenadas pAtual = {linhaInicial - 1, colunaInicial - 1};

    /**
     * @brief inicializacao dos contadores. o "i" sera usado nos loops. "nMov" conta
     * a quantidade de movimentos com sucesso. e decrementado nos backtrackings.
     * "nMovTotal" conta o total de movimentos, tanto "para frente" quanto "para tras".
     * ele nunca e decrementado. "nMovBackTotal" conta a quantidade de backtrackings
     */

    int i, nMov = 0;
    long long int nMovTotal = 1, nMovBackTotal = 0;
    
    /**
     * @brief inicializacao do vetor "hist". ele guardara o movimento realizado para cada
     * incremento do "nMov". caso um backtracking seja realizado, a ultima posicao escrita
     * do vetor sera apagada. ele e inicializado com -1 para indicar que nenhum dos
     * movimentos do vetor de movimentos foi realizado
     */

    short int hist[64];
    for (i = 0; i < 64; ++i) {
        hist[i] = kNaoMovimentado;
    }

    /**
     * o while e executado ate que um caminho seja encontrado. nesse caso, o loop
     * sera quebrado
     */

    while (1) {

        /**
         * @brief o for atribui ao "i" o valor correspondente ao primeiro movimento
         * ainda nao utilizado na ordem de prioridade. comecando do -1, o for
         * atribui 0 ao "i", que corresponde a primeira posicao no vetor de prioridades.
         */

        for (i = hist[nMov] + 1; ; ++i) {

            /**
             * se o "i" for igual a 8, nao ha mais movimentos disponiveis. nesse caso, o
             * programa realiza o backtracking
             */

            if (i == 8) {
                moveTras(tabuleiro, &pAtual.linha, &pAtual.coluna, prioridade, &nMov,
                         &nMovTotal, &nMovBackTotal, hist);
                break;
                
            /**
             * caso contrario, ainda ha movimentos disponiveis. dai, o programa checa a
             * possibilidade do proximo e o realiza se disponivel. senao, o for incrementa
             * o "i" e o proximo movimento e analisado
             */

            } else if (cMovimento(tabuleiro, &pAtual.linha, &pAtual.coluna, prioridade, i)) {
                moveFrente(tabuleiro, &pAtual.linha, &pAtual.coluna, prioridade, i,
                           &nMov, &nMovTotal, hist);
                break;
            }
        }
        
        /**
         * se foram dados 63 passos a partir da segunda casa, todas as casas foram visitadas,
         * ou seja, um caminho foi encontrado
         */

        if (nMov == 63)
            break;

        /**
         * imprime a matriz a cada loop do while. ajuda a debugar e permite ver o programa
         * funcionar, mas deixa ele significativamente mais lento
         */

        // imprimeMatriz8x8(tabuleiro);
        // puts("");
    }

    /**
     * imprime os resultados do caminho encontrado
     */

    printf("Caminho encontrado!!\n\n");
    imprimeMatriz8x8(tabuleiro);
    printf("\nNumero de passos total: %lld\n", nMovTotal);
    printf("Numero de retornos: %lld\n\n", nMovBackTotal);

    return;
}

#endif  // PASSEIO_H