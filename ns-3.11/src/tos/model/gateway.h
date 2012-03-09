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
#include "calls-to-ns3.h"
/**
 * This function is used by all objects.
 * C does not care about void * tthis
 * so we can exploit it in order to save appropriate instance
 * of the object in the tos lib instance.
 */

//TODO: make this auto generated
void
printPacket( char *buf , int size){
	int i;
	printf("SIZE: %d\n", size);
	for (i=0;i<size-1;i++){
		printf("%02X ", (char)buf[i]);
	}
	printf("%02X\n",buf[i]);
}

extern int gateway(void *tthis,int call, int arg){
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
	switch (func) {
		case RADIO_ON:
			return 0;
			break;

		case RADIO_START:
			return 0;
			break;

		case RADIO_SLEEP:
			return 0;
			break;

		case RADIO_STOP:
			return 0;
			break;

		case RADIO_SET_CHANNEL:
			return 0;
			break;

		case RADIO_GET_CHANNEL:
			return 0;
			break;

		case RADIO_SET_TX_POWER:
			return 0;
			break;
		case RADIO_GET_TX_POWER:

			return 0;
			break;
		case RADIO_SEND:

			((TosToNs3Proxy *)obj)->msgToNs3((ns3pack*)hdr,msg);

			return 0;
			break;


		default:
			//OPS! never ever go here!
			//if you have -> core dump :D
			std::cerr <<" bad index no where to go "<< func<< std::endl;
			return -1;
			break;
	}
	return -1;
}

#endif /* GATEWAY_H_ */
