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


//functions for radiooh
void
TosToNs3Proxy::setMac(ns3::TosMacLow *mac){
	this->mac=mac;
	this->mac->SetRxCallback(ns3::MakeCallback (&TosToNs3Proxy::sendDown, this));
}

void
TosToNs3Proxy::msgToChannel(ns3pack* hdr, void * msg){
	std::cerr <<"header dest: "<< ((ns3pack*)hdr)->dest << std::endl;
	std::cerr <<"header src: "<< ((ns3pack*)hdr)->src << std::endl;

	ns3::WifiMacHeader whdr;
    whdr.SetTypeData ();
    whdr.SetAddr1 ("00:00:00:00:00:00");
    whdr.SetAddr2 ("00:00:00:00:00:00");
    whdr.SetDsNotFrom ();
    whdr.SetDsNotTo ();
    whdr.SetSequenceNumber (1);
    whdr.SetFragmentNumber (0);
    whdr.SetNoMoreFragments ();
    whdr.SetNoRetry ();
    ns3::Ptr<ns3::Packet> pkt = ns3::Create<ns3::Packet> (ns3::Packet(reinterpret_cast<uint8_t const
      		*>("hello"),5));
	mac->TransmitData(pkt, &whdr);

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

