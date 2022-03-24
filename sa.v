`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/03/15 18:40:59
// Design Name: 
// Module Name: sa
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module sa(
    clk,
    rst,
    img_in0,
    w_in0,
    img_in1,
    w_in1,
    out0,
    out1
    );
    input clk;
    input rst;
    input [7:0] img_in0;
    input [7:0] w_in0;
    input [7:0] img_in1;
    input [7:0] w_in1;
    output [7:0] out0;
    output [7:0] out1;
    
    wire [7:0] data_00_01;
    wire [7:0] data_00_10;
    wire [7:0] data_10_11;
    wire [7:0] data_01_11;
    wire [7:0] zero = 0;
    wire [7:0] weight = 2;
    
    pe pe00(
    .clk(clk),
    .rst(rst),
    .in_a(img_in0),
    .in_b(weight),
    .in_acc(zero),
    .out_a(data_00_10),
    .out_acc(data_00_01)
    );
    
    pe pe01(
    .clk(clk),
    .rst(rst),
    .in_a(img_in1),
    .in_b(weight),
    .in_acc(data_00_01),
    .out_a(data_01_11),
    .out_acc(out0)
    );
    
    wire [7:0] gnd;
    pe pe10(
    .clk(clk),
    .rst(rst),
    .in_a(data_00_10),
    .in_b(weight),
    .in_acc(zero),
    .out_a(gnd),
    .out_acc(data_10_11)
    );
    
    pe pe11(
    .clk(clk),
    .rst(rst),
    .in_a(data_01_11),
    .in_b(weight),
    .in_acc(data_10_11),
    .out_a(gnd),
    .out_acc(out1)
    );
    
    
    
endmodule
