/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
 * Copyright (c) 2009 MIRKO BANCHI
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 * Author: Mirko Banchi <mk.banchi@gmail.com>
 */
#include "wsn-helper.h"
#include "ns3/wifi-helper.h"
#include "wsn-mac-helper.h"
#include "ns3/wifi-wsn-device.h"
#include "ns3/wsn-wifi-mac.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-remote-station-manager.h"
#include "ns3/wifi-channel.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/propagation-delay-model.h"
#include "ns3/propagation-loss-model.h"
#include "ns3/mobility-model.h"
#include "ns3/log.h"
#include "ns3/config.h"
#include "ns3/simulator.h"
#include "ns3/names.h"

NS_LOG_COMPONENT_DEFINE ("WsnHelper");

namespace ns3 {

WsnPhyHelper::~WsnPhyHelper ()
{
}

WsnMacHelper::~WsnMacHelper ()
{
}

WsnHelper::WsnHelper ()
  : m_standard (WIFI_PHY_STANDARD_80211a)
{
}

WsnHelper
WsnHelper::Default (void)
{
  WsnHelper helper;
  helper.SetRemoteStationManager ("ns3::ArfWifiManager");
  return helper;
}

void
WsnHelper::SetRemoteStationManager (std::string type,
                                     std::string n0, const AttributeValue &v0,
                                     std::string n1, const AttributeValue &v1,
                                     std::string n2, const AttributeValue &v2,
                                     std::string n3, const AttributeValue &v3,
                                     std::string n4, const AttributeValue &v4,
                                     std::string n5, const AttributeValue &v5,
                                     std::string n6, const AttributeValue &v6,
                                     std::string n7, const AttributeValue &v7)
{
  m_stationManager = ObjectFactory ();
  m_stationManager.SetTypeId (type);
  m_stationManager.Set (n0, v0);
  m_stationManager.Set (n1, v1);
  m_stationManager.Set (n2, v2);
  m_stationManager.Set (n3, v3);
  m_stationManager.Set (n4, v4);
  m_stationManager.Set (n5, v5);
  m_stationManager.Set (n6, v6);
  m_stationManager.Set (n7, v7);
}

void
WsnHelper::SetStandard (enum WifiPhyStandard standard)
{
  m_standard = standard;
}


NetDeviceContainer
WsnHelper::Install (const WsnPhyHelper &phyHelper,
                     const WsnMacHelper &macHelper, NodeContainer c) const
{
  NetDeviceContainer devices;
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      Ptr<Node> node = *i;
      Ptr<WifiWsnDevice> device = CreateObject<WifiWsnDevice> ();
      Ptr<WifiRemoteStationManager> manager = m_stationManager.Create<WifiRemoteStationManager> ();
      Ptr<WsnWifiMac> mac = macHelper.Create ();
      Ptr<WifiPhy> phy = phyHelper.Create (node, device);
      mac->SetAddress (Mac48Address::Allocate ());
      mac->ConfigureStandard (m_standard);
      phy->ConfigureStandard (m_standard);
      device->SetMac (mac);
      device->SetPhy (phy);

      device->SetRemoteStationManager (manager);
      node->AddDevice (device);
      devices.Add (device);
      NS_LOG_DEBUG ("node=" << node << ", mob=" << node->GetObject<MobilityModel> ());
    }
  return devices;
}

NetDeviceContainer
WsnHelper::Install (const WsnPhyHelper &phy,
                     const WsnMacHelper &mac, Ptr<Node> node) const
{
  return Install (phy, mac, NodeContainer (node));
}

NetDeviceContainer
WsnHelper::Install (const WsnPhyHelper &phy,
                     const WsnMacHelper &mac, std::string nodeName) const
{
  Ptr<Node> node = Names::Find<Node> (nodeName);
  return Install (phy, mac, NodeContainer (node));
}

void
WsnHelper::EnableLogComponents (void)
{
  LogComponentEnable ("Aarfcd", LOG_LEVEL_ALL);
  LogComponentEnable ("AdhocWifiMac", LOG_LEVEL_ALL);
  LogComponentEnable ("AmrrWifiRemoteStation", LOG_LEVEL_ALL);
  LogComponentEnable ("ApWifiMac", LOG_LEVEL_ALL);
  LogComponentEnable ("ns3::ArfWifiManager", LOG_LEVEL_ALL);
  LogComponentEnable ("Cara", LOG_LEVEL_ALL);
  LogComponentEnable ("DcaTxop", LOG_LEVEL_ALL);
  LogComponentEnable ("DcfManager", LOG_LEVEL_ALL);
  LogComponentEnable ("DsssErrorRateModel", LOG_LEVEL_ALL);
  LogComponentEnable ("EdcaTxopN", LOG_LEVEL_ALL);
  LogComponentEnable ("InterferenceHelper", LOG_LEVEL_ALL);
  LogComponentEnable ("Jakes", LOG_LEVEL_ALL);
  LogComponentEnable ("MacLow", LOG_LEVEL_ALL);
  LogComponentEnable ("MacRxMiddle", LOG_LEVEL_ALL);
  LogComponentEnable ("MsduAggregator", LOG_LEVEL_ALL);
  LogComponentEnable ("MsduStandardAggregator", LOG_LEVEL_ALL);
  LogComponentEnable ("NistErrorRateModel", LOG_LEVEL_ALL);
  LogComponentEnable ("OnoeWifiRemoteStation", LOG_LEVEL_ALL);
  LogComponentEnable ("PropagationLossModel", LOG_LEVEL_ALL);
  LogComponentEnable ("RegularWifiMac", LOG_LEVEL_ALL);
  LogComponentEnable ("RegularWsnMac", LOG_LEVEL_ALL);
  LogComponentEnable ("RraaWifiManager", LOG_LEVEL_ALL);
  LogComponentEnable ("StaWifiMac", LOG_LEVEL_ALL);
  LogComponentEnable ("SupportedRates", LOG_LEVEL_ALL);
  LogComponentEnable ("WifiChannel", LOG_LEVEL_ALL);
  LogComponentEnable ("WifiPhyStateHelper", LOG_LEVEL_ALL);
  LogComponentEnable ("WifiPhy", LOG_LEVEL_ALL);
  LogComponentEnable ("WifiRemoteStationManager", LOG_LEVEL_ALL);
  LogComponentEnable ("WsnWifiMac", LOG_LEVEL_ALL);
  LogComponentEnable ("YansErrorRateModel", LOG_LEVEL_ALL);
  LogComponentEnable ("YansWifiChannel", LOG_LEVEL_ALL);
  LogComponentEnable ("YansWifiPhy", LOG_LEVEL_ALL);
}

} // namespace ns3
