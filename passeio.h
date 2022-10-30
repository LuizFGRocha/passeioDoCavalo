#ifndef PASSEIO_H
#define PASSEIO_H
#include <stdio.h>
#include "comandos.h"

// Serve para inicializar o histórico.
#define kNaoMovimentado -1

// Servem para abstrair os "modos" de movimento. Cada constante
// será usada para uma direção.
#define kCimaDireita 1
#define kDireitaCima 2
#define kDireitaBaixo 3
#define kBaixoDireita 4
#define kBaixoEsquerda 5
#define kEsquerdaBaixo 6
#define kEsquerdaCima 7
#define kCimaEsquerda 8

// Guarda coordenadas. Uma linha e uma coluna.
typedef struct{
    int linha, coluna;
} coordenadas;

// A estrutura casa constitui o tabuleiro.
// Cada casa tem:
// **um valor, que corresponde ao número do movimento em que o cavalo passou pela casa 
// **um "maiorTentado", que guia quantos caminhos saindo dessa casa já foram testados,
// para que o backtracking seja realizado 
// **um vetor de coordenadas que listas as próximas casas possíveis, em ordem de qualidade
// **sua posição.
typedef struct{
    int valor, proximosPossiveis, maiorTentado, estudada;
    coordenadas proxima[8];
    coordenadas posicao;
} casa;

// Checa a possibilidade de realizar um movimento. Retorna 1 se sim e 0 se não.
// A casa diz respeito à coordenada que será abandonada.
// O modo a ser inserido deve ser um inteiro de 1 a 8. As constantes nesse intervalo
// definidas no início deste arquivo servem para abstrair isso.
int cMovimento(coordenadas casa, int modo);

// Verdadeiro se a coordenada está no tabuleiro, falso se ela não está.
int ehValido(coordenadas coordenadas) {
    return (coordenadas.linha >= 0 && coordenadas.linha <= 7 && coordenadas.coluna >= 0 && coordenadas.coluna <= 7);
}

// Determina o número de movimentos possíveis saindo de uma casa dada como entrada.
// Checa se o movimento vai para dentro da tabuleiro e se o cavalo ainda não passou
// pela casa. Casas não visitadas tem o valor 0.
int nMovsPossiveis(coordenadas casa) {
    int i, count = 0;
    for (i = 1; i <= 8; ++i) {
        if (cMovimento(casa, i)) count++;
    }
    return count;
}

coordenadas proximo(coordenadas casaAtual, int modo) {
    coordenadas a;
    switch(modo) {
        case kCimaDireita:
            a.linha = casaAtual.linha - 2;
            a.coluna = casaAtual.coluna + 1;
            return a;
        case kDireitaCima:
            a.linha = casaAtual.linha - 1;   
            a.coluna = casaAtual.coluna + 2;   
            return a;
        case kDireitaBaixo:
            a.linha = casaAtual.linha + 1;
            a.coluna = casaAtual.coluna + 2;
            return a;
        case kBaixoDireita:
            a.linha = casaAtual.linha + 2;
            a.coluna = casaAtual.coluna + 1;
            return a;
        case kBaixoEsquerda:
            a.linha = casaAtual.linha + 2;
            a.coluna = casaAtual.coluna - 1;
            return a;
        case kEsquerdaBaixo:
            a.linha = casaAtual.linha + 1;
            a.coluna = casaAtual.coluna - 2;
            return a;
        case kEsquerdaCima:
            a.linha = casaAtual.linha - 1;
            a.coluna = casaAtual.coluna - 2;
            return a;
        case kCimaEsquerda:
            a.linha = casaAtual.linha - 2;
            a.coluna = casaAtual.coluna - 1;
            return a;
        default:
            a.linha = 0;
            a.coluna = 0;
            return a;
    }
}

// Um tabuleiro formado por casas. Cada casa tem:
// **um valor, que corresponde ao número do movimento em que o cavalo passou pela casa 
// **um "maiorTentado", que guia quantos caminhos saindo dessa casa já foram testados,
// para que o backtracking seja realizado 
// **um vetor de coordenadas que listas as próximas casas possíveis, em ordem de qualidade
// **sua posição.
// O vetor começa sem informações. Elas serão preenchidas durante a execução.
// É declarado no escopo global para simplificar as chamadas de função.
casa tabuleiro[8][8];

// Posição atual.
// É declarado no escopo global para simplificar as chamadas de função.
coordenadas pAtual;

// Número de movimentos com sucesso até um dado momento.
// É dado por: número de passos - número de backtrackings.
// Quando esse número chega a 64, o programa para.
// É declarado no escopo global para simplificar as chamadas de função.
int nMovAtual;

// Número de movimentos total.
// É declarado no escopo global para simplificar as chamadas de função.
int nMovTotal;

// Número de backtrackings total.
// É declarado no escopo global para simplificar as chamadas de função.
int nBackTotal;

