`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2022/03/15 18:27:06
// Design Name: 
// Module Name: pe
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


module pe(
    clk,
    rst,
    in_a,
    in_b,
    in_acc,
    out_a,
    out_acc
    );
    input clk;
    input rst;
    input signed [7:0] in_a;
    input signed [7:0] in_b;
    input signed [7:0] in_acc;
    output reg signed [7:0] out_a;
    output reg signed [7:0] out_acc;
    
    always @(posedge clk)
    begin
        out_a <= in_a;
        out_acc <= in_acc + in_a * in_b; 
    end
endmodule
