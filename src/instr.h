#ifndef __INSTR_H__
#define __INSTR_H__
#include <ap_int.h>
#include "sa.h"
#include "im2col.h"

#define ITYPE ap_uint<64>
#define I_BUF_SIZE 8 * 1024


// operation code
#define OP_LOAD_WEI			0
#define OP_LOAD_FET 		1
#define OP_SAVE_BACK		2
#define OP_MAX_POOL			3
#define OP_MTX_MUL			4
#define OP_LOAD_WEI_MTX		5
#define OP_LOAD_FET_MTX		6
#define OP_SAVE_MTX			7
#define OP_IM2COL			8
#define OP_GEN_MAP			9
#define OP_SET_PARM			10
#define OP_RESET_C			11
#define OP_MOV_RES2FET		12
#define OP_SET_FET_PARM		13
#define OP_SET_WEI_PARM		14


void load_instr(ITYPE *ddr_instr, ITYPE i_buf[I_BUF_SIZE], int instr_len, int offset);
void load_weight(DTYPE *ddr, DTYPE buf_weight[BUF_SIZE], int ddr_offset, int len);
void load_feature(DTYPE *ddr, DTYPE buf_feature[BUF_SIZE], int ddr_offset, int len);
void save_back(DTYPE *ddr, DTYPE buf_result[BUF_SIZE], int ddr_offset, int len);
void dsa(DTYPE *ddr, ITYPE *ddr_instr, int instr_len, int enable);
void run(DTYPE *ddr, ITYPE i_buf[I_BUF_SIZE], DTYPE buf_weight[BUF_SIZE], DTYPE buf_feature[BUF_SIZE],
		DTYPE buf_result[BUF_SIZE], int instr_len, DTYPE A[N][N], DTYPE B[N][N], DTYPE C[N][N]);
void move_result_buf_2_feature_buf(DTYPE buf_result[BUF_SIZE], DTYPE buf_feature[BUF_SIZE], int len, int result_addr, int feature_addr);

#endif
