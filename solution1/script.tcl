############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project testTPU
set_top im2col
add_files testTPU/src/im2col.cpp
add_files testTPU/src/im2col.h
add_files testTPU/src/instr.cpp
add_files testTPU/src/instr.h
add_files testTPU/src/sa.cpp
add_files testTPU/src/sa.h
add_files -tb testTPU/feature.dat
add_files -tb testTPU/src/tb_mxu.cpp
add_files -tb testTPU/weight.dat
open_solution "solution1"
set_part {xczu9eg-ffvb1156-2-i}
create_clock -period 10 -name default
config_compile -no_signed_zeros=0 -unsafe_math_optimizations=0
config_sdx -optimization_level none -target none
config_schedule -effort medium -relax_ii_for_timing=0
config_bind -effort medium
set_clock_uncertainty 12.5%
#source "./testTPU/solution1/directives.tcl"
csim_design -O
csynth_design
cosim_design -trace_level port -tool xsim
export_design -format ip_catalog
