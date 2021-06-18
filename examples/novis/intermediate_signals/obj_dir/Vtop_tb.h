// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VTOP_TB_H_
#define VERILATED_VTOP_TB_H_  // guard

#include "verilated_heavy.h"
#include "verilated_cov.h"

//==========

class Vtop_tb__Syms;
class Vtop_tb_VerilatedVcd;


//----------

VL_MODULE(Vtop_tb) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    CData/*0:0*/ top_tb__DOT__tb_out1;
    CData/*0:0*/ top_tb__DOT__tb_out2;
    CData/*2:0*/ top_tb__DOT__cnt;
    CData/*0:0*/ top_tb__DOT__intermediate_signal_inst__DOT__internal_sig;
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ top_tb__DOT____Vtogcov__clk;
    CData/*0:0*/ top_tb__DOT____Vtogcov__rst;
    CData/*0:0*/ top_tb__DOT____Vtogcov__tb_in1;
    CData/*0:0*/ top_tb__DOT____Vtogcov__tb_in2;
    CData/*0:0*/ top_tb__DOT____Vtogcov__tb_in3;
    CData/*0:0*/ top_tb__DOT____Vtogcov__tb_out1;
    CData/*0:0*/ top_tb__DOT____Vtogcov__tb_out2;
    CData/*2:0*/ top_tb__DOT____Vtogcov__cnt;
    CData/*0:0*/ top_tb__DOT__intermediate_signal_inst__DOT____Vtogcov__internal_sig;
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vm_traceActivity[2];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vtop_tb__Syms* __VlSymsp;  // Symbol table
  private:
    // Coverage
    void __vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
        const char* hierp, const char* pagep, const char* commentp, const char* linescovp);
  public:
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vtop_tb);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vtop_tb(VerilatedContext* contextp, const char* name = "TOP");
    Vtop_tb(const char* name = "TOP")
      : Vtop_tb(nullptr, name) {}
    /// Destroy the model; called (often implicitly) by application code
    ~Vtop_tb();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    
    // API METHODS
    /// Return current simulation context for this model.
    /// Used to get to e.g. simulation time via contextp()->time()
    VerilatedContext* contextp();
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); eval_end_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
    static void _eval_initial_loop(Vtop_tb__Syms* __restrict vlSymsp);
    void _traceDump();
    void _traceDumpOpen();
    void _traceDumpClose();
    void __Vconfigure(Vtop_tb__Syms* symsp, bool first);
  private:
    static QData _change_request(Vtop_tb__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vtop_tb__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__2(Vtop_tb__Syms* __restrict vlSymsp);
  private:
    void _configure_coverage(Vtop_tb__Syms* __restrict vlSymsp, bool first) VL_ATTR_COLD;
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vtop_tb__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vtop_tb__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vtop_tb__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vtop_tb__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__4(Vtop_tb__Syms* __restrict vlSymsp);
    static void _settle__TOP__3(Vtop_tb__Syms* __restrict vlSymsp) VL_ATTR_COLD;
  private:
    static void traceChgSub0(void* userp, VerilatedVcd* tracep);
    static void traceChgTop0(void* userp, VerilatedVcd* tracep);
    static void traceCleanup(void* userp, VerilatedVcd* /*unused*/);
    static void traceFullSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceFullTop0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitTop(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    void traceRegister(VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
