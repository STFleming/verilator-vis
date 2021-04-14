#! /bin/bash

# Install script for nant
# tested on Ubuntu 19.04
# tested on Ubuntu 20.04 on WSL2

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


cd verilator/
autoconf
unset VERILATOR_ROOT
./configure
make -j
make test
make install
