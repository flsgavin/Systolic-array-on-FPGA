#include "im2col.h"

void reset_map(MTYPE buf_map[MAP_SIZE]){
	for(int i = 0; i < MAP_SIZE; i++){
		buf_map[i] = 0;
	}
}

void generate_map(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int out_h, int out_w, MTYPE buf_map[MAP_SIZE]){
	ap_uint<16> Wi = feature_w;
	ap_uint<16> Hi = feature_h;
	ap_uint<16> s = stride;
	ap_uint<16> K = kernel_size;

//	Pos** out = new Pos*[out_h];
//	for(int i = 0; i < out_h; i++){
//		out[i] = new Pos[out_w];
//	}
	for(int i = 0; i < out_h; i++){
		for(int j = 0; j < out_w; j++){
			ap_uint<16> num_C = i / (((Wi - K) / s + 1) * ((Hi - K) / s + 1)); // 第几个特征图
			ap_uint<16> num_k = i % (((Wi - K) / s + 1) * ((Hi - K) / s + 1)); // 第几个卷积核
			ap_uint<16> start = num_k / ((Wi - K) / s + 1) * Wi + num_k % ((Wi - K) / s + 1) ;
			ap_uint<16> offset = j / K;
			//out[i][j] = Pos(num_C, start + offset * Wi + j % K);
			ap_uint<16> y = start + offset * Wi + j % K;
			buf_map[i * out_w + j] = (num_C, y);
		}
	}
}

void get_map_size(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int& out_h, int& out_w){
	out_h = feature_c*((feature_w - kernel_size) / stride + 1) * ((feature_h - kernel_size) / stride + 1);			//C*((Wi-K)/s+1)*((Hi-K)/s+1);
	out_w = kernel_size * kernel_size;
}


void im2col(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int out_h,
		int out_w, MTYPE buf_map[MAP_SIZE], DTYPE buf_result[BUF_SIZE], int read_addr, int write_addr){
	for(int i = 0; i < out_h; i++){
		for(int j = 0; j < out_w; j++){
//			int ii = map[i][j].x;
//			int jj = map[i][j].y;
			ap_uint<16> ii = buf_map[i * out_w + j](31, 16);
			ap_uint<16> jj = buf_map[i * out_w + j](15, 0);
			buf_result[write_addr + i * out_w + j] = buf_result[read_addr + ii * feature_w * feature_h + jj];
		}
	}
}