void passeio(int linhaInicial, int colunaInicial) {

    pAtual.linha = linhaInicial;
    pAtual.coluna = colunaInicial;

    nMovAtual = 1;

    tabuleiro[pAtual.linha][pAtual.coluna].valor = nMovAtual;

    // O loop roda até o nMovAtual chegar em 64, o que indica que foram feitos 64 movimentos
    // sucessivos e que, naturalmente, todas as casas foram visitadas.
    while (1) {
        
        if (nMovAtual == 64)
            break;

        // Os dois blocos abaixo analisam os movimentos da casa, encontrando-os e ordenando-os.

        if (!tabuleiro[pAtual.linha][pAtual.coluna].estudada) {
            // Encontra o vetor de próximas casas para a posição atual. Ele se constitui das cordenadas para as quais o
            // cavalo pode ir no próximo turno.
            for (int contI = 0; contI < 8; ++contI) {
                if (ehValido(proximo(tabuleiro[pAtual.linha][pAtual.coluna].posicao, contI))) {
                    tabuleiro[pAtual.linha][pAtual.coluna].proxima[tabuleiro[pAtual.linha][pAtual.coluna].proximosPossiveis++] = 
                    proximo(tabuleiro[pAtual.linha][pAtual.coluna].posicao, contI); 

                    tabuleiro[pAtual.linha][pAtual.coluna].proximosPossiveis++;
                }
            }

            // Ordena os elementos do vetor de proximos movimentos. As casas serão dispostas em ordem, vindo primeiro as
            // que têm mais movimentos seguintes possíveis. Bubble sort.
            coordenadas hold;
            int iter = tabuleiro[pAtual.linha][pAtual.coluna].proximosPossiveis - 1;
            int cont = 1;
            while(cont){
                cont = 0;
                for(int contI = 0; contI < iter; contI++){
                    if(nMovsPossiveis(tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI]) > nMovsPossiveis(tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI + 1])){
                        hold = tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI];
                        tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI] = tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI + 1];
                        tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI + 1] = hold;
                        cont++;
                    }
                }
                iter--;
            }
            tabuleiro[pAtual.linha][pAtual.coluna].estudada = 1;
        }

        // Se o número de tentativas realizadas é igual ao número de tentativas disponíveis, é necessário fazer um backtracking.
        if (tabuleiro[pAtual.linha][pAtual.coluna].maiorTentado == tabuleiro[pAtual.linha][pAtual.coluna].proximosPossiveis) {

        } else {
            // É realizado o movimento, sendo o escolhido o que tem menor número de próximas casas possíveis que ainda não foi tentado.
            tabuleiro[tabuleiro[pAtual.linha][pAtual.coluna].proxima[tabuleiro[pAtual.linha][pAtual.coluna].maiorTentado].linha]
            [tabuleiro[pAtual.linha][pAtual.coluna].proxima[tabuleiro[pAtual.linha][pAtual.coluna].maiorTentado].coluna].valor = ++nMovAtual;
        }

        // É atualizada a posição atual;
        pAtual.linha = tabuleiro[pAtual.linha][pAtual.coluna].proxima[tabuleiro[pAtual.linha][pAtual.coluna].maiorTentado].linha;
        pAtual.coluna = tabuleiro[pAtual.linha][pAtual.coluna].proxima[tabuleiro[pAtual.linha][pAtual.coluna].maiorTentado].coluna;

    }

    imprimeTabuleiro8x8(tabuleiro);
}

int cMovimento(coordenadas casa, int modo) {

    switch(modo){

        case kCimaDireita:
            if (tabuleiro[casa.linha - 2][casa.coluna + 1].valor != 0)
                return 0;

            if (casa.linha - 2 < 0)
                return 0;

            if (casa.coluna + 1 > 7)
                return 0;
    
            return 1;

        case kDireitaCima:
            if (tabuleiro[casa.linha - 1][casa.coluna + 2].valor != 0)
                return 0;

            if (casa.linha - 1 < 0)
                return 0;

            if (casa.coluna + 2 > 7)
                return 0;

            return 1;   

        case kDireitaBaixo:
            if (tabuleiro[casa.linha + 1][casa.coluna + 2].valor != 0)
                return 0;

            if (casa.linha + 1 > 7)
                return 0;

            if (casa.coluna + 2 > 7)
               return 0;

            return 1;   

        case kBaixoDireita:
            if (tabuleiro[casa.linha + 2][casa.coluna + 1].valor != 0)
                return 0;

            if (casa.linha + 2 > 7)
                return 0;

            if (casa.coluna + 1 > 7)
                return 0;

            return 1;   

        case kBaixoEsquerda:
            if (tabuleiro[casa.linha + 2][casa.coluna - 1].valor != 0)
                return 0;

            if (casa.linha + 2 > 7)
                return 0;

            if (casa.coluna - 1 < 0)
                return 0;

            return 1; 

        case kEsquerdaBaixo:
            if (tabuleiro[casa.linha + 1][casa.coluna - 2].valor != 0)
                return 0;

            if (casa.linha + 1 > 7)
                return 0;

            if (casa.coluna - 2 < 0)
                return 0;

            return 1;   

        case kEsquerdaCima:
            if (tabuleiro[casa.linha - 1][casa.coluna - 2].valor != 0)
                return 0;

            if (casa.linha - 1 < 0)
                return 0;

            if (casa.coluna - 2 < 0)
                return 0;

            return 1; 

        case kCimaEsquerda:
            if (tabuleiro[casa.linha - 2][casa.coluna - 1].valor != 0)
                return 0;

            if (casa.linha - 2 < 0)
                return 0;

            if (casa.coluna - 1 < 0)
                return 0;

            return 1;
    }
}

#endif // PASSEIO_H