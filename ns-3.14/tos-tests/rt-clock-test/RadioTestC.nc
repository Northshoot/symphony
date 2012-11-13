
 
#include "Timer.h"
#define NEXT 100

module RadioTestC @safe() {
	uses {
		interface Boot;
		interface Timer<TMilli> as MilliTimer;
		interface Leds;

	}
}
implementation {
	

   unsigned int next;
   
	event void Boot.booted() {
		//gatewayLogg(proxy,__PRETTY_FUNCTION__,__LINE__, "Boot Booted");
		printf("Boot.booted %d at %d\n",TOS_NODE_ID,call MilliTimer.getNow());
		next = call MilliTimer.getNow();
		call MilliTimer.startPeriodic( NEXT );
        next = call MilliTimer.getNow()+NEXT;
	}

 
	event void MilliTimer.fired() {
		unsigned int now = call MilliTimer.getNow();
		unsigned int diff = now-next ;
		if(diff >0){
		  printf("(%d)-Time expected: %d now: %d diff: %d\n",TOS_NODE_ID, next, now, now-next );
		  }
		next = call MilliTimer.getNow()+NEXT;
		//gatewayLogg(proxy,__PRETTY_FUNCTION__,__LINE__, "MilliTimer.fired()" );
		
	}




}




