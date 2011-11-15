#TinyOS options
TOS_APP=TimerAppC
SIM_OBJ=sim
TARGET=ns3
MAIN=main
OUT=test

#compilers
GPP=g++
GCC=gcc
NCC=ncc

all:
		@echo "                                   "
		@echo ""
		@echo "Linking all together              "
		$(GPP) $(MAIN).cc -o $(OUT) -ldl


		
clean:
	rm -rf $(OUT) *.o app.c