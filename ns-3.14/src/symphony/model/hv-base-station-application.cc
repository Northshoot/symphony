/*
 * Create a NS-3 Application to represent a base station that
 * has support for hyper vector based communications.
 *
 * @author Jose Angel Fernandez
 */
#include "ns3/icmpv4.h"
#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/socket.h"
#include "ns3/integer.h"
#include "ns3/boolean.h"
#include "ns3/inet-socket-address.h"
#include "ns3/packet.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/config.h"
#include "ns3/tos-device.h"
#include "ns3/names.h"
#include "ns3/string.h"
#include "ns3/object.h"
#include "ns3/tos-to-ns3-proxy.h"

#include "hv-base-station-application.h"

#include <stdio.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("HvBaseStation");
NS_OBJECT_ENSURE_REGISTERED (HvBaseStation);


HvBaseStation::HvBaseStation (TosNodeContainer nodes)
{
	m_nodes = nodes;
	init_mem = new init1[nodes.GetN()];
}

TypeId HvBaseStation::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::HvBaseStation")
    .SetParent<Application> ()
    .AddAttribute("InitializationVectorInterrupt","Callback for device interrupt with data event.",
           CallbackValue(),
           MakeCallbackAccessor(&HvBaseStation::m_InitializationVectorInterrupt),
           MakeCallbackChecker ())
    .AddAttribute("RandomVectorInterrupt","Callback for device interrupt with data event.",
           CallbackValue(),
           MakeCallbackAccessor(&HvBaseStation::m_RandomVectorInterrupt),
           MakeCallbackChecker ())
    .AddAttribute("Dimension", "Dimension of the hypervectors used",
    	   IntegerValue(10000),
    	   MakeIntegerAccessor(&HvBaseStation::m_dimension),
    	   MakeIntegerChecker<int16_t>());
  return tid;
}


void HvBaseStation::StartApplication (void)
{
  NS_LOG_FUNCTION (this);

  for (int j = 0; j < a;j++) { // cycle for filling hypervector
  	        m_P[j] = floor((double)rand() / RAND_MAX + 0.5);
  	      //  std::cout << m_P[j];
  }
  //std::cout << " -- \n";
  InitializeNodes(m_nodes);
}

void HvBaseStation::StopApplication (void)
{
  NS_LOG_FUNCTION (this);
}

void HvBaseStation::ReceiveHyperVector(uint16_t size, void * buffer)
{
	NS_LOG_FUNCTION(this);
}

void HvBaseStation::InitializeNodes(TosNodeContainer container)
{
	NS_LOG_FUNCTION(this);
	for (TosNodeContainer::Iterator i = container.Begin(); i != container.End(); i++)
	{
		Ptr<TosNode> node = *i;

	    Callback<int, uint8_t,uint16_t,void *> tmp1=
	              MakeCallback(&Ns3ToTosProxy::InitializationVectorInterrupt,(node->GetNs3ToTosProxy()));
	    this->SetAttribute("InitializationVectorInterrupt", CallbackValue(tmp1));

	    Callback<int, uint8_t,uint16_t,void *> tmp2=
	              MakeCallback(&Ns3ToTosProxy::RandomVectorInterrupt,(node->GetNs3ToTosProxy()));
	    this->SetAttribute("RandomVectorInterrupt", CallbackValue(tmp2));


	    init1 initial; // initial is structural variable of type init1
	    srand((unsigned)time(NULL)); // for hypervector generation

	    initial.id = node->GetId(); // id is serial number ?change for sensor and actuator?
	    for (int j = 0; j < a;j++) { // cycle for filling hypervector
	        initial.role_hv[j] = floor((double)rand() / RAND_MAX + 0.5);
	        std::cout << initial.role_hv[j];
	    }
	    init_mem[initial.id] = initial; // i'th record equal to initial
	    std::cout << "\n";
	    m_InitializationVectorInterrupt(0, sizeof(initial), &initial);
	    m_RandomVectorInterrupt(0, sizeof(m_P), &m_P);
	}
}

HvBaseStation::~HvBaseStation ()
{

}

void HvBaseStation::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  Application::DoDispose ();
}

} // namespace ns3
