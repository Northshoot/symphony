/*
 * LibToTosProxy.h
 *
 *  Created on: Apr 27, 2010
 *      Author: Laurynas Riliskis
 */

#ifndef LIBTOTOSPROXY_H_
#define LIBTOTOSPROXY_H_
/**
 * This struct is compiled in to C
 * Then the objects is send to C library as struct
 */

#ifdef __cplusplus
#include "ns3includes.h"
/**
 * Important that include does only for CPP
 * otherwise linking with C will fail
 * Which results in segfault
 */
#include "ns3includes.h"
#include "tos-node.h"
#include "simu-clock.h"

class LibToTosProxy {
   friend class TinyBridge;
   
    public:
   LibToTosProxy(ns3::TosNode * tos);
		/**
		 * Here goes functions that can be
		 * called from C-library
		 * Functions are proxied to tos node
		 */
	   int confirmSet(int);

	   uint32_t getNow(int);


    /**
     * Destructor
     */
	~LibToTosProxy();
private:
    ns3::TosNode * tosnode;
    ns3::SimuClock * simu_clock;

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

#endif /* LIBTOTOSPROXY_H_ */
