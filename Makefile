CC=g++
CFLAGS=-c -g -Wall -pedantic
LDFLAGS=-lxerces-c
SOURCES=main.cc symphony-xml.cc radio-model.cc hardware-model.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=symxml
RMOBJ=rm *.o

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	$(RMOBJ)

.cc.o:
	$(CC) $(CFLAGS) $< -o $@



clean:
	rm symxml *.o