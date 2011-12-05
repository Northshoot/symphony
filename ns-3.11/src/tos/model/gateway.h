/*
 * gateway.h
 *
 *  Created on: May 24, 2010
 *      Author: laurynas
 */

#ifndef GATEWAY_H_
#define GATEWAY_H_
#include "lib-to-tos-proxy.h"

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

extern int gatewayRadio(void *obj,int func,void *msg){
	switch (func) {
		case 0:

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
