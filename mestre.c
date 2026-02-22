#include <stdio.h>

#define LINHAS 10
#define COLUNAS 10
#define TAM_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5  // Valor para marcar área de efeito

// Função para imprimir o tabuleiro
void imprimir_tabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    printf("    ");
    for (int c = 0; c < COLUNAS; c++) {
        printf("%c ", 'A' + c);
    }
    printf("\n");
    for (int l = 0; l < LINHAS; l++) {
        printf("%2d  ", l);
        for (int c = 0; c < COLUNAS; c++) {
            printf("%d ", tabuleiro[l][c]);
        }
        printf("\n");
    }
}

// Função para posicionar navio horizontal
void posicionar_horizontal(int tabuleiro[LINHAS][COLUNAS], int linha, int coluna_inicial) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha][coluna_inicial + i] = NAVIO;
    }
}

// Função para posicionar navio vertical
void posicionar_vertical(int tabuleiro[LINHAS][COLUNAS], int linha_inicial, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha_inicial + i][coluna] = NAVIO;
    }
}

// Função para posicionar navio diagonal descendente
void posicionar_diagonal_desc(int tabuleiro[LINHAS][COLUNAS], int linha_inicial, int coluna_inicial) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha_inicial + i][coluna_inicial + i] = NAVIO;
    }
}

// Função para posicionar navio diagonal ascendente
void posicionar_diagonal_asc(int tabuleiro[LINHAS][COLUNAS], int linha_inicial, int coluna_inicial) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha_inicial - i][coluna_inicial + i] = NAVIO;
    }
}

// Função para aplicar habilidade (área de efeito) no tabuleiro
// matriz_habilidade: matriz quadrada (valores 0 ou 1)
// tamanho: tamanho da matriz (ex: 5x5)
// linha_origem e coluna_origem: ponto central da habilidade no tabuleiro
void aplicar_habilidade(int tabuleiro[LINHAS][COLUNAS], int matriz_habilidade[][7], int tamanho, int linha_origem, int coluna_origem) {
    int centro = tamanho / 2;  // Ponto central da matriz
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (matriz_habilidade[i][j] == 1) {
                int l = linha_origem - centro + i;
                int c = coluna_origem - centro + j;
                // Verifica se a posição está dentro do tabuleiro
                if (l >= 0 && l < LINHAS && c >= 0 && c < COLUNAS) {
                    // Marca como área de habilidade, mas não sobrescreve navio
                    if (tabuleiro[l][c] == AGUA) {
                        tabuleiro[l][c] = HABILIDADE;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[LINHAS][COLUNAS] = {AGUA};

    // --- Posicionamento dos navios ---
    posicionar_horizontal(tabuleiro, 1, 2);   // horizontal
    posicionar_vertical(tabuleiro, 5, 0);     // vertical
    posicionar_diagonal_desc(tabuleiro, 0, 6); // diagonal descendente
    posicionar_diagonal_asc(tabuleiro, 7, 2);  // diagonal ascendente

    // --- Matrizes de habilidades ---
    // Habilidade Cone (5x5)
    int cone[5][7] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };

    // Habilidade Cruz (5x5)
    int cruz[5][7] = {
        {0,0,1,0,0},
        {0,0,1,0,0},
        {1,1,1,1,1},
        {0,0,1,0,0},
        {0,0,1,0,0}
    };

    // Habilidade Octaedro (5x5)
    int octaedro[5][7] = {
        {0,0,1,0,0},
        {0,1,1,1,0},
        {1,1,1,1,1},
        {0,1,1,1,0},
        {0,0,1,0,0}
    };

    // --- Aplicar habilidades ---
    aplicar_habilidade(tabuleiro, cone, 5, 2, 3);     // Cone com origem na linha 2, coluna 3
    aplicar_habilidade(tabuleiro, cruz, 5, 5, 5);     // Cruz com origem na linha 5, coluna 5
    aplicar_habilidade(tabuleiro, octaedro, 5, 7, 7); // Octaedro com origem na linha 7, coluna 7

    // --- Exibir tabuleiro final ---
    imprimir_tabuleiro(tabuleiro);

    printf("\nNavios e habilidades aplicados com sucesso!\n");

    return 0;
}