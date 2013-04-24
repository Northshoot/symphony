#
export TOS_APP=ThroughputApp

sym:
	$(MAKE) -f makefile.symphony 
	
toss:
	COMPONENT=TOS_APP
	$(MAKE) -f $(APP) makefile.tossim micaz sim
	
clean:
	rm -rf $(OUT) *.o app.c
    

