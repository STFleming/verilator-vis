// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop_tb.h for the primary calling header

#include "Vtop_tb.h"
#include "Vtop_tb__Syms.h"

//==========

VerilatedContext* Vtop_tb::contextp() {
    return __VlSymsp->_vm_contextp__;
}

void Vtop_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtop_tb::eval\n"); );
    Vtop_tb__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("top_tb.sv", 26, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vtop_tb::eval_end_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+eval_end_step Vtop_tb::eval_end_step\n"); );
#ifdef VM_TRACE
    Vtop_tb__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Tracing
    if (VL_UNLIKELY(vlSymsp->__Vm_dumping)) _traceDump();
#endif  // VM_TRACE
}

void Vtop_tb::_eval_initial_loop(Vtop_tb__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("top_tb.sv", 26, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vtop_tb::_combo__TOP__2(Vtop_tb__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_combo__TOP__2\n"); );
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk) ^ vlTOPp->top_tb__DOT____Vtogcov__clk)) {
        ++(vlSymsp->__Vcoverage[0]);
        vlTOPp->top_tb__DOT____Vtogcov__clk = vlTOPp->clk;
    }
    if (((IData)(vlTOPp->rst) ^ vlTOPp->top_tb__DOT____Vtogcov__rst)) {
        ++(vlSymsp->__Vcoverage[1]);
        vlTOPp->top_tb__DOT____Vtogcov__rst = vlTOPp->rst;
    }
}

VL_INLINE_OPT void Vtop_tb::_sequent__TOP__4(Vtop_tb__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_sequent__TOP__4\n"); );
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    ++(vlSymsp->__Vcoverage[13]);
    VL_WRITEF("tb_out1 = %1#  tb_out2 = %1#\n",1,vlTOPp->top_tb__DOT__tb_out1,
              1,(IData)(vlTOPp->top_tb__DOT__tb_out2));
    ++(vlSymsp->__Vcoverage[12]);
    vlTOPp->top_tb__DOT__cnt = (7U & ((IData)(1U) + (IData)(vlTOPp->top_tb__DOT__cnt)));
    if (vlTOPp->rst) {
        ++(vlSymsp->__Vcoverage[10]);
        vlTOPp->top_tb__DOT__cnt = 0U;
    } else {
        ++(vlSymsp->__Vcoverage[11]);
    }
    if ((1U & ((IData)(vlTOPp->top_tb__DOT__cnt) ^ vlTOPp->top_tb__DOT____Vtogcov__tb_in1))) {
        ++(vlSymsp->__Vcoverage[2]);
        vlTOPp->top_tb__DOT____Vtogcov__tb_in1 = (1U 
                                                  & (IData)(vlTOPp->top_tb__DOT__cnt));
    }
    if ((1U & (((IData)(vlTOPp->top_tb__DOT__cnt) >> 1U) 
               ^ vlTOPp->top_tb__DOT____Vtogcov__tb_in2))) {
        ++(vlSymsp->__Vcoverage[3]);
        vlTOPp->top_tb__DOT____Vtogcov__tb_in2 = (1U 
                                                  & ((IData)(vlTOPp->top_tb__DOT__cnt) 
                                                     >> 1U));
    }
    if ((1U & (((IData)(vlTOPp->top_tb__DOT__cnt) >> 2U) 
               ^ vlTOPp->top_tb__DOT____Vtogcov__tb_in3))) {
        ++(vlSymsp->__Vcoverage[4]);
        vlTOPp->top_tb__DOT____Vtogcov__tb_in3 = (1U 
                                                  & ((IData)(vlTOPp->top_tb__DOT__cnt) 
                                                     >> 2U));
    }
    if ((1U & ((IData)(vlTOPp->top_tb__DOT__cnt) ^ vlTOPp->top_tb__DOT____Vtogcov__cnt))) {
        ++(vlSymsp->__Vcoverage[7]);
        vlTOPp->top_tb__DOT____Vtogcov__cnt = ((6U 
                                                & (IData)(vlTOPp->top_tb__DOT____Vtogcov__cnt)) 
                                               | (1U 
                                                  & (IData)(vlTOPp->top_tb__DOT__cnt)));
    }
    if ((2U & ((IData)(vlTOPp->top_tb__DOT__cnt) ^ vlTOPp->top_tb__DOT____Vtogcov__cnt))) {
        ++(vlSymsp->__Vcoverage[8]);
        vlTOPp->top_tb__DOT____Vtogcov__cnt = ((5U 
                                                & (IData)(vlTOPp->top_tb__DOT____Vtogcov__cnt)) 
                                               | (2U 
                                                  & (IData)(vlTOPp->top_tb__DOT__cnt)));
    }
    if ((4U & ((IData)(vlTOPp->top_tb__DOT__cnt) ^ vlTOPp->top_tb__DOT____Vtogcov__cnt))) {
        ++(vlSymsp->__Vcoverage[9]);
        vlTOPp->top_tb__DOT____Vtogcov__cnt = ((3U 
                                                & (IData)(vlTOPp->top_tb__DOT____Vtogcov__cnt)) 
                                               | (4U 
                                                  & (IData)(vlTOPp->top_tb__DOT__cnt)));
    }
    vlTOPp->top_tb__DOT__intermediate_signal_inst__DOT__internal_sig 
        = (1U & ((IData)(vlTOPp->top_tb__DOT__cnt) 
                 & ((IData)(vlTOPp->top_tb__DOT__cnt) 
                    >> 1U)));
    if (((IData)(vlTOPp->top_tb__DOT__intermediate_signal_inst__DOT__internal_sig) 
         ^ vlTOPp->top_tb__DOT__intermediate_signal_inst__DOT____Vtogcov__internal_sig)) {
        ++(vlSymsp->__Vcoverage[17]);
        vlTOPp->top_tb__DOT__intermediate_signal_inst__DOT____Vtogcov__internal_sig 
            = vlTOPp->top_tb__DOT__intermediate_signal_inst__DOT__internal_sig;
    }
    vlTOPp->top_tb__DOT__tb_out1 = ((IData)(vlTOPp->top_tb__DOT__intermediate_signal_inst__DOT__internal_sig) 
                                    & ((IData)(vlTOPp->top_tb__DOT__cnt) 
                                       >> 2U));
    vlTOPp->top_tb__DOT__tb_out2 = (1U & ((IData)(vlTOPp->top_tb__DOT__intermediate_signal_inst__DOT__internal_sig) 
                                          | ((IData)(vlTOPp->top_tb__DOT__cnt) 
                                             >> 2U)));
    if (((IData)(vlTOPp->top_tb__DOT__tb_out1) ^ vlTOPp->top_tb__DOT____Vtogcov__tb_out1)) {
        ++(vlSymsp->__Vcoverage[5]);
        vlTOPp->top_tb__DOT____Vtogcov__tb_out1 = vlTOPp->top_tb__DOT__tb_out1;
    }
    if (((IData)(vlTOPp->top_tb__DOT__tb_out2) ^ vlTOPp->top_tb__DOT____Vtogcov__tb_out2)) {
        ++(vlSymsp->__Vcoverage[6]);
        vlTOPp->top_tb__DOT____Vtogcov__tb_out2 = vlTOPp->top_tb__DOT__tb_out2;
    }
}

void Vtop_tb::_eval(Vtop_tb__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_eval\n"); );
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
        vlTOPp->__Vm_traceActivity[1U] = 1U;
    }
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

VL_INLINE_OPT QData Vtop_tb::_change_request(Vtop_tb__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_change_request\n"); );
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vtop_tb::_change_request_1(Vtop_tb__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_change_request_1\n"); );
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vtop_tb::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
