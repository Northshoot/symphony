/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * sensor.h
 *
 *  Created on: Oct 4, 2012
 *      Author: lauril
 */

#ifndef SYMPHONY_SENSOR_H_
#define SYMPHONY_SENSOR_H_

#include <string>
#include <map>
#include <stdint.h>
#include "ns3/callback.h"
#include "ns3/uinteger.h"
#include "ns3/object.h"
#include "ns3/event-id.h"
#include "ns3/nstime.h"
#include "ns3/ns3-to-tos-proxy_auto.h"
#include "ns3/calls-to-ns3.h"



namespace ns3
{

  class Magnetometer : public Object
  {
  public:
    static TypeId
    GetTypeId(void);

    const static uint32_t MIN_FILE_LENGTH = 8;
    Magnetometer();

    virtual
    ~Magnetometer();

    void
    DoStart(void);
    void
    DoDispose(void);

    void
    MagnetometerEvent(std::string fileN);



  private:
    Time m_started;
    /**
     * Read the binary data file and stores it in the buffer
     */
    void
    ReadData(const char * fileName);
    /**
     * Read directory and filter for your data
     */
    std::vector<uint64_t>
    GetMyData(void);
    /**
     * Date-Time Converter
     */
    Time
    GetTime(std :: string dateTime);

    /**
     * read in all file names in to the vector
     */
    std::vector<std::string>
    Init(void);

    Callback<int, uint8_t> m_SensorStartDone;
    Callback<int, uint8_t> m_SensorStopDone;
    Callback<int, uint8_t,uint16_t,void *> m_InterruptData;
    EventId m_next;
    std::string m_path;
    std::string m_ids;
    std::vector<std::string> m_directory;
    bool m_bufferQueue;
    std::vector<uint64_t> m_fileNames;
    char *m_buffer;
    long m_fileLen;
    uint32_t m_id;

  };
}

#endif /* SYMPHONY_SENSOR_H_ */
