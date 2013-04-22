#include "Timer.h"

module ClockTestC @safe() {
	uses {
		interface Boot;
		interface Timer<TMilli> as MilliTimer;
		interface Leds;

	}
}
implementation {
 uint32_t time_exec=0;
	event void Boot.booted() {
		call MilliTimer.startPeriodic( 500 );

	}

 
	event void MilliTimer.fired() {
		time_exec = call MilliTimer.getNow();
		dbg("Info", "Fired %u\n", time_exec);
		printf("\t\t######### %u\n",time_exec);
	}




}




