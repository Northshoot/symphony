/*
 * LibToTosProxy.h
 *
 *  Created on: Apr 27, 2010
 *      Author: Laurynas Riliskis
 */

#ifndef TOSTONS3PROXY_H_
#define TOSTONS3PROXY_H_
/**
 * This struct is compiled in to C
 * Then the objects is send to C library as struct
 */
#include "calls-to-ns3.h"
#ifdef __cplusplus

/**
 * Important that include does only for CPP
 * otherwise linking with C will fail
 * Which results in segfault
 */
#include "ns3/ptr.h"
#include "ns3/wifi-mac-header.h"

#include "simu-clock.h"
#include "tos-net-device.h"

class TosToNs3Proxy {
   friend class TosNode;
    public:
   	   TosToNs3Proxy();

		/**
		 * Here goes functions that can be
		 * called from C-library
		 * Functions are proxied to tos node
		 */
	   int confirmSet(int);
	   void setDevice(ns3::Ptr<ns3::TosNetDevice> device);
	   uint32_t getNow(int);
	   void setDownlink(void *  tos);

	   //we define a generic function for calls from TinyOS to
	   //ns3 then each function is dispatched to the right format by casting
	   int deviceCommand(DeviceCall call, int val1, int val2, void * obj1, void * obj2 );
	   ns3::Ptr<ns3::SimuClock>  simu_clock;

	~TosToNs3Proxy();
private:

     ns3::Ptr<ns3::TosNetDevice> m_tosnetdevice;


	
};


extern "C" {
#endif

int gateway(void *obj,int func,int arg);
int setProxy(void * obj);

int gatewayRadio(void *obj, DeviceCall call, int val1, int val2, void* hdr, void* msg);
void gatewayLogg(void *obj, const char* func, int line_num,const char* msg);

#ifdef __cplusplus
}
#endif

#endif /* TOSTONS3PROXY_H_ */
