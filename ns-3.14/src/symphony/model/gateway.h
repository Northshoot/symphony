/*
 * gateway.h
 *
 *  Created on: May 24, 2010
 *      Author: laurynas
 */

#ifndef GATEWAY_H_
#define GATEWAY_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tos-to-ns3-proxy.h"
#include "ns3includes.h"
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

extern   uint64_t
 gateway(void *tthis,int call, int arg){
  // or possibly an array of function pointers
 // printf("gateway call %u\n", call);
	switch (call) {
		case 0:
			return ((TosToNs3Proxy *)tthis)->confirmSet(arg);
			break;

		case 1:
			return ((TosToNs3Proxy *)tthis)->getNow(arg);
			break;
		case 2:
			//std::cout << "((TosToNs3Proxy *)tthis)->getNow() "<< ((TosToNs3Proxy *)tthis)->getNow(arg) << std::endl;
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

/**
 * Dispatching of functions,
 * We just move call to the proxy object
 */
extern int gatewayRadio(void *obj, DeviceCall call, int val1, int val2, void* hdr, void* msg){
	//printf("\t\tgatewayRadio (%d) %d\n",  ((TosToNs3Proxy *)obj)->m_node_id, call);
	return ((TosToNs3Proxy *)obj)->deviceCommand(call, val1, val2, hdr,msg);

}

extern int gatewaySensor(void *obj, SensorCall call){
  return ((TosToNs3Proxy *)obj)->SensorCommand(call);
}

extern void gatewayApplication(void *obj, ApplicationCall call, uint16_t length, void * data){
  return ((TosToNs3Proxy *)obj)->ApplicationCommand(call, length, data);
}

extern uint64_t gatewayTime(void *obj,  PRECISION prec) {
  uint64_t a = 0;
    printf("gatewayTime call %u\n", prec);
    a= ((TosToNs3Proxy *)obj)->timeCommand(prec);
	return a;
}

//TODO: make a pretty printer from the nodes
extern void gatewayLogg(void *obj,  char* func, int line_num, char* msg){
//  char string[]={"this$is$a$string"};
//
//  char searchchar = '$';
//  char replacechar = ':';
//  const char *valueptr; // will store pointer retrieved from strchr
//
//  valueptr = strchr(string, searchchar);
//  if(valueptr != NULL) // Check for NULL
//       *valueptr = replacechar;
//
//  // Loop until end of string
//  while (valueptr !=NULL) {
//      valueptr = strchr(valueptr + 1, searchchar);
//      if(valueptr != NULL) // Check for NULL
//           *valueptr = replacechar;
//  }

  //printf("(%d) - %s::%d - %s\n",  ((TosToNs3Proxy *)obj)->m_node_id, func, line_num, msg);
	printf("#######################\n\n\tNOT YET IMPLEMENTED\n#######################\n");
}
#endif /* GATEWAY_H_ */
