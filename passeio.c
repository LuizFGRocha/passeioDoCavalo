#ifndef PASSEIO_H
#define PASSEIO_H
#include <stdio.h>

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
    int valor, proximosPossiveis, maiorTentado;
    coordenadas proxima[8];
    coordenadas posicao;
} casa;

// Checa a possibilidade de realizar um movimento. Retorna 1 se sim e 0 se não.
// A casa diz respeito à coordenada que será abandonada.
// O modo a ser inserido deve ser um inteiro de 1 a 8. As constantes nesse intervalo
// definidas no início deste arquivo servem para abstrair isso.
int cMovimento(casa casa, int modo) {

    switch(seletorDePrioridade(modo)){

        case kCimaDireita:
            if (tabuleiro[casa.posicao.linha - 2][casa.posicao.coluna + 1] != 0)
                return 0;

            if (casa.posicao.linha - 2 < 0)
                return 0;

            if (casa.posicao.coluna + 1 > 7)
                return 0;
    
            return 1;

        case kDireitaCima:
            if (tabuleiro[casa.posicao.linha - 1][casa.posicao.coluna + 2] != 0)
                return 0;

            if (casa.posicao.linha - 1 < 0)
                return 0;

            if (casa.posicao.coluna + 2 > 7)
                return 0;

            return 1;   

        case kDireitaBaixo:
            if (tabuleiro[casa.posicao.linha + 1][casa.posicao.coluna + 2] != 0)
                return 0;

            if (casa.posicao.linha + 1 > 7)
                return 0;

            if (casa.posicao.coluna + 2 > 7)
               return 0;

            return 1;   

        case kBaixoDireita:
            if (tabuleiro[casa.posicao.linha + 2][casa.posicao.coluna + 1] != 0)
                return 0;

            if (casa.posicao.linha + 2 > 7)
                return 0;

            if (casa.posicao.coluna + 1 > 7)
                return 0;

            return 1;   

        case kBaixoEsquerda:
            if (tabuleiro[casa.posicao.linha + 2][casa.posicao.coluna - 1] != 0)
                return 0;

            if (casa.posicao.linha + 2 > 7)
                return 0;

            if (casa.posicao.coluna - 1 < 0)
                return 0;

            return 1; 

        case kEsquerdaBaixo:
            if (tabuleiro[casa.posicao.linha + 1][casa.posicao.coluna - 2] != 0)
                return 0;

            if (casa.posicao.linha + 1 > 7)
                return 0;

            if (casa.posicao.coluna - 2 < 0)
                return 0;

            return 1;   

        case kEsquerdaCima:
            if (tabuleiro[casa.posicao.linha - 1][casa.posicao.coluna - 2] != 0)
                return 0;

            if (casa.posicao.linha - 1 < 0)
                return 0;

            if (casa.posicao.coluna - 2 < 0)
                return 0;

            return 1; 

        case kCimaEsquerda:
            if (tabuleiro[casa.posicao.linha - 2][casa.posicao.coluna - 1] != 0)
                return 0;

            if (casa.posicao.linha - 2 < 0)
                return 0;

            if (casa.posicao.coluna - 1 < 0)
                return 0;

            return 1;
    }
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

void passeio(int linhaInicial, int colunaInicial) {

    pAtual = {linhaInicial, colunaInicial};

    nMovAtual = 1;

    tabuleiro[pAtual.linha][pAtual.coluna].valor = nMovAtual;

    // O loop roda até o nMovAtual chegar em 64, o que indica que foram feitos 64 movimentos
    // sucessivos e que, naturalmente, todas as casas foram visitadas.
    while (1) {

        // Encontra o vetor de próximas casas para a posição atual. Ele se constitui das cordenadas para as quais o
        // cavalo pode ir no próximo turno.
        for (int contI = 0; contI < 8; ++contI) {
            tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI] = proximo(tabuleiro[pAtual.linha][pAtual.coluna].posicao, contI); 
        }

        // Ordena os elementos do vetor de proximos movimentos. As casas serão dispostas em ordem, vindo primeiro as
        // que têm mais movimentos seguintes possíveis. Bubble sort.
        coordenadas hold;
        int iter = 7;
        int cont = 1;
        while(cont){
            cont = 0;
            for(int contI = 0; contI < iter; contI++){
                if(nMovsPossiveis(tabuleiro[pAtual.linha][pAtual].proxima[contI]) > nMovsPossiveis(tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI + 1])){
                    hold = tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI];
                    tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI] = tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI + 1];
                    tabuleiro[pAtual.linha][pAtual.coluna].proxima[contI + 1] = hold;
                    cont++;
                }
            }
            iter--;
        }

        // É realizado o movimento, sendo o escolhido o que tem menor número de próximas casas possíveis.
        tabuleiro[tabuleiro[pAtual.linha][pAtual.coluna].proximo[0].linha][tabuleiro[pAtual.linha][pAtual.coluna].proximo[0].coluna].valor = ++nMov;

        // É atualizada a posição atual;
        pAtual = {tabuleiro[pAtual.linha][pAtual.coluna].proximo[0].linha, tabuleiro[pAtual.linha][pAtual.coluna].proximo[0].coluna}

    }
}

#endif // PASSEIO_H