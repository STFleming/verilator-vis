// Arduino-like software driver for the custom MMIO interface 
//
//  author: stf

extern void regWrite(uint32_t addr, uint32_t data); 

uint32_t val;

// runs once on startup
void setup() {
        val = 32;
}

// runs continuously
void loop() {
        regWrite(0x00010008, val++);
}

