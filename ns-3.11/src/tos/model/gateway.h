/*
 * gateway.h
 *
 *  Created on: May 24, 2010
 *      Author: laurynas
 */

#ifndef GATEWAY_H_
#define GATEWAY_H_
#include "lib-to-tos-proxy.h"
#include "ns3includes.h"

/**
 * This function is used by all objects.
 * C does not care about void * tthis
 * so we can exploit it in order to save appropriate instance
 * of the object in the tos lib instance.
 */

//TODO: make this auto generated


extern int gateway(void *tthis,int call, int arg){
 std::cout << "gateway call "<< call <<" arg " << arg << std::endl;
  // here should be a switch case on "call"
  // or possibly an array of function pointers
	switch (call) {
		case 0:
			return ((LibToTosProxy *)tthis)->confirmSet(arg);
			break;

		case 1:
			return ((LibToTosProxy *)tthis)->getNow(arg);
			break;
		case 2:
			std::cout << "((LibToTosProxy *)tthis)->getNow() "<< ((LibToTosProxy *)tthis)->getNow(arg) << std::endl;
			return 0;
			break;

		default:
			//OPS! never ever go here!
			//if you have -> core dump :D
			std::cerr <<" bad index no where to go "<< call<< std::endl;
			return -1;
			break;
	}


}
typedef struct radio_count_msg {
	uint16_t counter;
} radio_count_msg_t;

extern int gatewayRadio(void *obj,int func, void* msg){
	message_t tempmsg ;
	uint i;
	memcpy((void *)&tempmsg, msg, sizeof(message_t));

//	message_t* p = (message_t*)msg;
	radio_count_msg_t* rcm = (radio_count_msg_t*)&tempmsg.data;
	ns3packet_header_t* h =(ns3packet_header_t*)&tempmsg.header;
	am_addr_t d =h->dest;
	am_addr_t d1 =h->src;

	uint8_t *pkt = (uint8_t *)&tempmsg;
    for(i=0; i<sizeof(msg); i++){
    	 std::cout << pkt[i] <<" ";
    }
    std::cerr<< std::endl;
	switch (func) {
		case 0:
			std::cerr <<"gatewayRadio got msg: "<< sizeof(msg) <<" vs "<< sizeof(tempmsg)<< std::endl;
			std::cerr <<"counter "<< rcm->counter << std::endl;
			std::cerr <<"destination "<< d <<" "<< d1<< std::endl;
			return 0;
			break;


		default:
			//OPS! never ever go here!
			//if you have -> core dump :D
			//std::cerr <<" bad index no where to go "<< call<< std::endl;
			return -1;
			break;
	}
	return -1;
}

#endif /* GATEWAY_H_ */
