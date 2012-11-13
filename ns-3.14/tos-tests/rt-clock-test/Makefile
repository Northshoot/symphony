#steps needed to build
#1.compile tos app to c
#2.add extern "C" to app.c
#3.compile it as library
#4.compile proxy objects
#5.Link library with proxies
#6.Link whole simulations




#TinyOS options
TOS_APP=RadioApp
SIM_OBJ=sim
TARGET=ns3
NODE=symphony.xml

#compilers
GXX=g++
GCC=gcc
NCC=ncc
PY=python



TOS_APP_C=app.c
TOS_NS3=$(TOSDIR)/platforms/ns3

POST=$(SYMPHONY_SRC)/helper/postprocess.py

#flags and options 
OPTFLAGS_GPP = #-g -O0
LINK_NS_OPT=-lstdc++
OPTFLAGS_GCC = -g -O0 -Wall -Wshadow
#NCC_OPT= -c -fPIC -o $(SIM_OBJ).o $(OPTFLAGS_GCC) -fnesc-gcc=$(GCC) -Wnesc-all -target=$(TARGET) -fnesc-cfile=app.c $(TOS_APP).nc
NCC_OPT=-fPIC -g -c -o /dev/null -fnesc-gcc=$(GCC) -target=$(TARGET) -fnesc-cfile=$(TOS_APP_C) $(TOS_APP).nc -I$(SYMPHONY_BUILD)
NCC_OPT_WALL= -Wall -g -c -o /dev/null -fnesc-gcc=$(GCC) -target=$(TARGET) -fnesc-cfile=$(TOS_APP_C) $(TOS_APP).nc -I$(SYMPHONY_BUILD)
#include dirs

#for headers always use "ns3/header.h" to allow moving to waf in future
NS3_INCL = -I$(SYMPHONY_BUILD) 
TOS_INCL = -I$(TOS_NS3)
PRE_NS_LIB=libns3-dev
POST_NS_LIB=debug.so
NS3_OBJ = $(SYMPHONY_BUILD)/$(PRE_NS_LIB)-symphony-$(POST_NS_LIB)
CALL_HEADER=$(SYMPHONY_SRC)/model/calls-to-ns3.h

CXXFLAGS=-g -Wall 
CXXLIBFLAGS=$(CXXFLAGS) -fPIC
LINKFLAGS=-Wl,--warn-unresolved-symbols -L/home/lauril/dev/symphony/elf/ -Wl,--no-as-needed  -L../../../../../elf/ldso $(NS3_OBJ)  

#app to create
LIB=libtos

all:
		@echo "                                   "
		@echo "Building TinyOS image              "
		$(NCC) $(NCC_OPT_WALL)
		$(PY) $(POST) $(TOS_APP_C) $(LIB).c
		@echo ""
		@echo "Building TinyOS object             "
		$(CXX) $(CXXLIBFLAGS)  -c -o $(LIB).o $(LIB).c
		$(CXX) $(LIB).o -shared -o $(LIB).so
		@echo  $(NS3_OBJ)  

		@echo "                           "		
		@echo "*** copying library to ns_dir***"
		cp $(LIB).so $(SYMPHONY_BUILD)/
		cp $(NODE) $(SYMPHONY_BUILD)/		
		@echo "*** tos-ns was successfully build***"
		@echo ""
		
clean:
	rm -rf $(OUT) *.o app.c
	
	


    

