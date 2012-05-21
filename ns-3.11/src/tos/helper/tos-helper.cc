/*
 * tos-helper.cc
 *
 *  Created on: Feb 13, 2012
 *      Author: lauril
 */


#include "ns3/tos-node.h"
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

#include "tos-net-device-container.h"
#include "tos-helper.h"
#include "ns3/tos-net-device.h"
#include "ns3/tos-mac-low.h"
#include "ns3/RF230-radio-model.h"

NS_LOG_COMPONENT_DEFINE ("TosHelper");

namespace ns3 {
TosPhyHelper::~TosPhyHelper() {}

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

TosNetDeviceContainer
TosHelper::Install(const TosPhyHelper &phyHelper, TosNodeContainer c) const
{
	NS_LOG_FUNCTION_NOARGS();
	TosNetDeviceContainer devices;
	  for (TosNodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
	    {
	      Ptr<TosNode> node = *i;
	      NS_LOG_DEBUG(node);
	      Ptr<TosNetDevice> device = CreateObject<TosNetDevice> ();
	      Ptr<TosMacLow> mac = new TosMacLow();
	      Ptr<WifiPhy> phy = phyHelper.Create (node, device);
	      mac->SetAddress (Mac48Address::Allocate ());
	      phy->ConfigureStandard (m_standard);
	      device->SetNode(node);
	      device->SetPhy (phy);
	      device->SetMac (mac);
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
	  LogComponentEnable ("DsssErrorRateModel", LOG_LEVEL_ALL);
	  LogComponentEnable ("InterferenceHelper", LOG_LEVEL_ALL);

	  LogComponentEnable ("NistErrorRateModel", LOG_LEVEL_ALL);
	  LogComponentEnable ("PropagationLossModel", LOG_LEVEL_ALL);
	  LogComponentEnable ("WifiChannel", LOG_LEVEL_ALL);
	  LogComponentEnable ("WifiPhyStateHelper", LOG_LEVEL_ALL);
	  LogComponentEnable ("WifiPhy", LOG_LEVEL_ALL);


	  LogComponentEnable ("TosMacLow", LOG_LEVEL_ALL);
	  LogComponentEnable ("TosHelper", LOG_LEVEL_ALL);
	  LogComponentEnable ("YansTosPhyHelper", LOG_LEVEL_ALL);
	  LogComponentEnable ("TosNetDevice", LOG_LEVEL_ALL);
	  LogComponentEnable ("TosNode", LOG_LEVEL_ALL);
	  LogComponentEnable ("TosMobilityHelper", LOG_LEVEL_ALL);


	  LogComponentEnable ("YansErrorRateModel", LOG_LEVEL_ALL);
	  LogComponentEnable ("YansWifiChannel", LOG_LEVEL_ALL);
	  LogComponentEnable ("YansWifiPhy", LOG_LEVEL_ALL);
}

void
TosHelper::EnableLogComponentsAll (LogLevel level){
	LogComponentEnableAll(level);
}

} /* namespace ns3 */
