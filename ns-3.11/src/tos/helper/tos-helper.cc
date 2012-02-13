/*
 * tos-helper.cc
 *
 *  Created on: Feb 13, 2012
 *      Author: lauril
 */

#include "tos-helper.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-channel.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/mobility-model.h"
#include "ns3/log.h"
#include "ns3/config.h"
#include "ns3/simulator.h"
#include "ns3/names.h"

namespace ns3 {

TosHelper::TosHelper():
		m_standard (WIFI_PHY_STANDARD_80211a) { }

TosHelper::~TosHelper() {
	// TODO Auto-generated destructor stub
}

TosHelper
TosHelper::Default(void)
{
	TosHelper toshelper;
	return toshelper;
}

NetDeviceContainer
TosHelper::Install(const YansWsnPhyHelper & phy, TosNodeContainer c) const
{
	  NetDeviceContainer devices;
	  for (TosNodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
	    {
	      Ptr<Node> node = *i;
	      Ptr<WsnTosDevice> device = CreateObject<WsnTosDevice> ();
	      Ptr<TosMacLow> mac = new TosMacLow();
	      Ptr<WifiPhy> phy = phy.Create ((Node)node, device);
	      mac->SetAddress (Mac48Address::Allocate ());
	      phy->ConfigureStandard (m_standard);
	      device->SetMac (mac);
	      device->SetPhy (phy);
	      node->AddDevice (device);
	      devices.Add (device);
	      NS_LOG_DEBUG ("node=" << node << ", mob=" << node->GetObject<MobilityModel> ());
	    }
	  return devices;
}

void
TosHelper::SetStandard(enum WifiPhyStandard standard)
{
	 m_standard = standard;
}

void
TosHelper::EnableLogComponents(void)
{
}



} /* namespace ns3 */
