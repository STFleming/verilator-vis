// visualisation structure class
//
// created from a json description, this is rendered into C++ and Sv
//
// author: stf

#pragma once

#include <map>
#include <cstdint>
#include <string>

#include "VisSignal.hpp"

class VisStruct {
    public:
	    VisStruct() {
                 m_name = "";
	    }

	    VisStruct(std::string name){
                m_name = name;
	    }

            void add(VisSignal s) {
                m_signals[s.name()] = s;
	    }

	    void add(VisStruct s) {
                m_substructs[s.name()] = s;
	    }

            std::string name() {
                return m_name;
	    }

	    void name(std::string n) {
                 m_name = n;
	    }

	    void print(FILE *fp) {
		 fprintf(fp, "struct: %s\n", m_name.c_str()); 
		 fprintf(fp, "\tsignals:\n");
                 for(auto psig: m_signals){
                     psig.second.print(fp);
		 }
		 fprintf(fp, "\tstructs:\n");
		 for(auto pstruct: m_substructs) {
                     fprintf(fp, "substruct: %s\n", pstruct.first.c_str());
		 }
	    }

	    // prints just the verilog signature for this struct
        void verilog_sig(FILE *fp) {
                fprintf(fp, "\t%s_dvis_t %s;\n", m_name.c_str(), m_name.c_str());
	    }

        void verilog(FILE *fp) {
                 fprintf(fp, "typedef struct packed {\n");
                 for(auto psig: m_signals){
                     psig.second.verilog(fp);
		         }
		         for(auto pstruct: m_substructs) {
                             pstruct.second.verilog_sig(fp);
		         }
		         fprintf(fp, "} %s_dvis_t;\n\n", m_name.c_str());
	    }

	// render the declaration of the cpp signals -- returns the nubmer of signals declared
	 uint32_t cpp_decl(FILE *fp) {
		uint32_t count = 0;
		for(auto psig : m_signals){
			psig.second.cpp_decl(fp);	
			count++;
		}
		return count;
	 }

	// render the statements for caputring the data
	uint32_t cpp_capture_stmt(FILE *fp, uint32_t curr_idx){
		uint32_t idx = curr_idx;
		for(auto psig : m_signals){
                    idx = psig.second.cpp_capture_stmt(fp, idx); 
		}	
		return idx;
	}

    // bool to see if there are any sub structs
    bool noSubStructs() { return m_substructs.empty(); }

	// renders the json for this struct 
	void json(FILE *fp){
		fprintf(fp, "fprintf(fp, \"{\\n\");\n");
		fprintf(fp, "fprintf(fp, \"\\t\\t\\\"struct_name\\\":\\\"%s\\\",\\n\");\n", m_name.c_str());
		fprintf(fp, "fprintf(fp, \"\\t\\t\\\"signals\\\":[\\n\");\n");
		for(auto psig : m_signals){
			psig.second.json(fp);
			if((psig.first != m_signals.rbegin()->first) || !noSubStructs()) {
				fprintf(fp,     "\tfprintf(fp, \"},\\n\");\n"     );
			} else {
				fprintf(fp,     "\tfprintf(fp, \"}\\n\");\n"     );
			}
		}
		// Now get all the substructs to render their JSON
       for(iterator sin=begin(); sin!=end(); ++sin) {
            VisStruct t = (*sin).second;
            t.json(fp);
            if(((*sin).first != m_substructs.rbegin()->first)) {
                fprintf(fp,     "\tfprintf(fp, \"]},\\n\");\n"     );         
            } else {                                                         
                fprintf(fp,     "\tfprintf(fp, \"]}\\n\");\n"     );          
            }
        }
	}


    // renders the json for this struct into a string object
    void jsonStr(FILE* fp) { 
		fprintf(fp, "str.append(\"\\t\\t\\\"%s\\\": {\\n\");\n", m_name.c_str());
		for(auto psig : m_signals){
			psig.second.jsonStr(fp);
			if((psig.first != m_signals.rbegin()->first) || !noSubStructs()) {
				fprintf(fp,     "\tstr.append(\",\\n\");\n"     );
			} else {
				fprintf(fp,     "\tstr.append(\"\\n\");\n"     );
			}
		}
		// Now get all the substructs to render their JSON
       for(iterator sin=begin(); sin!=end(); ++sin) {
            VisStruct t = (*sin).second;
            t.jsonStr(fp);
            if(((*sin).first != m_substructs.rbegin()->first)) {
                fprintf(fp,     "\tstr.append(\"},\\n\");\n"     );         
            } else {                                                        
                fprintf(fp,     "\tstr.append(\"}\\n\");\n"     );          
            }
        }
	}
   
    

	    // iterators
	    typedef std::map<std::string, VisStruct>::iterator iterator;
	    iterator begin() { return m_substructs.begin(); }
	    iterator end() { return m_substructs.end(); }

    private:
	    std::string m_name;
	    std::map<std::string, VisSignal> m_signals;
	    std::map<std::string, VisStruct> m_substructs;

};
