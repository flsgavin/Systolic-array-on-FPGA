#include "instr.h"

ITYPE i_buf[I_BUF_SIZE];
DTYPE buf_weight[BUF_SIZE];
DTYPE buf_feature[BUF_SIZE];
DTYPE buf_result[BUF_SIZE];
MTYPE buf_map[MAP_SIZE];



ap_uint<32> feature_h;
ap_uint<32> feature_w;
ap_uint<32> feature_c;
ap_uint<32> kernel_size;
ap_uint<32> kernel_num;
ap_uint<32> stride;
int out_h;
int out_w;

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
//		printf("%d  %f ", i, buf_weight[i]);
	}
//	printf("\n");
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

void move_result_buf_2_feature_buf(DTYPE buf_result[BUF_SIZE], DTYPE buf_feature[BUF_SIZE], int len, int result_addr, int feature_addr){
	for(int i = 0; i < len; i++){
		buf_feature[feature_addr + i] = buf_result[result_addr + i];
	}
}

void set_weight_parm(int _kernel_size, int _kernel_num, int _stride){
	kernel_size = _kernel_size;
	kernel_num = _kernel_num;
	stride = _stride;
}

void set_feature_parm(int _feature_w, int _feature_h, int _feature_c, int _out_w, int _out_h){
	feature_w = _feature_w;
	feature_h = _feature_h;
	feature_c = _feature_c;
	out_w = _out_w;
	out_h = _out_h;
}

void dsa(DTYPE *ddr, ITYPE *ddr_instr, int instr_len, int enable){
#pragma HLS INTERFACE m_axi depth=16384 	port=ddr
#pragma HLS INTERFACE m_axi depth=3300 		port=ddr_instr
#pragma HLS INTERFACE s_axilite port=instr_len  bundle=CTRL
#pragma HLS INTERFACE s_axilite port=enable  	bundle=CTRL
#pragma HLS INTERFACE s_axilite port=return 	bundle=CTRL

	DTYPE A[N][N];
	DTYPE B[N][N];
	DTYPE C[N][N];

#pragma HLS ARRAY_RESHAPE variable = A complete dim = 2
#pragma HLS ARRAY_RESHAPE variable = B complete dim = 1
//#pragma HLS ARRAY_RESHAPE variable = B complete dim = 2
#pragma HLS ARRAY_RESHAPE variable = C complete dim = 2

	if(!enable) return;
	int offset = 0;

	reset_C(C);
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
		run(ddr, i_buf, buf_weight, buf_feature, buf_result, len, A, B, C);
	}
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 16; j++){
				printf("%f ", buf_result[i * 16 + j]);
				if((j + 1) % 4 == 0) printf("\n");
			}
			printf("\n\n\n");
		}
}

void run(DTYPE *ddr, ITYPE i_buf[I_BUF_SIZE], DTYPE buf_weight[BUF_SIZE], DTYPE buf_feature[BUF_SIZE], DTYPE buf_result[BUF_SIZE], int instr_len, DTYPE A[N][N], DTYPE B[N][N], DTYPE C[N][N]){
	for(int i = 0; i < instr_len; i++){
		// fetch
		ITYPE instruction = i_buf[i];
		switch(instruction(63, 60)){
		case(OP_LOAD_WEI):{
			ap_uint<32> ddr_offset = instruction(59, 36); 		// 24 bit
			ap_uint<32> len 		= instruction(35, 12);		// 24 bit
			load_weight(ddr, buf_weight, ddr_offset, len);
			break;
		}

		case(OP_LOAD_FET):{
			ap_uint<32> ddr_offset = instruction(59, 36);
			ap_uint<32> len 		= instruction(35, 12);
			load_feature(ddr, buf_feature, ddr_offset, len);
			break;
		}
		case(OP_SAVE_BACK):{
			ap_uint<32> ddr_offset = instruction(59, 36);
			ap_uint<32> len 		= instruction(35, 12);
			save_back(ddr, buf_result, ddr_offset, len);
			break;
		}
		case(OP_MAX_POOL):{
			ap_uint<32> relu = instruction(11, 0); // 12 bit
			max_2x2_pooling(buf_feature, buf_result, out_w, feature_c, relu);
			break;
		}
		case(OP_MTX_MUL):{
			matrix_mult(A, B, C);
			break;
		}
		case(OP_LOAD_WEI_MTX):{
			int weight_w  = instruction(59, 48);		// 12 bit
			ap_uint<32> buf_start   = instruction(47, 24);		// 24 bit
			ap_uint<32> converted_w = instruction(23, 0);		// 24 bit
			// kernel_num ��set _wei_parm ����
			load_weight_from_buffer(buf_weight, A, weight_w, kernel_num, buf_start, converted_w);
			break;
		}
		case(OP_LOAD_FET_MTX):{
			ap_uint<32> w  		 = instruction(59, 54);		// 6 bit
			ap_uint<32> h  		 = instruction(53, 48);		// 6 bit
			ap_uint<32> buf_start   = instruction(47, 24);		// 24 bit
			ap_uint<32> converted_w = instruction(23, 0);		// 24 bit
			load_feature_from_buffer(buf_feature, B, w, h, buf_start, converted_w);
			break;
		}
		case(OP_SAVE_MTX):{
			ap_uint<32> w  		    = instruction(59, 54);		// 6 bit
			ap_uint<32> h  		    = instruction(53, 48);		// 6 bit
			ap_uint<32> buf_start      = instruction(47, 24);		// 24 bit
			ap_uint<32> result_total_w = instruction(23, 0);		// 24 bit
			write_back_to_result_buffer(C, buf_result, buf_start, w, h, result_total_w);
			break;
		}
		case(OP_IM2COL):{
			ap_uint<32> read_addr  = instruction(59, 36);	// 24 bit
			ap_uint<32> write_addr = instruction(35, 12);	// 24 bit
			im2col(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w, buf_map, buf_result, read_addr, write_addr);
			break;
		}
		case(OP_GEN_MAP):{
			feature_h 		= instruction(59, 48);		// 12 bit
			feature_w 		= instruction(47, 36);		// 12 bit
			feature_c 		= instruction(35, 24);		// 12 bit
			kernel_size 	= instruction(23, 12); 		// 12 bit
			stride 			= instruction(11, 0);		// 12 bit

			get_map_size(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w);
			generate_map(feature_h, feature_w, feature_c, kernel_size, stride, out_h, out_w, buf_map);
			break;
		}
		case(OP_SET_PARM):{
			kernel_size = instruction(59, 48);		// 12 bit
			break;
		}
		case(OP_RESET_C):{
			reset_C(C);
			break;
		}
		case(OP_MOV_RES2FET):{
			int len 			= instruction(59, 40);
			int result_addr 	= instruction(39, 20);
			int feature_addr 	= instruction(19, 0);
			move_result_buf_2_feature_buf(buf_result, buf_feature, len, result_addr, feature_addr);
			break;
		}
		case(OP_SET_FET_PARM):{
			int _feature_w 	= instruction(59, 48);
			int _feature_h 	= instruction(47, 36);
			int _feature_c 	= instruction(35, 24);
			int _out_w 		= instruction(23, 12);
			int _out_h 		= instruction(11, 0);
			set_feature_parm(_feature_w, _feature_h, _feature_c, _out_w, _out_h);
			break;
		}
		case(OP_SET_WEI_PARM):{
			int _kernel_size = instruction(59, 48);
			int _kernel_num  = instruction(47, 36);
			int _stride 	 = instruction(35, 24);
			set_weight_parm(_kernel_size, _kernel_num, _stride);
			break;
		}
		default:
			return;
		}


		// decode

		// execute
	}



}
