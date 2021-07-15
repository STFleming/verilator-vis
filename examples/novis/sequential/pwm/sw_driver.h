// Arduino-like software driver for the custom MMIO interface 
//
//  author: stf

extern void regWrite(uint32_t addr, uint32_t data); 
extern uint32_t regRead(uint32_t addr); 
extern void exit();

uint32_t val;
uint32_t res;

// runs once on startup
void setup() {

	// setup the config reg
	uint32_t config_reg = 0;
	config_reg |= 2; // divval
	config_reg |= (1024 << 16); // max cnt 
	regWrite(0xBBBB0000, config_reg);	

	// setup the high and low points
	uint32_t cmp_levels = 0;
	cmp_levels |= 0; // lpoint
	cmp_levels |= (512 << 16); // hpoint
	regWrite(0xBBBB0004, cmp_levels);

}

// runs continuously
void loop() {
	bool fin = false;
	while (!fin) {
		uint32_t clk_cnt;
		clk_cnt = regRead(0xBBBBFFFF);
		if(clk_cnt >= 20000) {
			fin = true;
		}
	}
	exit();
}

