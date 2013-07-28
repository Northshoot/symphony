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
  uint32_t counter = 0;
  
  //Initialization hypervectors send by the BaseStationn
  init1 init_Hv;
  init1 init_Random;
  
  //Last temperature received by the node. Default value = 0
  int last_Temp = 0;
  
  //Filler prepared to send to base station.
  int filler[DIMENSION];
  int aux_Filler[DIMENSION];
  
  //Sending packet
  bool sending = 0;
 
  
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
 	  
 	  memcpy( npkt->vector, filler, sizeof(filler) );
 	  npkt->nodeId = TOS_NODE_ID;
		
		printf("[%d] Send hypervector to base station \n", TOS_NODE_ID);
		call Ns3Application.SendDataToApplication(sizeof(NodePacket), npkt);
		
		sending = 0;
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
	  if (!sending){
	  	//Receives an integer with the value of the temperature
   		last_Temp = *(int32_t*) buffer;
    
   		printf("[%d] Termometer - New measurement ready in the node (%d bytes length) -> Value: %d \n",TOS_NODE_ID, length, last_Temp);
  	
  		//Shift the initialization hypervector to get the filler 
  		Shift( filler, init_Hv.role_hv, DIMENSION, last_Temp);
  		//printFiller();
  		
  		// Random XOR ( Initialization OR Filler)	
  		Or( filler, filler,  init_Hv.role_hv, DIMENSION);
  		//printFiller();
  		Xor( filler, filler, init_Random.role_hv, DIMENSION);
  		//printFiller();

  		//TODO Check with negative values
  		sending = 1;  	  
    	post send(); 
    }  
  }
    
    /*
     * Receives the initialization vector from the simulator
     */
     async event void InitVector.interruptWithData(error_t result, uint16_t length, void * buffer)
    {
      	memcpy( &(init_Hv), buffer, length);   
        printf("[%d] Received Init HV: Id: %d \n", TOS_NODE_ID, init_Hv.id);
    }
     
    /*
     * Receives the randomization vector from the simulator
     */ 
     async event void RandomVector.interruptWithData(error_t result, uint16_t length, void * buffer)
    {
  			memcpy( &(init_Random), buffer, length);
  			printf("[%d] Received Random HV \n", TOS_NODE_ID);
    }


// Function for Xor operation. Input parameters are two interacting vectors (arr1, arr2), result vector (arr0) and dimensionality (n)
void Xor(int *arr0, int *arr1, int *arr2, int n)
{
		int i;
    for(i = 0;i<n;i++) {
        arr0[i] = arr1[i] ^ arr2[i];
    }
}

// Function for Or operation. Input parameters are two interacting vectors (arr1, arr2), result vector (arr0) and dimensionality (n)
void Or(int *arr0, int *arr1, int *arr2, int n)
{
	int i;
    for(i = 0;i<n;i++) {
        arr0[i] = arr1[i] | arr2[i];
    }
}

//Function for obtaining new vector from old one by shifting its. Input parameters are input vector (arr2), dimensionality (n), shifting vector arr1 and shift value in bits (k)
void Shift(int *arr1, int *arr2, int n, int k)
{
	int i;
    for(i=0;i<n;i++) {
        if (i+k < n) {
        arr1[i+k] = (arr2[i]);
        } else arr1[i + k - n] = arr2[i];
    }
}

void printFiller(){
	int i = 0;
	printf("\n");
	for (i = 0 ; i < DIMENSION; i++){
		printf("%d", filler[i] );
	}
	printf("\n");
	
}


}

