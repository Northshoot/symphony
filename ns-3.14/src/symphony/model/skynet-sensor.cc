/*
 * sensor.cc
 *
 *  Created on: Oct 4, 2012
 *      Author: lauril
 */
#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <dirent.h>


#include "ns3/log.h"
#include "ns3/nstime.h"
#include "ns3/string.h"
#include "ns3/callback.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/assert.h"
#include "ns3/type-id.h"
#include "skynet-sensor.h"

NS_LOG_COMPONENT_DEFINE("SkynetSensor");

namespace ns3
{

  NS_OBJECT_ENSURE_REGISTERED(SkynetSensor);

  TypeId
  SkynetSensor::GetTypeId(void)
  {
    static TypeId tid =
        TypeId("ns3::SkynetSensor")
        .SetParent<RawSensor> ()
        .AddConstructor<SkynetSensor> ()
        .AddAttribute(
            "TemperatureValue", "The value of the temperature sensor.",
            IntegerValue(0),
            MakeIntegerAccessor(&SkynetSensor::m_temp),
            MakeIntegerChecker<int32_t>());
    return tid;
  }

   void
  SkynetSensor::DoStart(void)
  {
	NS_LOG_FUNCTION (this);
    RawSensor::DoStart();

    //Simulator::ScheduleNow(&SkynetSensor::SetTemperatureValue, this, m_temp );
    //this must be sett!
    NS_ASSERT_MSG(!m_SensorStartDone.IsNull(), "SkynetSensor - SensorStartDone is not set!");
    m_SensorStartDone(0);
  }

  void
  SkynetSensor::DoDispose(void)
  {
	NS_LOG_FUNCTION (this);
    RawSensor::DoDispose();
    NS_LOG_INFO("DoDispose()");
  }

  void
  SkynetSensor::RawSensorEvent(std::string fileN)
  {
	 NS_LOG_FUNCTION (this);
     NS_LOG_INFO(Simulator::Now());
     m_InterruptData(0, 2,(void*) m_buffer);
    // Simulator::Schedule(Time(2000000000.0), &SkynetSensor::RawSensorEvent, this, m_path );
  }

  void
  SkynetSensor::SetTemperatureValue(int temp)
  {
	  m_InterruptData(0, sizeof(temp), &temp);
  }

  SkynetSensor::SkynetSensor()
  {
    NS_LOG_FUNCTION (this);

  }

  SkynetSensor::~SkynetSensor()
  {
	 NS_LOG_FUNCTION (this);
    // TODO Auto-generated destructor stub
  }

}//namespace
