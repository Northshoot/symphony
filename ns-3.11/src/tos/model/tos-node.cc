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
#include "ns3/uinteger.h"
#include "ns3/object-vector.h"
#include "ns3/global-value.h"
#include "ns3/assert.h"
#include "ns3/log.h"

#include "simu-clock.h"
#include "tos-node.h"
#include "ns3-to-tos-proxy_auto.h"
#include "tos-to-ns3-proxy.h"
#include "tos-node-list.h"
#include "tos-net-device.h"

using namespace std;
NS_LOG_COMPONENT_DEFINE("TosNode");

namespace ns3
{

  NS_OBJECT_ENSURE_REGISTERED(TosNode);

  TypeId
  TosNode::GetTypeId(void)
  {
    static TypeId tid = TypeId("ns3::TosNode").SetParent<Node>().AddConstructor<
        TosNode>().AddAttribute("TosDeviceList",
        "The list of devices associated to this Node.", ObjectVectorValue(),
        MakeObjectVectorAccessor(&TosNode::m_devices),
        MakeObjectVectorChecker<TosNetDevice>()).AddAttribute("Tid",
        "The id (unique integer) of this Node.",
        TypeId::ATTR_GET, // allow only getting it.
        UintegerValue(0), MakeUintegerAccessor(&TosNode::m_id),
        MakeUintegerChecker<uint32_t>());
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

  TosNode::TosNode(uint32_t node_id, Time bootTime)
  {

    TosNode(node_id, bootTime, "./libtos.so");
  }

  TosNode::TosNode(uint32_t node_id, Time bootTime, const char *lib) :
      m_id(node_id), m_bootTime(bootTime), m_libname(lib)
  {
    Construct();
  }

  void
  TosNode::Construct(void)
  {
    m_id = TosNodeList::Add(this);
    nstotos = new Ns3ToTosProxy(); //ns3 to tos
    tostons = new TosToNs3Proxy(); //tos to ns3
    m_init=false;
    NS_LOG_FUNCTION_NOARGS();
  }

  void
  TosNode::SetCallback(std::vector<std::string> tosExternals){
    m_tos_functions=tosExternals;
    m_init=true;
  }

  uint32_t
  TosNode::GetId(void) const
  {
    return m_id;
  }

  SimuClock *
  TosNode::getClock()
  {
    return simuclock;
  }

  void
  TosNode::ShutDownNode(Time ttl)
  {
    m_shutdown_event = Simulator::Schedule(m_shutDownTime, &TosNode::DoDispose,
        this);
  }

  void
  TosNode::BootBooted(void)
  {
    simuclock->Start();
    NS_LOG_FUNCTION(this << " " <<m_id << " " << simuclock->getTimeNow() << " ms" );
    //tickTime(100);
    nstotos->sim_main_start_mote(m_id);
    Simulator::Remove(m_boot_event);
  }

  uint32_t
  TosNode::wrapFire(uint32_t a)
  {
    a = simuclock->getTimeNow();
    //cout<< "Time " << a << " ms"<<endl;
    nstotos->tickFired(a);
    return 0;
  }

  uint32_t
  TosNode::getNow()
  {
    cout << "TosNode::getNow()" << endl;
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
    cout << "TosNode::DoDispose(void)" << endl;
    if (m_shutdown_event.IsRunning())
      {
        m_shutdown_event.Cancel();
        Simulator::Remove(m_shutdown_event);
      }
    if (m_boot_event.IsRunning())
      {
        Simulator::Cancel(m_boot_event);
        Simulator::Remove(m_boot_event);
      }
    dlclose(handler);
    delete nstotos;
    delete tostons;
    //finally despose object
    Object::DoDispose();
  }

  TosNode::~TosNode()
  {
    //everything removed in DoDispose
    cout << "TosNode::~TosNode()" << endl;
  }

  void
  TosNode::DoStart()
  {
    //open instance of the library  LM_ID_NEWLM
    NS_ASSERT(m_init);
    callBackFromClock = MakeCallback(&TosNode::wrapFire, this);
    simuclock = new SimuClock(NANOSECOND, NONE, callBackFromClock);
    tostons->simu_clock = simuclock;
    m_libname = "/home/lauril/dev/symphony/ns-3.11/build/debug/libtos.so";

    //changed from dlmopen LM_ID_NEWLM, will check if more libs can be loaded
    //for eclipse debug full path is needed for the lib
    //TODO: add script for copying libtos.so to build/debug
    handler = dlmopen(LM_ID_NEWLM, m_libname, RTLD_LAZY);
    if (!handler)
      {
        std::cerr << handler << "Cannot open library: " << dlerror() << '\n';
        exit(1);
      }
    else
      {

        for (uint32_t i = 0; i < m_tos_functions.size(); i++)
          {
            string f = m_tos_functions.at(i);
            nstotos->addFunction(f, getFunc(f.c_str()));
          }

      }
    nstotos->setProxy((long) tostons);
    NS_LOG_FUNCTION(this<<" " << m_libname);
    //has to be started from nodes
//	for (std::vector<Ptr<TosNetDevice> >::iterator i = m_devices.begin ();
//	       i != m_devices.end (); i++)
//	    {
//	      Ptr<TosNetDevice> device = *i;
//	      device->Start ();
//	    }
    Node::DoStart();
    Simulator::Schedule(m_bootTime, &TosNode::BootBooted, this);
  }

  uint32_t
  TosNode::AddDevice(Ptr<TosNetDevice> device)
  {
    uint32_t index = m_devices.size();
    m_devices.push_back(device);
    // device->SetNode (this);
//    	  device->SetIfIndex (index);
//    	  device->SetReceiveCallback (MakeCallback (&Node::NonPromiscReceiveFromDevice, this));
    //TosNetDevice is started explicitly from tinyos code
//    	  Simulator::ScheduleWithContext (GetId (), Seconds (0.0),
//    	                                  &TosNetDevice::Start, device);
    tostons->setDevice(device);
    device->setNs3ToTos(nstotos);
    device->SetDeviceSendDoneCallback(
        MakeCallback(&Ns3ToTosProxy::sendSendDone, nstotos));
    device->SetRadioStartDoneCallback(
        MakeCallback(&Ns3ToTosProxy::radioStartDone, nstotos));
    device->SetReceiveMessageCallback(
        MakeCallback(&Ns3ToTosProxy::receiveMessage, nstotos));
    return index;

  }

  Ptr<TosNetDevice>
  TosNode::GetDevice(uint32_t index) const
  {
    NS_ASSERT_MSG (index < m_devices.size (), "Device index " << index <<
        " is out of range (only have " << m_devices.size () << " devices).");
    return m_devices[index];
  }

  uint32_t
  TosNode::GetNDevices(void) const
  {
    return m_devices.size();
  }

  void *
  TosNode::getFunc(const char* func_name)
  {
    char *error = NULL;
    void * tmp = dlsym(handler, func_name);
    if ((error = dlerror()) != NULL)
      {
        std::cerr << "func " << tmp << '\n';
        std::cerr << "Cannot get function: " << func_name << " " << error
            << '\n';
        exit(1);
      }
    else
      {
        std::cerr << "got func " << func_name << '\n';
        return tmp;
      }
  }

}
