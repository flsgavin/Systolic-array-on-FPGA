#include "sa.h"
#include <stdio.h>

int main(){
	int A[N][N] = {{1,2,3,4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15,16}};
	int B[N][N] = {{2,2,3,4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15,16}};
	int C[N][N] = {};
	int D[N/2][N/2] = {};
	matrix_mult(A, B, C, true);
	max_2x2_pooling(C, D);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}

	for(int i = 0; i < N / 2; i++){
		for(int j = 0; j < N / 2; j++){
			printf("%d ", D[i][j]);
		}
		printf("\n");
	}
}
