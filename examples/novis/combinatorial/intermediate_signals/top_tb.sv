// intermediate_signals  (Readler -- VBE -- page 8)  
//
// Implements a 2 input MUX from first principles.
//
// author: stf

module intermediate_signal (
	// Inputs
	input logic in_1,
	input logic in_2,
	input logic in_3,

	// Outputs
	output logic out_1,
	output logic out_2
);
// -------------------------------

logic internal_sig;

assign internal_sig = in_1 & in_2; 

assign out_1 = internal_sig & in_3; 
assign out_2 = internal_sig | in_3;

endmodule

module top_tb(
    input clk,
    input rst
);

   // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   // Testbench signals
   // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   logic tb_in1;
   logic tb_in2;
   logic tb_in3;

   logic tb_out1;
   logic tb_out2;

   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   // Testbench logic for signal sequencing
   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   logic [2:0] cnt;
   always_ff @(posedge clk) begin
	cnt <= cnt + 3'd1;	
	if (rst) begin
	    cnt <= 3'd0;
	end
   end
   assign tb_in1 = cnt[0];
   assign tb_in2 = cnt[1];
   assign tb_in3 = cnt[2];
   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

   intermediate_signal intermediate_signal_inst(
	// inputs
        .in_1(tb_in1),
        .in_2(tb_in2),
        .in_3(tb_in3),
	
	// outputs
        .out_1(tb_out1),
        .out_2(tb_out2)
   );

   always_ff @(posedge clk) begin 
        $display("tb_out1 = %d  tb_out2 = %d", tb_out1, tb_out2);
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
