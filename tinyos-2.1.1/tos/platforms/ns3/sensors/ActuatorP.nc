#include "../sim/sim_main.h"
#include "defines.h"
#include "ns3/calls-to-ns3.h"


/**
 * Receives the initialization hypervectors from the simulator
 * inside the TinyOS node.
 *
 * @author Jose Angel Fernandez Rodrigues
 * @date   July 2013
 */
module ActuatorP
{
	provides
	{
		interface InterruptWithData as actuatorInputInterrupt;
		interface InterruptWithData as actuatorHvInputInterrupt;
	}
}

implementation
{
		extern void actuatorInterrupt(error_t result, uint16_t lenght, void * buffer)@C() @spontaneous() {
    	signal actuatorInputInterrupt.interruptWithData( result, lenght, buffer);
    }
    
    extern void actuatorHvInterrupt(error_t result, uint16_t lenght, void * buffer)@C() @spontaneous() {
    	signal actuatorHvInputInterrupt.interruptWithData( result, lenght, buffer);
    }
}
