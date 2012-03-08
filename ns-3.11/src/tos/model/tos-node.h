/*
 * TosNode.h
 *
 *  Created on: Mar 4, 2010
 *      Author: laurynas
 */

#ifndef TOSNODE_H_
#define TOSNODE_H_
#include <vector>

#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/callback.h"
#include "ns3/node.h"
#include "ns3/ptr.h"

#include "simu-clock.h"
#include "ns3-to-tos-proxy.h"
#include "tos-to-ns3-proxy.h"
#include "tos-net-device.h"


//typedef int(LibToTosProxy::*fucnpoint)(int);

namespace ns3 {


class TosNode : public Node{
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

	  /**
	   * \param device WsnTosDevice to associate to this node.
	   * \returns the index of the TosNetDevice into the Node's list of
	   *          NetDevice.
	   *
	   * Associate this device to this node.
	   */
	  uint32_t AddDevice (Ptr<TosNetDevice> device);
	  /**
	   * \param index the index of the requested NetDevice
	   * \returns the requested TosNetDevice associated to this Node.
	   *
	   * The indexes used by the GetDevice method start at one and
	   * end at GetNDevices ()
	   */
	  Ptr<TosNetDevice> GetDevice (uint32_t index) const;
	  /**
	   * \returns the number of NetDevice instances associated
	   *          to this Node.
	   */
	  uint32_t GetNDevices (void) const;


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
	uint32_t    m_id;         // Node id for this node
	SimuClock *	simuclock;
	uint32_t    m_sid;        	// System id for this node
	Time        m_bootTime; 	//boot time of the node
	Time        m_shutDownTime;	//shut down time of the node
	Time		m_timer;
	EventId		timer_event;
	EventId		m_boot_event;	//boot event
	EventId		m_shutdown_event;//shut down event
	//reference to the
	Ptr<Node>	m_node;
	std::vector<Ptr <TosNetDevice> > m_devices;
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
	TosToNs3Proxy *tostons;
	/**
	 * Pointer to proxy for tos to lib communiactions
	 */
	Ns3ToTosProxy *nstotos;

};

}



#endif /* TOSNODE_H_ */
