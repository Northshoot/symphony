/*
 * LibToTosProxy.cpp
 *
 *  Created on: Apr 27, 2010
 *      Author: Laurynas Riliskis
 */
#include <iostream>
#include "ns3/assert.h"
#include "tos-node.h"

#include "lib-to-tos-proxy.h"
#include "gateway.h"




LibToTosProxy::LibToTosProxy(ns3::TosNode * tos) {
	//std::cout<<"confirm add "<<(void *)(&LibToTosProxy::confirmSet)<<'\n';
	tosnode=tos;
	simu_clock=tosnode->getClock();
	NS_ASSERT_MSG(simu_clock != NULL, "Clock is null in LibToTosProxy");
	//std::cout<<"clock "<<simu_clock->getTimeNow()<<'\n';
//	std::cout<<"confirm add "<<(void *)(&LibToTosProxy::confirmSet)<<'\n';

}
//fucntions for TosNode
int LibToTosProxy::confirmSet(int a){
	//std::cout<<"LibToTosProxy called: "<< a <<" time " << simu_clock->getTimeNow()<<'\n';
	//std::cout<<" time " << simu_clock->getTimeNow()<<'\n';
	return 0;
}

//functions for SimuClock

uint32_t
LibToTosProxy::getNow(int b){
	NS_ASSERT_MSG(simu_clock != NULL, "Clock is null in LibToTosProxy::getNow");
	uint32_t a = simu_clock->getTimeNow();
	std::cout<<"LibToTosProxy::getNow(void) " <<a<<std::endl;

	return a;
}


//functions for radio
void
LibToTosProxy::setDownlink(void *  tos){
	downlink=(tosfuncvoid)tos;
}

void
LibToTosProxy::sendDown(void *  msg){
	downlink(msg);
}

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
