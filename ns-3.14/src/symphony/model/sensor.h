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

  class Sensor : public Object
  {
  public:
    static TypeId
    GetTypeId(void);
    const static uint32_t MIN_FILE_LENGTH = 10;
    Sensor();
    virtual
    ~Sensor();

    void
    DoStart(void);
    void
    DoDispose(void);

  private:
    Time m_started;
    /**
     * Read the binary data file and stores it in the buffer
     */
    void
    ReadData(char * buffer, const char * fileName);
    /**
     * Read directory and filter for your data
     */
    std::vector<std::string>
    GetMyData(void);
    /**
     * Date-Time Converter
     */
    Time
    GetTime(std :: string dateTime);
    void
    CreateQueue(void);
    /**
     * read in all file names in to the vector
     */
    std::vector<std::string>
    Init(void);

    void
    DataCollector(void);

    EventId m_next;
    std::string m_path;
    std::vector<std::string> m_directory;
    bool m_bufferQueue;
    std::vector<std::string> m_fileNames;
    std::map<char *, std::string> m_queue;
    uint32_t m_id;
  };
}

#endif /* SYMPHONY_SENSOR_H_ */
