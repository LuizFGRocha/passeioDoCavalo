#ifndef PASSEIO_H
#define PASSEIO_H
#include <stdio.h>

/******************************************************************************
*                                 CONSTANTES                                  *
******************************************************************************/

// Servem para abstrair os "modos" de movimento. Cada constante
// será usada para uma direção.
#define kCimaDireita 1 // Dois para cima e um para a direita
#define kDireitaCima 2 // Dois para a direita e um para cima
#define kDireitaBaixo 3 // Dois para a direita e um para baixo
#define kBaixoDireita 4 // Dois para baixo e um para a direita
#define kBaixoEsquerda 5 // Dois para baixo e um para a esquerda
#define kEsquerdaBaixo 6 // Dois para a esquerda e um para baixo
#define kEsquerdaCima 7 // Dois para a esquerda e um para cima
#define kCimaEsquerda 8 // Dois para cima e um para a esquerda

/******************************************************************************
*                            ESTRUTURAS DE DADOS                              *
******************************************************************************/

// Guarda coordenadas. Uma linha e uma coluna.
typedef struct{
    int linha, coluna;
} coordenadas;

// A estrutura casa constitui o tabuleiro. Mais detalhes na declaração.
typedef struct{
    // Diz qual é a posição da casa, de 1 a 64. A primeira casa
    // que o cavalo visita tem valor 1, a segunda tem valor 2, 
    // assim em diante.
    int valor;

    // Diz quantas opções de movimento existem a partir dessa casa.
    // Uma opção é considerada se a casa está no tabuleiro e ainda
    // não foi visitada.
    int qtdProximosPossiveis;

    // Diz qual foi o maior movimento já tentado dentre os disponíveis,
    // que estão listados em ordem de qualidade no vetor "próxima". 
    // Quando um backtracking é feto, esse valor é incrementado, de modo
    // indicar que, na próxima tentativa de movimento, outro movimento
    // deve ser tentado.
    int maiorTentado; 

    // Pode assumir os valores 0 ou 1, para não estudada e estudada,
    // respectivamente. Dizemos que uma casa está "estudada" quando
    // seu vetor "proxima" foi preenchido e ordenado, sua "qtdProximosPossiveis"
    // foi determinada e seu valor de "maiorTentado" foi zerado.
    int estudada;

    // Vetor que contém as casas acessíveis a partir dessa com um único
    // movimento. Está ordenado em ordem de qualidade pela heurística do 
    // grau mínimo: as casas menos acessíveis (que têm menos movimentos
    // disponíveis) vêm antes e, assim, são tentadas antes.
    coordenadas proxima[8];

    // Guarda a casa que o cavalo ocupou antes da atual. Guia o backtracking.
    coordenadas anterior;

    // Guarda as coordenadas da posição da casa.
    coordenadas posicao;
} casa;

/******************************************************************************
*                                   FUNÇÕES                                   *
******************************************************************************/

// Retorna a coordenada resultante da realização do movimento determinado pelo modo.
// Os modos são inteiros variando de 1 a 8 e correspondem às constantes com nome sugestivo
// declaradas no início deste arquivo. Há mais detalhes na declaração delas.
coordenadas proximo(coordenadas casaAtual, int modo);

// Verdadeiro se a coordenada está no tabuleiro e não foi utilizada, 
// falso se ela não está ou se ela foi utilizada.
int ehValido(casa tabuleiro[][8], coordenadas coordenadas);

// Imprime o tabuleiro na saída padrão.
void imprimeTabuleiro8x8(casa tabuleiro[][8]);

// Determina o número de movimentos possíveis saindo de uma casa dada como entrada.
// Checa se o movimento vai para dentro da tabuleiro e se o cavalo ainda não passou
// pela casa. Casas não visitadas tem o valor 0.
int nMovsPossiveis(casa tabuleiro[][8], coordenadas casa);


/******************************************************************************
*                                FUNÇÃO PASSEIO                               *
******************************************************************************/

