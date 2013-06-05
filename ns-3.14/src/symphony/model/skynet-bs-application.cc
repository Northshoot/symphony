/*
 * Create a NS-3 Application that opens a TCP Socket and 
 * waits for incoming connections
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
#include "ns3/skynet-sensor.h"
#include "ns3/names.h"
#include "ns3/string.h"
#include "ns3/object.h"

#include "ns3/tos-node-container.h"

#include "skynet-bs-application.h"

#include <stdio.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SkynetBaseStation");
NS_OBJECT_ENSURE_REGISTERED (SkynetBaseStation);


SkynetBaseStation::SkynetBaseStation ()
{
}

TypeId SkynetBaseStation::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SkynetBaseStation")
    .SetParent<Application> ()
    .AddConstructor<SkynetBaseStation> ();
  return tid;
}


void SkynetBaseStation::StartApplication (void)
{
  NS_LOG_FUNCTION (this);
}

void SkynetBaseStation::StopApplication (void)
{
  NS_LOG_FUNCTION (this);
}

void SkynetBaseStation::DistributeActuatorsInitVectors(TosNodeContainer container)
{
	TosNodeContainer::Iterator i;
	for (i = container.Begin (); i != container.End (); ++i)
	{
		//(*i)->method ();  // some TosNode method
	}
}

void SkynetBaseStation::DistributeSensorsInitVectors(TosNodeContainer container)
{
	TosNodeContainer::Iterator i;
	for (i = container.Begin (); i != container.End (); ++i)
	{
		//(*i)->method ();  // some TosNode method
	}

}

SkynetBaseStation::~SkynetBaseStation ()
{

}

void SkynetBaseStation::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  Application::DoDispose ();
}

} // namespace ns3
