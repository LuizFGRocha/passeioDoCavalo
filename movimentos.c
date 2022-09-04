#include "movimentos.h"

/*

as funcoes retornam 1 se o movimento for realizado com sucesso e 0 se o
movimento nao for possivel, seja porque a casa esta fora do tabuleiro, seja
porque a casa ja foi utilizada anteriormente

as funcoes, na ordem em que estao dispostas, serao referidas de 1 a 8

*/

int cimaDireita(int tabuleiro[][8], int* m, int* n, int* nMovs){ // movimento 1

    if (tabuleiro[*m][*n] != 0)
        return 0;

    if (*n - 2 < 0)
        return 0;

    if (*m + 1 > 7)
        return 0;

    return 1;   

}

int direitaCima(int tabuleiro[][8], int* m, int* n, int* nMovs){ // movimento 2

    if (tabuleiro[*m][*n] != 0)
        return 0;

    if (*n - 1 < 0)
        return 0;

    if (*m + 2 > 7)
        return 0;

    return 1;   
    
}

int direitaBaixo(int tabuleiro[][8], int* m, int* n, int* nMovs){ // movimento 3

    if (tabuleiro[*m][*n] != 0)
        return 0;

    if (*n + 1 > 7)
        return 0;

    if (*m + 2 > 7)
        return 0;

    return 1;   
    
}

int baixoDireita(int tabuleiro[][8], int* m, int* n, int* nMovs){ // movimento 4

    if (tabuleiro[*m][*n] != 0)
        return 0;

    if (*n + 2 > 7)
        return 0;

    if (*m + 1 > 7)
        return 0;

    return 1;   
    
}

int baixoEsquerda(int tabuleiro[][8], int* m, int* n, int* nMovs){ // movimento 5

    if (tabuleiro[*m][*n] != 0)
        return 0;

    if (*n + 2 > 7)
        return 0;

    if (*m - 1 < 7)
        return 0;

    return 1;   
    
}

int esquerdaBaixo(int tabuleiro[][8], int* m, int* n, int* nMovs){ // movimento 6

    if (tabuleiro[*m][*n] != 0)
        return 0;

    if (*n + 1 > 7)
        return 0;

    if (*m - 2 < 0)
        return 0;

    return 1;   
    
}

int esquerdaCima(int tabuleiro[][8], int* m, int* n, int* nMovs){ // movimento 7

    if (tabuleiro[*m][*n] != 0)
        return 0;

    if (*n - 1 < 0)
        return 0;

    if (*m - 2 < 0)
        return 0;

    return 1;   
    
}

int cimaEsquerda(int tabuleiro[][8], int* m, int* n, int* nMovs){ // movimento 8

    if (tabuleiro[*m][*n] != 0)
        return 0;

    if (*n - 2 < 0)
        return 0;

    if (*m - 1 < 0)
        return 0;

    return 1;   
    
}
