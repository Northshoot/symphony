
 
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
		printf("App: booted\n");
		call AMControl.start();
	}

	event void AMControl.startDone(error_t err) {
		printf("App: AMControl.startDone(error_t err) \n");
		if (err == SUCCESS && TOS_NODE_ID == 1) {
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
				rcm->counter =4;
				printf("AMControl.startDone: about to send\n");
				if (call AMSend.send(2, &packet, sizeof(radio_count_msg_t)) == SUCCESS) {
					//dbg("RadioCountToLedsC", "RadioCountToLedsC: packet sent.\n", counter);	
					locked = TRUE;
				}
			}
			//call MilliTimer.startPeriodic(500); 
			
		}
		else {
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

			rcm->counter = 6;
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
		printf("RadioTest event message_t* Receive.receive %u\n",((radio_count_msg_t*)payload)->counter);
		//post send();
		if (len != sizeof(radio_count_msg_t)) {return bufPtr;}
		else {
			//radio_count_msg_t* rcm = (radio_count_msg_t*)payload;
			dbg("RadioCountToLedsC", "Received counter %u.\n", ((radio_count_msg_t*)payload)->counter);
			return bufPtr;
		}
		
	}

	event void AMSend.sendDone(message_t* bufPtr, error_t error) {
		if (&packet == bufPtr) {
			locked = FALSE;
		}
	}

}




