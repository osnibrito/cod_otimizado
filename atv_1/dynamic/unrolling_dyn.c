#include <stdio.h>
#include <stdlib.h>
#include "utils_dynamic.c"
#define SEED 132

int main (int argc, char* argv[]){
    int N = 15;
	srand(SEED);

    int **matriz_a = aloca_matriz(N);
    int **matriz_b = aloca_matriz(N);
    int **matriz_resultado = aloca_matriz(N);

    gera_matriz(N, matriz_a);
    gera_matriz(N, matriz_b);
    // begin clock
    int i, j, k;
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            matriz_resultado[i][j] = 0;
            for(k = 0; k < N-1; k+=2){
                matriz_resultado[i][j] += matriz_a[i][k] * matriz_b[k][j];
                matriz_resultado[i][j] += matriz_a[i][k+1] * matriz_b[k+1][j];
            }
            if(N % 2 != 0) matriz_resultado[i][j] += matriz_a[i][k] * matriz_b[k][j];
        }
    }
}