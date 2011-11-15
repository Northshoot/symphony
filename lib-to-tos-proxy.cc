/*
 * LibToTosProxy.cpp
 *
 *  Created on: Apr 27, 2010
 *      Author: Laurynas Riliskis
 */
#include <iostream>
//#include "tos-node.h"

#include "lib-to-tos-proxy.h"
#include "gateway.h"




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


//functions for radio

LibToTosProxy::~LibToTosProxy() {
	// TODO Auto-generated destructor stub
}

//int gateway(void *tthis,int call,int arg){
////  std::cout << "gateway " << arg << std::endl;
//  // here should be a switch case on "call"
//  // or possibly an array of function pointers
//  if(call == 1)
//	  return ((LibToTosProxy *)tthis)->confirmSet(arg);
//  else
//	  return ((LibToTosProxy *)tthis)->tickTime(arg);
//}
