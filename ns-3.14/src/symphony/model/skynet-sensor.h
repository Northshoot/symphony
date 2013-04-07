/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * sensor.h
 *
 *  Created on: Oct 4, 2012
 *      Author: lauril
 */

#ifndef SKYNET_SENSOR_H_
#define SKYNET_SENSOR_H_

#include <string>
#include <map>
#include <stdint.h>
#include "ns3/callback.h"
#include "ns3/integer.h"
#include "ns3/object.h"
#include "ns3/event-id.h"
#include "ns3/nstime.h"
#include "raw-sensor.h"

namespace ns3
{

  class SkynetSensor : public RawSensor
  {
  public:
    static TypeId
    GetTypeId(void);

    const static uint32_t MIN_FILE_LENGTH = 8;
    SkynetSensor();

    virtual
    ~SkynetSensor();

    void
    DoStart(void);

    void
    DoDispose(void);

    void
    SetTemperatureValue(int temp);

    void
    RawSensorEvent(std::string fileN);

  private:
    int m_temp;

  };
}

#endif /* SYMPHONY_SENSOR_H_ */
