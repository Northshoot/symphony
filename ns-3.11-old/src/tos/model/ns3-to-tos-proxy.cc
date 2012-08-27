/*
 * TosToLibProxy.cpp
 *
 *  Created on: Apr 21, 2010
 *      Author: laurynas
 */
#include <iostream>
#include "ns3-to-tos-proxy.h"


Ns3ToTosProxy::Ns3ToTosProxy() {
	m_tos_functions.set_empty_key("empty");
}


void
Ns3ToTosProxy::addFunction(std::string name, void * pointer){
	m_tos_functions[name]=pointer;

}

void
Ns3ToTosProxy::setStartMote(void * tos){

	pass__sim_main_start_mote=(tosfunc)tos;
}
void
Ns3ToTosProxy::setTimerFired(void *  tos){
	pass__timerFired=(tosfunc)tos;
}

void
Ns3ToTosProxy::setDownlink(void * tos){
	pass__rxMsg =(tosfuncvoid)tos;
}

void
Ns3ToTosProxy::runNextEvent(void *  tos){
	pass__runNext=(tosfunc)tos;
}
uint32_t
Ns3ToTosProxy::timerFired(uint32_t a){
	pass__timerFired(a);
	return a;
}

void
Ns3ToTosProxy::start_mote(int id){
	((tosfunc)m_tos_functions["sim_main_start_mote"])(id);

}

void
Ns3ToTosProxy::rxMsg(void *msg){
	std::cout<<"Ns3ToTosProxy::rxMsg(void *msg) "<<std::endl;
	pass__rxMsg(msg);
}

Ns3ToTosProxy::~Ns3ToTosProxy() {

}
