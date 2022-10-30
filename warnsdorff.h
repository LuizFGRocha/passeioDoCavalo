/*
#define kCimaDireita 1
#define kDireitaCima 2
#define kDireitaBaixo 3
#define kBaixoDireita 4
#define kBaixoEsquerda 5
#define kEsquerdaBaixo 6
#define kEsquerdaCima 7
#define kCimaEsquerda 8

typedef struct{
    int linha, coluna;
} coordenadas;

typedef struct{
    int valor, proximosPossiveis, maiorTentado;
    coordenadas proxima[8];
    coordenadas posicao;
} casa;



typedef struct {
    int movimento;
    coordenadas posicao;
} proximaCasa;



coordenadas proximo(coordenadas casaAtual, int modo) {
    switch(modo) {
        case kCimaDireita:
            return coordenadas{casaAtual.linha - 2, casaAtual.coluna + 1};
        case kDireitaCima:
            return coordenadas{casaAtual.linha - 1, casaAtual.coluna + 2};
        case kDireitaBaixo:
            return coordenadas{casaAtual.linha + 1, casaAtual.coluna + 2};
        case kBaixoDireita:
            return coordenadas{casaAtual.linha + 2, casaAtual.coluna + 1};
        case kBaixoEsquerda:
            return coordenadas{casaAtual.linha + 2, casaAtual.coluna - 1};
        case kEsquerdaBaixo:
            return coordenadas{casaAtual.linha + 1, casaAtual.coluna - 2};
        case kEsquerdaCima:
            return coordenadas{casaAtual.linha - 1, casaAtual.coluna - 2};
        case kCimaEsquerda:
            return coordenadas{casaAtual.linha - 2, casaAtual.coluna - 1};
        default:
            return coordenadas{0, 0};
    }
}


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

int nMovsPossiveis(coordenadas casa) {
    int i, count = 0;
    for (i = 1; i <= 8; ++i) {
        if (cMovimento(casa, i)) count++;
    }
    return count;
}

// Guardar em um vetor as próximas em ordem de qualidade. Usar um contador para passar por elas em ordem. Esse vetor sempre terá 8 elementos.


    Primeira casa => Vetor de próximas, casa uma com uma direção. O vetor é formado pela ordenação das casas com base em quantas próximas elas
    têm, do menor para o maior.


casa tabuleiro[8][8];

// Definindo a primeira casa.

tabuleiro[0][0].valor = 1;

// Agora, precisamos determinar quais são as próximas casas possíveis.

for (i = 0; i < 8; ++i) {
    tabuleiro[0][0].proxima[i] = proximo(tabuleiro[0][0].posicao, i); 
}

// Então, tendo o vetor de próximas, devemos ordenar seu elementos a partir da quantidade de próximas de cada um.

casa hold;
iter = 7;
int cont = 1;
while(cont){
    cont = 0;
    for(int i = 0; i < iter; i++){
        if(nMovsPossiveis(tabuleiro[0][0].proxima[i]) > nMovsPossiveis(tabuleiro[0][0].proxima[i + 1])){
            hold = tabuleiro[0][0].proxima[i];
            tabuleiro[0][0].proxima[i] = tabuleiro[0][0].proxima[i + 1];
            tabuleiro[0][0].proxima[i + 1] = hold;
            cont++;
        }
    }
    iter--;
}

// Agora que está ordenado, vamos para a primeira casa do vetor.

tabuleiro[tabuleiro[0][0].proxima[i].posicao.linha][tabuleiro[0][0].proxima[i].posicao.coluna].valor = 2;

*/
