/*
 * gateway.h
 *
 *  Created on: May 24, 2010
 *      Author: laurynas
 */

#ifndef GATEWAY_H_
#define GATEWAY_H_
#include <stdio.h>
#include "tos-to-ns3-proxy.h"
#include "ns3includes.h"
#include "tos-packet.h"
#include "ns3/log.h"
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
			return ((TosToNs3Proxy *)tthis)->confirmSet(arg);
			break;

		case 1:
			return ((TosToNs3Proxy *)tthis)->getNow(arg);
			break;
		case 2:
			std::cout << "((TosToNs3Proxy *)tthis)->getNow() "<< ((TosToNs3Proxy *)tthis)->getNow(arg) << std::endl;
			return 0;
			break;

		default:
			//OPS! never ever go here!
			//if you have -> core dump :D
			std::cerr <<" bad index no where to go "<< call<< std::endl;
			return -1;
			break;
	}
	return 0;

}


extern int gatewayRadio(void *obj, int func, void* hdr, void* msg){
	//TosPacket* tpk = new TosPacket((message_t*) msg);
//	ns3packet_header_t* hdr = (ns3packet_header_t*)(((message_t*)msg)->data - sizeof(ns3packet_header_t));
//	message_t tempmsg ;
//	uint i;
//	memcpy((void *)&tempmsg, msg, sizeof(message_t));
//
////	message_t* p = (message_t*)msg;
//	radio_count_msg_t* rcm = (radio_count_msg_t*)&tempmsg.data;
//	ns3packet_header_t* h =(ns3packet_header_t*)&tempmsg.header;
//	am_addr_t d =h->dest;
//	am_addr_t d1 =h->src;
//
//	uint8_t *pkt = (uint8_t *)&tempmsg;
//    for(i=0; i<sizeof(msg); i++){
//    	 std::cout << pkt[i] <<" ";
//    }
//    std::cerr<< std::endl;
//	radio* pkt = (radio*)((message_t*)msg)->data;
//	uintptr_t *raw_ptr;
//	uint i;
//	raw_ptr = (uintptr_t *) (((message_t*)msg)->data - sizeof(ns3packet_header_t));
	switch (func) {
		case 0:
//			printf("bytes of struct located at 0x%08lx\n",(uintptr_t) raw_ptr);
//			for(i=sizeof(msg); i >0 ; i--) {
//				printf("%u ", raw_ptr[i]);
//				if(i%16 == 15) // Print a newline every 16 bytes.
//					printf("\n");
//				}
//				printf("\n");


			//std::cerr <<"gatewayRadio got msg: "<< sizeof(msg) << std::endl;

			std::cerr <<"header dest: "<< ((ns3pack*)hdr)->dest << std::endl;
			std::cerr <<"header src: "<< ((ns3pack*)hdr)->src << std::endl;
			((TosToNs3Proxy *)obj)->msgToChannel((ns3pack*)hdr,msg);
//			std::cerr<<"data " << pkt->counter << std::endl;
			//std::cerr <<"destination "<< d <<" "<< d1<< std::endl;
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
