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
	DTYPE A[N][N];
	DTYPE B[N][N];
	static DTYPE C[N][N];

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



	int kernel_size = 5;
	int kernel_num = 10;
	load_weight(ddr, buf_weight, 0, kernel_size * kernel_size * kernel_num);

	load_weight_from_buffer(buf_weight, A, kernel_size * kernel_size, kernel_num, 0, kernel_size * kernel_size * 1);

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


	int buf_start_addr = 0;
	for(int buf_offset = 0; buf_offset < 24 * 24; buf_offset += N){
		int w = -1;
		if(24 * 24 - buf_offset >= 32){
			w = 32;
		}else{
			w = 24 * 24 - buf_offset;
		}
		load_feature_from_buffer(buf_feature, B, w, 25, buf_offset, 24 * 24);
		matrix_mult(A, B, C, false);
		write_back_to_result_buffer(C, buf_result, buf_start_addr, w, 10, 24 * 24);
		reset_C(C);
		buf_start_addr += w;
	}

//	for(int i = 0; i < 10; i++){
//		for(int j = 0; j < 24 * 24; j++){
//			printf("%f ", buf_result[i * 24 * 24 + j]);
//		}
//		printf("\n");
//	}



//	for(int i = 0; i < 32 * 32 * 3; i++){
//		buf_result[i] = i + 1;
//	}
	int out_h = -1;
	int out_w = -1;
	int feature_h = 24;
	int feature_w = 24;
	int feature_c = 10;
	kernel_size = 2;
	int stride = 2;
	get_map_size(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w);

	assert(out_h != -1 && out_w != -1);

	generate_map(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w, buf_map);


	im2col(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w, buf_map, buf_result, 0, 1024 * 16);



//	for(int i = 0; i < out_h; i++){
//		for(int j = 0; j < out_w; j++){
//			printf("%f ", buf_result[1024 * 16 + i * out_w + j]);
//		}
//		printf("\n");
//	}

	//copy result to feature


	for(int i = 0; i < out_h * out_w; i++){
		buf_feature[i] = buf_result[1024 * 16 + i];
	}


	// max pooling relu

	max_2x2_pooling(buf_feature, out_w, feature_c, true);

//
//	printf("\n\n\n=====================%d================================\n\n\n", out_w);
//	for(int k = 0; k < 10; k++){
//		for(int i = 0; i < 144; i++){
//			printf("%f ", buf_feature[k * 144 + i]);
//			if((i + 1)% 12 == 0){
//				printf("\n");
//			}
//		}
//		printf("\n\n\n");
//	}

	// conv2d

	feature_h = 12;
	feature_w = 12;
	feature_c = 10;
	kernel_size = 5;
	stride = 1;

	get_map_size(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w);
	generate_map(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w, buf_map);

	for(int i = 0; i < 10 * 12 * 12; i++){
		buf_result[i] = buf_feature[i];
	}

	im2col(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w, buf_map, buf_result, 0, 1024 * 16);

//	printf("%d  %d \n", out_h, out_w);

	//TODO : new function
	for(int i = 0; i < out_h * out_w; i++){
		buf_feature[i] = buf_result[i + 1024 * 16];
	}

	FILE *fid2;
	fid2 = fopen("layer_2_weights.bin", "rb");
	fread(ddr, sizeof(DTYPE), 5 * 5 * 10 * 20, fid2);

	kernel_size = 5;
	kernel_num = 20;
	load_weight(ddr, buf_weight, 0, kernel_size * kernel_size * feature_c * kernel_num);

//	for(int index = 0; index < kernel_size * kernel_size * feature_c; index += N){
//		int buf_start = index;
//		load_weight_from_buffer(buf_weight, A, kernel_size, kernel_num, buf_start, kernel_size * kernel_size * feature_c);
//		load_feature_from_buffer(buf_feature, B, N, N, buf_start, 8 * 8);
//	}



	reset_C(C);
	buf_start_addr = 0;
	for(int j = 0; j < out_w; j += N){
		for(int index = 0; index < kernel_size * kernel_size * feature_c; index += N){
			int weight_w;
			if(kernel_size * kernel_size * feature_c - index > N)
				weight_w = N;
			else
				weight_w = kernel_size * kernel_size * feature_c - index;
			load_weight_from_buffer(buf_weight, A, weight_w, kernel_num, index, kernel_size * kernel_size * feature_c);
			int feature_addr = index * 8 * 8 + j;
			int feature_h = weight_w;
			load_feature_from_buffer(buf_feature, B, N, feature_h, feature_addr, 8 * 8);
			matrix_mult(A, B, C, false);
		}
//		printf("%d\n", j);
		write_back_to_result_buffer(C, buf_result, buf_start_addr + j, N, N, 8 * 8);
		reset_C(C);
	}

//	for(int i = 0; i < 20; i++){
//		for(int j = 0; j < 64; j++){
//			printf("%f ", buf_result[i * 64 + j]);
//		}
//		printf("\n");
//	}

	// 2x2 max pooling relu
	feature_h = 8;
	feature_w = 8;
	feature_c = 20;
	kernel_size = 2;
	stride = 2;

	get_map_size(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w);
	generate_map(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w, buf_map);
	im2col(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w, buf_map, buf_result, 0, 1024 * 16);

	for(int i = 0; i < out_h * out_w; i++){
		buf_feature[i] = buf_result[1024 * 16 + i];
	}
	max_2x2_pooling(buf_feature, out_w, feature_c, true);

//	for(int i = 0; i < 20; i++){
//		for(int j = 0; j < 16; j++){
//			printf("%f ", buf_feature[i * 16 + j]);
//			if((j + 1) % 4 == 0) printf("\n");
//		}
//		printf("\n\n\n");
//	}

	FILE *fid_3;
	fid_3 = fopen("layer_3_weights.bin", "rb");
	fread(ddr, sizeof(DTYPE), 10 * 20 * 4 * 4, fid_3);

	index = 0;
	for(int i = 0; i < 10; i++){
		DTYPE temp = 0;
		for(int j = 0; j < 320; j++){
			temp += ddr[i * 320 + j] * buf_feature[j];
		}
		buf_result[i] = temp;
	}

	FILE *fid_4;
	fid_4 = fopen("layer_4_weights.bin", "rb");
	fread(ddr, sizeof(DTYPE), 10, fid_4);
	DTYPE maxNum = buf_result[0];
	int res_num = 0;
	for(int i = 0; i < 10; i++){
		buf_result[i] += ddr[i];
		printf("%f ", buf_result[i]);
		if(maxNum < buf_result[i]){
			maxNum = buf_result[i];
			res_num = i;
		}
	}
	printf("\n");

	printf("=================================================\n");
	printf("=================================================\n");
	printf("==                                             ==\n");
	printf("==                                             ==\n");
	printf("==                                             ==\n");
	printf("==                                             ==\n");
	printf("==                    %d                        ==\n", res_num);
	printf("==                                             ==\n");
	printf("==                                             ==\n");
	printf("==                                             ==\n");
	printf("==                                             ==\n");
	printf("=================================================\n");
	printf("=================================================\n");




}
