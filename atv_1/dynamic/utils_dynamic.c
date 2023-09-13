#include <stdio.h>
#include <stdlib.h>
#define SEED 132

int **aloca_matriz(int N){
	int **matriz = (int **) malloc(sizeof(int *) * N);
    
	for(int i = 0; i < N; i++){
        matriz[i] = (int *) malloc(sizeof(int) * N);
    }
	return matriz;
}

void gera_matriz(int N, int **matriz){

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            matriz[i][j]=rand()%11;
        }
    }
	return;
}
void print_vec(int N, int *vec){
	for(int i = 0; i < N; i++){
		printf("%d ", vec[i]);
	}
	printf("\n");
	return;
}

// Função auxiliar que imprime uma matriz de inteiros dado seu tamanho
void print_mat(int N, int **mat){
	for(int i = 0; i < N; i++){
		print_vec(N, mat[i]);
	}
	printf("\n");
	return;
}