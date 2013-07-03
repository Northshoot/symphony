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


HvBaseStation::HvBaseStation ()
{

}

TypeId HvBaseStation::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::HvBaseStation")
    .SetParent<Application> ()
    .AddConstructor<HvBaseStation> ()
    .AddAttribute("InitializationInterrupt","Callback for device interrupt with data event.",
           CallbackValue(),
           MakeCallbackAccessor(&HvBaseStation::m_InitializationInterrupt),
           MakeCallbackChecker ());
  return tid;
}


void HvBaseStation::StartApplication (void)
{
  NS_LOG_FUNCTION (this);

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
	              MakeCallback(&Ns3ToTosProxy::InitializationInterrupt,(node->GetNs3ToTosProxy()));
	    this->SetAttribute("InitializationInterrupt", CallbackValue(tmp1));
		int c = 5;
        m_InitializationInterrupt(0, sizeof(c), &c);
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
