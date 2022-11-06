#include "sa.h"
#include <stdio.h>

void load_matrix_from_buffer(DTYPE buf_weight[BUF_SIZE], DTYPE buf_feature[BUF_SIZE], int A_start, int B_start, DTYPE A[N][N], DTYPE B[N][N]){

#pragma HLS ARRAY_RESHAPE variable = A complete dim = 2
#pragma HLS ARRAY_RESHAPE variable = B complete dim = 2

	for(int i = 0; i < N; i++){
#pragma HLS PIPELINE II = 1
		for(int j = 0; j < N; j++){
			int offset = (i << LEFT_SHIFT) + j;
			A[i][j] = buf_weight[A_start + offset];
			B[i][j] = buf_feature[B_start + offset];
		}
	}
}

void load_feature_from_buffer(DTYPE buf_feature[BUF_SIZE], DTYPE B[N][N], int w, int h, int buf_start, int converted_w){
#pragma HLS ARRAY_RESHAPE variable = B complete dim = 2
	if(w > N || h > N)
		return;
	int index = buf_start;
	for(int i = 0; i < h; i++){
#pragma HLS PIPELINE II = 1
		for(int j = 0; j < N; j++){
			if(j < w)
				B[i][j] = buf_feature[index];
			else
				B[i][j] = 0;
			index++;
			if(j == N - 1){
				index = index - N + converted_w;
			}
		}
	}
	for(int i = h; i < N; i++){
#pragma HLS PIPELINE II = 1
		for(int j = 0; j < N; j++){
			B[i][j] = 0;
		}
	}
}

void load_weight_from_buffer(DTYPE buf_weight[BUF_SIZE], DTYPE A[N][N], int kernel_size, int kernel_num, int buf_start){
#pragma HLS ARRAY_RESHAPE variable = A complete dim = 2
	int kk = kernel_size * kernel_size;
	if(kk > N || kernel_num > N)
		return;
	int index = buf_start;
	for(int i = 0; i < kernel_num; i++){
#pragma HLS PIPELINE II = 1
		for(int j = 0; j < N; j++){
			if(j < kk)
				A[i][j] = buf_weight[index++];
			else
				A[i][j] = 0;
		}
	}
	for(int i = kernel_num; i < N; i++){
#pragma HLS PIPELINE II = 1
		for(int j = 0; j < N; j++){
			A[i][j] = 0;
		}
	}
}



/*
 * @parameter
 * 		buf_start_addr 特征图首行偏移地址
 *
 *
 */
void write_back_to_result_buffer(DTYPE C[N][N], DTYPE buf_result[BUF_SIZE], int buf_start_addr, int w, int h, int result_total_w){
#pragma HLS ARRAY_RESHAPE variable = C complete dim = 2
	if(w > N || h > N)
		return;
	if(buf_start_addr + (N << LEFT_SHIFT) >= BUF_SIZE)  // buf_start_addr + N * N >= BUF_SIZE
		return;
	int index = buf_start_addr;
	for(int i = 0; i < h; i++){
#pragma HLS PIPELINE II = 1
		for(int j = 0; j < w; j++){
			buf_result[index] = C[i][j];
			index++;
			if(j == w - 1){
				index = index + result_total_w - w;
			}
		}
	}
}

void matrix_mult(DTYPE A[N][N], DTYPE B[N][N], DTYPE C[N][N], bool relu){
#pragma HLS ARRAY_RESHAPE variable = A complete dim = 2
#pragma HLS ARRAY_RESHAPE variable = B complete dim = 1

	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
#pragma HLS PIPELINE II = 1
			DTYPE temp = 0.0;
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


