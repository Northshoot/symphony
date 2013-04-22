/*
 * TosNode.cpp
 *
 *  Created on: Mar 4, 2010
 *      Author: laurynas
 */
#include <vector>
#include<map>
#include <iostream>

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
#include "ns3/tos-loader.h"

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

   NS_OBJECT_ENSURE_REGISTERED (TosNode);

  TypeId
  TosNode::GetTypeId(void)
  {
    static TypeId tid = TypeId("ns3::TosNode")
        .SetParent<Node>()
        .AddConstructor<TosNode>()
        .AddAttribute("TosDeviceList","The list of devices associated to this Node.", ObjectVectorValue(),
        MakeObjectVectorAccessor(&TosNode::m_devices),
        MakeObjectVectorChecker<TosNetDevice>())
        .AddAttribute("Tid", "The id (unique integer) of this Node.",
        TypeId::ATTR_GET, // allow only getting it.
        UintegerValue(0), MakeUintegerAccessor(&TosNode::m_id),
        MakeUintegerChecker<uint32_t>())
        .AddAttribute("TosId", "The id (unique integer) of this Node.",
                TypeId::ATTR_SET, // allow only getting it.
                UintegerValue(0), MakeUintegerAccessor(&TosNode::tos_id),
                MakeUintegerChecker<uint32_t>())

        ;
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

  TosNode::TosNode(uint32_t node_id, Time bootTime, const char* lib) :
    tos_id(node_id), m_bootTime(bootTime), m_libname(lib)
  {
    Construct();
  }

  void
  TosNode::Construct(void)
  {
    m_id = TosNodeList::Add(this);
    nstotos = new Ns3ToTosProxy(); //ns3 to tos
    tostons = new TosToNs3Proxy(); //tos to ns3
    m_init = false;

  }
void
TosNode::AddApplication(Ptr<SymphonyApplication> app)
{
  m_application = app;
}
void
  TosNode::SetCallback(std::vector<std::string> tosExternals)
  {
    m_tos_functions = tosExternals;
    m_tosLoader = new TosLoader();
    handler = m_tosLoader->getHandler(m_libname);
    if (!handler)
      {
        std::cerr << handler << "Cannot open library: "  << '\n';
        exit(1);
      }
    m_init = true;
  }

  uint32_t
  TosNode::GetId(void) const
  {
    return m_id;
  }

  Ptr<SimuClock>
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
    nstotos->sim_main_start_mote(tos_id);
    //NS_LOG_FUNCTION(tos_id << Simulator::Now().GetMilliSeconds());
    Simulator::Remove (m_boot_event);
  }

  uint32_t
  TosNode::wrapFire(uint64_t a)
  {
    nstotos->tickFired(a);
    //NS_LOG_FUNCTION(tos_id << Simulator::Now().GetMilliSeconds());
    return 0;
  }

  uint64_t
  TosNode::getNow()
  {
   cout << "TosNode::getNow()" << endl;
    //simuclock->getTimeNow();
   uint64_t a=   Simulator::Now().GetMilliSeconds();
   cout<< "Time " << a << " ms"<<endl;
    return a;
  }

  void
  TosNode::DoDispose(void)
  {
	  NS_LOG_FUNCTION(this<< Simulator::Now().GetMilliSeconds());
    /**
     * Check and remove shutdown event
     */
    //    for (std::vector<Ptr<TosNetDevice> >::iterator i = m_devices.begin ();
    //         i != m_devices.end (); i++)
    //      {
    //        Ptr<NetDevice> device = *i;
    //        device->Dispose ();
    //        *i = 0;
    //      }
    m_devices.clear();
    //    if (m_shutdown_event.IsRunning())
    //      {
    //        m_shutdown_event.Cancel();
    //        Simulator::Remove(m_shutdown_event);
    //      }
    //    if (m_boot_event.IsRunning())
    //      {
    //        Simulator::Cancel(m_boot_event);
    //        Simulator::Remove(m_boot_event);
    //      }
//    dlclose (handler);
    delete nstotos;
    delete tostons;
    //    delete m_libname;
    //    delete error;
    m_devices.clear();
    Node::DoDispose();
  }

  TosNode::~TosNode()
  {
  }

  void
  TosNode::DoStart()
  {
    //open instance of the library  LM_ID_NEWLM
    NS_ASSERT (m_init);
    NS_LOG_FUNCTION("TosID " << tos_id << "SysId " << GetId());
    if( m_application !=NULL) {

        tostons->SetApplication(m_application);

        Callback<void, uint8_t> tmp =
            MakeCallback(&Ns3ToTosProxy::ApplicationStartDone,nstotos);
        m_application->SetAttribute("StartDone", CallbackValue(tmp));

        Callback<void, uint8_t> tmp1=
            MakeCallback(&Ns3ToTosProxy::AplicationStopDone,nstotos);
        m_application->SetAttribute("StopDone", CallbackValue(tmp1));

        m_application->StartApplication();
    }
    callBackFromClock = MakeCallback(&TosNode::wrapFire, this);
    simuclock = CreateObject < SimuClock
        > (MILLISECOND, STATIC, callBackFromClock);
    simuclock->setTimeDrift(5, MICROSECOND);
    tostons->simu_clock = simuclock;
    //changed from dlmopen LM_ID_NEWLM, will check if more libs can be loaded
    //for eclipse debug full path is needed for the lib

      {
        for (uint32_t i = 0; i < m_tos_functions.size(); i++)
          {
            string f = m_tos_functions[i];
            //NS_LOG_FUNCTION(this<<"adding function " << f);
            void * fu = m_tosLoader->getFunction(f.c_str());
 //           if(fu){
            	nstotos->addFunction(f, fu);
//            	NS_LOG_FUNCTION(this<<"adding function " << f);
//            } else {
//            	NS_LOG_FUNCTION(this<<"Can't add function" << f);
//            }
          }
      }

    nstotos->setProxy((long) (tostons));
    //has to be started from nodes
    //	for (std::vector<Ptr<TosNetDevice> >::iterator i = m_devices.begin ();
    //	       i != m_devices.end (); i++)
    //	    {
    //	      Ptr<TosNetDevice> device = *i;
    //	      device->Start ();
    //	    }
    nstotos->setUniqueID(tos_id);
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


    device->SetAttribute("SendDone",
        CallbackValue(MakeCallback(&Ns3ToTosProxy::sendDone, nstotos))
        );
    device->SetAttribute("StartDone",
        CallbackValue(MakeCallback(&Ns3ToTosProxy::radioStartDone, nstotos))
        );
    device->SetAttribute("ReceivePacket",
        CallbackValue(MakeCallback(&Ns3ToTosProxy::receiveMessage, nstotos))
        );

    return index;
  }

  Ptr<TosNetDevice>
  TosNode::GetDevice(uint32_t index) const
  {
    NS_ASSERT_MSG(index < m_devices.size(),
        "Device index " << index << " is out of range (only have "
            << m_devices.size() << " devices).");
    return m_devices[index];
  }

  uint32_t
  TosNode::GetNDevices(void) const
  {
    return m_devices.size();
  }

  uint32_t
  TosNode::AddSensor(Ptr<RawSensor> sensor)
  {
    uint32_t index = m_sensors.size();
    sensor->SetAttribute("RsId",UintegerValue(tos_id));
    m_sensors.push_back(sensor);

    return index;
  }

  Ptr<RawSensor>
  TosNode::GetSensor(uint32_t index) const
  {
    NS_ASSERT_MSG(index < m_sensors.size(),
        "Sensor index " << index << " is out of range (only have "
            << m_devices.size() << " sensors).");
    return m_sensors[index];
  }

  uint32_t
  TosNode::GetNSensors(void) const
  {
    return m_sensors.size();
  }
  TosToNs3Proxy *
  TosNode::GetTosToNs3Proxy(void)
  {
    return tostons;
  }
  Ns3ToTosProxy *
  TosNode::GetNs3ToTosProxy(void)
  {
    return nstotos;
  }

  void *
  TosNode::getFunc(const char* func_name)
  {
//    char *error = NULL;
//    void * tmp = dlsym(handler, func_name);
//    if ((error = dlerror()) != NULL)
//      {
////        std::stringstream sstm;
////        sstm << "Cannot get function: " << name << "\n" << error;
////        NS_ASSERT_MSG(false, sstm.str());
//        //this is not fail safe, better way for multiple models is neede
//        //for now return default function which prints error is the function is not found
//      std::string defFunc = "sim_function_not_found";
//      std::stringstream sstm;
//      sstm << "Function not found: " << func_name << ". Using default TOS function.\n" << error;
//      void * tmp = dlsym(handler, defFunc.c_str());
//      NS_LOG_ERROR(sstm.str());
//      return tmp;
//      }
//    else
//      {
//        return tmp;
//      }
      return NULL;
  }

}
