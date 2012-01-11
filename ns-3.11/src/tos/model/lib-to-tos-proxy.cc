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



LibToTosProxy::LibToTosProxy() {

}

//fucntions for TosNode
int LibToTosProxy::confirmSet(int a){
	std::cout<<"LibToTosProxy called: "<< a <<" time " << simu_clock->getTimeNow()<<'\n';
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

