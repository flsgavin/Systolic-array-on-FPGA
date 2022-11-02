#include "sa.h"
#include "instr.h"
#include <stdio.h>

int main(){
//	int A[N][N] = {{1,2,3,4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15,16}};
//	int B[N][N] = {{2,2,3,4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15,16}};
//	int C[N][N] = {};
//	int D[N/2][N/2] = {};
//	matrix_mult(A, B, C, true);
//	max_2x2_pooling(C, D);
//	for(int i = 0; i < N; i++){
//		for(int j = 0; j < N; j++){
//			printf("%d ", C[i][j]);
//		}
//		printf("\n");
//	}
//
//	for(int i = 0; i < N / 2; i++){
//		for(int j = 0; j < N / 2; j++){
//			printf("%d ", D[i][j]);
//		}
//		printf("\n");
//	}
	DTYPE* ddr;
	ITYPE* ddr_instr;

	ddr = (DTYPE *) malloc(sizeof(DTYPE) * (16384));
	ddr_instr = (ITYPE *) malloc(sizeof(ITYPE) * 3300);

	FILE *fid;
	fid = fopen("feature.dat", "rb");
	fread(ddr, sizeof(DTYPE), 16384, fid);
	static DTYPE buf_feature[BUF_SIZE];
	static DTYPE buf_weight[BUF_SIZE];

	static DTYPE A[N][N], B[N][N], C[N][N];

	load_feature(ddr, buf_feature, 0, 4096);

//	for(int i = 0; i < 4096; i++){
//		printf("%x ", buf_feature[i]);
//	}
//	printf("\n*********************************************\n");
	load_weight(ddr, buf_weight, 0, 4096);
//	for(int i = 0; i < 4096; i++){
//		printf("%x ", buf_weight[i]);
//	}
//	printf("\n*********************************************\n");
	load_matrix_from_buffer(buf_weight, buf_feature, 0, 0, A, B);
	matrix_mult(A, B, C, ACTIVE);
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			printf("%d ", C[i][j]);
		}
		printf("\n");
	}



	//void write_back_to_result_buffer(DTYPE C[N][N], DTYPE buf_result[BUF_SIZE], int buf_start_addr);



}
