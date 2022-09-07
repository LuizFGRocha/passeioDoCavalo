#include "movimentos.h"

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

/**
 * @brief checa a possibilidade de um movimento
 * 
 * @param tabuleiro o tabuleiro para o qual a possibilidade sera checada
 * @param linha a linha atual no tabuleiro
 * @param coluna a coluna atual no tabuleiro
 * @param modo o modo que sera checado
 * @return 1 se o movimento e possivel, 0 se nao
 */

int cMovimento(short int tabuleiro[][8], short int* linha, short int* coluna,
               short int prioridade[], int i) {

    switch(prioridade[i]){
        case kCimaDireita:
            return cCimaDireita(tabuleiro, linha, coluna);
        case kDireitaCima:
            return cDireitaCima(tabuleiro, linha, coluna);
        case kDireitaBaixo:
            return cDireitaBaixo(tabuleiro, linha, coluna);
        case kBaixoDireita:
            return cBaixoDireita(tabuleiro, linha, coluna);
        case kBaixoEsquerda:
            return cBaixoEsquerda(tabuleiro, linha, coluna);
        case kEsquerdaBaixo:
            return cEsquerdaBaixo(tabuleiro, linha, coluna);
        case kEsquerdaCima:
            return cEsquerdaCima(tabuleiro, linha, coluna);
        case kCimaEsquerda:
            return cCimaEsquerda(tabuleiro, linha, coluna);
    }
}

/**
 * @brief serve para mover para frente (como no contrario de fazer o backtracking)
 * 
 * @param tabuleiro tabuleiro no qual o movimento sera feito
 * @param linha linha atual no tabuleiro
 * @param coluna coluna atual no tabuleiro
 * @param modo o movimento a ser executado (ver explicacao na definicao das constantes)
 * @param nMov posicao ordinal do movimento atual (nao confundir cm nMovTotal)
 * @param nMovTotal numero de movimentos realizados, ignorando os retornos
 * @param hist vetor que contem os movimentos realizados anteriormente
 */

void moveFrente(short int tabuleiro[][8], short int* linha, short int* coluna,
                short int prioridade[], int i, int* nMov, long long int* nMovTotal,
                short int* hist) {

    (*nMovTotal)++;

    hist[(*nMov)++] = i;

    switch(prioridade[i]){
        case kCimaDireita:
            mvCimaDireita(tabuleiro, linha, coluna);
            break;
        case kDireitaCima:
            mvDireitaCima(tabuleiro, linha, coluna);
            break;
        case kDireitaBaixo:
            mvDireitaBaixo(tabuleiro, linha, coluna);
            break;
        case kBaixoDireita:
            mvBaixoDireita(tabuleiro, linha, coluna);
            break;
        case kBaixoEsquerda:
            mvBaixoEsquerda(tabuleiro, linha, coluna);
            break;
        case kEsquerdaBaixo:
            mvEsquerdaBaixo(tabuleiro, linha, coluna);
            break;
        case kEsquerdaCima:
            mvEsquerdaCima(tabuleiro, linha, coluna);
            break;
        case kCimaEsquerda:
            mvCimaEsquerda(tabuleiro, linha, coluna);
            break;
    }

    tabuleiro[*linha][*coluna] = *nMov + 1;
    return;
}

void moveTras(short int tabuleiro[][8], short int* linha, short int* coluna,
              short int* prioridade, int* nMov, long long int* nMovTotal,
              long long int* nMovBackTotal, short int* hist) {

    (*nMovBackTotal)++;
    (*nMovTotal)++;

    tabuleiro[*linha][*coluna] = 0;

    switch(prioridade[hist[*nMov - 1]]) {
        case kCimaDireita:
            mvBaixoEsquerda(tabuleiro, linha, coluna);
            break;
        case kDireitaCima:
            mvEsquerdaBaixo(tabuleiro, linha, coluna);
            break;
        case kDireitaBaixo:
            mvEsquerdaCima(tabuleiro, linha, coluna);
            break;
        case kBaixoDireita:
            mvCimaEsquerda(tabuleiro, linha, coluna);
            break;
        case kBaixoEsquerda:
            mvCimaDireita(tabuleiro, linha, coluna);
            break;
        case kEsquerdaBaixo:
            mvDireitaCima(tabuleiro, linha, coluna);
            break;
        case kEsquerdaCima:
            mvDireitaBaixo(tabuleiro, linha, coluna);
            break;
        case kCimaEsquerda:
            mvBaixoDireita(tabuleiro, linha, coluna);
            break;
    }

    hist[*nMov] = -1;
    (*nMov)--;
    return;
}


