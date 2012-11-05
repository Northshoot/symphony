
 
#include "Timer.h"

module RadioTestC @safe() {
	uses {
		interface Boot;
		interface Timer<TMilli> as MilliTimer;
		interface Leds;

	}
}
implementation {
 
	event void Boot.booted() {
		gatewayLogg(proxy,__PRETTY_FUNCTION__,__LINE__, "Boot Booted");
		call MilliTimer.startPeriodic( 500 );

	}

 
	event void MilliTimer.fired() {
		
		gatewayLogg(proxy,__PRETTY_FUNCTION__,__LINE__, "MilliTimer.fired()" );
		call Leds.led1Toggle();
	}




}




