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

// Used to write into the MMIO registers
void regWrite(uint32_t addr, uint32_t data) {
	mmio_cmd_t t;
	t.addr = addr;
	t.data = data;
	t.wr = 1;
	t.rd = 0;
	mmio_cmd_q.push(t);	
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

    regWrite(0x0001008, 56); 

    // Simulate until $finish
    while (!Verilated::gotFinish()) {
        main_time++;  // Time passes...

	top->addr_in = 0x00010004;
	top->data_in = 42;
	top->wr_in = 0;
	top->rd_in = 0;

        // Toggle a fast (time/2 period) clock
        top->clk = !top->clk;

        if (!top->clk) {
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
