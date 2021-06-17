INC=./inc
SRC=./src
BIN=./bin

INCLUDES=$(INC)/

PLAT := $(shell uname -m)
ifeq ($(PLAT), arm64)
	M1_INC  = -I $(shell brew --prefix boost)/include 
	M1_INC += -I $(shell brew --prefix rapidjson)/include
	M1_INC += -I $(shell brew --prefix binutils)/include
	M1_INC += -I $(shell brew --prefix openssl)/include
	M1_INC += -I $(shell brew --prefix cpprestsdk)/include
	
	M1_LIB  = -L $(shell brew --prefix boost)/lib 
	M1_LIB += -L $(shell brew --prefix rapidjson)/lib
	M1_LIB += -L $(shell brew --prefix binutils)/lib
	M1_LIB += -L $(shell brew --prefix openssl)/lib
	M1_LIB += -L $(shell brew --prefix cpprestsdk)/lib
endif


BOOST_FLAGS= -lboost_system -lssl -lcrypto -lcpprest -lboost_program_options
#CPPFLAGS=-std=c++14 -fconcepts
CPPFLAGS=-std=c++14

$(BIN)/draig_vis: $(SRC)/vis_struct_gen.cpp $(INCLUDES)
	mkdir -p $(BIN)
ifeq ($(PLAT), arm64)
	g++ $(CPPFLAGS) -I$(INC) $(M1_INC) $(SRC)/vis_struct_gen.cpp -o $(BIN)/vis_struct_gen $(M1_LIB) -lstdc++ $(BOOST_FLAGS) -lpthread 
else
	g++ $(CPPFLAGS) -I$(INC) $(SRC)/vis_struct_gen.cpp -o $(BIN)/vis_struct_gen -lstdc++ $(BOOST_FLAGS) -lpthread 
endif

clean:
	rm -rf $(BIN)/*
