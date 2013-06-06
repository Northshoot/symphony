#include "../sim/sim_main.h"
#include "defines.h"
#include "ns3/calls-to-ns3.h"

module TemperatureSensorP
{
	provides
	{
		interface SplitControl;
		interface InterruptWithData as Data;
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
    	signal Data.interruptWithData( result, lenght, buffer);
    	}
}
