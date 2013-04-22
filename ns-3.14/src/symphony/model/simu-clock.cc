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
#include "ns3/random-variable-stream.h"
#include "ns3/double.h"

#include "simu-clock.h"
#include "calls-to-ns3.h"

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

  SimuClock::SimuClock(PRECISION p, Callback<uint32_t, uint64_t> tf)
  {
    SimuClock(p, NONE, tf);
  }

  SimuClock::SimuClock(PRECISION p, TIMEDRIFT t,
      Callback<uint32_t, uint64_t> tf) :
      prec(p), type(t), timeDrift(0), callBack(tf)
  {
    count = 0;
    if (type == RANDOM)
      {
        InitRandom();
      }
    Construct();
  }

  SimuClock::~SimuClock()
  {

    DoDispose();
  }

void
SimuClock::InitRandom(void)
{
  //implementation can be done by configuring the clock more generically
  //for now we are "happy" about this static connection
  mean = 50.0;
  variance = 5.0;
  randomDriftDistribution = CreateObject<NormalRandomVariable> ();
  randomDriftDistribution->SetAttribute ("Mean", DoubleValue (mean));
  randomDriftDistribution->SetAttribute ("Variance", DoubleValue (variance));
}
void
SimuClock::Construct(void)
{
  double crystal;
  crystal = 1.0 / 1024.0;
  tickTime = MicroSeconds(crystal*MICROSECOND);
  timeDrift = MicroSeconds(0);
}
  uint64_t
  SimuClock::getTimeNow()
  {
    return Simulator::Now().GetMicroSeconds();
  }

  void
  SimuClock::DoStart()
  {
    //set up time first time there is no drift
    tick_event = Simulator::Schedule(tickTime+timeDrift, &SimuClock::timerFired, this);
  }

  void
  SimuClock::setTimeDrift(uint64_t td, PRECISION precision)
  {
	  switch (precision) {
		case SECOND:
			timeDrift = ns3::Seconds(td*1.0);
			break;
		case MILLISECOND:
			timeDrift = ns3::MilliSeconds(td);
			break;
		case MICROSECOND:
			timeDrift = ns3::MicroSeconds(td);
			break;
		case NANOSECOND:
			timeDrift = ns3::NanoSeconds(td);
			break;
		default:
			NS_ASSERT_MSG(true,"undefined PRECISION for clock drift");
			break;
	}
  }

  void
  SimuClock::timerFired()
  {
    Time nextTick;
    switch (type) {
      case STATIC:
        nextTick = tickTime+timeDrift;
        break;

      case EXPONENTIAL:
        timeDrift=SimuClock::addTime(MICROSECOND,timeDrift,5);
        nextTick = tickTime+timeDrift;
        break;

      case RANDOM:
        nextTick=tickTime+MicroSeconds(randomDriftDistribution->GetInteger());

        break;
      default:
        //default == NONE
        nextTick = tickTime;
        break;
    }
    tick_event = Simulator::Schedule(nextTick, &SimuClock::timerFired,
            this);
    callBack(Simulator::Now().GetMicroSeconds());

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
      //std::cout << "nano" << crystal << " " << NANOSECOND << std::endl;
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

