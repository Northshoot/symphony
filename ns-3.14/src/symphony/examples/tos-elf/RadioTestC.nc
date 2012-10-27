
 
#include "Timer.h"

typedef nx_struct radio_count_msg {
	nx_uint16_t counter;
	nx_uint32_t a;
	nx_uint32_t b;
	nx_uint32_t c;
	nx_uint32_t d;
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
    uint8_t dest=0;
	bool locked;
	uint16_t counter = 0;
 
	event void Boot.booted() {
		printf("App: booted %d\n", TOS_NODE_ID);
		if(TOS_NODE_ID != 10) dest = 0;

		call AMControl.start();
	}

	event void AMControl.startDone(error_t err) {
		printf("AMControl.startDone: TOS_NODE_ID == %d\n", TOS_NODE_ID);
		if (err == SUCCESS) {
		  if  (TOS_NODE_ID != 0){
            //call MilliTimer.startOneShot(100);			
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
		printf("TOSNODE (%d) send() - COUNTER (%d)- DEST (%d) PKT SIZE (%ld)\n", 
		TOS_NODE_ID, counter, dest, sizeof(radio_count_msg_t));
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
			rcm->a = 178956970;
			rcm->b = 196852667;
			rcm->c = 214748364;
            rcm->d = 232644061;
			if (call AMSend.send(dest, &packet, sizeof(radio_count_msg_t)) == SUCCESS) {
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

		if (len != sizeof(radio_count_msg_t)) {
		  printf("Buffer error on reception %d\n",len);
			return bufPtr;}
		else {
			//radio_count_msg_t* rcm = (radio_count_msg_t*)payload;
			              //get counter       
            atomic counter = ((radio_count_msg_t*)payload)->counter;
            printf("TOSNODE (%d) receive (%d) len (%d)\n",TOS_NODE_ID
            ,counter, len );
            //post send();
            call MilliTimer.startOneShot(10);   
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




