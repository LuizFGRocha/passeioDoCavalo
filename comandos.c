#include <stdio.h>
#include "comandos.h"

void imprimeMatriz8x8(short int matriz[][8]){
    int i, j;
    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 7; ++j) {
            printf("%d ", matriz[i][j]);
        }
        printf("%d\n", matriz[i][7]);
    }
    return;
}