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

#include "ns3/node.h"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/callback.h"

#include "SimuClock.h"
#include "ns3/TosToLibProxy.h"

namespace ns3 {

class TosNode : public Object{
public:
	static TypeId GetTypeId (void);
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

	virtual ~TosNode();
	
	/**
	 * Set proxy object to the node image
	 */

	void setProxy(TosToLibProxy * ttl);
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


protected:
  /**
   * The dispose method. Subclasses must override this method
   * and must chain up to it by calling Node::DoDispose at the
   * end of their own DoDispose method.
   */
  virtual void DoDispose (void);


	private:
  	  	SimuClock *	simuclock;
		uint32_t    node_id;         	// Node id for this node
		uint32_t    m_sid;        	// System id for this node
		Time        m_bootTime; 	//boot time of the node
		Time        m_shutDownTime;	//shut down time of the node
		Time		m_timer;
		EventId		timer_event;
		EventId		m_boot_event;	//boot event
		EventId		m_shutdown_event;//shut down event
		TosToLibProxy *	tostolib;
    
};

}
//wraping functions for C


#endif /* TOSNODE_H_ */
