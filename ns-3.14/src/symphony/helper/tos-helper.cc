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
#include "ns3/type-id.h"

#include "tos-net-device-container.h"
#include "tos-helper.h"
#include "symphony-xml.h"
#include "ns3/tos-net-device.h"
#include "ns3/tos-mac-low.h"
#include "ns3/RF230-radio-model.h"
#include "ns3/symphony-sensor-container.h"
#include "ns3/raw-sensor.h"

NS_LOG_COMPONENT_DEFINE ("TosHelper");

namespace ns3 {
TosPhyHelper::~TosPhyHelper() {}

TosHelper::TosHelper():
		m_standard (WIFI_PHY_STANDARD_80211a) {
}

void
TosHelper::SetNodeModel(std::string file)
{
  std::string m_xmlFile=file;
  NS_LOG_FUNCTION(file);
  sym.readConfigFile(m_xmlFile);
  m_tosExternals = sym.getExternalFunctions();
  m_radioModel = sym.getModel("radio");
}
TosHelper::~TosHelper() {
  m_tosExternals.clear();
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
	      Ptr<TosNetDevice> device = CreateObject<TosNetDevice> ();
	      Ptr<TosMacLow> mac = CreateObject<TosMacLow>();
	      Ptr<WifiPhy> phy = phyHelper.Create (node, device);
	      mac->SetAddress (Mac48Address::Allocate ());
	      phy->ConfigureStandard (m_standard);
	      device->SetNode(node);
	      device->SetPhy (phy);
	      device->SetMac (mac);
	      node->AddDevice (device);
	      node->SetCallback(m_tosExternals);
	      device->SetRadioModel(m_radioModel);
	      devices.Add (device);
	      NS_LOG_DEBUG ("node=" << node << ", mob=" << node->GetObject<MobilityModel> ());
	    }
	  return devices;
}

SymphonySensorContainer
TosHelper::InstallSensors(uint32_t i , TosNodeContainer c, std::string path)
{
  NS_LOG_FUNCTION_NOARGS();
  SymphonySensorContainer sensors;
      for (TosNodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
        {
          Ptr<TosNode> node = *i;
          Ptr<RawSensor> sensor = CreateObject<RawSensor> ();
          sensor->SetAttribute("RsId", UintegerValue(node->GetId()));
          sensor->SetAttribute("SensorDataPath", StringValue(path));
          sensors.Add(sensor);
          (node->GetTosToNs3Proxy())->SetSensor(sensor);
          sensor->SetNs3ToTosProxy(node->GetNs3ToTosProxy());
          node->SetCallback(m_tosExternals);
          NS_LOG_DEBUG ("node=" << node << ", sensor=" << sensor);
        }
      return sensors;

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
