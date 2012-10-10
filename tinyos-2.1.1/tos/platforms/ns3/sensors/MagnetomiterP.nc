#include "../sim/sim_main.h"
#include "defines.h"
#include "ns3/calls-to-ns3.h"

module MagnetomiterP
{
	provides
	{
		interface SplitControl;
		interface InterruptWithData as data;
		
	}
}

implementation
{
	 command error_t SplitControl.start(){
	 	
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
    	}
}