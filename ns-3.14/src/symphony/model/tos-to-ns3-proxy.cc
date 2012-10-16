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
#include "raw-sensor.h"


TosToNs3Proxy::TosToNs3Proxy() { }

//functions for TosNode
int
TosToNs3Proxy::confirmSet(int a){
	return 0;
}

//functions for SimuClock
uint32_t
TosToNs3Proxy::getNow(int b){
	NS_ASSERT_MSG(simu_clock != NULL, "Clock is null in LibToTosProxy::getNow");
	uint32_t a = simu_clock->getTimeNow();
	//std::cout<<"LibToTosProxy::getNow(void) " <<a<<std::endl;

	return a;
}

void
TosToNs3Proxy::setDevice(ns3::Ptr<ns3::TosNetDevice> device){
	m_tosnetdevice  = device;
}

void
TosToNs3Proxy::SetSensor(ns3::Ptr<ns3::RawSensor> sens)
{
  m_sensor=sens;
}
int
TosToNs3Proxy::deviceCommand(DeviceCall call, int val1, int val2, void * obj1, void * obj2){
        NS_ASSERT_MSG(m_tosnetdevice != NULL, "Device is NULL");
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
	        //std::cerr <<" m_tosnetdevice->DeviceSend "<<std::endl;
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

int
TosToNs3Proxy::SensorCommand(SensorCall call)
{

 NS_ASSERT_MSG(m_sensor != NULL, "Sensor is null");

  switch (call) {
  case SENSOR_ON:
           m_sensor->DoStart();
           return 1;
          break;

  case SENSOR_OFF:
           m_sensor->DoDispose();
           return 1;
          break;

  case SENSOR_GET_DATA:
    NS_ASSERT_MSG(false," bad index no where to go "+ call);
          break;

  case SENSOR_RESET:
    NS_ASSERT_MSG(false," bad index no where to go "+ call);
          break;

    default:
          //OPS! never ever go here!
          //if you have -> core dump :D
          NS_ASSERT_MSG(false," bad index no where to go "+ call);
          return -1;
          break;
}
//just in case if anything else fails
return -1;
}
TosToNs3Proxy::~TosToNs3Proxy() {}

