/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
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
#ifndef TOS_NET_DEVICE_CONTAINER_H
#define TOS_NET_DEVICE_CONTAINER_H

#include <stdint.h>
#include <vector>
#include "ns3/tos-net-device.h"

namespace ns3 {

/**
 * \brief holds a vector of ns3::TosNetDevice pointers
 *
 * Typically ns-3 NetDevices are installed on nodes using a net device
 * helper.  The helper Install method takes a NodeContainer which holds 
 * some number of Ptr<Node>.  For each of the Nodes in the NodeContainer
 * the helper will instantiate a net device, add a MAC address and a queue
 * to the device and install it to the node.  For each of the devices, the
 * helper also adds the device into a Container for later use by the caller.
 * This is that container used to hold the Ptr<TosNetDevice> which are
 * instantiated by the device helper.
 */
class TosNetDeviceContainer
{
public:
  typedef std::vector<Ptr<TosNetDevice> >::const_iterator Iterator;

  /**
   * Create an empty TosNetDeviceContainer.
   */
  TosNetDeviceContainer ();

  /**
   * \param dev a device to add to the container
   *
   * Create a TosNetDeviceContainer with exactly one net device that has previously
   * been instantiated
   */
  TosNetDeviceContainer (Ptr<TosNetDevice> dev);

  /**
   * Create a TosNetDeviceContainer with exactly one device which has been
   * previously instantiated and assigned a name using the Object name
   * service.  This TosNetDevice is specified by its assigned name.
   *
   * \param devName The name of the device to add to the container
   *
   * Create a TosNetDeviceContainer with exactly one device
   */
  TosNetDeviceContainer (std::string devName);

  /**
   * \param a a device container
   * \param b another device container
   *
   * Create a device container which is a concatenation of the two input
   * NetDeviceContainers.
   *
   * \note A frequently seen idiom that uses these constructors involves the
   * implicit conversion by constructor of Ptr<TosNetDevice>.  When used, two
   * Ptr<TosNetDevice> will be passed to this constructor instead of TosNetDeviceContainer&.
   * C++ will notice the implicit conversion path that goes through the 
   * TosNetDeviceContainer (Ptr<TosNetDevice> dev) constructor above.  Using this conversion
   * one may provide optionally provide arguments of Ptr<TosNetDevice> to these
   * constructors.
   */
  TosNetDeviceContainer (const TosNetDeviceContainer &a, const TosNetDeviceContainer &b);

  /**
   * \brief Get an iterator which refers to the first TosNetDevice in the
   * container.
   *
   * NetDevices can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the iterator method and is typically used in a 
   * for-loop to run through the NetDevices
   *
   * \code
   *   TosNetDeviceContainer::Iterator i;
   *   for (i = container.Begin (); i != container.End (); ++i)
   *     {
   *       (*i)->method ();  // some TosNetDevice method
   *     }
   * \endcode
   *
   * \returns an iterator which refers to the first TosNetDevice in the container.
   */
  Iterator Begin (void) const;

  /**
   * \brief Get an iterator which indicates past-the-last TosNetDevice in the
   * container.
   *
   * NetDevices can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the iterator method and is typically used in a 
   * for-loop to run through the NetDevices
   *
   * \code
   *   TosNetDeviceContainer::Iterator i;
   *   for (i = container.Begin (); i != container.End (); ++i)
   *     {
   *       (*i)->method ();  // some TosNetDevice method
   *     }
   * \endcode
   *
   * \returns an iterator which indicates an ending condition for a loop.
   */
  Iterator End (void) const;

  /**
   * \brief Get the number of Ptr<TosNetDevice> stored in this container.
   *
   * NetDevices can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the direct method and is typically used to
   * define an ending condition in a for-loop that runs through the stored
   * NetDevices
   *
   * \code
   *   uint32_t nDevices = container.GetN ();
   *   for (uint32_t i = 0 i < nDevices; ++i)
   *     {
   *       Ptr<TosNetDevice> p = container.Get (i)
   *       i->method ();  // some TosNetDevice method
   *     }
   * \endcode
   *
   * \returns the number of Ptr<TosNetDevice> stored in this container.
   */
  uint32_t GetN (void) const;

  /**
   * \brief Get the Ptr<TosNetDevice> stored in this container at a given
   * index.
   *
   * NetDevices can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the direct method and is used to retrieve the
   * indexed Ptr<TosNetDevice>.
   *
   * \code
   *   uint32_t nDevices = container.GetN ();
   *   for (uint32_t i = 0 i < nDevices; ++i)
   *     {
   *       Ptr<TosNetDevice> p = container.Get (i)
   *       i->method ();  // some TosNetDevice method
   *     }
   * \endcode
   *
   * \param i the index of the requested device pointer.
   * \returns the requested device pointer.
   */
  Ptr<TosNetDevice> Get (uint32_t i) const;

  /**
   * \brief Append the contents of another TosNetDeviceContainer to the end of
   * this container.
   *
   * \param other The TosNetDeviceContainer to append.
   */
  void Add (TosNetDeviceContainer other);

  /**
   * \brief Append a single Ptr<TosNetDevice> to this container.
   *
   * \param device The Ptr<TosNetDevice> to append.
   */
  void Add (Ptr<TosNetDevice> device);

  /**
   * \brief Append to this container the single Ptr<TosNetDevice> referred to
   * via its object name service registered name.
   *
   * \param deviceName The name of the TosNetDevice Object to add to the container.
   */
  void Add (std::string deviceName);

  void InstallHardwareModels(HardwareModel *hw) ;

private:
  std::vector<Ptr<TosNetDevice> > m_devices;
};

} // namespace ns3

#endif /* NET_DEVICE_CONTAINER_H */
