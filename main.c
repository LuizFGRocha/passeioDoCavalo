#include "passeio.h"
#include <time.h>

int main() {
    int linha, coluna;
    clock_t comeco = clock();
    fazerPasseio(8, 8);
    clock_t final = clock();
    printf("%lf\n", (double) (final - comeco) / CLOCKS_PER_SEC);
    return 0;
}
