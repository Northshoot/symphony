#steps needed to build
#1.compile tos app to c
#2.add extern "C" to app.c
#3.compile it as library
#4.compile proxy objects
#5.Link library with proxies
#6.Link whole simulations




#TinyOS options
TOS_APP=TimerAppC
SIM_OBJ=sim
TARGET=ns3

#compilers
GPP=g++
GCC=gcc
NCC=ncc
LIB=ar rcs
PY=python
POST=/home/lauril/dev/symphony/ns-3.11/src/tos/helper/postprocess.py


TOS_APP_C=app.c
NS3_DIR=/home/lauril/dev/symphony/ns-3.11/build/debug
TOS_NS3=$(TOSDIR)/platforms/ns3

#flags and options 
OPTFLAGS_GPP = #-g -O0
LINK_NS_OPT=-lstdc++
OPTFLAGS_GCC = -g -O0 -Wall -Wshadow
#NCC_OPT= -c -fPIC -o $(SIM_OBJ).o $(OPTFLAGS_GCC) -fnesc-gcc=$(GCC) -Wnesc-all -target=$(TARGET) -fnesc-cfile=app.c $(TOS_APP).nc
NCC_OPT=-fPIC -Wall -g -c -o /dev/null -fnesc-gcc=$(GCC) -target=$(TARGET) -fnesc-cfile=$(TOS_APP_C) $(TOS_APP).nc -I$(NS3_DIR)
#include dirs

#for headers always use "ns3/heade.h" to allow moving to waf in future
NS3_INCL = -I$(NS3_DIR) 
TOS_INCL = -I$(TOS_NS3)
NS3_OBJ = $(NS3_DIR)/libns3-tos.so
NS3_CORE =$(NS3_DIR)/libns3-core.so
NS3_NET =$(NS3_DIR)/libns3-network.so


#app to create
APP=time

TOS_IMG=post_app
#main file
MAIN=main
OUT=time_t

SIM_LIB=libtos

all:
		@echo "                                   "
		@echo "Building TinyOS image              "
		$(NCC) $(NCC_OPT)
		$(PY) $(POST) $(TOS_APP_C) $(SIM_LIB).c
		@echo ""
		@echo "Building TinyOS object             "
		$(GPP) -fPIC -Wall -g -c $(SIM_LIB).c	$(NS3_INCL)
		@echo ""
		@echo "Creating library and linking with proxy objects            "
		$(GPP) -g -shared -Wl,-soname,$(SIM_LIB).so.0 -o $(SIM_LIB).so $(SIM_LIB).o $(NS3_OBJ) $(NS3_CORE)  -ldl 
		@echo ""
		@echo "Linking all together              "
		$(GPP) $(MAIN).cc -o $(OUT) $(NS3_INCL) $(NS3_OBJ) -ldl
		@echo "                           "		
		@echo "*** tos-ns was successfully build***"
		@echo ""
		@echo "run it: ./"$(OUT)

		
clean:
	rm -rf $(OUT) *.o app.c
	
run:
	make
	-exec " ./"$(OUT)
	


    

