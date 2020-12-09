// RenderCpp : this file takes the description of the visualisation struct and renders a CPP parser for it.
//
// author: stf
#pragma once

#include <cstdint>
#include <cstdio>

#include "VisStruct.hpp"
#include "VisSignal.hpp"

class RenderCpp {
    public:
	RenderCpp(FILE *cppfp, VisStruct s) {
		m_top = s;
		m_cppfp = cppfp;
		m_total_signals = 0;

		fprintf(m_cppfp, "// Automatically generated file for parsing the visualisation struct in the C++ tb\n");
		fprintf(m_cppfp, "#include <cstdint>\n");
		fprintf(m_cppfp, "#include <cstdio>\n");
		fprintf(m_cppfp, "#include <verilated.h>\n");
		fprintf(m_cppfp, "\n\n");

		fprintf(m_cppfp, "class VisParser {\n");
		fprintf(m_cppfp, "public:\n");

		cpp_decl(m_top);

		constructor(); // renders the constructor which captures the data

		json(); // renders the json printing function

		fprintf(m_cppfp, "private:\n");
		fprintf(m_cppfp, "};\n");

		fprintf(m_cppfp, "// total number of signals = %u\n", m_total_signals);
	}

	~RenderCpp() {
		fclose(m_cppfp);
	}
	
	// recursively walk through the struct and generate the signal declarations
	void cpp_decl(VisStruct s){
		m_total_signals += s.cpp_decl(m_cppfp);
		for(VisStruct::iterator sin=s.begin(); sin != s.end(); ++sin){
			VisStruct t = (*sin).second;
			cpp_decl(t);
		}
	}	


	// generates the constructor
	void constructor() {
		fprintf(m_cppfp,"\n VisParser(WData* data) {\n"); 
		constructor_walk(m_top, m_total_signals);
		fprintf(m_cppfp, "  }\n\n");
	}

	// recursively walks over the signals to get the right data
	uint32_t constructor_walk(VisStruct s, uint32_t curr_idx){
		uint32_t idx = curr_idx;  
		idx = s.cpp_capture_stmt(m_cppfp, idx);
		for(VisStruct::iterator sin=s.begin(); sin != s.end(); ++sin) {
			VisStruct t = (*sin).second;
			idx = constructor_walk(t, idx);
		}
		return idx;
	}

	// generates the function that produces the json
	void json() {
		fprintf(m_cppfp, " void json(std::string &str) { // render the output as JSON\n"); 
	    json_walk(m_top);	
		fprintf(m_cppfp, "  }\n");
	}

	void json_walk(VisStruct s){
		fprintf(m_cppfp, "str.append(\"{\\n\");\n");
		s.jsonStr(m_cppfp);
		fprintf(m_cppfp, "str.append(\"}\\n\");\n");
		fprintf(m_cppfp, "str.append(\"}\\n\");\n");
	}


    private: 
	uint32_t m_total_signals;
	VisStruct m_top;

	FILE *m_cppfp;

};
