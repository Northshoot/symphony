/*
 * sensor.cc
 *
 *  Created on: Oct 4, 2012
 *      Author: lauril
 */
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <dirent.h>

#include "ns3/log.h"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/assert.h"
#include "ns3/type-id.h"
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
            MakeUintegerChecker<uint32_t>())
//        .AddAttribute("Path", "The path to directory were sensor data files are stored.",
//            TypeId::ATTR_CONSTRUCT, //read write
//            StringValue(), MakeStringAccessor(&Sensor::m_path),
//            MakeStringChecker())
            ;
    return tid;
  }

  void
  Sensor::DoStart(void)
  {

    m_directory = Init();
    m_fileNames = GetMyData();
    //m_bufferQueue = CreateQueue();

    m_started = Simulator::Now();
    Object::DoStart();
  }

  void
  Sensor::DoDispose(void)
  {
    Object::DoDispose();
  }

  void
  Sensor::ReadData(char *buffer, const char * fileName)
  {
    FILE *file;
    size_t fileLen;

    file = fopen(fileName, "rb");
    NS_ASSERT_MSG(file, "Can't open file.");

//    if (!file)
//    {
//            fprintf(stderr, "can't open file %s", "1.m4v");
//            exit(1);
//    }

    fseek(file, 0, SEEK_END);
    fileLen = ftell(file);
    fprintf(stderr, "file size %ld\n", fileLen);
    fseek(file, 0, SEEK_SET);

    buffer = (char *) malloc(fileLen);
    NS_ASSERT_MSG(buffer, "Memory error!");
//    if (!buffer)
//    {
//            fprintf(stderr, "Memory error!");
//    fclose(file);
//            exit(1);
//    }

    fread(buffer, fileLen, 1, file);
    fclose(file);
  }

  Sensor::Sensor()
  {
    // TODO Auto-generated constructor stub

  }

  Sensor::~Sensor()
  {
    // TODO Auto-generated destructor stub
  }

  std::vector<std::string>
  Sensor::GetMyData(void)
  {
    std::vector<std::string> data;

    return data;
  }

  Time
  Sensor::GetTime(std::string dateTime)
  {

    return Simulator::Now();
  }

  void
  Sensor::DataCollector(void)
  {
  }

  std::vector<std::string>
  Sensor::Init(void)
  {
    DIR *dp;
    struct dirent *ep;
    std::string j;
    const char *dirname = m_path.c_str();
    std::vector<std::string> dirNames;

    dp = opendir(dirname);
    NS_ASSERT_MSG(dp, "No such directory or can't open it.");
    if (dp != NULL)
      { //while we have something in directory
        while ((ep = readdir(dp)))
          {
            j = ep->d_name;
            if (ep->d_reclen > Sensor::MIN_FILE_LENGTH)
              {
                dirNames.push_back(m_path + j);
              }
          }
        (void) closedir(dp);
      }
    NS_ASSERT(dirNames.size()>0);

    return dirNames;
  }
}//namespace
