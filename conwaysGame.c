#include "conwaysGame.h"

int cuentaVecinos(char* matCelulas[], const unsigned short int i, const unsigned short int j, const unsigned short int width, const unsigned short int  height) {
    int f, c, cont = 0;
    for (f = i - 1; f <= i + 1; f++) {
        for (c = j - 1; c <= j + 1; c++) {
            if (f >= 0 && f < width && c >= 0 && c < height) {
                if (!(f == i && c == j)) {
                    if (matCelulas[f][c] == VIVO || matCelulas[f][c] == MURIENDO) {
                        cont++;
                    }
                }
            }
        }
    }
    return cont;
}

void calculaSiguiente(char* matCelulas[], const unsigned short int width, const unsigned short int  height) {
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            int cont = cuentaVecinos(matCelulas, i, j, width, height);
            if (matCelulas[i][j] == MUERTO && cont == 3)
                matCelulas[i][j] = NACIENDO;
            if (matCelulas[i][j] == VIVO && (cont < 2 || cont > 3))
                matCelulas[i][j] = MURIENDO;

        }
    }
    return;
}

void aplicaSiguiente(char* matCelulas[], const unsigned short int width, const unsigned short int  height) {
    int i, j;
    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            if (matCelulas[i][j] == MURIENDO) matCelulas[i][j] = MUERTO;
            if (matCelulas[i][j] == NACIENDO) matCelulas[i][j] = VIVO;
        }
    }
    return;
}

char** crearMatrizBidimensional(const unsigned short int width, const unsigned short int  height, const unsigned short int varSize) {
    char** matriz = malloc(sizeof(void*)*width);
    if(!matriz)
        return NULL;
    for(int i = 0; i < width; i++){
            matriz[i] = malloc(varSize*height);
            if(!matriz[i]){
                while(i >= 0){
                    free(matriz[i]);
                    i--;
                }
                free(matriz);
                return NULL;
            }
    }
    for(int i = 0; i < width; i++)
        for(int j = 0; j < height; j++)
            matriz[i][j] = MUERTO;
    return matriz;
}

void liberarMatriz(char* matCelulas[], const unsigned short int width) {
    for(int i = 0; i < width; i++)
        free(matCelulas[i]);
    free(matCelulas);
}

void cargarOscilador(char* matCelulas[], const unsigned short int i, const unsigned short int j) {
    matCelulas[j-4][i-4] = VIVO;
    matCelulas[j-4][i-3] = VIVO;
    matCelulas[j-4][i-2] = VIVO;
    matCelulas[j-4][i-1] = VIVO;
    matCelulas[j-4][i] = VIVO;
    matCelulas[j-4][i+1] = VIVO;

    matCelulas[j-3][i-4] = VIVO;
    matCelulas[j-3][i-3] = VIVO;
    matCelulas[j-3][i-2] = VIVO;
    matCelulas[j-3][i-1] = VIVO;
    matCelulas[j-3][i] = VIVO;
    matCelulas[j-3][i+1] = VIVO;

    matCelulas[j+4][i+4] = VIVO;
    matCelulas[j+4][i+3] = VIVO;
    matCelulas[j+4][i+2] = VIVO;
    matCelulas[j+4][i+1] = VIVO;
    matCelulas[j+4][i] = VIVO;
    matCelulas[j+4][i-1] = VIVO;

    matCelulas[j+3][i+4] = VIVO;
    matCelulas[j+3][i+3] = VIVO;
    matCelulas[j+3][i+2] = VIVO;
    matCelulas[j+3] [i+1]= VIVO;
    matCelulas[j+3][i] = VIVO;
    matCelulas[j+3][i-1] = VIVO;

    matCelulas[j-1][i-4] = VIVO;
    matCelulas[j][i-4] = VIVO;
    matCelulas[j+1][i-4] = VIVO;
    matCelulas[j+2][i-4] = VIVO;
    matCelulas[j+3][i-4] = VIVO;
    matCelulas[j+4][i-4] = VIVO;

    matCelulas[j-1][i-3] = VIVO;
    matCelulas[j][i-3] = VIVO;
    matCelulas [j+1][i-3] = VIVO;
    matCelulas[j+2][i-3] = VIVO;
    matCelulas[j+3][i-3] = VIVO;
    matCelulas[j+4][i-3] = VIVO;

    matCelulas[j-4][i+4] = VIVO;
    matCelulas[j-3][i+4] = VIVO;
    matCelulas[j-2][i+4] = VIVO;
    matCelulas[j-1][i+4] = VIVO;
    matCelulas[j][i+4] = VIVO;
    matCelulas[j+1][i+4] = VIVO;

    matCelulas[j-4][i+3] = VIVO;
    matCelulas[j-3][i+3] = VIVO;
    matCelulas[j-2][i+3] = VIVO;
    matCelulas[j-1][i+3] = VIVO;
    matCelulas[j][i+3] = VIVO;
    matCelulas[j+1][i+3] = VIVO;
}

void cargarGenShip(char* matCelulas[], const unsigned short int i, const unsigned short int j) {
    matCelulas[i][j+4] = VIVO;
    matCelulas[i+1][j+4] = VIVO;
    matCelulas[i][j+5] = VIVO;
    matCelulas[i+1][j+5] = VIVO;

    matCelulas[i+10][j+4] = VIVO;
    matCelulas[i+10][j+5] = VIVO;
    matCelulas[i+10][j+6] = VIVO;

    matCelulas[i+11][j+3] = VIVO;
    matCelulas[i+11][j+7] = VIVO;

    matCelulas[i+12][j+2] = VIVO;
    matCelulas[i+12][j+8] = VIVO;
    matCelulas[i+13][j+2] = VIVO;
    matCelulas[i+13][j+8] = VIVO;

    matCelulas[i+14][j+5] = VIVO;

    matCelulas[i+15][j+3] = VIVO;
    matCelulas[i+15][j+7] = VIVO;

    matCelulas[i+16][j+4] = VIVO;
    matCelulas[i+16][j+5] = VIVO;
    matCelulas[i+16][j+6] = VIVO;

    matCelulas[i+17][j+5] = VIVO;

    matCelulas[i+20][j+2] = VIVO;
    matCelulas[i+20][j+3] = VIVO;
    matCelulas[i+20][j+4] = VIVO;

    matCelulas[i+21][j+2] = VIVO;
    matCelulas[i+21][j+3] = VIVO;
    matCelulas[i+21][j+4] = VIVO;

    matCelulas[i+22][j+1] = VIVO;
    matCelulas[i+22][j+5] = VIVO;

    matCelulas[i+24][j+0] = VIVO;
    matCelulas[i+24][j+1] = VIVO;
    matCelulas[i+24][j+5] = VIVO;
    matCelulas[i+24][j+6] = VIVO;

    matCelulas[i+34][j+2] = VIVO;
    matCelulas[i+35][j+2] = VIVO;
    matCelulas[i+34][j+3] = VIVO;
    matCelulas[i+34][j+3] = VIVO;
}
