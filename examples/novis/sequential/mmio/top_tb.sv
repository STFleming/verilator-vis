// MMIO  
// 
// a memory-mapped IO module
// used to help demystify HW/SW communications a bit
//
// author: stf

// -------------------------------
//  Memory Mapped IO block 
// -------------------------------
module mmio (
        input logic clk,
        input logic rst,

	input logic [31:0]   addr_in, // The address for the memory mapped register
	input logic [31:0]   data_in, // incoming data 
	input logic          wr_in,   // the write signal 

	input logic          rd_in,   // the read signal
	output logic [31:0]  data_out // the output data
);
// -------------------------------

logic [31:0] config_reg;
logic [31:0] input_data_reg;
logic [31:0] output_data_reg;
logic [31:0] status_reg;

// Write process
always_ff @(posedge clk) begin
	if ((addr_in[15] == 1'b1) && wr_in) begin
		case(addr_in[3:0])
			4'h0 : config_reg <= data_in; 			
			4'h4 : input_data_reg <= data_in;  
			default: begin
			end
		endcase
	end

	if (rst) begin
		config_reg <= 32'd0;
		input_data_reg <= 32'd0;
	end
end

// Read Process 
always_ff @(posedge clk) begin
	if ((addr_in[15] == 1'b1) && rd_in) begin
		case(addr_in[3:0])
			4'h0 : data_out <= config_reg; 			
			4'h4 : data_out <= input_data_reg;  
			4'h8 : data_out <= output_data_reg;  
			4'hC : data_out <= status_reg;  
			default: data_out <= 32'd0;
		endcase
	end

	if (rst) begin
		data_out <= 32'd0;	
	end
end

assign output_data_reg = input_data_reg + 32'd42;
assign status_reg = config_reg;

endmodule
// ----- End of MMIO interfacing module -----

module top_tb(
    input clk,
    input rst,

    input logic [31:0]  addr_in,
    input logic [31:0]  data_in,
    input logic         wr_in,

    input logic         rd_in,
    output logic [31:0] data_out
);


   mmio mmio_inst(
        .clk(clk),
        .rst(rst),

        .addr_in(addr_in),
        .data_in(data_in),
	.wr_in(wr_in),

	.rd_in(rd_in),
	.data_out(data_out)
   );


   // Print some stuff as an example
   initial begin
      if ($test$plusargs("trace") != 0) begin
         $display("[%0t] Tracing to logs/vlt_dump.vcd...\n", $time);
         $dumpfile("logs/vlt_dump.vcd");
         $dumpvars();
      end
      $display("[%0t] Model running...\n", $time);
   end

endmodule
