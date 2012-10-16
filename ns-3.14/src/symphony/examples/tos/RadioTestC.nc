
 
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
    void task send();
	message_t packet;
	message_t packet1;
	message_t packet2;
    uint8_t dest=0;
	bool locked;
	uint16_t counter = 0;
 
	event void Boot.booted() {
		printf("App: booted %d\n", TOS_NODE_ID);
		if(TOS_NODE_ID == 0) dest = 3;
		else if (TOS_NODE_ID == 1) dest = 0;
		else printf("TOS_NODE_ID error: TOS_NODE_ID == %d\n", TOS_NODE_ID);
		call AMControl.start();
	}

	event void AMControl.startDone(error_t err) {
		if (err == SUCCESS) {
		  if  (TOS_NODE_ID == 0){
            post send();			
		  }
		  //printf("AMControl.startDone: TOS_NODE_ID == %d\n", TOS_NODE_ID);
		}else {
			call AMControl.start();
		}
	}

	event void AMControl.stopDone(error_t err) {
		// do nothing
	}
 
 	void task send(){
 		counter++;
 		//if (counter <15){
		printf("TOSNODE::void task send() TOS_NODE_ID::%d - COUNTER::%d - DEST::%d\n", TOS_NODE_ID, counter, dest);
		if (locked) {
			printf("LOCKED\n");
			return;
		}
		else {
			radio_count_msg_t* rcm = (radio_count_msg_t*)call Packet.getPayload(&packet, sizeof(radio_count_msg_t));
			if (rcm == NULL) {
				printf("rcm == NULL\n");
				return;
			}
			rcm->counter = counter;
			if (call AMSend.send(AM_BROADCAST_ADDR, &packet, sizeof(radio_count_msg_t)) == SUCCESS) {
				locked = TRUE;
			}
		}
		//}
 	}
	event void MilliTimer.fired() {
		//printf("event void MilliTimer.fired() %d Node %d\n", call MilliTimer.getNow(), TOS_NODE_ID);
		post send();
	}

	event message_t* Receive.receive(message_t* bufPtr, 
			void* payload, uint8_t len) {
		//get counter		
	    atomic counter = ((radio_count_msg_t*)payload)->counter;
		printf("TOSNODE:: %d RadioTest event message_t* Receive.receive %u\n",TOS_NODE_ID,counter );
		//post send();
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
			printf("event void AMSend.sendDone %d\n",TOS_NODE_ID);
			//call MilliTimer.startOneShot(2000);
		}

	}

}




