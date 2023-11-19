#include <stdio.h>
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

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            matriz_resultado[i][j] = 0;
            for(int k = 0; k < N; k++){
                matriz_resultado[i][j] += matriz_a[i][k] * matriz_b[k][j];
            }
        }
    }

    libera_matriz(N, matriz_a);
    libera_matriz(N, matriz_b);
    libera_matriz(N, matriz_resultado);
}
