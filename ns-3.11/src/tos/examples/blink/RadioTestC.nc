
 
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
		printf("App: booted %d\n", TOS_NODE_ID);
		call MilliTimer.startPeriodic( 500 );

	}

 
	event void MilliTimer.fired() {
		printf("event void MilliTimer.fired() %d\n", call MilliTimer.getNow());
		call Leds.led1Toggle();
	}




}




