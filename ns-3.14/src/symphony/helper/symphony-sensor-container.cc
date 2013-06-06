/*
 * symphony-sensor-container.cc
 *
 *  Created on: Oct 10, 2012
 *      Author: lauril
 */

#include "symphony-sensor-container.h"
#include "ns3/tos-device.h"

namespace ns3
{

SymphonySensorContainer::SymphonySensorContainer ()
{
}
SymphonySensorContainer::SymphonySensorContainer (Ptr<TosDevice> dev)
{
  m_sensors.push_back (dev);
}
SymphonySensorContainer::SymphonySensorContainer (std::string devName)
{
  Ptr<TosDevice> dev = Names::Find<TosDevice> (devName);
  m_sensors.push_back (dev);
}
SymphonySensorContainer::SymphonySensorContainer (const SymphonySensorContainer &a, const SymphonySensorContainer &b)
{
  *this = a;
  Add (b);
}


SymphonySensorContainer::Iterator
SymphonySensorContainer::Begin (void) const
{
  return m_sensors.begin ();
}
SymphonySensorContainer::Iterator
SymphonySensorContainer::End (void) const
{
  return m_sensors.end ();
}

uint32_t
SymphonySensorContainer::GetN (void) const
{
  return m_sensors.size ();
}
Ptr<TosDevice>
SymphonySensorContainer::Get (uint32_t i) const
{
  uint32_t index = m_sensors.size();
  NS_ASSERT(i<=index);
  return m_sensors[i];
}
void
SymphonySensorContainer::Add (SymphonySensorContainer other)
{
  for (Iterator i = other.Begin (); i != other.End (); i++)
    {
      m_sensors.push_back (*i);
    }
}
void
SymphonySensorContainer::Add (Ptr<TosDevice> sensor)
{
  m_sensors.push_back (sensor);
}
void
SymphonySensorContainer::Add (std::string sensorName)
{
  Ptr<TosDevice> sensor = Names::Find<TosDevice> (sensorName);
  m_sensors.push_back (sensor);
}




} /* namespace ns3 */
