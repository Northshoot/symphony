/*
 * TinyBridge.cpp
 *
 *  Created on: Apr 27, 2010
 *      Author: laurynas
 */

#define __USE_GNU 1



#include <iostream>
#include <cstdlib>
#include <ctime>
#include <dlfcn.h>



#include "tiny-bridge.h"

//TinyBridge::TinyBridge(ns3::TosNode *tos, const char * lib) {
//	tosnode		= tos;
//	libname		= lib;
//
//	//create proxy's
//	//libtotos	= new LibToTosProxy(tosnode); //ns3 to tos
//	tostolib	= new TosToLibProxy(); //tos to ns3
//
//	bridgeObjects();
//}
TinyBridge::TinyBridge(const char * lib) {

	libname		= lib;

	//create proxy's
	libtotos	= new LibToTosProxy(); //ns3 to tos
	tostolib	= new TosToLibProxy(); //tos to ns3

	bridgeObjects();
}

void
TinyBridge::bridgeObjects(){
	//open instance of the library  LM_ID_NEWLM
	handler = dlmopen( LM_ID_NEWLM ,libname, RTLD_LAZY );
    if (!handler) {
        std::cerr << handler << "Cannot open library: " << dlerror() << '\n';
        exit(1);
    } else {
		tosnode->setProxy(tostolib); // set link from tos to ns3
		((tosfunc)getFunc("setUniqueID"))(1); //set nodes id in lib
		setObj=(tosfunc)getFunc("setProxy");
		setObj((long)libtotos); //set link from ns3 to tos
		tostolib->setStartMote(getFunc("sim_main_start_mote")); //boot node
		tostolib->setTimerFired(getFunc("tickFired")); // connect clock tick
		run_next = (tosfunc)getFunc("runNextEventExternal");

    }
}

void *
TinyBridge::getFunc(const char* func_name){
	char *error=NULL;
	void * tmp = dlsym(handler,func_name);
	if( (error = dlerror()) != NULL){
		std::cerr<<"func "<< tmp <<'\n';
		std::cerr << "Cannot get function: " << func_name <<" " << error << '\n';
		exit(1);
	} else {
		return tmp;
	}
}

TinyBridge::~TinyBridge() {
	//delete tostolib;
	delete libtotos;
	//delete proxy;
	dlclose(handler);
}
