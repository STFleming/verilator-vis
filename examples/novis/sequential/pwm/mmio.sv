// PWM-MMIO  
// 
// memory mapped interface for the PWM module
//
// author: stf

// -------------------------------
//  PWM MMIO hardware block 
// -------------------------------
module mmio (
        input logic clk,
        input logic rst,

	input logic [31:0]   addr_in, // The address for the memory mapped register
	input logic [31:0]   data_in, // incoming data 
	input logic          wr_in,   // the write signal 

	input logic          rd_in,   // the read signal
	output logic 	     rd_valid_out, // when this is high there is a valid read signal at the output
	output logic [31:0]  data_out // the output data
);
// -------------------------------

logic [31:0] config_reg;
logic [31:0] comp_levels_reg;

logic pwm_out;

// count the clock cycles of the system
logic [31:0] clk_cnt;
always_ff @(posedge clk) begin
	clk_cnt <= clk_cnt + 32'd1;
	if (rst) begin
		clk_cnt <= 32'd0;
	end
end

// Write process
always_ff @(posedge clk) begin
	if ((addr_in[31:16] == 16'hBBBB) && wr_in) begin
		case(addr_in[15:0])
			16'h0000 : config_reg <= data_in; 			
			16'h0004 : comp_levels_reg <= data_in; 			
			default: begin
			end
		endcase
	end

	if (rst) begin
		config_reg <= 32'd0;
		comp_levels_reg <= 32'd0;
	end
end

// Read Process 
always_ff @(posedge clk) begin
	rd_valid_out <= rd_in;

	if ((addr_in[31:16] == 16'hBBBB) && rd_in) begin
		case(addr_in[15:0])
			16'h0000 : data_out <= config_reg; 			
			16'h0004 : data_out <= comp_levels_reg; 			
			16'hFFFF : data_out <= clk_cnt;
			default: data_out <= 32'd0;
		endcase
	end

	if (rst) begin
		data_out <= 32'd0;	
	end
end

pwm pwm_inst(
	.clk(clk),
	.rst(rst),

	.config_in(config_reg),
	.comp_levels_in(comp_levels_reg),
	
	.pwm_out(pwm_out)
);

endmodule
// ----- End of MMIO interfacing module -----
