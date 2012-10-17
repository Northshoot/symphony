
 
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
		printf("%s - %d\n",__PRETTY_FUNCTION__, call MilliTimer.getNow());
		call Leds.led1Toggle();
	}




}




