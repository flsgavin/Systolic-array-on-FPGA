// ==============================================================
// File generated on Tue Nov 01 13:39:42 +0800 2022
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// ==============================================================

#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;


// [dump_struct_tree [build_nameSpaceTree] dumpedStructList] ---------->


// [dump_enumeration [get_enumeration_list]] ---------->


// wrapc file define: "A"
#define AUTOTB_TVIN_A  "../tv/cdatafile/c.matrix_mult.autotvin_A.dat"
// wrapc file define: "B"
#define AUTOTB_TVIN_B  "../tv/cdatafile/c.matrix_mult.autotvin_B.dat"
// wrapc file define: "C"
#define AUTOTB_TVOUT_C  "../tv/cdatafile/c.matrix_mult.autotvout_C.dat"
#define AUTOTB_TVIN_C  "../tv/cdatafile/c.matrix_mult.autotvin_C.dat"
// wrapc file define: "relu"
#define AUTOTB_TVIN_relu  "../tv/cdatafile/c.matrix_mult.autotvin_relu.dat"

#define INTER_TCL  "../tv/cdatafile/ref.tcl"

// tvout file define: "C"
#define AUTOTB_TVOUT_PC_C  "../tv/rtldatafile/rtl.matrix_mult.autotvout_C.dat"

class INTER_TCL_FILE {
	public:
		INTER_TCL_FILE(const char* name) {
			mName = name;
			A_depth = 0;
			B_depth = 0;
			C_depth = 0;
			relu_depth = 0;
			trans_num =0;
		}

		~INTER_TCL_FILE() {
			mFile.open(mName);
			if (!mFile.good()) {
				cout << "Failed to open file ref.tcl" << endl;
				exit (1);
			}
			string total_list = get_depth_list();
			mFile << "set depth_list {\n";
			mFile << total_list;
			mFile << "}\n";
			mFile << "set trans_num "<<trans_num<<endl;
			mFile.close();
		}

		string get_depth_list () {
			stringstream total_list;
			total_list << "{A " << A_depth << "}\n";
			total_list << "{B " << B_depth << "}\n";
			total_list << "{C " << C_depth << "}\n";
			total_list << "{relu " << relu_depth << "}\n";
			return total_list.str();
		}

		void set_num (int num , int* class_num) {
			(*class_num) = (*class_num) > num ? (*class_num) : num;
		}
	public:
		int A_depth;
		int B_depth;
		int C_depth;
		int relu_depth;
		int trans_num;

	private:
		ofstream mFile;
		const char* mName;
};

extern void matrix_mult (
int A[64][64],
int B[64][64],
int C[64][64],
bool relu);

