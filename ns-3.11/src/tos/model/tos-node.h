/*
 * TosNode.h
 *
 *  Created on: Mar 4, 2010
 *      Author: laurynas
 */

#ifndef TOSNODE_H_
#define TOSNODE_H_
#include <vector>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <dlfcn.h>
#include <link.h>

#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/callback.h"

#include "simu-clock.h"
#include "tos-to-lib-proxy.h"
#include "ns3/lib-to-tos-proxy.h"


//typedef int(LibToTosProxy::*fucnpoint)(int);

namespace ns3 {


class TosNode : public Object{
public:

	static TypeId GetTypeId (void);

	TosNode();
	/**
	 * Creates TosNode with
	 * bootTime 0 and shutdown inf
	 */
	TosNode(uint32_t node_id);
	/**
	 * Creates TosNode with
	 * bootTime bootTime and shutdown inf
	 */
	TosNode(uint32_t node_id, Time bootTime);

	TosNode(uint32_t node_id ,Time bootTime,const char * lib);

	/**
	 * Starts tos implementation of node at bootTime
	 */
	void BootBooted(void);

	/**
	 * ShutDowns the tos implemenation of node
	 * calls DoDispose()
	 */
	void ShutDownNode(Time ttl);

	void tickTime(int);




	uint32_t  getNow();
	uint32_t wrapFire(uint32_t);
	/**
	 * \returns the unique id of this node.
	 *
	 * This unique id happens to be also the index of the TosNode into
	 * the TosNodeList.
	 */
	uint32_t GetId (void) const;

	/**
	 * Callback function
	 */
	Callback<uint32_t,uint32_t> callBackFromClock;

	SimuClock * getClock();

	virtual ~TosNode();
protected:
	/**
	 * The dispose method. Subclasses must override this method
	 * and must chain up to it by calling Node::DoDispose at the
	 * end of their own DoDispose method.
	 */
	virtual void DoDispose (void);

	virtual void DoStart(void);


private:
	 void Construct (void);

	SimuClock *	simuclock;
	uint32_t    node_id;         	// Node id for this node
	uint32_t    m_sid;        	// System id for this node
	Time        m_bootTime; 	//boot time of the node
	Time        m_shutDownTime;	//shut down time of the node
	Time		m_timer;
	EventId		timer_event;
	EventId		m_boot_event;	//boot event
	EventId		m_shutdown_event;//shut down event
	bool m_started;

	/**
	 * Returns pointer to tos library function
	 * For now its predefined
	 */
	void * getFunc(const char * func);

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
	const char * m_libname;
	/**
	 * Error variable, used then opening library
	 */
	char *error;
	/**
	 * Pointer to proxy for library to tos node communications
	 */
	LibToTosProxy *libtotos;
	/**
	 * Pointer to proxy for tos to lib communiactions
	 */
	TosToLibProxy *tostolib;

};

}



#endif /* TOSNODE_H_ */
