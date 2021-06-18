// bus_signals  (Readler -- VBE -- page 10)  
//
// author: stf

module bus_signals (
	// Inputs
	input logic [3:0] in_1,
	input logic [3:0] in_2,
	input logic in_3,

	// Outputs
	output logic [3:0] out_1
);

logic [3:0] in_3_bus;
assign in_3_bus = {4{in_3}}; // replicates the signal

assign out_1 = (~in_3_bus & in_1) | (in_3_bus & in_2);
endmodule

module top_tb(
    input clk,
    input rst
);

   // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   // Testbench signals
   // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   logic [3:0] tb_in1;
   logic [3:0] tb_in2;
   logic tb_in3;

   logic [3:0] tb_out1;

   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   // Testbench logic for signal sequencing
   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   always_ff @(posedge clk) begin
	tb_in1 <= tb_in1 + 4'd1;	
	tb_in2 <= tb_in2 + 4'd1;	
	tb_in3 <= ~tb_in3;
	if (rst) begin
	    tb_in1 <= 4'd0;
	    tb_in2 <= 4'd8;
	    tb_in3 <= 1'b0;
	end
   end
   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

   bus_signals bus_signals_inst(
	// inputs
        .in_1(tb_in1),
        .in_2(tb_in2),
        .in_3(tb_in3),
	
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
