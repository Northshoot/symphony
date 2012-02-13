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
#ifndef WSN_HELPER_H
#define WSN_HELPER_H

#include <string>
#include "ns3/attribute.h"
#include "ns3/object-factory.h"
#include "ns3/node-container.h"
#include "ns3/net-device-container.h"
#include "ns3/wifi-phy-standard.h"
#include "ns3/trace-helper.h"


namespace ns3 {

class WifiPhy;
class WsnWifiMac;
class Node;
class WifiWsnDevice;

/**
 * \brief create PHY objects
 *
 * This base class must be implemented by new PHY implementation which wish to integrate
 * with the \ref ns3::WsnHelper class.
 */
class WsnPhyHelper
{
public:
  virtual ~WsnPhyHelper ();

  /**
   * \param node the node on which the PHY object will reside
   * \param device the device within which the PHY object will reside
   * \returns a new PHY object.
   *
   * Subclasses must implement this method to allow the ns3::WsnHelper class
   * to create PHY objects from ns3::WsnHelper::Install.
   */
  virtual Ptr<WifiPhy> Create (Ptr<Node> node, Ptr<WifiWsnDevice> device) const = 0;

};

/**
 * \brief create MAC objects
 *
 * This base class must be implemented by new MAC implementation which wish to integrate
 * with the \ref ns3::WsnHelper class.
 */
class WsnMacHelper
{
public:
  virtual ~WsnMacHelper ();
  /**
   * \returns a new MAC object.
   *
   * Subclasses must implement this method to allow the ns3::WsnHelper class
   * to create MAC objects from ns3::WsnHelper::Install.
   */
  virtual Ptr<WsnWifiMac> Create (void) const = 0;
};

/**
 * \brief helps to create WifiNetDevice objects
 *
 * This class can help to create a large set of similar
 * WifiNetDevice objects and to configure a large set of
 * their attributes during creation.
 */
class WsnHelper
{
public:
  /**
   * Create a Wifi helper in an empty state: all its parameters
   * must be set before calling ns3::WsnHelper::Install
   */
  WsnHelper ();

  /**
   * \returns a new WsnHelper in a default state
   *
   * The default state is defined as being an Adhoc MAC layer with an ARF rate control algorithm
   * and both objects using their default attribute values. By default, configure MAC and PHY
   * for 802.11a.
   */
  static WsnHelper Default (void);


  /**
   * \param phy the PHY helper to create PHY objects
   * \param mac the MAC helper to create MAC objects
   * \param c the set of nodes on which a wifi device must be created
   * \returns a device container which contains all the devices created by this method.
   */
  NetDeviceContainer Install (const WsnPhyHelper &phy,
                              const WsnMacHelper &mac, NodeContainer c) const;
  /**
   * \param phy the PHY helper to create PHY objects
   * \param mac the MAC helper to create MAC objects
   * \param node the node on which a wifi device must be created
   * \returns a device container which contains all the devices created by this method.
   */
  NetDeviceContainer Install (const WsnPhyHelper &phy,
                              const WsnMacHelper &mac, Ptr<Node> node) const;
  /**
   * \param phy the PHY helper to create PHY objects
   * \param mac the MAC helper to create MAC objects
   * \param nodeName the name of node on which a wifi device must be created
   * \returns a device container which contains all the devices created by this method.
   */
  NetDeviceContainer Install (const WsnPhyHelper &phy,
                              const WsnMacHelper &mac, std::string nodeName) const;

  /**
   * \param standard the phy standard to configure during installation
   *
   * By default, all objects are configured for 802.11a
   */
  void SetStandard (enum WifiPhyStandard standard);

  /**
   * Helper to enable all WifiNetDevice log components with one statement
   */
  static void EnableLogComponents (void);


  const Ptr<WifiPhy> GetThisPhy(void);

private:

  enum WifiPhyStandard m_standard;

};

} // namespace ns3

#endif /* WSN_HELPER_H */
