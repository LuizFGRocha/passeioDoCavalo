int cMovimento(short int tabuleiro[][8], short int* linha, short int* coluna, short int modo);

void moveFrente(short int tabuleiro[][8], short int* linha, short int* coluna, int modo, int* nMov, long long int* nMovTotal, short int* hist);

void moveTras(short int tabuleiro[][8], short int* linha, short int* coluna, int* nMov, long long int* nMovTotal, long long int* nMovBackTotal, short int* hist);

int cCimaDireita(short int tabuleiro[][8], short int* m, short int* n);

int cDireitaCima(short int tabuleiro[][8], short int* m, short int* n);

int cDireitaBaixo(short int tabuleiro[][8], short int* m, short int* n);

int cBaixoDireita(short int tabuleiro[][8], short int* m, short int* n);

int cBaixoEsquerda(short int tabuleiro[][8], short int* m, short int* n);

int cEsquerdaBaixo(short int tabuleiro[][8], short int* m, short int* n);

int cEsquerdaCima(short int tabuleiro[][8], short int* m, short int* n);

int cCimaEsquerda(short int tabuleiro[][8], short int* m, short int* n);

/**
 * @brief As seguintes funcoes (iniciadas em mv) realizam os movimentos
 * 
 * @param tabuleiro Tabuleiro onde os movimentos serao feitos
 * @param linha Linha atual
 * @param coluna Coluna atual
 */

void mvCimaDireita(short int tabuleiro[][8], short int* linha, short int *coluna);

void mvDireitaCima(short int tabuleiro [][8], short int* linha, short int *coluna);

void mvDireitaBaixo(short int tabuleiro [][8], short int* linha, short int *coluna);

void mvBaixoDireita(short int tabuleiro [][8], short int* linha, short int *coluna);

void mvBaixoEsquerda(short int tabuleiro [][8], short int* linha, short int *coluna);

void mvEsquerdaBaixo(short int tabuleiro [][8], short int* linha, short int *coluna);

void mvEsquerdaCima(short int tabuleiro [][8], short int* linha, short int *coluna);

void mvCimaEsquerda(short int tabuleiro [][8], short int* linha, short int *coluna);