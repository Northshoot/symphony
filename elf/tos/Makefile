LIB=libtostest
TARGET=testtos
CXX=$(CC)
CXXFLAGS=-g -Wall 
CXXLIBFLAGS=$(CXXFLAGS) -fPIC
LINKFLAGS=-Wl,--warn-unresolved-symbols -I/home/lauril/dev/symphony/elf/ -Wl,--no-as-needed

ldso:
	$(CXX) $(CXXLIBFLAGS)  -c -o $(LIB).o $(LIB).c
	$(CXX) $(LIB).o $(LINKFLAGS) -shared -L/home/lauril/dev/symphony/elf/ldso -nostdlib -o $(LIB).so
	$(CC) $(CXXFLAGS) -c -o $(TARGET).o $(TARGET).c
	$(CXX) $(TARGET).o $(LINKFLAGS) -ldl -o $(TARGET)
	melftedit $(TARGET) ../ldso
	LD_LIBRARY_PATH=../ ./$(TARGET)
	
snd:
	$(CXX) $(CXXLIBFLAGS)  -c -o $(LIB).o $(LIB).c
	$(CXX) $(LIB).o $(LINKFLAGS) -shared  -o $(LIB).so
	$(CC) $(CXXFLAGS) -c -o $(TARGET).o $(TARGET).c
	$(CXX) $(TARGET).o -Wl,--warn-unresolved-symbols -L. -Wl,--no-as-needed -ldl -o $(TARGET)
#	./$(TARGET)
	
clean:
	 rm *.o *.so $(TARGET)
