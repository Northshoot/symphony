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

#include <stdint.h>
#include "tos-to-lib-proxy.h"
#include "lib-to-tos-proxy.h"
//#include "tos-node.h"
//#include "simu-clock.h"


/**
 * cast type of functions from ns to tos
 */
typedef int(LibToTosProxy::*fucnpoint)(int);

class TinyBridge {
public:
	//TinyBridge(ns3::TosNode * tos, const char * lib);

	TinyBridge( const char * lib);
	/**
	 * Returns pointer to tos library function
	 * For now its predefined
	 */
	void * getFunc(const char *);
	
	/**
	 * Destructor of the bridge class
	 * 
	 */
    ~TinyBridge();
    
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
    //ns3::TosNode *tosnode;
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

#endif /* TINYBRIDGE_H_ */
