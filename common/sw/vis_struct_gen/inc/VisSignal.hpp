// VisSignal class
//
// This is a signal within a VisStruct class
#pragma once

#include <cstdint>
#include <string>

#define MAX_BITWIDTH 64 

class VisSignal {

    public:
        VisSignal(){

	}

        VisSignal(std::string name, uint32_t width) {
            m_width = width;
	    m_name = name;
	}

	std::string name() {
            return m_name;
	}

	void name(std::string n) {
            m_name = n;
	}

    void print(FILE *fp) {
            fprintf(fp, "signal: %s width: %u\n", m_name.c_str(), m_width);	
	}

	void verilog(FILE *fp) {
            if(m_width > MAX_BITWIDTH) {
                fprintf(stderr, "Error! max bitwidth size currently supported is %u bits\n", MAX_BITWIDTH);
                exit(-1);
            }
            if(m_width != MAX_BITWIDTH) {
                fprintf(fp, "\tlogic[%u:0] %s_padding_bits;\n", (MAX_BITWIDTH-m_width)-1, m_name.c_str());
            }
            fprintf(fp, "\tlogic[%u:0] %s;\n\n", m_width-1, m_name.c_str());
	}


	// cpp decl
	uint32_t cpp_decl(FILE *fp) {
		fprintf(fp, "uint64_t %s;\n", m_name.c_str());
		return 1; // returns the nubmer of signals added
	}


	// cpp capture statement (line that captures the data)
	uint32_t cpp_capture_stmt(FILE *fp, uint32_t curr_idx){
		fprintf(fp, "\t\t%s = ((uint64_t)(data[%u]) << 32) | data[%u];\n", m_name.c_str(), (curr_idx*2)-1, (curr_idx*2)-2);
	       return curr_idx - 1;	
	}


	// renders the json for this signal
    void json(FILE *fp){
                fprintf(fp,     "\tfprintf(fp, \"{\\n\");\n"     );
                fprintf(fp,     "\tfprintf(fp, \"\\t\\\"name\\\": \\\"%s\\\",\\n\" );\n"  , m_name.c_str());
                fprintf(fp,     "\tfprintf(fp, \"\\t\\\"value\\\": %%lu \\n\", %s );\n"  , m_name.c_str());
        }

	// renders the json for this signal
    void jsonStr(FILE *fp){
                fprintf(fp,     "\tstr.append(\"\\t\\\"%s\\\": \" + std::to_string(%s));\n", m_name.c_str(), m_name.c_str());
        }



    private:
        uint32_t m_width;
	std::string m_name;
};
