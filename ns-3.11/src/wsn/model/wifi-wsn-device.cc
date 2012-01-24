/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006 INRIA
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
 */
#include "wifi-wsn-device.h"
#include "ns3/wifi-mac.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-remote-station-manager.h"
#include "ns3/wifi-channel.h"
#include "ns3/llc-snap-header.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/pointer.h"
#include "ns3/node.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/log.h"

NS_LOG_COMPONENT_DEFINE ("WifiWsnDevice");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (WifiWsnDevice);

TypeId
WifiWsnDevice::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::WifiWsnDevice")
    .SetParent<NetDevice> ()
    .AddConstructor<WifiWsnDevice> ()
    .AddAttribute ("Mtu", "The MAC-level Maximum Transmission Unit",
                   UintegerValue (MAX_MSDU_SIZE - LLC_SNAP_HEADER_LENGTH),
                   MakeUintegerAccessor (&WifiWsnDevice::SetMtu,
                                         &WifiWsnDevice::GetMtu),
                   MakeUintegerChecker<uint16_t> (1,MAX_MSDU_SIZE - LLC_SNAP_HEADER_LENGTH))
    .AddAttribute ("Channel", "The channel attached to this device",
                   PointerValue (),
                   MakePointerAccessor (&WifiWsnDevice::DoGetChannel),
                   MakePointerChecker<WifiChannel> ())
    .AddAttribute ("Phy", "The PHY layer attached to this device.",
                   PointerValue (),
                   MakePointerAccessor (&WifiWsnDevice::GetPhy,
                                        &WifiWsnDevice::SetPhy),
                   MakePointerChecker<WifiPhy> ())
    .AddAttribute ("Mac", "The MAC layer attached to this device.",
                   PointerValue (),
                   MakePointerAccessor (&WifiWsnDevice::GetMac,
                                        &WifiWsnDevice::SetMac),
                   MakePointerChecker<WifiMac> ())
//    .AddAttribute ("RemoteStationManager", "The station manager attached to this device.",
//                   PointerValue (),
//                   MakePointerAccessor (&WifiWsnDevice::SetRemoteStationManager,
//                                        &WifiWsnDevice::GetRemoteStationManager),
//                   MakePointerChecker<WifiRemoteStationManager> ())
  ;
  return tid;
}

WifiWsnDevice::WifiWsnDevice ()
  : m_configComplete (false)
{
  NS_LOG_FUNCTION_NOARGS ();
}
WifiWsnDevice::~WifiWsnDevice ()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
WifiWsnDevice::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();
  m_node = 0;
  m_mac->Dispose ();
  m_phy->Dispose ();
//  m_stationManager->Dispose ();
  m_mac = 0;
  m_phy = 0;
//  m_stationManager = 0;
  // chain up.
  NetDevice::DoDispose ();
}

void
WifiWsnDevice::DoStart (void)
{
  m_phy->Start ();
  m_mac->Start ();
  //m_stationManager->Start ();
  NetDevice::DoStart ();
}

void
WifiWsnDevice::CompleteConfig (void)
{
  if (m_mac == 0
      || m_phy == 0
     // || m_stationManager == 0
      || m_node == 0
      || m_configComplete)
    {
      return;
    }
 // m_mac->SetWifiRemoteStationManager (m_stationManager);
  m_mac->SetWifiPhy (m_phy);
  m_mac->SetForwardUpCallback (MakeCallback (&WifiWsnDevice::ForwardUp, this));
  m_mac->SetLinkUpCallback (MakeCallback (&WifiWsnDevice::LinkUp, this));
  m_mac->SetLinkDownCallback (MakeCallback (&WifiWsnDevice::LinkDown, this));
  //m_stationManager->SetupPhy (m_phy);
  m_configComplete = true;
}

void
WifiWsnDevice::SetMac (Ptr<WifiMac> mac)
{
  m_mac = mac;
  CompleteConfig ();
}
void
WifiWsnDevice::SetPhy (Ptr<WifiPhy> phy)
{
  m_phy = phy;
  CompleteConfig ();
}
//
//void
//WifiWsnDevice::SetRemoteStationManager (Ptr<WifiRemoteStationManager> manager)
//{
//  m_stationManager = manager;
//  CompleteConfig ();
//}
Ptr<WifiMac>
WifiWsnDevice::GetMac (void) const
{
  return m_mac;
}
Ptr<WifiPhy>
WifiWsnDevice::GetPhy (void) const

{
  return m_phy;
}
//
//Ptr<WifiRemoteStationManager>
//WifiWsnDevice::GetRemoteStationManager (void) const
//{
//  return m_stationManager;
//}

