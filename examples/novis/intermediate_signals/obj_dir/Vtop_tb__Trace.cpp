// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop_tb__Syms.h"


void Vtop_tb::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vtop_tb__Syms* __restrict vlSymsp = static_cast<Vtop_tb__Syms*>(userp);
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vtop_tb::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vtop_tb__Syms* __restrict vlSymsp = static_cast<Vtop_tb__Syms*>(userp);
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        if (VL_UNLIKELY(vlTOPp->__Vm_traceActivity[1U])) {
            tracep->chgBit(oldp+0,((1U & (IData)(vlTOPp->top_tb__DOT__cnt))));
            tracep->chgBit(oldp+1,((1U & ((IData)(vlTOPp->top_tb__DOT__cnt) 
                                          >> 1U))));
            tracep->chgBit(oldp+2,((1U & ((IData)(vlTOPp->top_tb__DOT__cnt) 
                                          >> 2U))));
            tracep->chgBit(oldp+3,(vlTOPp->top_tb__DOT__tb_out1));
            tracep->chgBit(oldp+4,(vlTOPp->top_tb__DOT__tb_out2));
            tracep->chgCData(oldp+5,(vlTOPp->top_tb__DOT__cnt),3);
            tracep->chgBit(oldp+6,(vlTOPp->top_tb__DOT__intermediate_signal_inst__DOT__internal_sig));
        }
        tracep->chgBit(oldp+7,(vlTOPp->clk));
        tracep->chgBit(oldp+8,(vlTOPp->rst));
    }
}

void Vtop_tb::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vtop_tb__Syms* __restrict vlSymsp = static_cast<Vtop_tb__Syms*>(userp);
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
        vlTOPp->__Vm_traceActivity[1U] = 0U;
    }
}
