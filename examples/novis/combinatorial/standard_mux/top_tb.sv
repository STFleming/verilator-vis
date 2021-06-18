// standard_mux  (Readler -- VBE -- page 12)  
//
// author: stf

// -----------------------------
// standard MUX module
// -----------------------------
module standard_mux (
	// Inputs
	input logic [3:0] in_1,
	input logic [3:0] in_2,
	input logic [3:0] in_3,
	input logic [3:0] in_4,
	input logic [1:0] sel,

	// Outputs
	output logic [3:0] out_1
);

always_comb begin 
    case (sel) 
    	2'd0 : out_1 = in_1; 
    	2'd1 : out_1 = in_2; 
    	2'd2 : out_1 = in_3; 
    	2'd3 : out_1 = in_4; 
	default: out_1 = {4{1'b0}};
    endcase 
end

endmodule
// -----------------------------

module top_tb(
    input clk,
    input rst
);

   // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   // Testbench signals
   // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   logic [3:0] tb_in1;
   logic [3:0] tb_in2;
   logic [3:0] tb_in3;
   logic [3:0] tb_in4;

   logic [1:0] tb_sel;

   logic [3:0] tb_out1;

   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   // Testbench logic for signal sequencing
   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   always_ff @(posedge clk) begin
	tb_in1 <= tb_in1 + 4'd1;	
	tb_in2 <= tb_in2 + 4'd1;	
	tb_in3 <= tb_in3 + 4'd1;	
	tb_in4 <= tb_in4 + 4'd1;	
	tb_sel <= tb_in1[3:2];
	if (rst) begin
            tb_sel <= 2'd0;
	    tb_in1 <= 4'd0;
	    tb_in2 <= 4'd7;
	    tb_in3 <= 4'd12;
	    tb_in4 <= 4'd15;
	end
   end
   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

   standard_mux standard_mux_inst(
	// inputs
        .in_1(tb_in1),
        .in_2(tb_in2),
        .in_3(tb_in3),
        .in_4(tb_in4),
	.sel(tb_sel),
	
	// outputs
        .out_1(tb_out1)
   );

   always_ff @(posedge clk) begin 
        $display("tb_out1 = %d", tb_out1);
   end

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
