#ifndef __INSTR_H__
#define __INSTR_H__
#include <ap_int.h>
#include "sa.h"

#define ITYPE ap_uint<32>
#define I_BUF_SIZE 8 * 1024


// operation code
#define OP_LOAD_WEI		0
#define OP_LOAD_IMG 	1
#define OP_SAVE_BACK	2
#define OP_MAX_POOL		3
#define OP_MTX_MUL		4


void load_instr(ITYPE *ddr_instr, ITYPE i_buf[I_BUF_SIZE], int instr_len, int offset);
void load_weight(DTYPE *ddr, DTYPE buf_weight[BUF_SIZE], int ddr_offset, int len);
void load_feature(DTYPE *ddr, DTYPE buf_feature[BUF_SIZE], int ddr_offset, int len);
void save_back(DTYPE *ddr, DTYPE buf_feature[BUF_SIZE], int ddr_offset, int len);
void dsa(DTYPE *ddr, ITYPE *ddr_instr, int instr_len);
void run(DTYPE *ddr, ITYPE i_buf[I_BUF_SIZE], DTYPE buf_weight[BUF_SIZE], DTYPE buf_feature[BUF_SIZE],
		DTYPE buf_result[BUF_SIZE], int instr_len);

#endif
