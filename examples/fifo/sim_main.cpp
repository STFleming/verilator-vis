// DESCRIPTION: Verilator: Verilog example module
//
// This file ONLY is placed under the Creative Commons Public Domain, for
// any use, without warranty, 2017 by Wilson Snyder.
// SPDX-License-Identifier: CC0-1.0
//======================================================================

// Include common routines
#include <verilated.h>

// Include model header, generated from Verilating "top.v"
#include "Vfifo_tb.h"

#include <queue>
#include <cstdint>

#include "visualiser.hpp"
#include "controller.hpp"

#include "_vis.hpp" // auto-generated, takes the raw bits from the port and re-renders it as a JSON object for the web-fe

#include <sstream>

// Current simulation time (64-bit unsigned)
vluint64_t main_time = 0;
// Called by $time in Verilog
double sc_time_stamp() {
    return main_time;  // Note does conversion to real, to match SystemC
}

int main(int argc, char** argv, char** env) {
    // This is a more complicated example, please also see the simpler examples/make_hello_c.

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
    Vfifo_tb* top = new Vfifo_tb;  // Or use a const unique_ptr, or the VL_UNIQUE_PTR wrapper

    // Set some inputs
    top->rst = 0;
    top->clk = 0;

    // Set the write channel to 0 initially
    top->wr_data_in = 0;
    top->wr_valid_in = 0;
    top->rd_ready_in = 0;

    uint32_t wrdata = 0;

    Visualiser vis("ws://localhost:1234");
    Controller cntrl(&vis);

    // Simulate until $finish
    while (!Verilated::gotFinish()) {
        main_time++;  // Time passes...

        // Toggle a fast (time/2 period) clock
        top->clk = !top->clk;

        if (!top->clk) {
            if (main_time > 1 && main_time < 10) {
                top->rst = 1;  // Assert reset
            } else {
                top->rst = 0;  // Deassert reset
            }

            // Write to the fifo 
            if(top->wr_ready_out == 1) {
                top->wr_valid_in = 1;
                top->wr_data_in = wrdata++;
            } else {
                top->wr_valid_in = 0;
            }

            // Always be ready to read the data (auto-consume)
            top->rd_ready_in = 1;

	        // examine the visualisation port and pull the state of the system out
            VisParser   vis_json(top->vis_out); 
            std::string state_json;
            vis_json.json(state_json);
            vis.send(state_json);
	    
        }

        if(cntrl.tick()){
                fprintf(stderr, "Received the end signal from the frontend.\n");
                break;
        }


        // Evaluate model
        // (If you have multiple models being simulated in the same
        // timestep then instead of eval(), call eval_step() on each, then
        // eval_end_step() on each.)
        top->eval();

        if(main_time > 5000) { // timeout the simulation
            fprintf(stderr, "\n\nERROR! The simulation timed out!\n\n\n");
            break;
        }

    }

    // Tell the frontend that we are done
    vis.halt();

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
