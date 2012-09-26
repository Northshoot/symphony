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
#include <stdlib.h>
#include <dlfcn.h>
#include <link.h>

#include "ns3/object.h"
#include "ns3/ptr.h"

#include "tos-to-lib-proxy.h"
#include "lib-to-tos-proxy.h"
#include "tos-node.h"
#include "simu-clock.h"
#include "tiny-bridge.h"

namespace ns3 {
NS_OBJECT_ENSURE_REGISTERED(TinyBridge);

TypeId
TinyBridge::GetTypeId(void)
{
	static  TypeId tid = TypeId("ns3::TinyBridge");

	return tid;
}
TinyBridge::TinyBridge() {
 //what to do?
}

TinyBridge::TinyBridge(ns3::TosNode *tos) {
	tosnode		= tos;
	//default libname
	libname		= "./libtos.so";

	//create proxy's
	libtotos	= new LibToTosProxy(tosnode); //ns3 to tos
	tostolib	= new TosToLibProxy(); //tos to ns3

	//bridgeObjects();
}

TinyBridge::TinyBridge(ns3::TosNode *tos, const char * lib) {
	tosnode		= tos;
	libname		= lib;

	//create proxy's
	libtotos	= new LibToTosProxy(tosnode); //ns3 to tos
	tostolib	= new TosToLibProxy(); //tos to ns3

	//bridgeObjects();
}

void
TinyBridge::DoStart(){
	//open instance of the library  LM_ID_NEWLM
	std::cerr << "doStart" << '/n';
	handler = dlmopen( LM_ID_NEWLM ,libname, RTLD_LAZY );

    if (!handler) {
        std::cerr << handler << "Cannot open library: " << dlerror() << '\n';
        exit(1);
    } else {
		tosnode->setProxy(tostolib); // set link from tos to ns3
		((tosfunc)getFunc("setUniqueID"))(tosnode->GetId()); //set nodes id in lib
		setObj=(tosfunc)getFunc("setProxy");
		setObj((long)libtotos); //set link from ns3 to tos
		tostolib->setStartMote(getFunc("sim_main_start_mote")); //boot node
		tostolib->setTimerFired(getFunc("tickFired")); // connect clock tick
		run_next = (tosfunc)getFunc("runNextEventExternal");
		libtotos->setDownlink(getFunc("receivePkt"));

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
void
TinyBridge::DoDispose() {
	dlclose(handler);
	delete tostolib;
	delete libtotos;

}
TinyBridge::~TinyBridge() {

}
}
