#ifndef __SA_H__
#define __SA_H__

#define N 32
#define LEFT_SHIFT 5 		// logN

#define BUF_SIZE 32 * 1024
#define DTYPE float

#define ACTIVE true
#define NO_ACTIVE false

void load_weight_from_buffer(DTYPE buf_weight[BUF_SIZE], DTYPE A[N][N], int kernel_size, int kernel_num, int buf_start);

void load_matrix_from_buffer(DTYPE buf_weight[BUF_SIZE], DTYPE buf_feature[BUF_SIZE],
		int A_start, int B_start, DTYPE A[N][N], DTYPE B[N][N]);

void write_back_to_result_buffer(DTYPE C[N][N], DTYPE buf_result[BUF_SIZE], int buf_start_addr);

void matrix_mult(int A[N][N], int B[N][N], int C[N][N], bool relu);

void max_2x2_pooling(DTYPE feature_in[N][N], DTYPE feature_out[N/2][N/2]);


#endif
