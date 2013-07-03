#include "../sim/sim_main.h"
#include "defines.h"
#include "ns3/calls-to-ns3.h"

module HypervectorInitP
{
	provides
	{
		interface InterruptWithData as data;
	}
}

implementation
{
		extern void InitializationInterrupt(error_t result, uint16_t lenght, void * buffer)@C() @spontaneous() {
		  printf("Hi \n");
    	signal data.interruptWithData( result, lenght, buffer);
    }

	 /*command error_t SplitControl.start(){
	 	
		return gatewaySensor( proxy ,SENSOR_ON);
		}
		
	  extern int sensorStartDone(error_t error)@C() @spontaneous(){
        signal SplitControl.startDone( error );        
        return 0;
    }
    
    command error_t SplitControl.stop(){
        return 0;
        }
        
    extern int sensorStopDone(error_t error)@C() @spontaneous(){
        signal SplitControl.stopDone( error );        
    return 0;
    }
    
    extern void interruptData(error_t result, uint16_t lenght, void * buffer)@C() @spontaneous() {
    	signal data.interruptWithData( result, lenght, buffer);
    	} */
}
