#include "Timer.h"
#include "SkynetTos.h"
 
/**
 * Implementation for the Skynet Tiny OS Node App
 *
 * @author Jose Angel Fernandez Rodrigues
 * @date   March 2013
 */

module SkynetTosC @safe() {
  uses {
    interface Boot;
    interface Timer<TMilli> as MilliTimer;
    interface SplitControl as AppControl;
    interface Ns3Application;
    
    interface SplitControl as SensorControl;
    interface InterruptWithData as DataIn;
  }
}

implementation {
  
  void task send();	
	
	typedef struct {
			uint32_t nodeId;
      uint32_t counter;
    } NodePacket;
  
  uint32_t counter = 0;
 
  
	event void Boot.booted() {
		printf("[%d] App(sensor): booted\n", TOS_NODE_ID);
		call AppControl.start();
		call SensorControl.start();
	}

	event void AppControl.startDone(error_t err) {
		printf("[%d] App(sensor): started\n", TOS_NODE_ID);
		if (err == SUCCESS) {
		  if  (TOS_NODE_ID == 0){
            call MilliTimer.startPeriodic(1000);	
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
 		npkt->counter = counter;
 		npkt->nodeId = TOS_NODE_ID;
		call Ns3Application.SendDataToApplication(sizeof(NodePacket), npkt);
	}

	event void MilliTimer.fired() {
		//post send();
	}
	
	event void SensorControl.startDone(error_t err) {
      if (err == SUCCESS) {
				// do nothing	
			}else {
         call SensorControl.start();
      }
    }

    event void SensorControl.stopDone(error_t err) {
        // do nothing
    }
 

    async event void DataIn.interruptWithData(error_t result, uint16_t length, void * buffer) {
    
   int32_t * i = (int32_t*) buffer;
   counter = *i;
   // memcpy ((void *) i, buffer, sizeof(i));
    
    printf("[%d] Termometer - New measurement ready in the node (%d bytes length) -> Value: %d \n",TOS_NODE_ID, length, counter);
    
    post send();
    
    }
  
  
}




