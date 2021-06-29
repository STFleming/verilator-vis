// Software driver file
//
// author: stf

class SwDriver {
	public:
		// simulate arduino like setup and loop functions
		void loop();
		void setup(); 

		void regWrite(uint32_t addr, uint32_t data); 
		uint32_t regRead(uint32_t addr);

	private: 

		

}
