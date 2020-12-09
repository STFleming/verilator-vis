// Simple testbench for the latency insensitive ram module 
//
// author: stf

module top(
    input clk,
    input rst,
    output logic [31:0] rd_data_out,
    output logic rd_data_valid_out
);

    // testbench signals
    logic [7:0] rd_addr;
    logic rd_req_ready;
    logic rd_req_valid;

    logic [7:0] wr_addr;
    logic [31:0] wr_data;
    logic wr_valid;

   initial begin
      $display("\n\n\nStarting the LatencyInsensitive RAM (li_ram) testbench\n\n\n");
   end

   // The module under test
    li_ram #(
        .ADDR_WIDTH(8),
        .DATA_WIDTH(32)
    ) dut (
       .clk(clk),
       .rst(rst),

       .rd_req_addr_in(rd_addr),
       .rd_req_valid_in(rd_req_valid),
       .rd_req_ready_out(rd_req_ready),

       .rd_resp_data_out(rd_data_out),
       .rd_resp_valid_out(rd_data_valid_out),
       .rd_resp_ready_in(1'b1),

       .wr_addr_in(wr_addr),
       .wr_data_in(wr_data),
       .wr_valid_in(wr_valid),
       .wr_ready_out(/* unused */) // currenty no backpressure on the write channel (maybe when we have a non-dual port version)
    );

    // Fills the RAM with data
    logic [31:0] tb_wr_data;
    logic [7:0] tb_wr_addr;
    logic tb_ram_init_fin;
    always_ff @(posedge clk) begin
         
        if (tb_wr_addr != 255) begin
            tb_wr_data <= tb_wr_data + 32'd1;
            tb_wr_addr <= tb_wr_addr + 8'd1;
            tb_ram_init_fin <= 1'b0;
        end else begin
            tb_ram_init_fin <= 1'b1;
        end

        if (rst) begin
            tb_wr_data <= 32'd1000;
            tb_wr_addr <= 8'd0;
            tb_ram_init_fin <= 1'b0;
        end
    end
    assign wr_data = tb_wr_data;
    assign wr_addr = tb_wr_addr;
    assign wr_valid = ~tb_ram_init_fin;

   
    // Once the RAM has finished start reading out the data 
    assign rd_req_valid = (rd_addr != 255) && tb_ram_init_fin; 
    always_ff @(posedge clk) begin
            
        if(rd_addr < 255) begin
            if (rd_req_ready && rd_req_valid) begin
                rd_addr <= rd_addr + 8'd1;         
            end
        end else begin
            $finish;
        end

        if (rst) begin
            rd_addr <= 8'd0;
        end
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
