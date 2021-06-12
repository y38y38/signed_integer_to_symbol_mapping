module signed_integer_to_symbol_mapping(
	input clk,
	input reset_n,
//	input logic input_enable,

	//本当は19bitで足りるが、本関数の処理上桁溢れする可能性があるので、
	//1bit多く用意しておく。
	input [19:0] input_data,
	output reg [23:0] sum

);

function [19:0] Signedintegertosymbolmapping;
	input [19:0] val;
	begin
		if (input_data[19] != 1'b1) begin
			Signedintegertosymbolmapping = input_data << 1;
		end else begin
			Signedintegertosymbolmapping = ((~(input_data - 1)) << 1) -1;
		end
	end
endfunction

logic [31:0] q = 32'h0;
logic [5:0] codeword_length = 6'h0;


always @(posedge clk, negedge reset_n) begin
	if (!reset_n) begin
		sum = 24'h0;
	end else begin
		sum = Signedintegertosymbolmapping(input_data);
	end
end

endmodule;
