// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop_tb.h for the primary calling header

#include "Vtop_tb.h"
#include "Vtop_tb__Syms.h"

//==========

Vtop_tb::Vtop_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModule{_vcname__}
 {
    Vtop_tb__Syms* __restrict vlSymsp = __VlSymsp = new Vtop_tb__Syms(_vcontextp__, this, name());
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vtop_tb::__Vconfigure(Vtop_tb__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    _configure_coverage(vlSymsp, first);
    vlSymsp->_vm_contextp__->timeunit(-12);
    vlSymsp->_vm_contextp__->timeprecision(-12);
}

Vtop_tb::~Vtop_tb() {
#ifdef VM_TRACE
    if (VL_UNLIKELY(__VlSymsp->__Vm_dumping)) _traceDumpClose();
#endif  // VM_TRACE
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = nullptr);
}

// Coverage
void Vtop_tb::__vlCoverInsert(uint32_t* countp, bool enable, const char* filenamep, int lineno, int column,
    const char* hierp, const char* pagep, const char* commentp, const char* linescovp) {
    uint32_t* count32p = countp;
    static uint32_t fake_zero_count = 0;
    if (!enable) count32p = &fake_zero_count;
    *count32p = 0;
    VL_COVER_INSERT(__VlSymsp->_vm_contextp__->coveragep(), count32p,  "filename",filenamep,  "lineno",lineno,  "column",column,
        "hier",std::string(name())+hierp,  "page",pagep,  "comment",commentp,  (linescovp[0] ? "linescov" : ""), linescovp);
}

void Vtop_tb::_initial__TOP__1(Vtop_tb__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_initial__TOP__1\n"); );
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    WData/*159:0*/ __Vtemp1[5];
    // Body
    if (VL_UNLIKELY((0U != VL_TESTPLUSARGS_I("trace")))) {
        VL_WRITEF("[%0t] Tracing to logs/vlt_dump.vcd...\n\n",
                  64,VL_TIME_UNITED_Q(1));
        __Vtemp1[0U] = 0x2e766364U;
        __Vtemp1[1U] = 0x64756d70U;
        __Vtemp1[2U] = 0x766c745fU;
        __Vtemp1[3U] = 0x6f67732fU;
        __Vtemp1[4U] = 0x6cU;
        vlSymsp->_vm_contextp__->dumpfile(VL_CVT_PACK_STR_NW(5, __Vtemp1));
        vlSymsp->TOPp->_traceDumpOpen();
        ++(vlSymsp->__Vcoverage[14]);
    } else {
        ++(vlSymsp->__Vcoverage[15]);
    }
    VL_WRITEF("[%0t] Model running...\n\n",64,VL_TIME_UNITED_Q(1));
    ++(vlSymsp->__Vcoverage[16]);
}

