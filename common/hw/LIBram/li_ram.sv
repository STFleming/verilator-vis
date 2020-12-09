// A latency insensitive ram module
// A ram module that used valid / ready / data triplets for handshaking
//
// author: stf

module li_ram #(
    parameter ADDR_WIDTH=8,
    parameter DATA_WIDTH=16
)
(

    input clk,
    input rst,

    // Read req channel
    input logic [ADDR_WIDTH-1:0] rd_req_addr_in,
    input logic                      rd_req_valid_in,
    output logic                     rd_req_ready_out,

    // Read resp channel
    output logic [DATA_WIDTH-1:0] rd_resp_data_out,
    output logic                      rd_resp_valid_out,
    input logic                       rd_resp_ready_in,
    
    // Write req channel
    input logic [ADDR_WIDTH-1:0]  wr_addr_in,
    input logic [DATA_WIDTH-1:0]  wr_data_in,
    input logic                       wr_valid_in,
    output logic                      wr_ready_out

    // visualisation out
);

// -----=======--------========--------========
//                Signals
// -----=======--------========--------========
logic ram_wr; // write enable for the RAM module 
logic ram_rd; // read enable for the RAM module
logic [DATA_WIDTH-1:0] rd_data; // the read data
logic token;
logic first_stage_valid;
logic first_stage_ready; 
logic second_stage_valid;
logic second_stage_ready;
// -----=======--------========--------========

// stall for 2 pipe stages
assign rd_req_ready_out = first_stage_ready && second_stage_ready;
assign wr_ready_out = 1'b1; // always ready no arbitration
assign ram_wr = wr_valid_in;

// ############################################
//            Read Channel
// ############################################
always_comb begin
    //defaults
    first_stage_valid = 1'b0;
    ram_rd = 1'b0;

    if(rd_req_valid_in && rd_req_ready_out) begin
        first_stage_valid = 1'b1; 
        ram_rd = 1'b1;
    end
end


SkidBuffer #(
    .WIDTH(1) // I was worried about it optimising it away
) first_stage_sb (
    .clk(clk),
    .arst(rst),
    
    .dat_i(first_stage_valid),
    .valid_i(first_stage_valid),
    .ready_i(first_stage_ready),

    .dat_o(token),
    .valid_o(second_stage_valid),
    .ready_o(second_stage_ready)
);


SkidBuffer #(
    .WIDTH(DATA_WIDTH)
) second_stage_sb (
    .clk(clk),
    .arst(rst),
    
    .dat_i(rd_data),
    .valid_i(second_stage_valid),
    .ready_i(second_stage_ready),

    .dat_o(rd_resp_data_out),
    .valid_o(rd_resp_valid_out),
    .ready_o(rd_resp_ready_in)
);

// ############################################



// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// The RAM
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
sc_ram #(
    .ADDR_WIDTH(ADDR_WIDTH),
    .DATA_WIDTH(DATA_WIDTH)
) li_ram_storage (
    .clk(clk),

    .ena(1'b1),
    .enb(ram_rd),
    .wea(ram_wr),

    .addra(wr_addr_in),
    .addrb(rd_req_addr_in),
    
    .dia(wr_data_in),
    .dob(rd_data)
);

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


endmodule; /* li_ram */
