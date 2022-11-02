#include "sa.h"
#include <stdio.h>

void load_matrix_from_buffer(DTYPE buf_weight[BUF_SIZE], DTYPE buf_feature[BUF_SIZE], int A_start, int B_start, DTYPE A[N][N], DTYPE B[N][N]){

#pragma HLS ARRAY_RESHAPE variable = A complete dim = 2
#pragma HLS ARRAY_RESHAPE variable = B complete dim = 2
printf("HELLO \n");
	for(int i = 0; i < N; i++){
#pragma HLS PIPELINE II = 1
		for(int j = 0; j < N; j++){
			int offset = (i << LEFT_SHIFT) + j;
			printf("%d %d \n", offset, i * N + j);
			A[i][j] = buf_weight[A_start + offset];
			//printf("%d ", A[i][j]);
			B[i][j] = buf_feature[B_start + offset];
		}
		printf("\n");
	}
}

//void write_matrix_to_buffer(DTYPE buf_feature[BUF_SIZE], int C_start, DTYPE C[N][N]){
//#pragma HLS ARRAY_RESHAPE variable = C complete dim = 2
//	for(int i = 0; i < N; i++){
//#pragma HLS PIPELINE II = 1
//		for(int j = 0; j < N; j++){
//			int offset = i << LEFT_SHIFT + j;
//			buf_feature[C_start + offset] = C[i][j];
//		}
//	}
//}

void write_back_to_result_buffer(DTYPE C[N][N], DTYPE buf_result[BUF_SIZE], int buf_start_addr){
#pragma HLS ARRAY_RESHAPE variable = C complete dim = 2
	if(buf_start_addr + (N << LEFT_SHIFT) >= BUF_SIZE)  // buf_start_addr + N * N >= BUF_SIZE
		return;
	for(int i = 0; i < N; i++){
#pragma HLS PIPELINE II = 1
		for(int j = 0; j < N; j++){
			int offset = (i << LEFT_SHIFT) + j;
			buf_result[buf_start_addr + offset] = C[i][j];
		}
	}
}

void matrix_mult(DTYPE A[N][N], DTYPE B[N][N], DTYPE C[N][N], bool relu){
#pragma HLS ARRAY_RESHAPE variable = A complete dim = 2
#pragma HLS ARRAY_RESHAPE variable = B complete dim = 1

	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
#pragma HLS PIPELINE II = 1
			int temp = 0;
			for(int k = 0; k < N; k++){
				temp += A[i][k] * B[k][j];
			}
			if(relu)
				C[i][j] = temp > 0 ? temp : 0;
			else
				C[i][j] = temp;
		}
	}
}

inline DTYPE max(DTYPE a, DTYPE b){
	return a > b ? a : b;
}

void max_2x2_pooling(DTYPE feature_in[N][N], DTYPE feature_out[N/2][N/2]){
#pragma HLS ARRAY_RESHAPE variable = feature_in complete dim = 2
#pragma HLS ARRAY_RESHAPE variable = feature_out complete dim = 2
	for(int i = 0; i < N; i += 2){
#pragma HLS PIPELINE II = 1
		for(int j = 0; j < N; j += 2){
			DTYPE t1 = max(feature_in[i][j], feature_in[i][j + 1]);
			DTYPE t2 = max(feature_in[i + 1][j], feature_in[i + 1][j + 1]);
			feature_out[i / 2][j / 2] = max(t1, t2);
		}
	}
}

void im2col(DTYPE buf_feature[BUF_SIZE], int feature_h, int feature_w, int kernel_size, int read_addr, int write_addr){

}