void AESL_WRAP_matrix_mult (
int A[64][64],
int B[64][64],
int C[64][64],
bool relu)
{
	refine_signal_handler();
	fstream wrapc_switch_file_token;
	wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
	int AESL_i;
	if (wrapc_switch_file_token.good())
	{
		CodeState = ENTER_WRAPC_PC;
		static unsigned AESL_transaction_pc = 0;
		string AESL_token;
		string AESL_num;
		static AESL_FILE_HANDLER aesl_fh;


		// output port post check: "C"
		aesl_fh.read(AUTOTB_TVOUT_PC_C, AESL_token); // [[transaction]]
		if (AESL_token != "[[transaction]]")
		{
			exit(1);
		}
		aesl_fh.read(AUTOTB_TVOUT_PC_C, AESL_num); // transaction number

		if (atoi(AESL_num.c_str()) == AESL_transaction_pc)
		{
			aesl_fh.read(AUTOTB_TVOUT_PC_C, AESL_token); // data

			sc_bv<32> *C_pc_buffer = new sc_bv<32>[4096];
			int i = 0;

			while (AESL_token != "[[/transaction]]")
			{
				bool no_x = false;
				bool err = false;

				// search and replace 'X' with "0" from the 1st char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('X');
					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'C', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				no_x = false;

				// search and replace 'x' with "0" from the 3rd char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('x', 2);

					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'C', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				// push token into output port buffer
				if (AESL_token != "")
				{
					C_pc_buffer[i] = AESL_token.c_str();
					i++;
				}

				aesl_fh.read(AUTOTB_TVOUT_PC_C, AESL_token); // data or [[/transaction]]

				if (AESL_token == "[[[/runtime]]]" || aesl_fh.eof(AUTOTB_TVOUT_PC_C))
				{
					exit(1);
				}
			}

			// ***********************************
			if (i > 0)
			{
				// RTL Name: C
				{
					// bitslice(31, 0)
					// {
						// celement: C(31, 0)
						// {
							sc_lv<32>* C_lv0_0_63_1_lv1_0_63_1 = new sc_lv<32>[4096];
						// }
					// }

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: C(31, 0)
						{
							// carray: (0) => (63) @ (1)
							for (int i_0 = 0; i_0 <= 63; i_0 += 1)
							{
								// carray: (0) => (63) @ (1)
								for (int i_1 = 0; i_1 <= 63; i_1 += 1)
								{
									if (&(C[0][0]) != NULL) // check the null address if the c port is array or others
									{
										C_lv0_0_63_1_lv1_0_63_1[hls_map_index].range(31, 0) = sc_bv<32>(C_pc_buffer[hls_map_index].range(31, 0));
										hls_map_index++;
									}
								}
							}
						}
					}

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: C(31, 0)
						{
							// carray: (0) => (63) @ (1)
							for (int i_0 = 0; i_0 <= 63; i_0 += 1)
							{
								// carray: (0) => (63) @ (1)
								for (int i_1 = 0; i_1 <= 63; i_1 += 1)
								{
									// sub                    : i_0 i_1
									// ori_name               : C[i_0][i_1]
									// sub_1st_elem           : 0 0
									// ori_name_1st_elem      : C[0][0]
									// output_left_conversion : C[i_0][i_1]
									// output_type_conversion : (C_lv0_0_63_1_lv1_0_63_1[hls_map_index]).to_uint64()
									if (&(C[0][0]) != NULL) // check the null address if the c port is array or others
									{
										C[i_0][i_1] = (C_lv0_0_63_1_lv1_0_63_1[hls_map_index]).to_uint64();
										hls_map_index++;
									}
								}
							}
						}
					}
				}
			}

			// release memory allocation
			delete [] C_pc_buffer;
		}

		AESL_transaction_pc++;
	}
	else
	{
		CodeState = ENTER_WRAPC;
		static unsigned AESL_transaction;

		static AESL_FILE_HANDLER aesl_fh;

		// "A"
		char* tvin_A = new char[517];
		aesl_fh.touch(AUTOTB_TVIN_A);

		// "B"
		char* tvin_B = new char[517];
		aesl_fh.touch(AUTOTB_TVIN_B);

		// "C"
		char* tvin_C = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_C);
		char* tvout_C = new char[50];
		aesl_fh.touch(AUTOTB_TVOUT_C);

		// "relu"
		char* tvin_relu = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_relu);

		CodeState = DUMP_INPUTS;
		static INTER_TCL_FILE tcl_file(INTER_TCL);
		int leading_zero;

		// [[transaction]]
		sprintf(tvin_A, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_A, tvin_A);

		sc_bv<2048>* A_tvin_wrapc_buffer = new sc_bv<2048>[64];

		// RTL Name: A
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (0) => (0) @ (2)
						for (int i_1 = 0; i_1 <= 0; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(31, 0) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(63, 32)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (1) => (1) @ (2)
						for (int i_1 = 1; i_1 <= 1; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(63, 32) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(95, 64)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (2) => (2) @ (2)
						for (int i_1 = 2; i_1 <= 2; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(95, 64) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(127, 96)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (3) => (3) @ (2)
						for (int i_1 = 3; i_1 <= 3; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(127, 96) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(159, 128)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (4) => (4) @ (2)
						for (int i_1 = 4; i_1 <= 4; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(159, 128) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(191, 160)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (5) => (5) @ (2)
						for (int i_1 = 5; i_1 <= 5; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(191, 160) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(223, 192)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (6) => (6) @ (2)
						for (int i_1 = 6; i_1 <= 6; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(223, 192) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(255, 224)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (7) => (7) @ (2)
						for (int i_1 = 7; i_1 <= 7; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(255, 224) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(287, 256)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (8) => (8) @ (2)
						for (int i_1 = 8; i_1 <= 8; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(287, 256) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(319, 288)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (9) => (9) @ (2)
						for (int i_1 = 9; i_1 <= 9; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(319, 288) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(351, 320)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (10) => (10) @ (2)
						for (int i_1 = 10; i_1 <= 10; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(351, 320) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(383, 352)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (11) => (11) @ (2)
						for (int i_1 = 11; i_1 <= 11; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(383, 352) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(415, 384)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (12) => (12) @ (2)
						for (int i_1 = 12; i_1 <= 12; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(415, 384) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(447, 416)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (13) => (13) @ (2)
						for (int i_1 = 13; i_1 <= 13; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(447, 416) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(479, 448)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (14) => (14) @ (2)
						for (int i_1 = 14; i_1 <= 14; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(479, 448) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(511, 480)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (15) => (15) @ (2)
						for (int i_1 = 15; i_1 <= 15; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(511, 480) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(543, 512)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (16) => (16) @ (2)
						for (int i_1 = 16; i_1 <= 16; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(543, 512) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(575, 544)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (17) => (17) @ (2)
						for (int i_1 = 17; i_1 <= 17; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(575, 544) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(607, 576)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (18) => (18) @ (2)
						for (int i_1 = 18; i_1 <= 18; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(607, 576) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(639, 608)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (19) => (19) @ (2)
						for (int i_1 = 19; i_1 <= 19; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(639, 608) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(671, 640)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (20) => (20) @ (2)
						for (int i_1 = 20; i_1 <= 20; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(671, 640) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(703, 672)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (21) => (21) @ (2)
						for (int i_1 = 21; i_1 <= 21; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(703, 672) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(735, 704)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (22) => (22) @ (2)
						for (int i_1 = 22; i_1 <= 22; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(735, 704) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(767, 736)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (23) => (23) @ (2)
						for (int i_1 = 23; i_1 <= 23; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(767, 736) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(799, 768)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (24) => (24) @ (2)
						for (int i_1 = 24; i_1 <= 24; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(799, 768) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(831, 800)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (25) => (25) @ (2)
						for (int i_1 = 25; i_1 <= 25; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(831, 800) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(863, 832)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (26) => (26) @ (2)
						for (int i_1 = 26; i_1 <= 26; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(863, 832) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(895, 864)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (27) => (27) @ (2)
						for (int i_1 = 27; i_1 <= 27; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(895, 864) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(927, 896)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (28) => (28) @ (2)
						for (int i_1 = 28; i_1 <= 28; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(927, 896) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(959, 928)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (29) => (29) @ (2)
						for (int i_1 = 29; i_1 <= 29; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(959, 928) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(991, 960)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (30) => (30) @ (2)
						for (int i_1 = 30; i_1 <= 30; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(991, 960) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1023, 992)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (31) => (31) @ (2)
						for (int i_1 = 31; i_1 <= 31; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1023, 992) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1055, 1024)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (32) => (32) @ (2)
						for (int i_1 = 32; i_1 <= 32; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1055, 1024) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1087, 1056)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (33) => (33) @ (2)
						for (int i_1 = 33; i_1 <= 33; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1087, 1056) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1119, 1088)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (34) => (34) @ (2)
						for (int i_1 = 34; i_1 <= 34; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1119, 1088) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1151, 1120)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (35) => (35) @ (2)
						for (int i_1 = 35; i_1 <= 35; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1151, 1120) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1183, 1152)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (36) => (36) @ (2)
						for (int i_1 = 36; i_1 <= 36; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1183, 1152) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1215, 1184)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (37) => (37) @ (2)
						for (int i_1 = 37; i_1 <= 37; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1215, 1184) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1247, 1216)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (38) => (38) @ (2)
						for (int i_1 = 38; i_1 <= 38; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1247, 1216) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1279, 1248)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (39) => (39) @ (2)
						for (int i_1 = 39; i_1 <= 39; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1279, 1248) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1311, 1280)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (40) => (40) @ (2)
						for (int i_1 = 40; i_1 <= 40; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1311, 1280) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1343, 1312)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (41) => (41) @ (2)
						for (int i_1 = 41; i_1 <= 41; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1343, 1312) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1375, 1344)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (42) => (42) @ (2)
						for (int i_1 = 42; i_1 <= 42; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1375, 1344) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1407, 1376)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (43) => (43) @ (2)
						for (int i_1 = 43; i_1 <= 43; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1407, 1376) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1439, 1408)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (44) => (44) @ (2)
						for (int i_1 = 44; i_1 <= 44; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1439, 1408) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1471, 1440)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (45) => (45) @ (2)
						for (int i_1 = 45; i_1 <= 45; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1471, 1440) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1503, 1472)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (46) => (46) @ (2)
						for (int i_1 = 46; i_1 <= 46; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1503, 1472) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1535, 1504)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (47) => (47) @ (2)
						for (int i_1 = 47; i_1 <= 47; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1535, 1504) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1567, 1536)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (48) => (48) @ (2)
						for (int i_1 = 48; i_1 <= 48; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1567, 1536) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1599, 1568)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (49) => (49) @ (2)
						for (int i_1 = 49; i_1 <= 49; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1599, 1568) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1631, 1600)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (50) => (50) @ (2)
						for (int i_1 = 50; i_1 <= 50; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1631, 1600) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1663, 1632)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (51) => (51) @ (2)
						for (int i_1 = 51; i_1 <= 51; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1663, 1632) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1695, 1664)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (52) => (52) @ (2)
						for (int i_1 = 52; i_1 <= 52; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1695, 1664) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1727, 1696)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (53) => (53) @ (2)
						for (int i_1 = 53; i_1 <= 53; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1727, 1696) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1759, 1728)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (54) => (54) @ (2)
						for (int i_1 = 54; i_1 <= 54; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1759, 1728) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1791, 1760)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (55) => (55) @ (2)
						for (int i_1 = 55; i_1 <= 55; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1791, 1760) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1823, 1792)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (56) => (56) @ (2)
						for (int i_1 = 56; i_1 <= 56; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1823, 1792) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1855, 1824)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (57) => (57) @ (2)
						for (int i_1 = 57; i_1 <= 57; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1855, 1824) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1887, 1856)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (58) => (58) @ (2)
						for (int i_1 = 58; i_1 <= 58; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1887, 1856) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1919, 1888)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (59) => (59) @ (2)
						for (int i_1 = 59; i_1 <= 59; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1919, 1888) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1951, 1920)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (60) => (60) @ (2)
						for (int i_1 = 60; i_1 <= 60; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1951, 1920) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1983, 1952)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (61) => (61) @ (2)
						for (int i_1 = 61; i_1 <= 61; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(1983, 1952) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(2015, 1984)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (62) => (62) @ (2)
						for (int i_1 = 62; i_1 <= 62; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(2015, 1984) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(2047, 2016)
			{
				int hls_map_index = 0;
				// celement: A(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (63) => (63) @ (2)
						for (int i_1 = 63; i_1 <= 63; i_1 += 2)
						{
							// sub                   : i_0 i_1
							// ori_name              : A[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : A[0][0]
							// regulate_c_name       : A
							// input_type_conversion : A[i_0][i_1]
							if (&(A[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> A_tmp_mem;
								A_tmp_mem = A[i_0][i_1];
								A_tvin_wrapc_buffer[hls_map_index].range(2047, 2016) = A_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 64; i++)
		{
			sprintf(tvin_A, "%s\n", (A_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_A, tvin_A);
		}

		tcl_file.set_num(64, &tcl_file.A_depth);
		sprintf(tvin_A, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_A, tvin_A);

		// release memory allocation
		delete [] A_tvin_wrapc_buffer;

		// [[transaction]]
		sprintf(tvin_B, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_B, tvin_B);

		sc_bv<2048>* B_tvin_wrapc_buffer = new sc_bv<2048>[64];

		// RTL Name: B
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (0) => (0) @ (2)
					for (int i_0 = 0; i_0 <= 0; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(31, 0) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(63, 32)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (1) => (1) @ (2)
					for (int i_0 = 1; i_0 <= 1; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(63, 32) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(95, 64)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (2) => (2) @ (2)
					for (int i_0 = 2; i_0 <= 2; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(95, 64) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(127, 96)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (3) => (3) @ (2)
					for (int i_0 = 3; i_0 <= 3; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(127, 96) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(159, 128)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (4) => (4) @ (2)
					for (int i_0 = 4; i_0 <= 4; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(159, 128) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(191, 160)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (5) => (5) @ (2)
					for (int i_0 = 5; i_0 <= 5; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(191, 160) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(223, 192)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (6) => (6) @ (2)
					for (int i_0 = 6; i_0 <= 6; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(223, 192) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(255, 224)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (7) => (7) @ (2)
					for (int i_0 = 7; i_0 <= 7; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(255, 224) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(287, 256)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (8) => (8) @ (2)
					for (int i_0 = 8; i_0 <= 8; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(287, 256) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(319, 288)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (9) => (9) @ (2)
					for (int i_0 = 9; i_0 <= 9; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(319, 288) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(351, 320)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (10) => (10) @ (2)
					for (int i_0 = 10; i_0 <= 10; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(351, 320) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(383, 352)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (11) => (11) @ (2)
					for (int i_0 = 11; i_0 <= 11; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(383, 352) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(415, 384)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (12) => (12) @ (2)
					for (int i_0 = 12; i_0 <= 12; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(415, 384) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(447, 416)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (13) => (13) @ (2)
					for (int i_0 = 13; i_0 <= 13; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(447, 416) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(479, 448)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (14) => (14) @ (2)
					for (int i_0 = 14; i_0 <= 14; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(479, 448) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(511, 480)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (15) => (15) @ (2)
					for (int i_0 = 15; i_0 <= 15; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(511, 480) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(543, 512)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (16) => (16) @ (2)
					for (int i_0 = 16; i_0 <= 16; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(543, 512) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(575, 544)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (17) => (17) @ (2)
					for (int i_0 = 17; i_0 <= 17; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(575, 544) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(607, 576)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (18) => (18) @ (2)
					for (int i_0 = 18; i_0 <= 18; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(607, 576) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(639, 608)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (19) => (19) @ (2)
					for (int i_0 = 19; i_0 <= 19; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(639, 608) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(671, 640)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (20) => (20) @ (2)
					for (int i_0 = 20; i_0 <= 20; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(671, 640) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(703, 672)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (21) => (21) @ (2)
					for (int i_0 = 21; i_0 <= 21; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(703, 672) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(735, 704)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (22) => (22) @ (2)
					for (int i_0 = 22; i_0 <= 22; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(735, 704) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(767, 736)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (23) => (23) @ (2)
					for (int i_0 = 23; i_0 <= 23; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(767, 736) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(799, 768)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (24) => (24) @ (2)
					for (int i_0 = 24; i_0 <= 24; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(799, 768) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(831, 800)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (25) => (25) @ (2)
					for (int i_0 = 25; i_0 <= 25; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(831, 800) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(863, 832)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (26) => (26) @ (2)
					for (int i_0 = 26; i_0 <= 26; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(863, 832) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(895, 864)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (27) => (27) @ (2)
					for (int i_0 = 27; i_0 <= 27; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(895, 864) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(927, 896)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (28) => (28) @ (2)
					for (int i_0 = 28; i_0 <= 28; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(927, 896) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(959, 928)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (29) => (29) @ (2)
					for (int i_0 = 29; i_0 <= 29; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(959, 928) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(991, 960)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (30) => (30) @ (2)
					for (int i_0 = 30; i_0 <= 30; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(991, 960) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1023, 992)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (31) => (31) @ (2)
					for (int i_0 = 31; i_0 <= 31; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1023, 992) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1055, 1024)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (32) => (32) @ (2)
					for (int i_0 = 32; i_0 <= 32; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1055, 1024) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1087, 1056)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (33) => (33) @ (2)
					for (int i_0 = 33; i_0 <= 33; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1087, 1056) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1119, 1088)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (34) => (34) @ (2)
					for (int i_0 = 34; i_0 <= 34; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1119, 1088) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1151, 1120)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (35) => (35) @ (2)
					for (int i_0 = 35; i_0 <= 35; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1151, 1120) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1183, 1152)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (36) => (36) @ (2)
					for (int i_0 = 36; i_0 <= 36; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1183, 1152) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1215, 1184)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (37) => (37) @ (2)
					for (int i_0 = 37; i_0 <= 37; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1215, 1184) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1247, 1216)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (38) => (38) @ (2)
					for (int i_0 = 38; i_0 <= 38; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1247, 1216) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1279, 1248)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (39) => (39) @ (2)
					for (int i_0 = 39; i_0 <= 39; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1279, 1248) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1311, 1280)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (40) => (40) @ (2)
					for (int i_0 = 40; i_0 <= 40; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1311, 1280) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1343, 1312)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (41) => (41) @ (2)
					for (int i_0 = 41; i_0 <= 41; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1343, 1312) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1375, 1344)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (42) => (42) @ (2)
					for (int i_0 = 42; i_0 <= 42; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1375, 1344) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1407, 1376)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (43) => (43) @ (2)
					for (int i_0 = 43; i_0 <= 43; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1407, 1376) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1439, 1408)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (44) => (44) @ (2)
					for (int i_0 = 44; i_0 <= 44; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1439, 1408) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1471, 1440)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (45) => (45) @ (2)
					for (int i_0 = 45; i_0 <= 45; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1471, 1440) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1503, 1472)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (46) => (46) @ (2)
					for (int i_0 = 46; i_0 <= 46; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1503, 1472) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1535, 1504)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (47) => (47) @ (2)
					for (int i_0 = 47; i_0 <= 47; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1535, 1504) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1567, 1536)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (48) => (48) @ (2)
					for (int i_0 = 48; i_0 <= 48; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1567, 1536) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1599, 1568)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (49) => (49) @ (2)
					for (int i_0 = 49; i_0 <= 49; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1599, 1568) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1631, 1600)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (50) => (50) @ (2)
					for (int i_0 = 50; i_0 <= 50; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1631, 1600) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1663, 1632)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (51) => (51) @ (2)
					for (int i_0 = 51; i_0 <= 51; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1663, 1632) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1695, 1664)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (52) => (52) @ (2)
					for (int i_0 = 52; i_0 <= 52; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1695, 1664) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1727, 1696)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (53) => (53) @ (2)
					for (int i_0 = 53; i_0 <= 53; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1727, 1696) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1759, 1728)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (54) => (54) @ (2)
					for (int i_0 = 54; i_0 <= 54; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1759, 1728) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1791, 1760)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (55) => (55) @ (2)
					for (int i_0 = 55; i_0 <= 55; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1791, 1760) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1823, 1792)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (56) => (56) @ (2)
					for (int i_0 = 56; i_0 <= 56; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1823, 1792) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1855, 1824)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (57) => (57) @ (2)
					for (int i_0 = 57; i_0 <= 57; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1855, 1824) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1887, 1856)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (58) => (58) @ (2)
					for (int i_0 = 58; i_0 <= 58; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1887, 1856) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1919, 1888)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (59) => (59) @ (2)
					for (int i_0 = 59; i_0 <= 59; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1919, 1888) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1951, 1920)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (60) => (60) @ (2)
					for (int i_0 = 60; i_0 <= 60; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1951, 1920) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(1983, 1952)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (61) => (61) @ (2)
					for (int i_0 = 61; i_0 <= 61; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(1983, 1952) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(2015, 1984)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (62) => (62) @ (2)
					for (int i_0 = 62; i_0 <= 62; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(2015, 1984) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
			// bitslice(2047, 2016)
			{
				int hls_map_index = 0;
				// celement: B(31, 0)
				{
					// carray: (63) => (63) @ (2)
					for (int i_0 = 63; i_0 <= 63; i_0 += 2)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : B[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : B[0][0]
							// regulate_c_name       : B
							// input_type_conversion : B[i_0][i_1]
							if (&(B[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> B_tmp_mem;
								B_tmp_mem = B[i_0][i_1];
								B_tvin_wrapc_buffer[hls_map_index].range(2047, 2016) = B_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 64; i++)
		{
			sprintf(tvin_B, "%s\n", (B_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_B, tvin_B);
		}

		tcl_file.set_num(64, &tcl_file.B_depth);
		sprintf(tvin_B, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_B, tvin_B);

		// release memory allocation
		delete [] B_tvin_wrapc_buffer;

		// [[transaction]]
		sprintf(tvin_C, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_C, tvin_C);

		sc_bv<32>* C_tvin_wrapc_buffer = new sc_bv<32>[4096];

		// RTL Name: C
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: C(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : C[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : C[0][0]
							// regulate_c_name       : C
							// input_type_conversion : C[i_0][i_1]
							if (&(C[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> C_tmp_mem;
								C_tmp_mem = C[i_0][i_1];
								C_tvin_wrapc_buffer[hls_map_index].range(31, 0) = C_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 4096; i++)
		{
			sprintf(tvin_C, "%s\n", (C_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_C, tvin_C);
		}

		tcl_file.set_num(4096, &tcl_file.C_depth);
		sprintf(tvin_C, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_C, tvin_C);

		// release memory allocation
		delete [] C_tvin_wrapc_buffer;

		// [[transaction]]
		sprintf(tvin_relu, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_relu, tvin_relu);

		sc_bv<1> relu_tvin_wrapc_buffer;

		// RTL Name: relu
		{
			// bitslice(0, 0)
			{
				// celement: relu(0, 0)
				{
					// carray: (0) => (0) @ (0)
					{
						// sub                   : 
						// ori_name              : relu
						// sub_1st_elem          : 
						// ori_name_1st_elem     : relu
						// regulate_c_name       : relu
						// input_type_conversion : relu
						if (&(relu) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<1> relu_tmp_mem;
							relu_tmp_mem = relu;
							relu_tvin_wrapc_buffer.range(0, 0) = relu_tmp_mem.range(0, 0);
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvin_relu, "%s\n", (relu_tvin_wrapc_buffer).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_relu, tvin_relu);
		}

		tcl_file.set_num(1, &tcl_file.relu_depth);
		sprintf(tvin_relu, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_relu, tvin_relu);

// [call_c_dut] ---------->

		CodeState = CALL_C_DUT;
		matrix_mult(A, B, C, relu);

		CodeState = DUMP_OUTPUTS;

		// [[transaction]]
		sprintf(tvout_C, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVOUT_C, tvout_C);

		sc_bv<32>* C_tvout_wrapc_buffer = new sc_bv<32>[4096];

		// RTL Name: C
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: C(31, 0)
				{
					// carray: (0) => (63) @ (1)
					for (int i_0 = 0; i_0 <= 63; i_0 += 1)
					{
						// carray: (0) => (63) @ (1)
						for (int i_1 = 0; i_1 <= 63; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : C[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : C[0][0]
							// regulate_c_name       : C
							// input_type_conversion : C[i_0][i_1]
							if (&(C[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> C_tmp_mem;
								C_tmp_mem = C[i_0][i_1];
								C_tvout_wrapc_buffer[hls_map_index].range(31, 0) = C_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 4096; i++)
		{
			sprintf(tvout_C, "%s\n", (C_tvout_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVOUT_C, tvout_C);
		}

		tcl_file.set_num(4096, &tcl_file.C_depth);
		sprintf(tvout_C, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVOUT_C, tvout_C);

		// release memory allocation
		delete [] C_tvout_wrapc_buffer;

		CodeState = DELETE_CHAR_BUFFERS;
		// release memory allocation: "A"
		delete [] tvin_A;
		// release memory allocation: "B"
		delete [] tvin_B;
		// release memory allocation: "C"
		delete [] tvout_C;
		delete [] tvin_C;
		// release memory allocation: "relu"
		delete [] tvin_relu;

		AESL_transaction++;

		tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
	}
}

