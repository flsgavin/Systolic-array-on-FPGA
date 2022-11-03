#include "sa.h"
#include "instr.h"
#include "im2col.h"
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
	static DTYPE buf_result[BUF_SIZE];
	static MTYPE buf_map[MAP_SIZE];

	static DTYPE A[N][N], B[N][N], C[N][N];

//	load_feature(ddr, buf_feature, 0, 4096);
//
//
//	load_weight(ddr, buf_weight, 0, 4096);
//
//	load_matrix_from_buffer(buf_weight, buf_feature, 0, 0, A, B);
//	matrix_mult(A, B, C, ACTIVE);
//	for(int i = 0; i < N; i++){
//		for(int j = 0; j < N; j++){
//			printf("%d ", C[i][j]);
//		}
//		printf("\n");
//	}

	for(int i = 0; i < 32 * 32 * 3; i++){
		buf_result[i] = i + 1;
	}
	int out_h = -1;
	int out_w = -1;
	get_map_size(32, 32, 3, 2, 1, out_h, out_w);

	assert(out_h != -1 && out_w != -1);

	generate_map(32, 32, 3, 2, 1, out_h, out_w, buf_map);

//	for(int i = 0; i < )

	im2col(32, 32, 3, 2, 1, out_h, out_w, buf_map, buf_result, 0, 1024 * 16);

	for(int i = 0; i < out_h; i++){
		for(int j = 0; j < out_w; j++){
			printf("%d ", buf_result[1024 * 16 + i * out_w + j]);
		}
		printf("\n");
	}


}
