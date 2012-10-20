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
	//TODO: dispatch from TosToNs3Proxy as in radio gateway
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
	return ((TosToNs3Proxy *)obj)->deviceCommand(call, val1, val2, hdr,msg);

}

extern int gatewaySensor(void *obj, SensorCall call){
  return ((TosToNs3Proxy *)obj)->SensorCommand(call);
}

void gatewayApplication(void *obj, ApplicationCall call, uint16_t length, void * data){
  return ((TosToNs3Proxy *)obj)->ApplicationCommand(call, length, data);
}


extern void gatewayLogg(void *obj, const char* func, int line_num,const char* msg){
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

  printf("%s::%d - %s\n", func, line_num, msg);

}
#endif /* GATEWAY_H_ */
