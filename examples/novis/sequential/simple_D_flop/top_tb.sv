// Simple D_Type FlipFlop (Readler -- VBE -- page 15)  
//
// author: stf

// -------------------------------
// simple D flop module 
// -------------------------------
module simple_D_flop (
        input logic clk,
        input logic rst,

	input logic in_1,
        output logic out_1 
);
// -------------------------------

always_ff @(posedge clk) begin

	out_1 <= in_1;

	if (rst) begin
		out_1 <= 1'b0;
	end
end

endmodule
// ----- End of simple_D_flop module -----

module top_tb(
    input clk,
    input rst
);

   logic a_tb;

   logic[31:0] cnt;

   always_ff @(posedge clk) begin

	if (cnt >= 32'd4) begin
        	a_tb <= !a_tb;
		cnt <= 32'd0;
	end else begin
		cnt <= cnt + 32'd1;
	end

        if (rst) begin
        	a_tb <= 1'b0;
		cnt <= 32'd0;	
        end
   end
   
   logic out_tb;

   simple_D_flop simple_D_flop_inst(
        .clk(clk),
        .rst(rst),

        .in_1(a_tb),
        .out_1(out_tb)
   );

   always_ff @(posedge clk) begin 
        $display("out_tb = %d", out_tb);
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
