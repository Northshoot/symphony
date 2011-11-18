#compilers
GPP=g++
GCC=gcc
NCC=ncc
PY=python
POST=/home/lauril/dev/symphony/ns-3.11/src/tos/helper/postprocess.py

#TinyOS options
TOS_APP=RadioApp#TimerAppC
SIM_OBJ=sim
TARGET=ns3
MAIN=main
OUT=test
SIM_LIB=libtos

TOS_APP_C=app.c
NS3_DIR=/home/lauril/dev/symphony/ns-3.11/build/debug
TOS_NS3=$(TOSDIR)/platforms/ns3
LOC_DIR=/home/lauril/dev/symphony/tosexternaltests
#flags and options 
OPTFLAGS_GPP = #-g -O0
LINK_NS_OPT=-lstdc++
OPTFLAGS_GCC = -g -O0 -Wall -Wshadow
NCC_OPT=-fPIC -Wall -g -c -o /dev/null -fnesc-gcc=$(GCC) -target=$(TARGET) -fnesc-cfile=$(TOS_APP_C) $(TOS_APP).nc -I$(LOC_DIR)


FILES=tos-to-lib-proxy.cc  tiny-bridge.cc 
OBJ=tos-to-lib-proxy.o lib-to-tos-proxy.o tiny-bridge.o 


all:
		@echo "                                   "
		@echo "Building TinyOS              "
		$(NCC) $(NCC_OPT)
		@echo "Postprocessing TinyOS              "
		$(PY) $(POST) $(TOS_APP_C) $(SIM_LIB).c
		@echo ""
		@echo "Building TinyOS object             "
		$(GPP) -fPIC -Wall -g -c $(SIM_LIB).c -I$(LOC_DIR)
		@echo ""
		@echo "Creating library and linking with proxy objects     "
		$(GPP) -c -fPIC lib-to-tos-proxy.cc
		$(GPP) -g -shared -Wl,-soname,$(SIM_LIB).so.0 -o $(SIM_LIB).so $(SIM_LIB).o  lib-to-tos-proxy.o -ldl 
		@echo ""
		@echo "Linking all together              "
		$(GPP) main.cc $(FILES) lib-to-tos-proxy.o -o $(OUT) -ldl


		
clean:
	rm -rf $(OUT) *.o app.c