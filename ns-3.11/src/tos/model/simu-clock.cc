/*
 * SimuClock.cpp
 *
 *  Created on: Aug 18, 2010
 *      Author: laurynas
 */
#include <cstdlib>
#include "ns3/object.h"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/assert.h"
#include "ns3/callback.h"
#include "ns3/ptr.h"

#include "simu-clock.h"

using namespace std;
namespace ns3
{
  NS_OBJECT_ENSURE_REGISTERED(SimuClock);

  TypeId
  SimuClock::GetTypeId(void)
  {
    static TypeId tid = TypeId("ns3::SimuClock").SetParent<Object>();

    return tid;
  }
  SimuClock::SimuClock(PRECISION p, TIMEDRIFT t,
      Callback<uint32_t, uint32_t> tf) :
      prec(p), type(t), timeDrift(0), callBack(tf)
  {
    count = 0;
  }

  SimuClock::~SimuClock()
  {

    DoDispose();
  }

  uint32_t
  SimuClock::getTimeNow()
  {
    //cout<< "SimuClock::getNow() "<<endl;
    //std::cout<<"getNow "<<Simulator::Now().GetMilliSeconds()<<std::endl;
    return Simulator::Now().GetMilliSeconds();
  }

  void
  SimuClock::DoStart()
  {
    //set up time
    double crystal;
    crystal = 1.0 / 1024.0;
    //std::cout<<"crystal "<<crystal<<std::endl;
    tickTime = SimuClock::getTime(prec, crystal);
    //std::cout<<"tickTime "<<tickTime<<std::endl;
    tick_event = Simulator::Schedule(tickTime, &SimuClock::timerFired, this);
  }

  void
  SimuClock::setTimeDrift(uint64_t td)
  {
    timeDrift = td;
  }

  void
  SimuClock::timerFired()
  {
    //std::cout<<"tick "<<Simulator::Now().GetMilliSeconds()<<std::endl;
    if (type == NONE)
      {
        tick_event = Simulator::Schedule(tickTime, &SimuClock::timerFired,
            this);
        count++;
        callBack(0);
      }
    else if (type == STATIC)
      {
        //TODO:
        std::cout << "SimuClock::timerFired() STATIC not implemented!"
            << std::endl;
        exit(1);
      }
    else if (type == EXPONENTIAL)
      {
        //TODO:
        std::cout << "SimuClock::timerFired() EXPONENTIAL not implemented!"
            << std::endl;
        exit(1);
      }
  }

  Time
  SimuClock::addTime(PRECISION p, Time tm_1, uint64_t tm_2)
  {
    Time t = Seconds(0.0);
    switch (p)
      {
    case SECOND:
      t = tm_1 + Seconds(tm_2 * 1.0);
      break;

    case MILLISECOND:
      t = tm_1 + MilliSeconds(tm_2);
      break;

    case MICROSECOND:
      t = tm_1 + MicroSeconds(tm_2);
      break;

    case NANOSECOND:
      t = tm_1 + NanoSeconds(tm_2);
      break;

    default:
      t = tm_1 + NanoSeconds(tm_2);
      break;
      }
    return t;
  }
  Time
  SimuClock::getTime(PRECISION p, double crystal)
  {
    NS_ASSERT_MSG(crystal != 0, "Cannot multiply with zero");
    Time t;
    //std::cout<<"SimuClock::getTime " <<p<<std::endl;
    switch (p)
      {
    case SECOND:
      t = Seconds(crystal * SECOND);
      break;
    case MILLISECOND:
      t = MilliSeconds((uint64_t) (crystal * MILLISECOND));
      break;

    case MICROSECOND:
      t = MicroSeconds((uint64_t) (crystal * MICROSECOND));
      break;

    case NANOSECOND:
      t = NanoSeconds((uint64_t) (crystal * NANOSECOND));
      break;
    default:
      std::cout << "nano" << crystal << " " << NANOSECOND << std::endl;
      t = NanoSeconds((uint64_t) (crystal * NANOSECOND));
      break;

      }
    //std::cout<<"SimuClock::getTime::tickTime "<<t<<std::endl;
    return t;
  }

  void
  SimuClock::DoDispose(void)
  {
    //std::cout << "DoDispose " << count << std::endl;
    //std::cout<<"DoDispose "<< tick_event.IsRunning() << std::endl;
  }
} //ns3 namespace

