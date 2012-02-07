/*
 * TosToLibProxy.cpp
 *
 *  Created on: Apr 21, 2010
 *      Author: laurynas
 */
#include <iostream>
#include "ns3-to-tos-proxy.h"


Ns3ToTosProxy::Ns3ToTosProxy() { }



void
Ns3ToTosProxy::setStartMote(void * tos){
	//std::cout<<"TosToLibProxy boot node " << (int)tos <<std::endl;
	pass__sim_main_start_mote=(tosfunc)tos;
}
void
Ns3ToTosProxy::setTimerFired(void *  tos){
	pass__timerFired=(tosfunc)tos;
}
void
Ns3ToTosProxy::runNextEvent(void *  tos){
	pass__runNext=(tosfunc)tos;
}
uint32_t
Ns3ToTosProxy::timerFired(uint32_t a){
	//std::cout<<"TosToLibProxy::timerFired() "<<a<<std::endl;
	pass__timerFired(a);

	return a;
}
void
Ns3ToTosProxy::start_mote(int id){
//	std::cout<<"TosToLibProxy boot node " <<std::endl;
	pass__sim_main_start_mote(id);

}

Ns3ToTosProxy::~Ns3ToTosProxy() {

}
