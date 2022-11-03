#include "im2col.h"

Pos** generate_map(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int out_h, int out_w){
	int Wi = feature_w;
	int Hi = feature_h;
	int s = stride;
	int K = kernel_size;
	Pos** out = new Pos*[out_h];
	for(int i = 0; i < out_h; i++){
		out[i] = new Pos[out_w];
	}
	for(int i = 0; i < out_h; i++){
		for(int j = 0; j < out_w; j++){
			int num_C = i / (((Wi - K) / s + 1) * ((Hi - K) / s + 1)); // 第几个特征图
			int num_k = i % (((Wi - K) / s + 1) * ((Hi - K) / s + 1)); // 第几个卷积核
			int zs = num_k / ((Wi - K) / s + 1) * Wi + num_k % ((Wi - K) / s + 1) ;
			int add = j / K;
			out[i][j] = Pos(num_C, zs + add * Wi + j % K);
		}
	}
	return out;
}

void get_map_size(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int& out_h, int& out_w){
	out_h = feature_c*((feature_w - kernel_size) / stride + 1) * ((feature_h - kernel_size) / stride + 1);			//C*((Wi-K)/s+1)*((Hi-K)/s+1);
	out_w = kernel_size * kernel_size;
}


void im2col(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int out_h,
		int out_w, Pos** map, DTYPE buf_result[BUF_SIZE], int read_addr, int write_addr){
	for(int i = 0; i < out_h; i++){
		for(int j = 0; j < out_w; j++){
			int ii = map[i][j].x;
			int jj = map[i][j].y;
			buf_result[write_addr + i * out_w + j] = buf_result[read_addr + ii * feature_w * feature_h + jj];
		}
	}
}
