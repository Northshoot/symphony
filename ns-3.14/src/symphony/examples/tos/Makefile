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
GPP=g++
GCC=gcc
NCC=ncc
LIB=ar rcs
PY=python



TOS_APP_C=app.c
NS3_DIR=/home/lauril/dev/symphony/ns-3.11/build
SYMPHONY_SRC=/home/lauril/dev/symphony/ns-3.11/src/symphony
TOS_NS3=$(TOSDIR)/platforms/ns3

POST=$(SYMPHONY_SRC)/helper/postprocess.py

#flags and options 
OPTFLAGS_GPP = #-g -O0
LINK_NS_OPT=-lstdc++
OPTFLAGS_GCC = -g -O0 -Wall -Wshadow
#NCC_OPT= -c -fPIC -o $(SIM_OBJ).o $(OPTFLAGS_GCC) -fnesc-gcc=$(GCC) -Wnesc-all -target=$(TARGET) -fnesc-cfile=app.c $(TOS_APP).nc
NCC_OPT=-fPIC -g -c -o /dev/null -fnesc-gcc=$(GCC) -target=$(TARGET) -fnesc-cfile=$(TOS_APP_C) $(TOS_APP).nc -I$(NS3_DIR)
NCC_OPT_WALL=-fPIC -Wall -g -c -o /dev/null -fnesc-gcc=$(GCC) -target=$(TARGET) -fnesc-cfile=$(TOS_APP_C) $(TOS_APP).nc -I$(NS3_DIR)
#include dirs

#for headers always use "ns3/header.h" to allow moving to waf in future
NS3_INCL = -I$(NS3_DIR) 
TOS_INCL = -I$(TOS_NS3)
PRE_NS_LIB=libns3-dev
POST_NS_LIB=debug.so
NS3_OBJ = $(NS3_DIR)/$(PRE_NS_LIB)-symphony-$(POST_NS_LIB)
NS3_CORE =$(NS3_DIR)/$(PRE_NS_LIB)-core-$(POST_NS_LIB)
NS3_NET =$(NS3_DIR)/$(PRE_NS_LIB)-network-$(POST_NS_LIB)
CALL_HEADER=$(NS3_SRC)/model/calls-to-ns3.h

#app to create
SIM_LIB=libtos

all:
		@echo "                                   "
		@echo "Building TinyOS image              "
		$(NCC) $(NCC_OPT_WALL)
		$(PY) $(POST) $(TOS_APP_C) $(SIM_LIB).c
		@echo ""
		@echo "Building TinyOS object             "
		$(GPP) -fPIC -Wall -g -c $(SIM_LIB).c	$(NS3_INCL)
		@echo ""
		@echo "Creating library and linking with proxy objects            "
		$(GPP) -g -shared -Wl,-soname,$(SIM_LIB).so.0 -o $(SIM_LIB).so $(SIM_LIB).o $(NS3_OBJ) -ldl 

		@echo "                           "		
		@echo "*** copying library to ns_dir***"
		cp $(SIM_LIB).so $(NS3_DIR)/
		cp $(NODE) $(NS3_DIR)/		
		@echo "*** tos-ns was successfully build***"
		@echo ""
		
clean:
	rm -rf $(OUT) *.o app.c
	
	


    

