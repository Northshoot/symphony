#include "Timer.h"
#include "SkynetTos.h"
 
/**
 * Implementation of a node based on the Skynet project
 *
 * @author Jose Angel Fernandez Rodrigues
 * @date   March 2013
 */

module SkynetTosC @safe() {
  uses {
    interface Boot;
    interface SplitControl as AppControl;
    interface Ns3Application;
    
    interface SplitControl as SensorControl;
    interface InterruptWithData as DataIn;
    interface InterruptWithData as InitVector;
 		interface InterruptWithData as RandomVector;
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
		printf("[%d] App: booted\n", TOS_NODE_ID);
		call AppControl.start();
		call SensorControl.start();
	}

	event void AppControl.startDone(error_t err) {
		printf("[%d] App: started\n", TOS_NODE_ID);
		
		if (err != SUCCESS) {
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

	event void SensorControl.startDone(error_t err) {
    if (err != SUCCESS) {
		  call SensorControl.start();
    }
  }

  event void SensorControl.stopDone(error_t err) {
      // do nothing
  }
 

		/*
		 * Simulates an interruption of a sensor with the measures
		 * received from the simulator
		 */
	async event void DataIn.interruptWithData(error_t result, uint16_t length, void * buffer)
	 {
   	int32_t * i = (int32_t*) buffer;
   	counter = *i;
 	  // memcpy ((void *) i, buffer, sizeof(i));
    
   	printf("[%d] Termometer - New measurement ready in the node (%d bytes length) -> Value: %d \n",TOS_NODE_ID, length, counter);
    
    post send();   
  }
    
    /*
     * Receives the initialization vectors from the simulator
     */ 
   async event void InitVector.interruptWithData(error_t result, uint16_t length, void * buffer)
    {
        int i;
        
        init1* a = (init1*) buffer;
        printf("[%d] Received Init HV: Id: %d  xRi: ", a->id);
        /*
        for ( i = 0; i < DIMENSION; i++){
        	printf("%d",a->role_hv[i]);
        }
        */
        printf("\n");
    }
    
     async event void RandomVector.interruptWithData(error_t result, uint16_t length, void * buffer)
    {
  			int i;
        int * data = (int*) buffer;
        
        printf("[%d] Received random HV ", TOS_NODE_ID);
       /*
        for ( i = 0; i < DIMENSION; i++){
        	printf("%d",data[i]);
        }
       
        printf("\n"); */
    }
}




