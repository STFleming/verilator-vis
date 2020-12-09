// Library for a riscv instruction -- takes the raw bits and then unpacks it
//  THIS IS NOT CURRENTLY A REAL RISCV INSTRUCTION -- just a pseudo one
//
// author: stf


class riscvInst {

    constructor(op_code, sr_1, sr_2, dest_r) {
        this.op = this.op2str(op_code);
        this.sr1 = String(sr_1); 
        this.sr2 = String(sr_2); 
        this.dest = String(dest_r);
    }

    op2str(op_code) {
        switch(op_code) {
            case 0:
                return "ADD";
            case 1:
                return "SUB";
            case 3:
                return "LOAD";
            case 4:
                return "STORE";
            case 5:
                return "BRANCHI";
            case 127:
                return "HALT";
        }
    }

    toString() {
        return this.op + " " + this.sr1 + " " + this.sr2 + " " + this.dest;
    }

    isBranch() { return (this.op == "BRANCHI");; } 

}
