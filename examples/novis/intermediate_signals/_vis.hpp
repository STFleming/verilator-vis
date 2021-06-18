// Automatically generated file for parsing the visualisation struct in the C++ tb
#include <cstdint>
#include <cstdio>
#include <verilated.h>


class VisParser {
public:
uint64_t rd_data;
uint64_t rd_valid;
uint64_t wr_data;
uint64_t wr_valid;

 VisParser(WData* data) {
		rd_data = ((uint64_t)(data[7]) << 32) | data[6];
		rd_valid = ((uint64_t)(data[5]) << 32) | data[4];
		wr_data = ((uint64_t)(data[3]) << 32) | data[2];
		wr_valid = ((uint64_t)(data[1]) << 32) | data[0];
  }

 void json(std::string &str) { // render the output as JSON
str.append("{\n");
str.append("\t\t\"fifo_vis\": {\n");
str.append("\t\t\"read\": {\n");
	str.append("\t\"rd_data\": " + std::to_string(rd_data));
	str.append(",\n");
	str.append("\t\"rd_valid\": " + std::to_string(rd_valid));
	str.append("\n");
	str.append("},\n");
str.append("\t\t\"write\": {\n");
	str.append("\t\"wr_data\": " + std::to_string(wr_data));
	str.append(",\n");
	str.append("\t\"wr_valid\": " + std::to_string(wr_valid));
	str.append("\n");
	str.append("}\n");
str.append("}\n");
str.append("}\n");
  }
private:
};
// total number of signals = 4
