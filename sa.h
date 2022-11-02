#ifndef __SA_H__
#define __SA_H__

#define N 64
#define LEFT_SHIFT 6 		// logN

#define BUF_SIZE 32 * 1024
#define DTYPE int

#define ACTIVE true
#define NO_ACTIVE false

void matrix_mult(int A[N][N], int B[N][N], int C[N][N], bool relu);

void max_2x2_pooling(DTYPE feature_in[N][N], DTYPE feature_out[N/2][N/2]);


#endif
