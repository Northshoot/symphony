#steps needed to build
#1.compile tos app to c
#2.add extern "C" to app.c
#3.compile it as library
#4.compile proxy objects
#5.Link library with proxies
#6.Link whole simulations


#TinyOS options

export TOS_APP=RadioApp

sym:
	$(MAKE) -f makefile.symphony 
	
toss:
	COMPONENT=TOS_APP
	$(MAKE) -f $(APP) makefile.tossim micaz sim
	
clean:
	rm -rf $(OUT) *.o app.c
    

