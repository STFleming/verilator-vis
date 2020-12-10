// The Draig Processor: The register file
// i32 variant 
//
// author: stf

import verilatorVis::*;

module register_file_tb(
    input clk,
    input rst,

    input logic [4:0]  wr_addr_in,
    input logic [31:0] wr_data_in,
    input logic        wr_data_valid_in,
    output logic       wr_data_ready_out,

    // Visualisation state output
    output regfile_vis_dvis_t vis_out

);

   // continually sweep over the addresses
   logic [4:0] porta_addr; 
   logic [4:0] portb_addr; 

   always_ff @(posedge clk) begin
           porta_addr <= porta_addr + 5'd1;
           portb_addr <= portb_addr + 5'd1;

           if (rst) begin
                porta_addr <= 5'd0;
                portb_addr <= 5'd15;
           end
   end

   logic [31:0] porta_data;
   logic [31:0] portb_data;

   RegisterFile #(
        .LOG_NUM_REG(5), // 16 registers in the register file
        .ADDR_WIDTH(5),
        .DATA_WIDTH(32)
   ) dut (
        .clk(clk),
        .rst(rst),

        .porta_rd_addr_in(porta_addr),
        .porta_rd_data_out(porta_data),

        .portb_rd_addr_in(portb_addr),
        .portb_rd_data_out(portb_data),

        .wr_addr_in(wr_addr_in),
        .wr_data_in(wr_data_in),
        .wr_data_valid_in(wr_data_valid_in),
        .wr_data_ready_out(wr_data_ready_out)
   );

   always_comb begin
        vis_out = {$bits(regfile_vis_dvis_t){1'b0}};
        vis_out.wr_reg.wr_addr  = wr_addr_in;
        vis_out.wr_reg.wr_data  = wr_data_in;
        vis_out.wr_reg.wr_valid = wr_data_valid_in && wr_data_ready_out;

        vis_out.sr0.sr0_addr    = porta_addr;
        vis_out.sr0.sr0_data    = porta_data; 

        vis_out.sr1.sr1_addr    = portb_addr;
        vis_out.sr1.sr1_data    = portb_data; 
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
