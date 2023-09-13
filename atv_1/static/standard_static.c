#include "utils_static.c"
#define SEED 132

int main (int argc, char* argv[]){
    int N = 15;

    int matriz_a[N][N];
    gera_matriz(N, matriz_a);

    int matriz_b[N][N];
    gera_matriz(N, matriz_b);

    int matriz_resultado[N][N];

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            matriz_resultado[i][j] = 0;
            for(int k = 0; k < N; k++){
                matriz_resultado[i][j] += matriz_a[i][k] * matriz_b[k][j];
            }
        }
    }

}