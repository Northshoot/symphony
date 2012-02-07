/*
 * LibToTosProxy.cpp
 *
 *  Created on: Apr 27, 2010
 *      Author: Laurynas Riliskis
 */
#include <iostream>
#include "ns3/assert.h"
#include "ns3/ptr.h"
#include "ns3/packet.h"
#include "tos-node.h"

#include "tos-to-ns3-proxy.h"
#include "gateway.h"

#include "ns3/packet.h"



TosToNs3Proxy::TosToNs3Proxy() { }

//fucntions for TosNode
int
TosToNs3Proxy::confirmSet(int a){
	std::cout<<"LibToTosProxy called: "<< a <<" time " << simu_clock->getTimeNow()<<'\n';
	return 0;
}

//functions for SimuClock
uint32_t
TosToNs3Proxy::getNow(int b){
	NS_ASSERT_MSG(simu_clock != NULL, "Clock is null in LibToTosProxy::getNow");
	uint32_t a = simu_clock->getTimeNow();
	std::cout<<"LibToTosProxy::getNow(void) " <<a<<std::endl;

	return a;
}


//functions for radiooh
void
TosToNs3Proxy::setMac(ns3::TosMacLow *mac){
	this->mac=mac;
}

void
TosToNs3Proxy::msgToChannel(ns3pack* hdr, void * msg){
	std::cerr <<"header dest: "<< ((ns3pack*)hdr)->dest << std::endl;
	std::cerr <<"header src: "<< ((ns3pack*)hdr)->src << std::endl;
	mac->TransmitData(ns3::Create<ns3::Packet>(20));
}
void
TosToNs3Proxy::setDownlink(void *  tos){
	downlink=(tosfuncvoid)tos;
}
void
TosToNs3Proxy::sendDown(void *  msg){
	downlink(msg);
}

TosToNs3Proxy::~TosToNs3Proxy() {
	// TODO Auto-generated destructor stub
}

