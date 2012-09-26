/*
 * TinyBridge.h
 *
 *  Created on: Apr 27, 2010
 *      Author: laurynas
 */
#ifndef __USE_GNU
#define __USE_GNU
#endif

#ifndef TINYBRIDGE_H_
#define TINYBRIDGE_H_

#include "ns3/object.h"
#include "ns3/ptr.h"

#include "tos-to-lib-proxy.h"
#include "lib-to-tos-proxy.h"
#include "tos-node.h"
#include "simu-clock.h"


/**
 * cast type of functions from ns to tos
 */
typedef int(LibToTosProxy::*fucnpoint)(int);

namespace ns3 {

class TinyBridge {
public:
	static TypeId GetTypeId (void);

	TinyBridge() ;

	TinyBridge(ns3::TosNode *tos);

	TinyBridge(ns3::TosNode * tos, const char * lib);
	/**
	 * Returns pointer to tos library function
	 * For now its predefined
	 */
	void * getFunc(const char *);
	void DoStart (void);
	
	/**
	 * Destructor of the bridge class
	 * 
	 */
	virtual ~TinyBridge();
    
protected:
  /**
   * The dispose method. Subclasses must override this method
   * and must chain up to it by calling Node::DoDispose at the
   * end of their own DoDispose method.
   */
   void DoDispose (void);

private:
    /**
     * Function that opens library
     * and bridges objects and lib together
     */
    void bridgeObjects(void);
    
    /**
     * library handler
     */
    void *handler;   
    
    /**
     * Unique id of this
     */
    int un;

    /**
     * Function to set proxy in node image
     */
    tosfunc setObj;

    tosfunc run_next;
    /**
     * name of the library to open
     */
    const char * libname;
    /**
     * Error variable, used then opening library
     */
    char *error;
    /**
     * Pointer to TosNode class
     */
    ns3::TosNode *tosnode;
    /**
     * Pointer to proxy for library to tos node communications
     */
    LibToTosProxy *libtotos;
    /**
     * Pointer to orxy for tos to lib communiactions
     */
    TosToLibProxy *tostolib;

    /**
     * Node clock
     */
    //SimuClock * clock;


    //LibToTosPointers *proxy;
};
}

#endif /* TINYBRIDGE_H_ */
