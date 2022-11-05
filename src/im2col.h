#include "sa.h"
#include "instr.h"

#define MAP_SIZE 64 * 1024
#define MTYPE ap_uint<32>

void reset_map(MTYPE buf_map[MAP_SIZE]);

void generate_map(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int out_h, int out_w, MTYPE buf_map[MAP_SIZE]);

void get_map_size(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int& out_h, int& out_w);

void im2col(int feature_h, int feature_w, int feature_c, int kernel_size, int stride, int out_h,
		int out_w, MTYPE buf_map[MAP_SIZE], DTYPE buf_result[BUF_SIZE], int read_addr, int write_addr);


