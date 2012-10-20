
 
#include "Timer.h"



module ApplicationAppC @safe() {
	uses {
		interface Boot;
		interface Timer<TMilli> as MilliTimer;
		interface SplitControl as AppControl;
		interface Ns3Application;
	}
}
implementation {
    void task send();	
	
	typedef struct {
      uint32_t counter;
      uint32_t nodeTime;
    } NodePacket;
    uint32_t counter = 0;
 
	event void Boot.booted() {
		printf("App: booted %d\n", TOS_NODE_ID);
		call AppControl.start();
	}

	event void AppControl.startDone(error_t err) {
		printf("StartDone\n");
		if (err == SUCCESS) {
		  if  (TOS_NODE_ID == 0){
            call MilliTimer.startPeriodic(100);	
		  }
		}else {
			call AppControl.start();
		}
	}

	event void AppControl.stopDone(error_t err) {
		// do nothing
	}
 
 	void task send(){
 		NodePacket *npkt;
        npkt= (NodePacket*) malloc(sizeof(NodePacket));
 		counter++;
 		npkt->counter=counter;
		printf("TOSNODE::void task send() TOS_NODE_ID::%d - COUNTER::%d\n", TOS_NODE_ID, counter);
		call Ns3Application.SendDataToApplication(sizeof(NodePacket), npkt);

		}

	event void MilliTimer.fired() {
		post send();
	}
}




