// Infers a dual-port single clock block RAM
// For Xilinx devices taken from UG901 page 118
//
// Port A = write port
// Port B = read port
//
// author: stf

module sc_ram #(
    parameter ADDR_WIDTH=8, 
    parameter DATA_WIDTH=16
)
(

    input logic clk,
    input logic ena,
    input logic enb,
    input logic wea,

    input logic [ADDR_WIDTH-1:0] addra,
    input logic [ADDR_WIDTH-1:0] addrb,

    input logic [DATA_WIDTH-1:0] dia,
    output logic [DATA_WIDTH-1:0] dob
);

logic [DATA_WIDTH-1:0] ram [2**ADDR_WIDTH-1:0];

// PORT A -- write port
always @(posedge clk) begin
    if (ena) begin
        if (wea) begin
            ram[addra] <= dia;
        end
    end
end

// PORT B -- read port
always @(posedge clk) begin
    if (enb) begin
        dob <= ram[addrb];
    end
end


endmodule /* sc_ram */
