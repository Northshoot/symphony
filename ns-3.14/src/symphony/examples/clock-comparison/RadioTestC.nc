
 
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
	  #ifdef SYMPHONY
		gatewayLogg(proxy,__PRETTY_FUNCTION__,__LINE__, "Boot Booted");
	  #endif
		call MilliTimer.startPeriodic( 500 );

	}

 
	event void MilliTimer.fired() {
		#ifdef SYMPHONY
		gatewayLogg(proxy,__PRETTY_FUNCTION__,__LINE__, "MilliTimer.fired()" );
		#endif
		call Leds.led1Toggle();
	}




}




