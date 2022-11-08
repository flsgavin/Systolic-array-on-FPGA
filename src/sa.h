#ifndef __SA_H__
#define __SA_H__

#define N 32
#define LEFT_SHIFT 5 		// logN

#define BUF_SIZE 64 * 1024
#define DTYPE float

#define ACTIVE true
#define NO_ACTIVE false

void load_feature_from_buffer(DTYPE buf_feature[BUF_SIZE], DTYPE B[N][N], int w, int h, int buf_start, int converted_w);

void load_weight_from_buffer(DTYPE buf_weight[BUF_SIZE], DTYPE A[N][N], int kernel_size, int kernel_num, int buf_start, int converted_w);

void load_matrix_from_buffer(DTYPE buf_weight[BUF_SIZE], DTYPE buf_feature[BUF_SIZE], int A_start, int B_start, DTYPE A[N][N], DTYPE B[N][N]);

void write_back_to_result_buffer(DTYPE C[N][N], DTYPE buf_result[BUF_SIZE], int buf_start_addr, int w, int h, int result_total_w);

void matrix_mult(DTYPE A[N][N], DTYPE B[N][N], DTYPE C[N][N], bool relu);

//void max_2x2_pooling(DTYPE feature_in[N][N], DTYPE feature_out[N/2][N/2]);

void max_2x2_pooling(DTYPE buf_feature[BUF_SIZE], int converted_feature_w, int feature_c, bool relu);

void reset_C(DTYPE C[N][N]);

#endif
