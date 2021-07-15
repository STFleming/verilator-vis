// PWM module
//
// author: stf

module pwm (
	input logic clk,
	input logic rst,

	input logic [31:0] config_in,
	input logic [31:0] comp_levels_in,

	output logic pwm_out

);

// config signals
logic [15:0] divval;
logic [15:0] maxcnt;

assign divval = config_in[15:0];
assign maxcnt = config_in[31:16];

// -------------------------------------
//    Clock divider stage
//
//    There might be a nicer way to do 
//    this, but this is the simplest
//    I could think of.
// -------------------------------------
logic divclk;
logic [15:0] divclk_cnt; // internal counter for the clock divider

always @(posedge clk) begin
	if(divclk_cnt >= divval) begin
		divclk <= !divclk;
		divclk_cnt <= 16'd0;
	end else begin
		divclk_cnt <= divclk_cnt + 16'd1;
	end

	if (rst) begin
		divclk <= 1'b0;
		divclk_cnt <= 16'd0;
	end
end
// -------------------------------------
//     End of clock divider stage
// -------------------------------------

// -------------------------------------
//     divclk posedge detector 
//	
//	Create a pulse on a divclk posedge
// -------------------------------------
logic divclk_ff;
always_ff @(posedge clk) begin
	divclk_ff <= divclk;
end

logic divclk_posedge; // will be high for exactly 1 cycle on a posedge
assign divclk_posedge = divclk && !divclk_ff;
// -------------------------------------

// -------------------------------------
//     Timer Counter 
//
//     count the number of divclk posedges
// -------------------------------------
logic [15:0] timer_cnt; // internal signal tracking the count of the timer circuit

// clock this with clk so that the reset signal works correctly
always @(posedge clk) begin
	if (divclk_posedge) begin
		if (timer_cnt >= maxcnt) begin
			timer_cnt <= 16'd0;
		end else begin
			timer_cnt <= timer_cnt + 16'd1;
		end
	end

	if (rst) begin
		timer_cnt <= 16'd0;
	end
end
// -------------------------------------
//   end of timer counter block
// -------------------------------------


// -------------------------------------
//	Comparator module
// -------------------------------------
// internal comparator level signals
logic [15:0] lpoint;
logic [15:0] hpoint;

assign lpoint = comp_levels_in[15:0];
assign hpoint = comp_levels_in[31:16];

always_ff @(posedge clk) begin
	if  (pwm_out && (timer_cnt == lpoint)) begin
		pwm_out <= 1'b0;
	end

	if (!pwm_out && (timer_cnt == hpoint)) begin
		pwm_out <= 1'b1;
	end

	if (rst) begin
		pwm_out <= 1'b0;
	end
end
// -------------------------------------

endmodule /* pwm */


