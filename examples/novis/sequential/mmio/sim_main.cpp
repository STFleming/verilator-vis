// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2017 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
//======================================================================

// Include common routines
#include <verilated.h>

// Include model header, generated from Verilating "top.v"
#include "Vtop_tb.h"

#include <queue>
#include <cstdint>

#include <sstream>
#include <queue>
#include <thread>

#include "sw_driver.h"

// Current simulation time (64-bit unsigned)
vluint64_t main_time = 0;
// Called by $time in Verilog
double sc_time_stamp() {
    return main_time;  // Note does conversion to real, to match SystemC
}

typedef struct {
	uint32_t addr;
	uint32_t data;
	uint8_t  wr;
	uint8_t  rd;
} mmio_cmd_t;

std::queue<mmio_cmd_t> mmio_cmd_q;

// structure of a read response message
typedef struct {
	uint32_t data;
} rd_resp_t; 

std::queue<rd_resp_t> read_resp_q;

// Used to write into the MMIO registers
void regWrite(uint32_t addr, uint32_t data) {
	mmio_cmd_t t;
	t.addr = addr;
	t.data = data;
	t.wr = 1;
	t.rd = 0;
	while(mmio_cmd_q.size() >= 10) {} // Make sure we don't over produce
	mmio_cmd_q.push(t);	
}

// Used to read from the MMIO registers
uint32_t regRead(uint32_t addr) {
	mmio_cmd_t t;
	t.addr = addr;
	t.data = 0;
	t.wr = 0;
	t.rd = 1;
	while(mmio_cmd_q.size() >= 10) {} // Make sure we don't over produce
	mmio_cmd_q.push(t);	

	// block until a read response is observed
	while(read_resp_q.empty()) {} 
	rd_resp_t resp = read_resp_q.front();
	read_resp_q.pop();
	return resp.data;
}

void loop_wrapper() {
    setup();
    while(true) {
	    loop();
    }	
}

int main(int argc, char** argv, char** env) {

    // Prevent unused variable warnings
    if (false && argc && argv && env) {}

    // Set debug level, 0 is off, 9 is highest presently used
    // May be overridden by commandArgs
    Verilated::debug(0);

    // Randomization reset policy
    // May be overridden by commandArgs
    Verilated::randReset(2);

    // Verilator must compute traced signals
    Verilated::traceEverOn(true);

    // Pass arguments so Verilated code can see them, e.g. $value$plusargs
    // This needs to be called before you create any model
    Verilated::commandArgs(argc, argv);

    // Create logs/ directory in case we have traces to put under it
    Verilated::mkdir("logs");

    // Construct the Verilated model, from Vtop.h generated from Verilating "top.v"
    Vtop_tb* top = new Vtop_tb;  // Or use a const unique_ptr, or the VL_UNIQUE_PTR wrapper

    // Set some inputs
    top->rst = 0;
    top->clk = 0;
    top->addr_in = 0;
    top->data_in = 0;
    top->wr_in = 0;
    top->rd_in = 0;

    std::thread loop_thread(loop_wrapper);


    // Simulate until $finish
    while (!Verilated::gotFinish()) {
        main_time++;  // Time passes...

        // Toggle a fast (time/2 period) clock
        top->clk = !top->clk;

        if (!top->clk) {

            // default case
            top->wr_in = 0;
            top->rd_in = 0;

            if (main_time > 1 && main_time < 10) {
                top->rst = 1;  // Assert reset
            } else {
                top->rst = 0;  // Deassert reset

		// We are no longer in reset, pull in mmio commands
		if(!mmio_cmd_q.empty()) {
			mmio_cmd_t t = mmio_cmd_q.front();
			mmio_cmd_q.pop();

			top->addr_in = t.addr;
			top->data_in = t.data;
			top->wr_in = t.wr;
			top->rd_in = t.rd;
		}

		// pull off any read responses
		if(top->rd_valid_out) {
			rd_resp_t r;
			r.data = top->data_out;
			read_resp_q.push(r);
		}
            }
        }


        // Evaluate model
        // (If you have multiple models being simulated in the same
        // timestep then instead of eval(), call eval_step() on each, then
        // eval_end_step() on each.)
        top->eval();

        if(main_time > 80) { // timeout the simulation
            fprintf(stderr, "\n\nERROR! The simulation timed out!\n\n\n");
            break;
        }

    }

    // Final model cleanup
    top->final();

    //  Coverage analysis (since test passed)
#if VM_COVERAGE
    Verilated::mkdir("logs");
    VerilatedCov::write("logs/coverage.dat");
#endif

    // Destroy model
    delete top;
    top = nullptr;

    // Fin
    exit(0);
}