/**
 * @brief as proximas funcoes (iniciadas em c e seguidas por um movimento)
 * checam se e possivel realizar o movimento indicado em seu nome
 * 
 * @param tabuleiro e o tabuleiro no qual o movimento vai ser feito
 * @param linha a linha atual
 * @param coluna a coluna atual
 * @return 1 se o movimento for possivel, 0 se nao
 */

int cCimaDireita(short int tabuleiro[][8], short int* linha, short int* coluna) { 
    // movimento 1

    if (tabuleiro[*linha - 2][*coluna + 1] != 0)
        return 0;

    if (*linha - 2 < 0)
        return 0;

    if (*coluna + 1 > 7)
        return 0;
    
    return 1;
}

int cDireitaCima(short int tabuleiro[][8], short int* linha, short int* coluna) { 
    // movimento 2

    if (tabuleiro[*linha - 1][*coluna + 2] != 0)
        return 0;

    if (*linha - 1 < 0)
        return 0;

    if (*coluna + 2 > 7)
        return 0;

    return 1;    
}

int cDireitaBaixo(short int tabuleiro[][8], short int* linha, short int* coluna) { 
    // movimento 3

    if (tabuleiro[*linha + 1][*coluna + 2] != 0)
        return 0;

    if (*linha + 1 > 7)
        return 0;

    if (*coluna + 2 > 7)
        return 0;

    return 1;   
}

int cBaixoDireita(short int tabuleiro[][8], short int* linha, short int* coluna) { 
    // movimento 4

    if (tabuleiro[*linha + 2][*coluna + 1] != 0)
        return 0;

    if (*linha + 2 > 7)
        return 0;

    if (*coluna + 1 > 7)
        return 0;

    return 1;   
}

int cBaixoEsquerda(short int tabuleiro[][8], short int* linha, short int* coluna) { 
    // movimento 5

    if (tabuleiro[*linha + 2][*coluna - 1] != 0)
        return 0;

    if (*linha + 2 > 7)
        return 0;

    if (*coluna - 1 < 0)
        return 0;

    return 1;   
}

int cEsquerdaBaixo(short int tabuleiro[][8], short int* linha, short int* coluna) { 
    // movimento 6

    if (tabuleiro[*linha + 1][*coluna - 2] != 0)
        return 0;

    if (*linha + 1 > 7)
        return 0;

    if (*coluna - 2 < 0)
        return 0;

    return 1;   
}

int cEsquerdaCima(short int tabuleiro[][8], short int* linha, short int* coluna) { 
    // movimento 7

    if (tabuleiro[*linha - 1][*coluna - 2] != 0)
        return 0;

    if (*linha - 1 < 0)
        return 0;

    if (*coluna - 2 < 0)
        return 0;

    return 1; 
}

int cCimaEsquerda(short int tabuleiro[][8], short int* linha, short int* coluna) { 
    // movimento 8

    if (tabuleiro[*linha - 2][*coluna - 1] != 0)
        return 0;

    if (*linha - 2 < 0)
        return 0;

    if (*coluna - 1 < 0)
        return 0;

    return 1;
}

void mvCimaDireita(short int tabuleiro[][8], short int* linha, short int *coluna) {
    *linha -= 2;
    *coluna += 1;
}

void mvDireitaCima(short int tabuleiro [][8], short int* linha, short int *coluna) {
    *linha -= 1;
    *coluna += 2;
}

void mvDireitaBaixo(short int tabuleiro [][8], short int* linha, short int *coluna) {
    *linha += 1;
    *coluna += 2;
}

void mvBaixoDireita(short int tabuleiro [][8], short int* linha, short int *coluna) {
    *linha += 2;
    *coluna += 1;
}

void mvBaixoEsquerda(short int tabuleiro [][8], short int* linha, short int *coluna) {
    *linha += 2;
    *coluna -= 1;
}

void mvEsquerdaBaixo(short int tabuleiro [][8], short int* linha, short int *coluna) {
    *linha += 1;
    *coluna -= 2;
}

void mvEsquerdaCima(short int tabuleiro [][8], short int* linha, short int *coluna) {
    *linha -= 1;
    *coluna -= 2;
}

void mvCimaEsquerda(short int tabuleiro [][8], short int* linha, short int *coluna) {
    *linha -= 2;
    *coluna -= 1;
}
