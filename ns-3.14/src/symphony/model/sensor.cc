/*
 * sensor.cc
 *
 *  Created on: Oct 4, 2012
 *      Author: lauril
 */

#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/assert.h"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/object-vector.h"

#include "sensor.h"

NS_LOG_COMPONENT_DEFINE("Sensor");

namespace ns3
{

  NS_OBJECT_ENSURE_REGISTERED(Sensor);

  TypeId
  Sensor::GetTypeId(void)
  {
    TypeId tid =
        TypeId("ns3::Sensor").SetParent<Object>().AddConstructor<Sensor>().AddAttribute(
            "Id", "The id (unique integer) of this Node.",
            TypeId::ATTR_GET, // allow only getting it.
            UintegerValue(0), MakeUintegerAccessor(&Sensor::m_id),
            MakeUintegerChecker<uint32_t>());
    return tid;
  }

  void
  Sensor::DoStart(void)
  {
    Object::DoStart();
  }

  void
  Sensor::DoDispose(void)
  {
    Object::DoDispose();
  }

  void
  Sensor::ReadData(void)
  {

  }
  Sensor::Sensor()
  {
    // TODO Auto-generated constructor stub

  }

  Sensor::~Sensor()
  {
    // TODO Auto-generated destructor stub
  }

}
