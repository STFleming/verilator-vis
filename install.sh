#! /bin/bash

# Install script for verilator-vis 
# tested on Ubuntu 19.04
# tested on Ubuntu 20.04 on WSL2
# tested on Mac M1 bigSur  

PLAT=`uname -m`

# We are targetting an M1 Mac (ToDo: make better and add more platforms)
# Install all the relevant libs
if [ $PLAT = arm64 ] 
then 

	brew update
	brew install verilator
	brew install boost
	brew install rapidjson
	brew install binutils
	brew install openssl
	brew install cpprestsdk
	brew install npm 
	
else
	# Assume we are in a debian based linux system
	# update package manager package list
	sudo apt-get update
	
	sudo apt-get install -y perl python3 make
	sudo apt-get install -y g++
	sudo apt-get install -y libfl2 libfl-dev zlibc zlib1g zlib1g-dev 
	sudo apt-get install -y ccache
	sudo apt-get install -y libgoogle-perftools-dev numactl perl-doc
	sudo apt-get install -y git autoconf flex bison
	sudo apt-get install -y gdb asciidoctor graphviz cmake clang clang-format binutils lcov
	sudo apt-get install -y npm
	cpan install Pod::Perldoc
	cpan install Unix::Processors
	cpan install Parallel::Forker
	cpan install Bit::Vector
	
	sudo apt-get install verilator

	#cd verilator/
	#autoconf
	#unset VERILATOR_ROOT
	#./configure
	#make -j
	#make test
	#make install

fi

cd common/sw/vis_struct_gen
make 
cd ../../../
