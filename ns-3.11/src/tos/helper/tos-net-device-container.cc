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

#include "tos-net-device-container.h"
#include "ns3/names.h"
#include "ns3/tos-net-device.h"

namespace ns3 {

TosNetDeviceContainer::TosNetDeviceContainer ()
{
}
TosNetDeviceContainer::TosNetDeviceContainer (Ptr<TosNetDevice> dev)
{
  m_devices.push_back (dev);
}
TosNetDeviceContainer::TosNetDeviceContainer (std::string devName)
{
  Ptr<TosNetDevice> dev = Names::Find<TosNetDevice> (devName);
  m_devices.push_back (dev);
}
TosNetDeviceContainer::TosNetDeviceContainer (const TosNetDeviceContainer &a, const TosNetDeviceContainer &b)
{
  *this = a;
  Add (b);
}

void
TosNetDeviceContainer::InstallHardwareModels(HardwareModel * hw)
{
  for(unsigned int i =0;i<m_devices.size();i++)
    {
      m_devices[i]->SetRadioModel(hw);
    }
}

TosNetDeviceContainer::Iterator
TosNetDeviceContainer::Begin (void) const
{
  return m_devices.begin ();
}
TosNetDeviceContainer::Iterator
TosNetDeviceContainer::End (void) const
{
  return m_devices.end ();
}

uint32_t 
TosNetDeviceContainer::GetN (void) const
{
  return m_devices.size ();
}
Ptr<TosNetDevice>
TosNetDeviceContainer::Get (uint32_t i) const
{
  return m_devices[i];
}
void 
TosNetDeviceContainer::Add (TosNetDeviceContainer other)
{
  for (Iterator i = other.Begin (); i != other.End (); i++)
    {
      m_devices.push_back (*i);
    }
}
void 
TosNetDeviceContainer::Add (Ptr<TosNetDevice> device)
{
  m_devices.push_back (device);
}
void 
TosNetDeviceContainer::Add (std::string deviceName)
{
  Ptr<TosNetDevice> device = Names::Find<TosNetDevice> (deviceName);
  m_devices.push_back (device);
}

} // namespace ns3
