#LIB=libtostest
LIB=libtostest
TARGET=testtos
CXX=g++
CC=gcc
CXXFLAGS=-g -Wall 
CXXLIBFLAGS=$(CXXFLAGS) -fPIC
LINKFLAGS=-Wl,--warn-unresolved-symbols -I/home/lauril/dev/symphony/elf/ -Wl,--no-as-needed

app:
	$(CXX) $(CXXFLAGS) -c -o $(TARGET).o $(TARGET).c
	$(CXX) $(TARGET).o $(LINKFLAGS) -ldl -o $(TARGET)
	../elfedit $(TARGET) ../ldso
	LD_LIBRARY_PATH=../ ./$(TARGET) 20
	
ldso:
	$(CC) $(CXXLIBFLAGS)  -c -o $(LIB).o $(LIB).c
	$(CC) $(LIB).o $(LINKFLAGS) -shared -L../ldso -nostdlib -o $(LIB).so
	$(CXX) $(CXXFLAGS) -c -o $(TARGET).o $(TARGET).c
	$(CXX) $(TARGET).o $(LINKFLAGS) -lrt -ldl -o $(TARGET)
	../elfedit $(TARGET) ../ldso
	LD_LIBRARY_PATH=../ ./$(TARGET) 20
	
snd:
	$(CXX) $(CXXLIBFLAGS)  -c -o $(LIB).o $(LIB).c
	$(CXX) $(LIB).o $(LINKFLAGS) -shared  -o $(LIB).so
	$(CC) $(CXXFLAGS) -c -o $(TARGET).o $(TARGET).c
	$(CXX) $(TARGET).o -Wl,--warn-unresolved-symbols -L. -Wl,--no-as-needed -ldl -o $(TARGET)
#	./$(TARGET)
	
clean:
	 rm *.o *.so $(TARGET)
