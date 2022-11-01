//#include "instr.h"
#include "sa.h"
#include "ap_int.h"

#define ITYPE ap_uint<32>
#define I_BUF_SIZE 8 * 1024


// operation code
#define OP_LOAD_WEI		0
#define OP_LOAD_IMG 	1
#define OP_SAVE_BACK	2
#define OP_MAX_POOL		3
#define OP_MTX_MUL		4


void load_instr(ITYPE *ddr_instr, ITYPE i_buf[I_BUF_SIZE], int instr_len, int offset);
void load_weight(DTYPE *ddr, DTYPE buf[BUF_SIZE], int offset, int len);
void dsa(DTYPE *ddr, ITYPE *ddr_instr, int instr_len);
void run(DTYPE *ddr, ITYPE i_buf[I_BUF_SIZE], DTYPE buf[BUF_SIZE], int instr_len);


void load_instr(ITYPE *ddr_instr, ITYPE i_buf[I_BUF_SIZE], int instr_len, int offset){
	if(instr_len >= I_BUF_SIZE){
		return;
	}
	for(int i = 0; i < instr_len; i++){
		i_buf[i + offset] = ddr_instr[i];
	}
}

void load_weight(DTYPE *ddr, DTYPE buf[BUF_SIZE], int offset, int len){

}

void dsa(DTYPE *ddr, ITYPE *ddr_instr, int instr_len){
#pragma HLS INTERFACE m_axi depth=16384 port=ddr
#pragma HLS INTERFACE m_axi depth=3300 port=ddr_instr
	int offset = 0;
	static ITYPE i_buf[I_BUF_SIZE];
	static DTYPE buf[BUF_SIZE];
	while(offset < instr_len && instr_len > 0){
		int len = 0;
		if(instr_len >= I_BUF_SIZE){
			len = I_BUF_SIZE;
		}else{
			len = instr_len;
		}
		instr_len -= len;
		load_instr(ddr_instr, i_buf, len, offset);
		offset += len;
		run(ddr, i_buf, buf, len);
	}


}

void run(DTYPE *ddr, ITYPE i_buf[I_BUF_SIZE], DTYPE buf[BUF_SIZE], int instr_len){
	for(int i = 0; i < instr_len; i++){
		// fetch
		ITYPE instruction = i_buf[i];
//		switch(instruction(31, 29)){
//		case(0):
////			int offset = instruction(28, 13);
////			int len = instruction(12, 0);
////			load_weight(ddr, buf, offset, len);
//			break;
//		case(1):
//			break;
//		case(2):
//			break;
//		case(3):
//			break;
//		case(4):
//			break;
//		default:
//			return;
//		}


		// decode

		// execute
	}



}
