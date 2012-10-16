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
#include "raw-sensor.h"

NS_LOG_COMPONENT_DEFINE("RawSensor");

namespace ns3
{

  NS_OBJECT_ENSURE_REGISTERED(RawSensor);

  TypeId
  RawSensor::GetTypeId(void)
  {
    static TypeId tid =
        TypeId("ns3::RawSensor")
        .SetParent<Object> ()
        .AddConstructor<RawSensor> ()
        .AddAttribute(
            "RsId", "The id (unique integer) of this RawSensor.",
            TypeId::ATTR_SET, // allow only getting it.
            UintegerValue(0), MakeUintegerAccessor(&RawSensor::m_id),
            MakeUintegerChecker<uint32_t>())
        .AddAttribute("SensorDataPath", "The path to directory were sensor data files are stored.",
            StringValue(),
            MakeStringAccessor(&RawSensor::m_path),
            MakeStringChecker())
         .AddAttribute("SensorStartDone","Callback for sensor start done event.",
             CallbackValue(),
             MakeCallbackAccessor(&RawSensor::m_SensorStartDone),
             MakeCallbackChecker ())
          .AddAttribute("SensorStopDone","Callback for sensor stop done event.",
                          CallbackValue(),
                          MakeCallbackAccessor(&RawSensor::m_SensorStopDone),
                          MakeCallbackChecker ())
          .AddAttribute("InterruptData","Callback for sensor Interrupt with data event.",
                                       CallbackValue(),
                                       MakeCallbackAccessor(&RawSensor::m_InterruptData),
                                       MakeCallbackChecker ())
            ;
    return tid;
  }

  void
  RawSensor::DoStart(void)
  {

    m_ids="ID10";
    m_directory = Init();
    m_fileNames = GetMyData();
    Object::DoStart();
    m_started = Simulator::Now();
    if(m_fileNames.size()>0){
      uint64_t now=m_fileNames.front();
      m_fileNames.erase(m_fileNames.begin());
      uint64_t next=m_fileNames.front();
      m_fileNames.erase(m_fileNames.begin());

      std::string fileN = m_path+m_ids+"_"+boost::lexical_cast<std::string>(now);
      ReadData(fileN.c_str());
      m_bufferQueue=true;
      m_next=Simulator::Schedule(m_started+MilliSeconds(now),&RawSensor::RawSensorEvent, this, MilliSeconds(next));
    } else {
        NS_LOG_INFO("No more sensor data.");
        m_bufferQueue=false;
    }
    //this must be sett!
    NS_ASSERT_MSG(!m_SensorStartDone.IsNull(), "SensorStartDone is not set!");
    m_SensorStartDone(0);
  }

  void
  RawSensor::DoDispose(void)
  {
    //SensorStopDone(0);
    if(m_next.IsRunning()){
        m_next.Cancel();
        if(m_bufferQueue) free(m_buffer);
    }

    Object::DoDispose();
  }

  void
  RawSensor::RawSensorEvent(Time ms)
  {
    uint64_t next;
    //do something with m_buffer

    //remember to free the memory
    free(m_buffer);
    //Reschedule event while data still exist
    if(m_fileNames.size()>0){
      next=m_fileNames.front();
      m_fileNames.erase(m_fileNames.begin());
      std::string fileN = m_path+m_ids +"_"+ boost::lexical_cast<std::string>(next);
      NS_LOG_INFO(fileN);
      ReadData(fileN.c_str());
      m_bufferQueue = true;
      m_next=Simulator::Schedule(m_started+ms,&RawSensor::RawSensorEvent, this, MilliSeconds(next));
    } else {
        NS_LOG_INFO("No more sensor data.");
        m_bufferQueue=false;
    }
  }
  void
  RawSensor::ReadData( const char * fileName)
  {
    NS_LOG_INFO(fileName);
    FILE *file;
    file = fopen(fileName, "rb");
    NS_ASSERT_MSG(file, "Can't open file.");
    fseek(file, 0, SEEK_END);
    m_fileLen = ftell(file);
    fseek(file, 0, SEEK_SET);
    m_buffer = (char *) malloc(m_fileLen);
    NS_ASSERT_MSG(m_buffer, "Memory error!");

    fread(m_buffer, m_fileLen, 1, file);
    fclose(file);
    NS_ASSERT_MSG(!m_InterruptData.IsNull(),"Callback for sensor interrupt with data is not set");
    int val = m_InterruptData(0,m_fileLen,(void*) m_buffer);
    NS_LOG_DEBUG(val);
  }

  RawSensor::RawSensor()
  {
    NS_LOG_FUNCTION (this);

  }

  RawSensor::~RawSensor()
  {
    // TODO Auto-generated destructor stub
  }


  std::vector<uint64_t>
  RawSensor::GetMyData(void)
  {
    std::vector<uint64_t> data;
    for(unsigned int i =0; i< m_directory.size();i++){
        std::string str = m_directory[i];
        std::vector<std::string> file;
        boost::split(file, str, boost::is_any_of("_"));
        if(file[0]==m_ids){
            data.push_back(boost::lexical_cast<uint64_t>(file[1]));

        }
    }
//    std::vector<uint64_t> data_s=data;
    boost::sort(data);
//    for(unsigned int i=0; i< data.size();i++){
//        std::cout<<"data:sorted "<<data[i]<<":"<<data_s[i]<<std::endl;
//    }
    return data;
  }

  Time
  RawSensor::GetTime(std::string dateTime)
  {

    return Simulator::Now();
  }



  std::vector<std::string>
  RawSensor::Init(void)
  {
    DIR *dp;
    struct dirent *ep;
    std::string j;
    const char *dirname = m_path.c_str();
    std::vector<std::string> fileNames;

    dp = opendir(dirname);
    NS_ASSERT_MSG(dp, "No such directory or can't open it.");
    if (dp != NULL)
      { //while we have something in directory
        while ((ep = readdir(dp)))
          {
            j = ep->d_name;
            //linux will give dirs "."-this and ".."-up dirs in the readin
            if (ep->d_reclen > RawSensor::MIN_FILE_LENGTH)
              {
                fileNames.push_back(j);

              }
          }
        (void) closedir(dp);
      }
    NS_ASSERT(fileNames.size()>0);

    return fileNames;
  }
}//namespace
