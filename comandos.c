#include <stdio.h>
#include "comandos.h"
#include "passeio.c"

void imprimeTabuleiro8x8(casa tabuleiro[][8]){
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 7; ++j) {
            printf("%d ", tabuleiro[i][j].valor);
        }
        printf("%d\n", tabuleiro[i][7].valor);
    }
    return;
}