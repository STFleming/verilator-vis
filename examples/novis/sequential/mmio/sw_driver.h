// Arduino-like software driver for the custom MMIO interface 
//
//  author: stf

extern void regWrite(uint32_t addr, uint32_t data); 
extern uint32_t regRead(uint32_t addr); 

uint32_t val;
uint32_t res;

// runs once on startup
void setup() {
        val = 32;
}

// runs continuously
void loop() {
        regWrite(0xbeef0004, val++);
	res = regRead(0xbeef0004);
}

