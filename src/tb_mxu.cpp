#include "sa.h"
#include "instr.h"
#include "im2col.h"
#include <stdio.h>

DTYPE C[N][N];


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
	DTYPE A[N][N];
	DTYPE B[N][N];


	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			C[i][j] = 0;
		}
	}

	DTYPE* ddr;
	ITYPE* ddr_instr;

	ddr = (DTYPE *) malloc(sizeof(DTYPE) * (16384));
	ddr_instr = (ITYPE *) malloc(sizeof(ITYPE) * 3300);

	FILE *fid;
	fid = fopen("layer_1_weights.bin", "rb");
	fread(ddr, sizeof(DTYPE), 5 * 5 * 10, fid);
//	for(int i = 0; i < 100; i++){
//		printf("%f ", ddr[i]);
//	}
//	printf("\n");
	static DTYPE buf_feature[BUF_SIZE];
	static DTYPE buf_weight[BUF_SIZE];
	static DTYPE buf_result[BUF_SIZE];
	static MTYPE buf_map[MAP_SIZE];



//	load_feature(ddr, buf_feature, 0, 4096);
//
//
	int kernel_size = 5;
	int kernel_num = 10;
	load_weight(ddr, buf_weight, 0, kernel_size * kernel_size * kernel_num);

	load_weight_from_buffer(buf_weight, A, kernel_size, kernel_num, 0);

//	for(int i = 0; i < N; i++){
//		for(int j = 0; j < N; j++){
//			printf("%f ", A[i][j]);
//		}
//		printf("\n");
//	}
//	for(int c = 0; c < 10; c++){
//		for(int i = 0; i < 5; i++){
//			for(int j = 0; j < 5; j++){
//				printf("%f ", buf_weight[c * 5 * 5 + i * 5 + j]);
//			}
//			printf("\n");
//		}
//		printf("+++++++++++++++++++++++++++++++\n");
//	}
	FILE *fid_img;
	fid_img = fopen("img.bin", "rb");

	DTYPE* ddr_img = (DTYPE *) malloc(sizeof(DTYPE) * (1024));
	fread(ddr_img, sizeof(DTYPE), 1024, fid_img);
	int index = 0;
	for(int i = 0; i < 24; i++){
		for(int j = 0; j < 24; j++){
			int offset = i * 28 + j;
			for(int k = 0; k < 5; k++){
				for(int r = 0; r < 5; r++){
					buf_feature[index] = ddr_img[offset + k * 28 + r];
					index += 576;
					if(k == 4 && r == 4){
						index -= 576 * 25;
						index++;
					}
				}

			}
		}
	}

//	for(int j = 0; j < 24 * 24; j++){
//		for(int i = 0; i < 25; i++){
//			printf("%f ", buf_feature[i * 25 + j]);
//		}
//		printf("\n");
//	}

//	for(int i = 0; i < 28; i++){
//		for(int j = 0; j < 28; j++){
//			printf("%f ", ddr_img[i * 28 + j]);
//		}
//		printf("\n");
//	}
//	load_feature(ddr_img, buf_feature, 0, 28 * 28);

	for(int buf_offset = 0; buf_offset < 24 * 24; buf_offset += N){
		int w = -1;
		if(24 * 24 - buf_offset >= 32){
			w = 32;
		}else{
			w = 24 * 24 - buf_offset;
		}
		load_feature_from_buffer(buf_feature, B, w, 25, buf_offset, 24 * 24);
		matrix_mult(A, B, C, false);
//		for(int i = 0; i < N; i++){
//			for(int j = 0; j < N; j++){
//				printf("%f ", A[i][j]);
//			}
//			printf("\n");
//		}
//		printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
	}


	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			printf("%f ", C[i][j]);
		}
		printf("\n");
	}



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

//	for(int i = 0; i < out_h; i++){
//		for(int j = 0; j < out_w; j++){
//			printf("%f ", buf_result[1024 * 16 + i * out_w + j]);
//		}
//		printf("\n");
//	}


}
