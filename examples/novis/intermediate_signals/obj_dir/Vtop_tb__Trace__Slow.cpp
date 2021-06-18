// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop_tb__Syms.h"


//======================

void Vtop_tb::_traceDump() {
    const VerilatedLockGuard lock(__VlSymsp->__Vm_dumperMutex);
    __VlSymsp->__Vm_dumperp->dump(VL_TIME_Q());
}
void Vtop_tb::_traceDumpOpen() {
    const VerilatedLockGuard lock(__VlSymsp->__Vm_dumperMutex);
    if (VL_UNLIKELY(!__VlSymsp->__Vm_dumperp)) {
        __VlSymsp->__Vm_dumperp = new VerilatedVcdC();
        trace(__VlSymsp->__Vm_dumperp, 0, 0);
        std::string dumpfile = __VlSymsp->_vm_contextp__->dumpfile();
        __VlSymsp->__Vm_dumperp->open(dumpfile.c_str());
        __VlSymsp->__Vm_dumping = true;
    }
}
void Vtop_tb::_traceDumpClose() {
    const VerilatedLockGuard lock(__VlSymsp->__Vm_dumperMutex);
    __VlSymsp->__Vm_dumping = false;
    VL_DO_CLEAR(delete __VlSymsp->__Vm_dumperp, __VlSymsp->__Vm_dumperp = nullptr);
}
void Vtop_tb::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vtop_tb::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vtop_tb__Syms* __restrict vlSymsp = static_cast<Vtop_tb__Syms*>(userp);
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vtop_tb::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vtop_tb::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vtop_tb__Syms* __restrict vlSymsp = static_cast<Vtop_tb__Syms*>(userp);
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vtop_tb::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vtop_tb__Syms* __restrict vlSymsp = static_cast<Vtop_tb__Syms*>(userp);
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+8,"clk", false,-1);
        tracep->declBit(c+9,"rst", false,-1);
        tracep->declBit(c+8,"top_tb clk", false,-1);
        tracep->declBit(c+9,"top_tb rst", false,-1);
        tracep->declBit(c+1,"top_tb tb_in1", false,-1);
        tracep->declBit(c+2,"top_tb tb_in2", false,-1);
        tracep->declBit(c+3,"top_tb tb_in3", false,-1);
        tracep->declBit(c+4,"top_tb tb_out1", false,-1);
        tracep->declBit(c+5,"top_tb tb_out2", false,-1);
        tracep->declBus(c+6,"top_tb cnt", false,-1, 2,0);
        tracep->declBit(c+1,"top_tb intermediate_signal_inst in_1", false,-1);
        tracep->declBit(c+2,"top_tb intermediate_signal_inst in_2", false,-1);
        tracep->declBit(c+3,"top_tb intermediate_signal_inst in_3", false,-1);
        tracep->declBit(c+4,"top_tb intermediate_signal_inst out_1", false,-1);
        tracep->declBit(c+5,"top_tb intermediate_signal_inst out_2", false,-1);
        tracep->declBit(c+7,"top_tb intermediate_signal_inst internal_sig", false,-1);
    }
}

void Vtop_tb::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vtop_tb::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vtop_tb__Syms* __restrict vlSymsp = static_cast<Vtop_tb__Syms*>(userp);
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vtop_tb::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vtop_tb__Syms* __restrict vlSymsp = static_cast<Vtop_tb__Syms*>(userp);
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,((1U & (IData)(vlTOPp->top_tb__DOT__cnt))));
        tracep->fullBit(oldp+2,((1U & ((IData)(vlTOPp->top_tb__DOT__cnt) 
                                       >> 1U))));
        tracep->fullBit(oldp+3,((1U & ((IData)(vlTOPp->top_tb__DOT__cnt) 
                                       >> 2U))));
        tracep->fullBit(oldp+4,(vlTOPp->top_tb__DOT__tb_out1));
        tracep->fullBit(oldp+5,(vlTOPp->top_tb__DOT__tb_out2));
        tracep->fullCData(oldp+6,(vlTOPp->top_tb__DOT__cnt),3);
        tracep->fullBit(oldp+7,(vlTOPp->top_tb__DOT__intermediate_signal_inst__DOT__internal_sig));
        tracep->fullBit(oldp+8,(vlTOPp->clk));
        tracep->fullBit(oldp+9,(vlTOPp->rst));
    }
}
