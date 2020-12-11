# Set the shell.
SHELL=/usr/bin/env bash

# Include the configuration.
# -include Makefile.inc


PYTHIA8 := /home/vinicius/simulationsSM/pythia8

CXX      := g++
XMLDOC   := $(PYTHIA8)/share/Pythia8/xmldoc
CXXFLAGS := -O3 -std=c++11 -I$(PYTHIA8)/include -I$(PYTHIA8)/include/Pythia8/ 
LDFLAGS  := -L$(PYTHIA8)/lib/ -L$(PYTHIA8)/lib -Wl,-rpath,$(PYTHIA8)/lib



pp2ttbar.exe: pp2ttbar.cc
	echo $(XMLDOC) > xml.doc
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@  pp2ttbar.cc -lpythia8 -ldl -DGZIPSUPPORT -lz
	
	
main01.exe: main01.cc
	echo $(XMLDOC) > xml.doc
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@  main01.cc -lpythia8 -ldl -DGZIPSUPPORT -lz	
