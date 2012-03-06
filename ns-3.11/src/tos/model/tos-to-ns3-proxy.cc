/*
 * LibToTosProxy.cpp
 *
 *  Created on: Apr 27, 2010
 *      Author: Laurynas Riliskis
 */
#include <iostream>
#include "ns3/assert.h"
#include "ns3/pointer.h"
#include "ns3/packet.h"
#include "ns3/wifi-mac-header.h"
#include "ns3/callback.h"
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

void
TosToNs3Proxy::setDevice(ns3::Ptr<ns3::TosNetDevice> device){
	m_tosnetdevice  = device;
}
void
TosToNs3Proxy::msgToTos(ns3pack* hdr, void * msg){ }


void
TosToNs3Proxy::msgToNs3(ns3pack* hdr, void * msg){
	m_tosnetdevice->DeviceSend(hdr, msg);


}
void
TosToNs3Proxy::setDownlink(void *  tos){
	downlink=(tosfuncvoid)tos;
}
void
TosToNs3Proxy::sendDown(ns3::Ptr<ns3::Packet> pkt ,const ns3::WifiMacHeader *hdr){
	std::cerr <<"got packet" << std::endl;
	//downlink(msg);
}

TosToNs3Proxy::~TosToNs3Proxy() {
	// TODO Auto-generated destructor stub
}

