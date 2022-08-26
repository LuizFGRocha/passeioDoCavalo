#include <stdio.h>
#include <stdlib.h>

// estas constantes formarão o vetor que enumera os movimentos que foram feitos
// **note que cada movimento tem seu inverso

#define kCimaDireita 1
#define kDireitaCima 2
#define kDireitaBaixo 3
#define kBaixoDireita 4
#define kBaixoEsquerda 5
#define kEsquerdaBaixo 6
#define kEsquerdaCima 7
#define kCimaEsquerda 8


/*

Esboco: 

1) Inicializar um tabuleiro 8x8, preencher as casas com 0.

2) Fazer funções que descrevem os possíveis movimentos do cavalo, incluindo
   critérios para decidir sobre a sua validade.


Detalhes: 

    as coordenadas do tabuleiro estao dadas como em uma matriz, na ordem [linha][coluna].


Brainstorm:

    se o movimento tiver sucesso, ele retorna 1. isso deve ser suficiente para
    saber a nova posicao e aumentar a quantidade de casas em que o cavalo andou

    vetores feitos com alocação dinamica. dobrar memoria conforme necessario,
    comecar com 10000

    nas bifurcacoes, dividir as possibilidades e dar o backtrack so se elas se
    esgotarem

    anotar as possibilidades de cada passo. matriz

*/


int main(){

    int tabuleiro[8][8] = {0}; // inicializa o tabuleiro e preenche todas as casas com 0

    char** historico = malloc(10000 * sizeof(char)); // o historico guardara os
                                                     // caracteres que definem
                                                     // as constantes, na sequencia
                                                     // em que os respectivos
                                                     // movimentos forem realizados

// TODO corrigir o comentario acima

    int passoAtual = 1;

    int resultado = fazerPasseio(tabuleiro, historico, passoAtual);




    int passoAtual = 1; // essa variavel guarda o passo atual na casa mais recente
                        // ela deve aumentar ou diminuir no decorrer da execucao
                        // do programa, na medida que o cavalo anda para frente
                        // e para trás, respectivamente

    free(historico);
}

/*

TODO

arrumar um jeito de desmarcar as possibilidades usadas a depender do backtrack,
alguma especie de análise geral do tabuliro. salvar imagem do momento do
backtrack e liberar as possibilidades se o estado estiver diferente?

*/