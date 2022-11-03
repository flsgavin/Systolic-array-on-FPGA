#include "sa.h"
#include "instr.h"

struct Pos{
	int x;
	int y;
	Pos(int i, int j){
		x = i; y = j;
	}
	Pos(){
		x = -1; y = -1;
	}
};


Pos** generate_map(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int out_h, int out_w);

void get_map_size(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int& out_h, int& out_w);

void im2col(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int out_h,
		int out_w, Pos** map, DTYPE buf_result[BUF_SIZE], int read_addr, int write_addr);


