	// verilator_coverage annotation
	// simple_in_n_out  (Readler -- VBE -- page 6)  
	//
	// author: stf
	
	module intermediate_signal (
		// Inputs
 000036		input logic in_1,
 000018		input logic in_2,
 000011		input logic in_3,
	
		// Outputs
%000008		output logic out_1,
 000010		output logic out_2
	);
	// -------------------------------
	
 000019	logic internal_sig;
	
	assign internal_sig = in_1 & in_2; 
	
	assign out_1 = internal_sig & in_3; 
	assign out_2 = internal_sig | in_3;
	
	endmodule
	
	module top_tb(
 000081	    input clk,
%000002	    input rst
	);
	
	   // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	   // Testbench signals
	   // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 000036	   logic tb_in1;
 000018	   logic tb_in2;
 000011	   logic tb_in3;
	
%000008	   logic tb_out1;
 000010	   logic tb_out2;
	
	   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	   // Testbench logic for signal sequencing
	   // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 000064	   logic [2:0] cnt;
 000080	   always_ff @(posedge clk) begin
 000040		cnt <= cnt + 3'd1;	
%000008		if (rst) begin
 000036		verilator_coverage: (next point on previous line)

%000004		    cnt <= 3'd0;
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
	
 000080	   always_ff @(posedge clk) begin 
 000040	        $display("tb_out1 = %d  tb_out2 = %d", tb_out1, tb_out2);
	   end
	
	
	   // Print some stuff as an example
%000002	   initial begin
%000002	      if ($test$plusargs("trace") != 0) begin
%000000	      verilator_coverage: (next point on previous line)

%000001	         $display("[%0t] Tracing to logs/vlt_dump.vcd...\n", $time);
%000001	         $dumpfile("logs/vlt_dump.vcd");
%000001	         $dumpvars();
	      end
%000001	      $display("[%0t] Model running...\n", $time);
	   end
	
	endmodule
	
