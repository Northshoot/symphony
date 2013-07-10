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
module HypervectorInitP
{
	provides
	{
		interface InterruptWithData as initVector;
		interface InterruptWithData as randomVector;
	}
}

implementation
{
		extern void InitializationVectorInterrupt(error_t result, uint16_t lenght, void * buffer)@C() @spontaneous() {
    	signal initVector.interruptWithData( result, lenght, buffer);
    }
    
    extern void RandomVectorInterrupt(error_t result, uint16_t lenght, void * buffer)@C() @spontaneous() {
    	signal randomVector.interruptWithData( result, lenght, buffer);
    }
}
