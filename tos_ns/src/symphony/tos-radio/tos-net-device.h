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

#ifndef TOS_NET_DEVICE_H
#define TOS_NET_DEVICE_H

//#include "ns3/net-device.h"
#include "ns3/tos-net-device.h"
#include "ns3/packet.h"
#include "ns3/traced-callback.h"
#include "ns3/mac48-address.h"
#include "ns3/TosNode.h"
#include "ns3/wifi-net-device.h"
#include <string>

namespace ns3 {

//class WifiRemoteStationManager;
//class WifiChannel;
//class WifiPhy;
//class WifiMac;

/**
 * \brief Hold together all Wifi-related objects.
 *
 * This class holds together ns3::WifiChannel, ns3::WifiPhy,
 * ns3::WifiMac, and, ns3::WifiRemoteStationManager.
 */
class TosNetDevice : public WifiNetDevice
{
public:
  static TypeId GetTypeId (void);

  TosNetDevice ();
   ~TosNetDevice ();

  /**
   * \param mac the mac layer to use.
   */
  void SetMac (Ptr<WifiMac> mac);
  /**
   * \param phy the phy layer to use.
   */
  void SetPhy (Ptr<WifiPhy> phy);
  /**
   * \param manager the manager to use.
   */
  void SetRemoteStationManager (Ptr<WifiRemoteStationManager> manager);
  /**
   * \returns the mac we are currently using.
   */
  Ptr<WifiMac> GetMac (void) const;
  /**
   * \returns the phy we are currently using.
   */
  Ptr<WifiPhy> GetPhy (void) const;
  /**
   * \returns the remote station manager we are currently using.
   */
  Ptr<WifiRemoteStationManager> GetRemoteStationManager (void) const;


  // inherited from TosNetDevice base class.
   void SetIfIndex(const uint32_t index);
   uint32_t GetIfIndex(void) const;
   Ptr<Channel> GetChannel (void) const;
   void SetAddress (Address address);
   Address GetAddress (void) const;
   bool SetMtu (const uint16_t mtu);
   uint16_t GetMtu (void) const;
   bool IsLinkUp (void) const;
   void AddLinkChangeCallback (Callback<void> callback);
   bool IsBroadcast (void) const;
   Address GetBroadcast (void) const;
   bool IsMulticast (void) const;
   Address GetMulticast (Ipv4Address multicastGroup) const;
   bool IsPointToPoint (void) const;
   bool IsBridge (void) const;
   bool Send(Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber);
   Ptr<Node> GetNode (void) const;
   Ptr<TosNode> GetTosNode (void) const;
   void SetNode (Ptr<TosNode> TosNode);
   bool NeedsArp (void) const;
   void SetReceiveCallback (TosNetDevice::ReceiveCallback cb);

   Address GetMulticast (Ipv6Address addr) const;

   bool SendFrom(Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber);
   void SetPromiscReceiveCallback (TosNetDevice::PromiscReceiveCallback cb);
   bool SupportsSendFrom (void) const;

private:

  // This value conforms to the 802.11 specification
  static const uint16_t MAX_MSDU_SIZE = 2304;

   void DoDispose (void);
   void DoStart (void);
  void ForwardUp (Ptr<Packet> packet, Mac48Address from, Mac48Address to);
  void LinkUp (void);
  void LinkDown (void);
  void Setup (void);
  Ptr<WifiChannel> DoGetChannel (void) const;
  void CompleteConfig (void);

  Ptr<TosNode> m_node;
  Ptr<Node> MM_node;
  Ptr<WifiPhy> m_phy;
  Ptr<WifiMac> m_mac;
  Ptr<WifiRemoteStationManager> m_stationManager;
  WifiNetDevice::ReceiveCallback m_forwardUp;
  WifiNetDevice::PromiscReceiveCallback m_promiscRx;

  TracedCallback<Ptr<const Packet>, Mac48Address> m_rxLogger;
  TracedCallback<Ptr<const Packet>, Mac48Address> m_txLogger;

  uint32_t m_ifIndex;
  bool m_linkUp;
  TracedCallback<> m_linkChanges;
  mutable uint16_t m_mtu;
  bool m_configComplete;
};

} // namespace ns3

#endif /* TOS_NET_DEVICE_H */
