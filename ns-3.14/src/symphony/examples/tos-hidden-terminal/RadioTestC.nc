#include "Timer.h"

typedef nx_struct radio_count_msg {
	nx_uint16_t counter;
	nx_uint16_t id;
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
		interface AMPacket;
	}
}
implementation {
	void task send();
	message_t packet;

	bool locked;
	uint16_t counter, counter_zero, counter_two = 0;
	uint16_t rx_id = 1;

	event void Boot.booted() {
		printf("App: booted %d\n", TOS_NODE_ID);
		call AMControl.start();
	}

	event void AMControl.startDone(error_t err) {
		if(err == SUCCESS) {
			if(TOS_NODE_ID == 1 ) {
				call MilliTimer.startOneShot(100);
			}
					  else if (TOS_NODE_ID == 0){
					  	call MilliTimer.startOneShot(1000);
					  	}
		}
		else {
			call AMControl.start();
		}

	}

	event void AMControl.stopDone(error_t err) {
		// do nothing
	}

	void task send() {
		counter++;
//		printf("void task send() :: %d timer fired, counter is %hu.\n", TOS_NODE_ID,
//				counter);
		if(locked) {
			return;
		}
		else {
			radio_count_msg_t * rcm = (radio_count_msg_t * ) call Packet.getPayload(
					&packet, sizeof(radio_count_msg_t));
			if(rcm == NULL) {
				return;
			}

			rcm->counter = counter;
			rcm->id = TOS_NODE_ID;
			if(call AMSend.send(2, &packet, sizeof(radio_count_msg_t)) == SUCCESS) {
				locked = TRUE;
			}
		}
	}
	event void MilliTimer.fired() {
		post send();
	}

	event message_t * Receive.receive(message_t * bufPtr, void * payload,
			uint8_t len) {

	   printf("RX_ID (%d) TX_ID (%d)\n", call AMPacket.source(bufPtr), call AMPacket.destination(bufPtr));
		atomic rx_id = ((radio_count_msg_t * ) payload)->id;
		switch(rx_id) {
			case 0 : 
                atomic counter_zero = ((radio_count_msg_t * ) payload)->counter;
			break;
			case 2 : 
                atomic counter_two = ((radio_count_msg_t * ) payload)->counter;
			break;
			default : break;
		}
		printf("\t# %d RX:: %u c::0 %u c::2 %u\n", TOS_NODE_ID, rx_id, counter_zero,counter_two);
		//call MilliTimer.startOneShot(1000);
		if(len != sizeof(radio_count_msg_t)) {
			return bufPtr;
		}
		else {
			//radio_count_msg_t* rcm = (radio_count_msg_t*)payload;
			printf("Buffer error on reception\n");
			return bufPtr;
		}

	}

	event void AMSend.sendDone(message_t * bufPtr, error_t error) {
		if(error == SUCCESS) {
			locked = FALSE;
			//call MilliTimer.startOneShot(1000);
			post send();
		}
		else {
			printf("#%d SEND DONE ERROR %d\n", TOS_NODE_ID, error);
		}

	}

}