// Realiza o passeio.
void passeio(int linhaInicial, int colunaInicial) {

    // Um tabuleiro formado por casas. Mais detalhes na declaração.
    casa tabuleiro[8][8];

    // Guarda as coordenadas da posição atual.
    coordenadas pAtual;

    // Número de movimentos com sucesso até um dado momento.
    // É dado por: número de passos - número de backtrackings.
    // Quando esse número chega a 64, o programa para.
    int nMovAtual;

    // Número de movimentos total.
    int nMovTotal;

    // Número de backtrackings total.
    int nBackTotal;

    // Inicializa as casas do tabuleiro.
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            tabuleiro[i][j].valor = 0;
            tabuleiro[i][j].estudada = 0;
            tabuleiro[i][j].maiorTentado = 0;
            tabuleiro[i][j].qtdProximosPossiveis = 0;
        }
    }
            
    // Inicializa a posição inicial (contando a partir de 0).
    pAtual.linha = linhaInicial - 1;
    pAtual.coluna = colunaInicial - 1;

    // Contabiliza o primeiro movimento (para a casa inicial).
    nMovAtual = 1;

    // Adiciona o primeiro movimento ao total e inicializa o total de backtrackings
    // como 0.
    nMovTotal = 1;
    nBackTotal = 0;

    // Coloca o valor 1 na casa inicial do tabuleiro.
    tabuleiro[pAtual.linha][pAtual.coluna].valor = nMovAtual;

    // O loop roda até o nMovAtual chegar em 64, o que indica que foram feitos 64 movimentos
    // sucessivos e que, naturalmente, todas as casas foram visitadas.
    while (nMovAtual < 64) {

        // Inicializa o campo de coordenadas da casa atual com as suas coordenadas.
        tabuleiro[pAtual.linha][pAtual.coluna].posicao.linha = pAtual.linha;
        tabuleiro[pAtual.linha][pAtual.coluna].posicao.coluna = pAtual.coluna;

        // Os dois blocos abaixo analisam os movimentos da casa, encontrando-os e ordenando-os, caso
        // ela ainda não tenha sido estudada.
        if (!tabuleiro[pAtual.linha][pAtual.coluna].estudada) {

            tabuleiro[pAtual.linha][pAtual.coluna].qtdProximosPossiveis = 0;
            tabuleiro[pAtual.linha][pAtual.coluna].maiorTentado = 0;
            // Encontra o vetor de próximas casas para a posição atual. Ele se constitui das cordenadas para as quais o
            // cavalo pode ir no próximo turno.
            for (int contI = 1; contI <= 8; ++contI) {

                if (ehValido(tabuleiro, proximo(pAtual, contI))) {
                    
                    // As próximas linhas são densas, mas acontece o seguinte:
                    // A posição de valor "qtdProximasPossiveis" do vetor "proxima" da casa indicada por "pAtual" recebe
                    // as coordenadas encontradas dentro deste if, se elas forem um móvimento válido, caso em que a
                    // a condição é verdadeira.
                    tabuleiro[pAtual.linha][pAtual.coluna].proxima[tabuleiro[pAtual.linha][pAtual.coluna].qtdProximosPossiveis] = 
                    proximo(tabuleiro[pAtual.linha][pAtual.coluna].posicao, contI); 

                    tabuleiro[pAtual.linha][pAtual.coluna].qtdProximosPossiveis++;
                }
            }

            // Ordena os elementos do vetor de proximos movimentos. As casas serão dispostas em ordem, vindo primeiro as
            // que têm mais movimentos seguintes possíveis, como segue da heurística do grau mínimo. É usado o bubble sort.
            coordenadas hold;
            int iter = tabuleiro[pAtual.linha][pAtual.coluna].qtdProximosPossiveis - 1;
            int cont = 1;
            while (cont) {
                cont = 0;
                for (int i = 0; i < iter; i++) {

                    // Se o número de movimentos possíveis de uma casa for maior que a de outra,
                    // suas posições são trocadas. A cada iteração, a maior é colocada no final.
                    if (nMovsPossiveis(tabuleiro, tabuleiro[pAtual.linha][pAtual.coluna].proxima[i]) > 
                        nMovsPossiveis(tabuleiro, tabuleiro[pAtual.linha][pAtual.coluna].proxima[i + 1])) {
                        hold = tabuleiro[pAtual.linha][pAtual.coluna].proxima[i];
                        tabuleiro[pAtual.linha][pAtual.coluna].proxima[i] = tabuleiro[pAtual.linha][pAtual.coluna].proxima[i + 1];
                        tabuleiro[pAtual.linha][pAtual.coluna].proxima[i + 1] = hold;
                        cont++;
                    }
                }
                iter--;
            }

            // O valor 1 indica que a casa em questão teve seu estudo concluído.
            tabuleiro[pAtual.linha][pAtual.coluna].estudada = 1;
        }

        // Se o número de tentativas realizadas é igual ao número de tentativas disponíveis, 
        // é necessário fazer um backtracking.
        // O backtracking é realizado se essa condição for verdadeira.
        if (tabuleiro[pAtual.linha][pAtual.coluna].maiorTentado == 
            tabuleiro[pAtual.linha][pAtual.coluna].qtdProximosPossiveis) {

            // Copiamos a linha atual e a coluna atual, de modo que a estrutura 
            // pAtual possa ser alterada sem comprometer o acesso às suas 
            // coordenadas inciais.
            int linhaAtual = pAtual.linha, colunaAtual = pAtual.coluna;

            // O valor da casa é restado para 0, para indicar que ela foi "desvisitada".
            tabuleiro[pAtual.linha][pAtual.coluna].valor = 0;

            // Já que o backtracking foi realizado, um retorno posterior a essa casa demanda 
            // que ela seja estudada novamente, tomando como base o estado atual do tabuleiro.
            tabuleiro[pAtual.linha][pAtual.coluna].estudada = 0;

            // Atribui à estrutura pAtual as coordenadas da casa anterior.
            pAtual.linha = tabuleiro[linhaAtual][colunaAtual].anterior.linha;
            pAtual.coluna = tabuleiro[linhaAtual][colunaAtual].anterior.coluna;

            // Aumenta o valor de maiorTentado, para indicar que mais um movimento foi tentado.
            tabuleiro[pAtual.linha][pAtual.coluna].maiorTentado++;

            // Diminui o número do movimento atual e aumenta o contador de backtracking.
            nMovAtual--;
            ++nBackTotal;
        } else {

            // Se não é necessário fazer o backtracking, é realizado o movimento, sendo o escolhido leva para a casa que tem o menor número 
            // de próximas casas possíveis que ainda não foi tentado.

            // A notação é muito densa devido aos múltiplos acessos às estruturas de dados. É feito o seguinte:
            // São acessados o valor da linha e o valor da coluna da melhor casa no vetor "proxima" da casa atual.
            // Esses valores são utilizados para acessar essa melhor casa no tabuleiro e colocar nela o valor de
            // "nMovAtual" + 1. 
            // Basicamente, o movimento é gravado no tabuleiro e nMovAtual é incrementada.
            tabuleiro[tabuleiro[pAtual.linha][pAtual.coluna].proxima[tabuleiro[pAtual.linha][pAtual.coluna].maiorTentado].linha]
            [tabuleiro[pAtual.linha][pAtual.coluna].proxima[tabuleiro[pAtual.linha][pAtual.coluna].maiorTentado].coluna].valor = ++nMovAtual;
            ++nMovTotal;

            // São gravados os valores atuais de linha e coluna (os de antes da realização do movimento) para que
            // eles sejam gravados no campo "anterior" da nova casa atual.
            int linhaAtual = pAtual.linha;
            int colunaAtual = pAtual.coluna;

            // A posição em "pAtual" é atualizada.
            pAtual.linha = tabuleiro[linhaAtual][colunaAtual].proxima[tabuleiro[linhaAtual][colunaAtual].maiorTentado].linha;
            pAtual.coluna = tabuleiro[linhaAtual][colunaAtual].proxima[tabuleiro[linhaAtual][colunaAtual].maiorTentado].coluna;

            // É preenchido o campo "anterior" da nova casa atual.
            tabuleiro[pAtual.linha][pAtual.coluna].anterior.linha = linhaAtual;
            tabuleiro[pAtual.linha][pAtual.coluna].anterior.coluna = colunaAtual;
        }

        // Descomente a próxima linha e rode o programa no debugger com um breakpoint nela
        // para ver o caminho ser encontrado passo a passo. O programa imprimirá uma nova matriz
        // toda vez que um movimento for feito, para frente ou para trás.
        // imprimeTabuleiro8x8(tabuleiro);
    }

    // As próximas linhas servem para criar o arquivo "saida.txt" e gravar os resultados nele.

    FILE* saida = fopen("saida.txt", "a");

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 7; ++j) {
            fprintf(saida, "%d ", tabuleiro[i][j].valor);
        }
        fprintf(saida, "%d\n", tabuleiro[i][7].valor);
    }
    fprintf(saida, "%d %d\n", nMovTotal, nBackTotal);

    fclose(saida);
    
    return;
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

int ehValido(casa tabuleiro[][8], coordenadas coordenadas) {
    return (coordenadas.linha >= 0 && coordenadas.linha <= 7 && coordenadas.coluna >= 0 && 
    coordenadas.coluna <= 7 && tabuleiro[coordenadas.linha][coordenadas.coluna].valor == 0);
}

void imprimeTabuleiro8x8(casa tabuleiro[][8]){
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 7; ++j) {
            printf("%2d ", tabuleiro[i][j].valor);
        }
        printf("%2d\n", tabuleiro[i][7].valor);
    }
    printf("\n");

    return;
}

int nMovsPossiveis(casa tabuleiro[][8], coordenadas casa) {
    int i, count = 0;
    for (i = 1; i <= 8; ++i) {
        if (ehValido(tabuleiro, proximo(casa, i))) count++;
    }
    return count;
}

#endif // PASSEIO_H