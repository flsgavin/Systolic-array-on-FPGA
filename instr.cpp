#include "instr.h"

void load_instr(ITYPE *ddr_instr, ITYPE i_buf[I_BUF_SIZE], int instr_len, int ddr_offset){
	if(instr_len >= I_BUF_SIZE){
		return;
	}
	for(int i = 0; i < instr_len; i++){
		i_buf[i] = ddr_instr[i + ddr_offset];
	}
}

void load_weight(DTYPE *ddr, DTYPE buf_weight[BUF_SIZE], int ddr_offset, int len){
	if(len > BUF_SIZE){
		return;
	}
	for(int i = 0; i < len; i++){
		buf_weight[i] = ddr[i + ddr_offset];
	}
}

void load_feature(DTYPE *ddr, DTYPE buf_feature[BUF_SIZE], int ddr_offset, int len){
	if(len > BUF_SIZE)
		return;
	for(int i = 0; i < len; i++){
		buf_feature[i] = ddr[i + ddr_offset];
	}
}

void save_back(DTYPE *ddr, DTYPE buf_result[BUF_SIZE], int ddr_offset, int len){
	for(int i = 0; i < len; i++){
		ddr[ddr_offset + i] = buf_result[i];
	}
}

void dsa(DTYPE *ddr, ITYPE *ddr_instr, int instr_len){
#pragma HLS INTERFACE m_axi depth=16384 port=ddr
#pragma HLS INTERFACE m_axi depth=3300 port=ddr_instr
	int offset = 0;
	static ITYPE i_buf[I_BUF_SIZE];
	static DTYPE buf_weight[BUF_SIZE];
	static DTYPE buf_feature[BUF_SIZE];
	static DTYPE buf_result[BUF_SIZE];
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
		run(ddr, i_buf, buf_weight, buf_feature, len);
	}


}

void run(DTYPE *ddr, ITYPE i_buf[I_BUF_SIZE], DTYPE buf_weight[BUF_SIZE], DTYPE buf_feature[BUF_SIZE], DTYPE buf_result[BUF_SIZE], int instr_len){
	for(int i = 0; i < instr_len; i++){
		// fetch
		ITYPE instruction = i_buf[i];
		switch(instruction(31, 29)){
		case(OP_LOAD_WEI):{
			int ddr_offset = instruction(28, 13);
			int len = instruction(12, 0);
			load_weight(ddr, buf_weight, ddr_offset, len);
			break;
		}

		case(OP_LOAD_IMG):{
			int ddr_offset = instruction(28, 13);
			int len = instruction(12, 0);
			load_feature(ddr, buf_feature, ddr_offset, len);
			break;
		}
		case(OP_SAVE_BACK):{
			int ddr_offset = instruction(28, 13);
			int len = instruction(12, 0);
			save_back(ddr, buf_result, ddr_offset, len);
			break;
		}
		case(OP_MAX_POOL):{
			break;
		}
		case(OP_MTX_MUL):{
			break;
		}
		default:
			return;
		}


		// decode

		// execute
	}



}
