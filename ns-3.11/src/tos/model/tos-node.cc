/*
 * TosNode.cpp
 *
 *  Created on: Mar 4, 2010
 *      Author: laurynas
 */
#include <vector>
#include <iostream>
#include <dlfcn.h>
#include <link.h>

#include "ns3/object.h"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/callback.h"
#include "ns3/assert.h"

#include "simu-clock.h"
#include "tos-node.h"
#include "tos-to-lib-proxy.h"
#include "lib-to-tos-proxy.h"
#include "tos-node-list.h"

using namespace std;



namespace ns3 {
NS_OBJECT_ENSURE_REGISTERED(TosNode);



TypeId
TosNode::GetTypeId(void)
{
	static  TypeId tid = TypeId("ns3::TosNode")
				.SetParent<Object> ()
				.AddConstructor<TosNode> ();

	return tid;
}

TosNode::TosNode()
{
	TosNode(0);

}

TosNode::TosNode(uint32_t node_id)
{
	TosNode(node_id, MilliSeconds(0));

}
TosNode::TosNode(uint32_t node_id ,Time bootTime) {

	TosNode(node_id ,bootTime,"./libtos.so");
}

TosNode::TosNode(uint32_t node_id ,Time bootTime,const char * lib) :
				node_id(node_id), m_bootTime(bootTime), m_libname(lib)
{
	cout<< "Node created " << node_id << " "<< Simulator::Now().GetMilliSeconds() << " ms"<<endl;
	Construct();





}

void
TosNode::Construct (void){
	node_id = TosNodeList::Add (this);
}

uint32_t
TosNode::GetId(void) const
{
	return node_id;
}
SimuClock *
TosNode::getClock()
{
	return simuclock;
}

void
TosNode::ShutDownNode(Time ttl)
{
	m_shutdown_event = Simulator::Schedule(m_shutDownTime, &TosNode::DoDispose, this);
}

void
TosNode::BootBooted(void)
{

	simuclock->Start();
	cout<< "BootBooted " << endl;
			cout << simuclock->getTimeNow() << " ms"<<endl;
	//tickTime(100);
	//cout<<"booted node id " << node_id <<" at " <<Simulator::Now().GetMilliSeconds() <<endl;
	tostolib->start_mote(node_id);


	Simulator::RunOneEvent();
	Simulator::Remove ( m_boot_event );

}


uint32_t
TosNode::wrapFire(uint32_t a)
{
	a=simuclock->getTimeNow();
	//cout<< "Time " << a << " ms"<<endl;
	tostolib->timerFired(a);
	return 0;
}
uint32_t
TosNode::getNow()
{
	cout<< "TosNode::getNow()"<<endl;
	//simuclock->getTimeNow();
	//cout<< "Time " << simuclock->getNow() << " ms"<<endl;
	return simuclock->getTimeNow();
}


void
TosNode::DoDispose(void)
{
	cout<<"TosNode::DoDispose(void)"<<endl;
	/**
	 * Check and remove shutdown event
	 */
	cout<<"TosNode::DoDispose(void)"<<endl;
	if(m_shutdown_event.IsRunning()){
		m_shutdown_event.Cancel();
		Simulator::Remove(m_shutdown_event);
	}

	if(m_boot_event.IsRunning()){
		Simulator::Cancel(m_boot_event);
		Simulator::Remove(m_boot_event);
	}
	dlclose(handler);
	delete tostolib;
	delete libtotos;
	//finally despose object
	Object::DoDispose();
}

TosNode::~TosNode() {
	//everything removed in DoDispose
	cout<<"TosNode::~TosNode()"<<endl;
}



void
TosNode::DoStart(){	//open instance of the library  LM_ID_NEWLM
	callBackFromClock = MakeCallback (&TosNode::wrapFire, this);
	simuclock = new SimuClock(NANOSECOND,NONE, callBackFromClock);
	//create proxy's
	libtotos	= new LibToTosProxy(); //ns3 to tos

	libtotos->simu_clock=simuclock;
	tostolib	= new TosToLibProxy(); //tos to ns3
//	DoStart();
//	Object::DoStart();

	Simulator::Schedule(m_bootTime, &TosNode::BootBooted, this);
	cout<<"TosNode::DoStart()"<<endl;
	handler = dlmopen( LM_ID_NEWLM ,"./libtos.so", RTLD_LAZY );
    if (!handler) {
        std::cerr << handler << "Cannot open library: " << dlerror() << '\n';
        exit(1);
    } else {

		((tosfunc)getFunc("setUniqueID"))(GetId()); //set nodes id in lib
		setObj=(tosfunc)getFunc("setProxy");

		setObj((long)this->libtotos); //set link from ns3 to tos
		tostolib->setStartMote(getFunc("sim_main_start_mote")); //boot node
		tostolib->setTimerFired(getFunc("tickFired")); // connect clock tick
		run_next = (tosfunc)getFunc("runNextEventExternal");
		libtotos->setDownlink(getFunc("receivePkt"));
    }
    Object::DoStart();
}

void *
TosNode::getFunc(const char* func_name){
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

}
