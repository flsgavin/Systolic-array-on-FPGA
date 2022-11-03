
log_wave [get_objects -filter {type == in_port || type == out_port || type == inout_port || type == port} /apatb_matrix_mult_top/AESL_inst_matrix_mult/*]
set designtopgroup [add_wave_group "Design Top Signals"]
set coutputgroup [add_wave_group "C Outputs" -into $designtopgroup]
set C_group [add_wave_group C(memory) -into $coutputgroup]
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/C_d0 -into $C_group -radix hex
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/C_we0 -into $C_group -color #ffff00 -radix hex
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/C_ce0 -into $C_group -color #ffff00 -radix hex
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/C_address0 -into $C_group -radix hex
set cinputgroup [add_wave_group "C Inputs" -into $designtopgroup]
set relu_group [add_wave_group relu(wire) -into $cinputgroup]
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/relu -into $relu_group -radix hex
set B_group [add_wave_group B(memory) -into $cinputgroup]
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/B_q0 -into $B_group -radix hex
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/B_ce0 -into $B_group -color #ffff00 -radix hex
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/B_address0 -into $B_group -radix hex
set A_group [add_wave_group A(memory) -into $cinputgroup]
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/A_q0 -into $A_group -radix hex
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/A_ce0 -into $A_group -color #ffff00 -radix hex
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/A_address0 -into $A_group -radix hex
set blocksiggroup [add_wave_group "Block-level IO Handshake" -into $designtopgroup]
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/ap_start -into $blocksiggroup
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/ap_done -into $blocksiggroup
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/ap_idle -into $blocksiggroup
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/ap_ready -into $blocksiggroup
set resetgroup [add_wave_group "Reset" -into $designtopgroup]
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/ap_rst -into $resetgroup
set clockgroup [add_wave_group "Clock" -into $designtopgroup]
add_wave /apatb_matrix_mult_top/AESL_inst_matrix_mult/ap_clk -into $clockgroup
save_wave_config matrix_mult.wcfg
run all
quit

