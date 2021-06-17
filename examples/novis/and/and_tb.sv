// And gate example
//
// author: stf

// -------------------------------
// and gate module
module and_gate (
        input logic a,
        input logic b,

        output logic c
);

assign c = a & b;

endmodule
// ----- End of and gate module -----

module and_tb(
    input clk,
    input rst
);

   logic a_tb;
   logic b_tb;

   logic c_tb;

   //assign a_tb = 1'b1;
   assign b_tb = 1'b1;

   always_ff @(posedge clk) begin
        a_tb <= !a_tb;
   end

   and_gate and_gate_inst(
        .a(a_tb),
        .b(b_tb),
        .c(c_tb)
   );

   always_ff @(posedge clk) begin 
        $display("c = %d", c_tb);
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
