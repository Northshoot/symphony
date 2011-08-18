/*
 * TosNode.cpp
 *
 *  Created on: Mar 4, 2010
 *      Author: laurynas
 */
#include <vector>

#include "ns3/object.h"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/callback.h"
#include "ns3/node.h"
#include "SimuClock.h"
#include "TosNode.h"
#include "ns3/tos-node-list.h"
#include "ns3/tos-net-device.h"

using namespace std;



namespace ns3 {
NS_OBJECT_ENSURE_REGISTERED(TosNode);



TypeId
TosNode::GetTypeId(void)
{
	static  TypeId tid = TypeId("ns3::TosNode")
				.SetParent<Node> ()
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
TosNode::TosNode(uint32_t node_id ,Time bootTime) :
				node_id(node_id), m_bootTime(bootTime)
{

	cout<< "Node created " << node_id << " "<< Simulator::Now().GetMilliSeconds() << " ms"<<endl;
	//cout<< "setting boot time " <<endl;
	Simulator::Schedule(m_bootTime, &TosNode::BootBooted, this);
	// build callback instance which points to MyCb::cbTwo
	callBackFromClock = MakeCallback (&TosNode::wrapFire, this);
//
	simuclock = new SimuClock(NANOSECOND,NONE, callBackFromClock);



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
TosNode::Construct(void)
{
	m_id=TosNodeList::Add(this);
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
	Node::DoStart();

	Simulator::RunOneEvent();
	Simulator::Remove ( m_boot_event );

}

void
TosNode::setProxy(TosToLibProxy * ttl){
	tostolib=ttl;
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

	//finally despose object
	Node::DoDispose();
}

TosNode::~TosNode() {
	//everything removed in DoDispose
	cout<<"TosNode::DoDispose(void)"<<endl;
}

}
