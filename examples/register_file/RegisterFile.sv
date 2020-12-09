// Parameterisable register file for the RISC-V Draig Processor
//
// Quad port set of registers -- not implemented using a BRAM for timing
// purposes.
//
// author: stf

module RegisterFile #(
    parameter LOG_NUM_REG = 4, // Log how many registers there are
    parameter ADDR_WIDTH = 3, // how many bits we need to address all the registers
    parameter DATA_WIDTH = 32 // How wide these registers are
) 
(
    input clk,
    input rst,

    // read port a 
    input logic [ADDR_WIDTH-1:0] porta_rd_addr_in,
    output logic [DATA_WIDTH-1:0] porta_rd_data_out,

    // read port b
    input logic [ADDR_WIDTH-1:0] portb_rd_addr_in,
    output logic [DATA_WIDTH-1:0] portb_rd_data_out,

    // Write port (We may need some arbitration here?)
    input logic [ADDR_WIDTH-1:0] wr_addr_in,
    input logic [DATA_WIDTH-1:0] wr_data_in,
    input logic                  wr_data_valid_in,
    output logic                 wr_data_ready_out

);

// Internal Storage 
logic [LOG_NUM_REG-1:0] [DATA_WIDTH-1:0] regs_ff; 

// Read channels
always_comb begin
    porta_rd_data_out = regs_ff[porta_rd_addr_in];
    portb_rd_data_out = regs_ff[portb_rd_addr_in];
end

// ---=---=---=---=---=---=---=---=---=---=---=---=
// Write channel
// ---=---=---=---=---=---=---=---=---=---=---=---=

// collision detection
always_comb begin
    wr_data_ready_out = 1'b1;
    //if ((porta_rd_addr_in == wr_addr_in) || (portb_rd_addr_in == wr_addr_in)) begin
    //    wr_data_ready_out = 1'b0; // Stall the write, we have a collision 
    //end
end

always_ff @(posedge clk) begin
     if (wr_data_valid_in && wr_data_ready_out) begin
        regs_ff[wr_addr_in] <= wr_data_in;
        regs_ff[0] <= {DATA_WIDTH{1'b0}}; // Reg 0 is always 0 in the RISC-V ISA
     end

     if (rst) begin
	for (int i=0; i<2**LOG_NUM_REG; i++) begin
            regs_ff[i] <= {DATA_WIDTH{1'b0}}; 
        end
    end
end

// ---=---=---=---=---=---=---=---=---=---=---=---=

endmodule /* RegisterFile */
