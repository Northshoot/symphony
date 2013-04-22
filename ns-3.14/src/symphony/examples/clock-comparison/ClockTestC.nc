#include "Timer.h"
#include "ns3/calls-to-ns3.h"

module ClockTestC @safe() {
	uses {
		interface Boot;
		interface Timer<TMilli> as MilliTimer;
		interface Leds;
		interface RealTimeClock as RTC;

	}
}
implementation {
    uint32_t time_exec=0;
    uint64_t time_rt=0;
	event void Boot.booted() {
		call MilliTimer.startPeriodic( 500 );

	}

 
	event void MilliTimer.fired() {
		time_exec = call MilliTimer.getNow();
		time_rt = call RTC.getTime(MILLISECOND);
		dbg("Info", "Fired %u\n", time_exec);
		printf("%lu\n", time_rt);
	}




}




