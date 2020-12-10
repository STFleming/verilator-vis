// FIFO visualisation example for verilator-vis
//
// author: stf

import verilatorVis::*;

module fifo_tb(
    input clk,
    input rst,

    input logic [31:0] wr_data_in,
    input logic wr_valid_in,
    output logic wr_ready_out,

    output logic [31:0] rd_data_out,
    output logic rd_valid_out,
    input logic rd_ready_in,

    // Visualisation state output
    output fifo_vis_dvis_t vis_out

);

logic fifo_empty;
assign rd_valid_out = ~fifo_empty;

logic fifo_full;
assign wr_ready_out = ~fifo_full;

   fifo_fwft #(
        .DATA_WIDTH(32),
        .DEPTH_WIDTH(5)
   ) dut (
        .clk(clk),
        .rst(rst),

        .din(wr_data_in),
        .wr_en(wr_valid_in && ~fifo_full),
        .full(fifo_full),

        .dout(rd_data_out),
        .rd_en(rd_ready_in && ~fifo_empty),
        .empty(fifo_empty)
   );

   always_comb begin
        vis_out = {$bits(fifo_vis_dvis_t){1'b0}};

        vis_out.write.wr_data = wr_data_in;
        vis_out.write.wr_valid = wr_valid_in && ~fifo_full;
        vis_out.read.rd_data = rd_data_out;
        vis_out.read.rd_valid = rd_ready_in && rd_valid_out;
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
