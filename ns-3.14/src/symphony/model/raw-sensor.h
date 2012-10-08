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
#include "ns3/uinteger.h"
#include "ns3/object.h"
#include "ns3/event-id.h"
#include "ns3/nstime.h"

#ifndef __SIZE_T
#define __SIZE_T
typedef unsigned int size_t;
#endif

namespace ns3
{

  class RawSensor : public Object
  {
  public:
    static TypeId
    GetTypeId(void);

    const static uint32_t MIN_FILE_LENGTH = 10;
    RawSensor();

    virtual
    ~RawSensor();

    void
    DoStart(void);
    void
    DoDispose(void);

    void
    RawSensorEvent(Time ms);

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


    EventId m_next;
    std::string m_path;
    std::string m_ids;
    std::vector<std::string> m_directory;
    bool m_bufferQueue;
    std::vector<uint64_t> m_fileNames;
    char *m_buffer;
    size_t m_fileLen;
    uint32_t m_id;
  };
}

#endif /* SYMPHONY_SENSOR_H_ */
