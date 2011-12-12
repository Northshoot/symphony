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
	handler = dlmopen( LM_ID_BASE ,libname, RTLD_NOW );
    if (!handler) {
        std::cerr << handler << "Cannot open library: " << dlerror() << '\n';
        exit(1);
    } else {
    	std::cout << "TinyBridge::bridgeObjects() " << "lib is open " << '\n';
		//tosnode->setProxy(tostolib); // set link from tos to ns3
		((tosfunc)getFunc("setUniqueID"))(1); //set nodes id in lib
		std::cout << "TinyBridge::bridgeObjects() " << "setUniqueID " << '\n';
		setObj=(tosfunc)getFunc("setProxy");
		std::cout << "TinyBridge::bridgeObjects() " << "setProxy " << '\n';
		setObj((long)libtotos); //set link from ns3 to tos
		std::cout << "TinyBridge::bridgeObjects() " << "set link from ns3 to tos " << '\n';
		tostolib->setStartMote(getFunc("sim_main_start_mote")); //boot node
		std::cout << "TinyBridge::bridgeObjects() " << "sim_main_start_mote"  << '\n';
		tostolib->setTimerFired(getFunc("tickFired")); // connect clock tick
		std::cout << "TinyBridge::bridgeObjects() " << "tickFired " << '\n';
		run_next = (tosfunc)getFunc("runNextEventExternal");
		std::cout << "TinyBridge::bridgeObjects() " << "runNextEventExternal " << '\n';
		tostolib->startNode();
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
	delete tostolib;
	delete libtotos;
	//delete proxy;
	dlclose(handler);
}
