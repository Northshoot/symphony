/*
 * LibToTosProxy.cpp
 *
 *  Created on: Apr 27, 2010
 *      Author: Laurynas Riliskis
 */
#include <iostream>
#include <inttypes.h>
//#include "tos-node.h"

#include "lib-to-tos-proxy.h"





LibToTosProxy::LibToTosProxy() {
	//std::cout<<"confirm add "<<(void *)(&LibToTosProxy::confirmSet)<<'\n';
//	tosnode=tos;
//	simu_clock=tosnode->getClock();

	//std::cout<<"clock "<<simu_clock->getTimeNow()<<'\n';
//	std::cout<<"confirm add "<<(void *)(&LibToTosProxy::confirmSet)<<'\n';

}
//fucntions for TosNode
int LibToTosProxy::confirmSet(int a){
	std::cout<<"LibToTosProxy called: "<< a <<" confirmSet(int a)"<<'\n';
	//std::cout<<" time " << simu_clock->getTimeNow()<<'\n';
	return 0;
}

//functions for SimuClock

uint32_t
LibToTosProxy::getNow(int b){
	//uint32_t a = simu_clock->getTimeNow();
	std::cout<<"LibToTosProxy::getNow(void) " <<b<<std::endl;

	return b;
}

int
LibToTosProxy::sendMessage(void * msg){
	std::cout<<"sendMessage(void * msg)" << sizeof(msg)<<std::endl;
	return 0;
}

//functions for radio

LibToTosProxy::~LibToTosProxy() {
	// TODO Auto-generated destructor stub
}

int gateway(void *tthis,int call, int arg){
 //std::cout << "gateway call "<< call <<" arg " << arg << std::endl;
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
			//std::cout << "((LibToTosProxy *)tthis)->getNow() "<< ((LibToTosProxy *)tthis)->getNow(arg) << std::endl;
			return 0;
			break;

		default:
			//OPS! never ever go here!
			//if you have -> core dump :D
			//std::cerr <<" bad index no where to go "<< call<< std::endl;
			return -1;
			break;
	}
}

int gatewayRadio(void *tthis,int call, void *msg){
	switch (call) {
		case 0:
			return ((LibToTosProxy *)tthis)->sendMessage(msg);
			break;

		default:
			//OPS! never ever go here!
			//if you have -> core dump :D
			//std::cerr <<" bad index no where to go "<< call<< std::endl;
			return -1;
			break;
	}
}