void
WifiWsnDevice::SetIfIndex (const uint32_t index)
{
  m_ifIndex = index;
}
uint32_t
WifiWsnDevice::GetIfIndex (void) const
{
  return m_ifIndex;
}
Ptr<Channel>
WifiWsnDevice::GetChannel (void) const
{
  return m_phy->GetChannel ();
}
Ptr<WifiChannel>
WifiWsnDevice::DoGetChannel (void) const
{
  return m_phy->GetChannel ();
}
void
WifiWsnDevice::SetAddress (Address address)
{
  m_mac->SetAddress (Mac48Address::ConvertFrom (address));
}
Address
WifiWsnDevice::GetAddress (void) const
{
  return m_mac->GetAddress ();
}
bool
WifiWsnDevice::SetMtu (const uint16_t mtu)
{
  if (mtu > MAX_MSDU_SIZE - LLC_SNAP_HEADER_LENGTH)
    {
      return false;
    }
  m_mtu = mtu;
  return true;
}
uint16_t
WifiWsnDevice::GetMtu (void) const
{
  return m_mtu;
}
bool
WifiWsnDevice::IsLinkUp (void) const
{
  return m_phy != 0 && m_linkUp;
}
void
WifiWsnDevice::AddLinkChangeCallback (Callback<void> callback)
{
  m_linkChanges.ConnectWithoutContext (callback);
}
bool
WifiWsnDevice::IsBroadcast (void) const
{
  return true;
}
Address
WifiWsnDevice::GetBroadcast (void) const
{
  return Mac48Address::GetBroadcast ();
}
bool
WifiWsnDevice::IsMulticast (void) const
{
  return true;
}
Address
WifiWsnDevice::GetMulticast (Ipv4Address multicastGroup) const
{
  return Mac48Address::GetMulticast (multicastGroup);
}
Address WifiWsnDevice::GetMulticast (Ipv6Address addr) const
{
  return Mac48Address::GetMulticast (addr);
}
bool
WifiWsnDevice::IsPointToPoint (void) const
{
  return false;
}
bool
WifiWsnDevice::IsBridge (void) const
{
  return false;
}
bool
WifiWsnDevice::Send (Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber)
{
  NS_ASSERT (Mac48Address::IsMatchingType (dest));

  Mac48Address realTo = Mac48Address::ConvertFrom (dest);

  LlcSnapHeader llc;
  llc.SetType (protocolNumber);
  packet->AddHeader (llc);

  m_mac->NotifyTx (packet);
  m_mac->Enqueue (packet, realTo);
  return true;
}
Ptr<Node>
WifiWsnDevice::GetNode (void) const
{
  return m_node;
}
void
WifiWsnDevice::SetNode (Ptr<Node> node)
{
  m_node = node;
  CompleteConfig ();
}
bool
WifiWsnDevice::NeedsArp (void) const
{
  return true;
}
void
WifiWsnDevice::SetReceiveCallback (NetDevice::ReceiveCallback cb)
{
  m_forwardUp = cb;
}

void
WifiWsnDevice::ForwardUp (Ptr<Packet> packet, Mac48Address from, Mac48Address to)
{
  LlcSnapHeader llc;
  packet->RemoveHeader (llc);
  enum NetDevice::PacketType type;
  if (to.IsBroadcast ())
    {
      type = NetDevice::PACKET_BROADCAST;
    }
  else if (to.IsGroup ())
    {
      type = NetDevice::PACKET_MULTICAST;
    }
  else if (to == m_mac->GetAddress ())
    {
      type = NetDevice::PACKET_HOST;
    }
  else
    {
      type = NetDevice::PACKET_OTHERHOST;
    }

  if (type != NetDevice::PACKET_OTHERHOST)
    {
      m_mac->NotifyRx (packet);
      m_forwardUp (this, packet, llc.GetType (), from);
    }

  if (!m_promiscRx.IsNull ())
    {
      m_mac->NotifyPromiscRx (packet);
      m_promiscRx (this, packet, llc.GetType (), from, to, type);
    }
}

void
WifiWsnDevice::LinkUp (void)
{
  m_linkUp = true;
  m_linkChanges ();
}
void
WifiWsnDevice::LinkDown (void)
{
  m_linkUp = false;
  m_linkChanges ();
}

bool
WifiWsnDevice::SendFrom (Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber)
{
  NS_ASSERT (Mac48Address::IsMatchingType (dest));
  NS_ASSERT (Mac48Address::IsMatchingType (source));

  Mac48Address realTo = Mac48Address::ConvertFrom (dest);
  Mac48Address realFrom = Mac48Address::ConvertFrom (source);

  LlcSnapHeader llc;
  llc.SetType (protocolNumber);
  packet->AddHeader (llc);

  m_mac->NotifyTx (packet);
  m_mac->Enqueue (packet, realTo, realFrom);

  return true;
}

void
WifiWsnDevice::SetPromiscReceiveCallback (PromiscReceiveCallback cb)
{
  m_promiscRx = cb;
}

bool
WifiWsnDevice::SupportsSendFrom (void) const
{
  return m_mac->SupportsSendFrom ();
}

} // namespace ns3

