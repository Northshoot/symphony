/*
 * LibToTosProxy.cpp
 *
 *  Created on: Apr 27, 2010
 *      Author: Laurynas Riliskis
 */
#include <iostream>
#include "ns3/assert.h"
#include "ns3/pointer.h"

#include "ns3/wifi-mac-header.h"
#include "ns3/callback.h"

#include "tos-node.h"
#include "tos-to-ns3-proxy.h"
#include "gateway.h"
#include "calls-to-ns3.h"
#include "tos-net-device.h"


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

int
TosToNs3Proxy::deviceCommand(DeviceCall call, int val1, int val2, void * obj1, void * obj2){

	switch (call) {
	case RADIO_ON:
		return m_tosnetdevice->DeviceTurnOn();
		break;

	case RADIO_START:
		return m_tosnetdevice->DeviceTurnOn();
		break;

	case RADIO_SLEEP:
		return m_tosnetdevice->DeviceStandby();
		break;

	case RADIO_STOP:
		return m_tosnetdevice->DeviceTurnOff();
		break;

	case RADIO_SET_CHANNEL:
		//perform sanity check
		if(val1>0)
			return m_tosnetdevice->DeviceSetChannel(val1);
		else
			return -1;
		break;

	case RADIO_GET_CHANNEL:
		return m_tosnetdevice->DeviceGetChannel();
		break;

	case RADIO_SET_TX_POWER:
		return -1;
		break;
	case RADIO_GET_TX_POWER:

		return -1;
		break;
	case RADIO_SEND:
		//keep the tongue in right mouth
		//TODO: make some sanity check
	        std::cerr <<" m_tosnetdevice->DeviceSend "<<std::endl;
		return m_tosnetdevice->DeviceSend(obj2);
		break;

	case RADIO_CANCEL:
		m_tosnetdevice->DeviceCancel((message_t *)obj2);
		return  0;
	default:
		//OPS! never ever go here!
		//if you have -> core dump :D
		std::cerr <<" bad index no where to go "<< call<< std::endl;
		return -1;
		break;
}
//just in case if anything else fails
return -1;
}


TosToNs3Proxy::~TosToNs3Proxy() {
	// TODO Auto-generated destructor stub
}

