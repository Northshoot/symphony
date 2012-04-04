
 
#include "Timer.h"

typedef nx_struct radio_count_msg {
	nx_uint16_t counter;
} radio_count_msg_t;

enum {
		AM_RADIO_COUNT_MSG = 6,
};

module RadioTestC @safe() {
	uses {
		interface Boot;
		interface Receive;
		interface AMSend;
		interface Timer<TMilli> as MilliTimer;
		interface SplitControl as AMControl;
		interface Packet;
	}
}
implementation {

	message_t packet;

	bool locked;
	uint16_t counter = 0;
 
	event void Boot.booted() {
		printf("App: booted %d\n", TOS_NODE_ID);
		call AMControl.start();
	}

	event void AMControl.startDone(error_t err) {
		printf("\tApp: AMControl.startDone(error_t err) \n");
		if (err == SUCCESS) {
		  if  (TOS_NODE_ID == 1){
			counter++;
			//dbg("RadioCountToLedsC", "RadioCountToLedsC: timer fired, counter is %hu.\n", counter);
			if (locked) {
				printf("App: AMControl.startDone(error_t err) LOCKED \n");
			}
			else {
				radio_count_msg_t* rcm = (radio_count_msg_t*)call Packet.getPayload(&packet, sizeof(radio_count_msg_t));
				if (rcm == NULL) {
					return;
				}
				rcm->counter =counter;
				printf("AMControl.startDone: about to send\n");
				if (call AMSend.send(AM_BROADCAST_ADDR, &packet, sizeof(radio_count_msg_t)) == SUCCESS) {
					//dbg("RadioCountToLedsC", "RadioCountToLedsC: packet sent.\n", counter);	
					//locked = TRUE;
				}
			}
			//call MilliTimer.startPeriodic(500); 
			
		  }
		}else {
			call AMControl.start();
		}
	}

	event void AMControl.stopDone(error_t err) {
		// do nothing
	}
 
 	void task send(){
 				counter++;
		dbg("RadioCountToLedsC", "RadioCountToLedsC: timer fired, counter is %hu.\n", counter);
		if (locked) {
			return;
		}
		else {
			radio_count_msg_t* rcm = (radio_count_msg_t*)call Packet.getPayload(&packet, sizeof(radio_count_msg_t));
			if (rcm == NULL) {
				return;
			}

			rcm->counter = counter;
			if (call AMSend.send(2, &packet, sizeof(radio_count_msg_t)) == SUCCESS) {
				dbg("RadioCountToLedsC", "RadioCountToLedsC: packet sent.\n", counter);	
				locked = TRUE;
			}
		}
 	}
	event void MilliTimer.fired() {
		post send();
	}

	event message_t* Receive.receive(message_t* bufPtr, 
			void* payload, uint8_t len) {
				
	    atomic counter = ((radio_count_msg_t*)payload)->counter;
		printf("# %d RadioTest event message_t* Receive.receive %u\n",TOS_NODE_ID,counter );
		call MilliTimer.startOneShot(1000);
		if (len != sizeof(radio_count_msg_t)) {return bufPtr;}
		else {
			//radio_count_msg_t* rcm = (radio_count_msg_t*)payload;
			printf("Buffer error on reception\n");
			return bufPtr;
		}
		
	}

	event void AMSend.sendDone(message_t* bufPtr, error_t error) {
		if (&packet == bufPtr) {
			locked = FALSE;
			printf("AMSend.sendDone\n");
		}
		printf("AMSend.sendDone\n");
		//call MilliTimer.startOneShot(1000);
	}

}