void Vtop_tb::_settle__TOP__3(Vtop_tb__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_settle__TOP__3\n"); );
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

void Vtop_tb::_eval_initial(Vtop_tb__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_eval_initial\n"); );
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vtop_tb::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::final\n"); );
    // Variables
    Vtop_tb__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vtop_tb::_eval_settle(Vtop_tb__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_eval_settle\n"); );
    Vtop_tb* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__3(vlSymsp);
    vlTOPp->__Vm_traceActivity[1U] = 1U;
    vlTOPp->__Vm_traceActivity[0U] = 1U;
}

void Vtop_tb::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst = VL_RAND_RESET_I(1);
    top_tb__DOT__tb_out1 = VL_RAND_RESET_I(1);
    top_tb__DOT__tb_out2 = VL_RAND_RESET_I(1);
    top_tb__DOT__cnt = VL_RAND_RESET_I(3);
    top_tb__DOT____Vtogcov__clk = VL_RAND_RESET_I(1);
    top_tb__DOT____Vtogcov__rst = VL_RAND_RESET_I(1);
    top_tb__DOT____Vtogcov__tb_in1 = VL_RAND_RESET_I(1);
    top_tb__DOT____Vtogcov__tb_in2 = VL_RAND_RESET_I(1);
    top_tb__DOT____Vtogcov__tb_in3 = VL_RAND_RESET_I(1);
    top_tb__DOT____Vtogcov__tb_out1 = VL_RAND_RESET_I(1);
    top_tb__DOT____Vtogcov__tb_out2 = VL_RAND_RESET_I(1);
    top_tb__DOT____Vtogcov__cnt = VL_RAND_RESET_I(3);
    top_tb__DOT__intermediate_signal_inst__DOT__internal_sig = VL_RAND_RESET_I(1);
    top_tb__DOT__intermediate_signal_inst__DOT____Vtogcov__internal_sig = VL_RAND_RESET_I(1);
    for (int __Vi0=0; __Vi0<2; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }
}

void Vtop_tb::_configure_coverage(Vtop_tb__Syms* __restrict vlSymsp, bool first) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop_tb::_configure_coverage\n"); );
    // Body
    if (false && vlSymsp && first) {}  // Prevent unused
    __vlCoverInsert(&(vlSymsp->__Vcoverage[0]), first, "top_tb.sv", 27, 11, ".top_tb", "v_toggle/top_tb", "clk", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[1]), first, "top_tb.sv", 28, 11, ".top_tb", "v_toggle/top_tb", "rst", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[2]), first, "top_tb.sv", 34, 10, ".top_tb", "v_toggle/top_tb", "tb_in1", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[3]), first, "top_tb.sv", 35, 10, ".top_tb", "v_toggle/top_tb", "tb_in2", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[4]), first, "top_tb.sv", 36, 10, ".top_tb", "v_toggle/top_tb", "tb_in3", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[5]), first, "top_tb.sv", 38, 10, ".top_tb", "v_toggle/top_tb", "tb_out1", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "top_tb.sv", 39, 10, ".top_tb", "v_toggle/top_tb", "tb_out2", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[7]), first, "top_tb.sv", 44, 16, ".top_tb", "v_toggle/top_tb", "cnt[0]", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[8]), first, "top_tb.sv", 44, 16, ".top_tb", "v_toggle/top_tb", "cnt[1]", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[9]), first, "top_tb.sv", 44, 16, ".top_tb", "v_toggle/top_tb", "cnt[2]", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[10]), first, "top_tb.sv", 47, 2, ".top_tb", "v_branch/top_tb", "if", "47-48");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[11]), first, "top_tb.sv", 47, 3, ".top_tb", "v_branch/top_tb", "else", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[12]), first, "top_tb.sv", 45, 4, ".top_tb", "v_line/top_tb", "block", "45-46");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[13]), first, "top_tb.sv", 67, 4, ".top_tb", "v_line/top_tb", "block", "67-68");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[14]), first, "top_tb.sv", 74, 7, ".top_tb", "v_branch/top_tb", "if", "74-77");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[15]), first, "top_tb.sv", 74, 8, ".top_tb", "v_branch/top_tb", "else", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[16]), first, "top_tb.sv", 73, 4, ".top_tb", "v_line/top_tb", "block", "73,79");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[2]), first, "top_tb.sv", 7, 14, ".top_tb.intermediate_signal_inst", "v_toggle/intermediate_signal", "in_1", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[3]), first, "top_tb.sv", 8, 14, ".top_tb.intermediate_signal_inst", "v_toggle/intermediate_signal", "in_2", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[4]), first, "top_tb.sv", 9, 14, ".top_tb.intermediate_signal_inst", "v_toggle/intermediate_signal", "in_3", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[5]), first, "top_tb.sv", 12, 15, ".top_tb.intermediate_signal_inst", "v_toggle/intermediate_signal", "out_1", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[6]), first, "top_tb.sv", 13, 15, ".top_tb.intermediate_signal_inst", "v_toggle/intermediate_signal", "out_2", "");
    __vlCoverInsert(&(vlSymsp->__Vcoverage[17]), first, "top_tb.sv", 17, 7, ".top_tb.intermediate_signal_inst", "v_toggle/intermediate_signal", "internal_sig", "");
}
