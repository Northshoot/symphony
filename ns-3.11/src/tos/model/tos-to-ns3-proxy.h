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

#ifdef __cplusplus

/**
 * Important that include does only for CPP
 * otherwise linking with C will fail
 * Which results in segfault
 */
#include "ns3includes.h"
#include "tos-mac-low.h"
//#include "tos-node.h"
#include "simu-clock.h"
typedef int (*tosfuncvoid)(void*);

class TosNode;

class TosToNs3Proxy {
   friend class TosNode;
    public:
   	   TosToNs3Proxy();
   	   //LibToTosProxy( ns3::TosNode * tos);
		/**
		 * Here goes functions that can be
		 * called from C-library
		 * Functions are proxied to tos node
		 */
	   int confirmSet(int);
	   void setMac(ns3::TosMacLow *mac);

	   uint32_t getNow(int);
	   void setDownlink(void *  tos);
	   void sendDown( void * msg);
	   void msgToChannel(ns3pack* hdr, void * msg);
	   ns3::SimuClock * simu_clock;

	~TosToNs3Proxy();
private:


    tosfuncvoid downlink;
    ns3::TosMacLow *mac;

    //LibToTosProxyToC * proxy;
	
};


extern "C" {
#endif

int gateway(void *obj,int func,int arg);
int setProxy(void * obj);

int gatewayRadio(void *obj, int func, void * hdr, void* msg);


#ifdef __cplusplus
}
#endif

#endif /* TOSTONS3PROXY_H_ */
