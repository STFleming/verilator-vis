INC=./inc
SRC=./src
BIN=./bin

INCLUDES=$(INC)/

BOOST_FLAGS= -lboost_system -lssl -lcrypto -lcpprest -lboost_program_options
CPPFLAGS=-std=c++14 -fconcepts

$(BIN)/draig_vis: $(SRC)/vis_struct_gen.cpp $(INCLUDES)
	mkdir -p $(BIN)
	g++ $(CPPFLAGS) -I$(INC) $(SRC)/vis_struct_gen.cpp -o $(BIN)/vis_struct_gen -lstdc++ $(BOOST_FLAGS) -lpthread 

clean:
	rm -rf $(BIN)/*
