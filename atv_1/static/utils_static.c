#include <stdio.h>
#include <stdlib.h>
#define SEED 132

void gera_matriz(int N, int matriz[N][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            matriz[i][j]=rand()%11;
        }
    }
}
void print_vec(int N, int vec[N]){
	for(int i = 0; i < N; i++){
		printf("%d ", vec[i]);
	}
	printf("\n");
}

// Função auxiliar que imprime uma matriz de inteiros dado seu tamanho
void print_mat(int N, int mat[N][N]){
	for(int i = 0; i < N; i++){
		print_vec(N, mat[i]);
	}
	printf("\n");
}