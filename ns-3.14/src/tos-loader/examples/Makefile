LIB=libtostest
TARGET=tos-loader-example
CXX=$(CC)
CXXFLAGS=-g -Wall -I/home/lauril/dev/symphony/ns-3.14/build
CXXLIBFLAGS=$(CXXFLAGS) -fPIC 
LINKFLAGS=-Wl,--warn-unresolved-symbols -L$(SYMPHONY_ELF) -L$(SYMPHONY_BUILD) -Wl,--no-as-needed
PRE_NS_LIB=libns3-dev
POST_NS_LIB=debug.so
NS3_CORE =$(SYMPHONY_BUILD)/$(PRE_NS_LIB)-core-$(POST_NS_LIB)
NS3_LOADER =$(SYMPHONY_BUILD)/$(PRE_NS_LIB)-tos-loader-$(POST_NS_LIB)


ldso:
	$(CC) $(CXXFLAGS) -c -o  $(TARGET).o $(TARGET).cc
	$(CXX) $(TARGET).o $(LINKFLAGS) $(NS3_LOADER) $(NS3_CORE) -ldl -o $(TARGET)
	../../../../elf/elfedit $(TARGET) ../../../../elf/ldso
	./$(TARGET)
	

	
clean:
	 rm *.o *.so $(TARGET)
