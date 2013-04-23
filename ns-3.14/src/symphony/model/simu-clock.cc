/*
 * SimuClock.cpp
 *
 *  Created on: Aug 18, 2010
 *      Author: laurynas
 */
#include <cstdlib>
#include <math.h>

#include "ns3/object.h"
#include "ns3/nstime.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/assert.h"
#include "ns3/callback.h"
#include "ns3/ptr.h"
#include "ns3/random-variable-stream.h"
#include "ns3/double.h"
#include "ns3/uinteger.h"
#include "ns3/pointer.h"
#include "ns3/string.h"
#include "ns3/enum.h"
#include "ns3/log.h"


#include "simu-clock.h"
#include "calls-to-ns3.h"

using namespace std;
NS_LOG_COMPONENT_DEFINE("SimuClock");
namespace ns3
{
  NS_OBJECT_ENSURE_REGISTERED(SimuClock);

  TypeId
  SimuClock::GetTypeId(void)
  {
    static TypeId tid = TypeId("ns3::SimuClock")
        .SetParent<Object>()
        .AddConstructor<SimuClock>()
        .AddAttribute ("TickTime", ("The time per tick"),
            TimeValue (Seconds(1.0/1024.0)),
            MakeTimeAccessor (&SimuClock::m_tickTime),
            MakeTimeChecker ())
        .AddAttribute ("ClockDriftType", ("The type of clock drift"),
            EnumValue(SimuClock::NONE),
            MakeEnumAccessor(&SimuClock::m_ClockDriftType),
            MakeEnumChecker(SimuClock::NONE, "None", SimuClock::STATIC, "Static",
                            SimuClock::EXPONENTIAL, "Exponential", SimuClock::RANDOM,"Random"))
        .AddAttribute ("ClockDriftPeriod", ("The period when clock drift occurs"),
            TimeValue (MilliSeconds(400)),
            MakeTimeAccessor (&SimuClock::m_clockDriftPeriod),
            MakeTimeChecker ())
        .AddAttribute ("ClockDrift", ("The clock drift per period"),
            TimeValue (MilliSeconds(1)),
            MakeTimeAccessor (&SimuClock::m_timeDrift),
            MakeTimeChecker ())
        .AddAttribute ("NormalDrift",
            "A gaussian random variable used to calculate the next drift value.",
           StringValue ("ns3::NormalRandomVariable[Mean=0.0|Variance=85.0|Bound=100.0]"), // Defaults to zero mean, and std dev = 1, and bound to +-10 of the mean
           MakePointerAccessor (&SimuClock::m_randomDriftDistribution),
           MakePointerChecker<NormalRandomVariable> ())
         .AddAttribute ("RandomMean", ("The mean of the random number."),
             DoubleValue (0),
             MakeDoubleAccessor (&SimuClock::m_mean),
             MakeDoubleChecker <double> ())
         .AddAttribute ("RandomVariance", ("The variance of the random."),
             DoubleValue (2),
             MakeDoubleAccessor (&SimuClock::m_variance),
             MakeDoubleChecker <double> ())
         .AddAttribute ("RandomBound", ("Limits of the random variable."),
             DoubleValue (10),
             MakeDoubleAccessor (&SimuClock::m_bound),
             MakeDoubleChecker <double> ())
         .AddAttribute ("TicksPerSecond", ("Defines how many ticks should be generated per second. Default is 1024."),
             DoubleValue (1024.0),
             MakeDoubleAccessor (&SimuClock::m_ticksPerSecond),
             MakeDoubleChecker <double> ())
            ;

    return tid;
  }

  SimuClock::SimuClock(){
    Construct();
  }

  SimuClock::SimuClock(Callback<uint32_t, uint64_t> tf){
    SimuClock(MICROSECOND, SimuClock::NONE, tf);
  }

  SimuClock::SimuClock(PRECISION p, Callback<uint32_t, uint64_t> tf)
  {
    SimuClock(p, SimuClock::NONE, tf);
  }

  SimuClock::SimuClock(PRECISION p, TimeDriftType t,
      Callback<uint32_t, uint64_t> tf) :
      prec(p), m_ClockDriftType(t), m_timeDrift(0), m_callBack(tf)
  {
    count = 0;

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

  //this can be dome more clean, by adding accessors to the simuclock and using
  //only abstract random class for integer generation
  m_randomDriftDistribution->SetStream(-123546789);
}
void
SimuClock::Construct(void)
{

  m_tickTime = MicroSeconds((1/m_ticksPerSecond)*NANOSECOND);
  m_exonentialCount=1;
  if (m_ClockDriftType == RANDOM)
    {
      InitRandom();
    }
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
    m_tickEvent = Simulator::Schedule(m_tickTime, &SimuClock::timerFired, this);
    //NS_LOG_FUNCTION(this<<" tickTime "<<m_tickTime <<" driftType " << m_ClockDriftType <<" timeDrift "<<m_timeDrift);
    if(m_ClockDriftType!=SimuClock::NONE)
      m_clockDriftEvent = Simulator::Schedule(m_clockDriftPeriod, &SimuClock::ClockDrift, this);
  }


void
SimuClock::ClockDrift()
{
  //update clock drift
  double drift;
  Time prevTick;
  Time now;
  switch (m_ClockDriftType) {
    case STATIC:
      m_tickTime+=m_timeDrift;
      break;
    case EXPONENTIAL:

      m_timeDrift=MicroSeconds(exp(m_exonentialCount));
      m_exonentialCount++;
      m_tickTime+=m_timeDrift;
      break;

    case RANDOM:
      //m_tickTime+=MicroSeconds(m_randomDriftDistribution->GetInteger());
      drift = m_randomDriftDistribution->GetValue();
      prevTick = m_tickTime;
      m_tickTime+=MicroSeconds(drift);

      //NS_LOG_FUNCTION(this<<" drift "<< drift << " floor "<< abs((int)floor(drift))<< " m_tickTime " << m_tickTime);
      //Since we dealing with random numbers there can be several unexpected cases
      //1. tickTime is negative
      m_tickTime = ns3::Abs(m_tickTime);
      //2. tickTime is bigger then maximum simulation time
      //3. tickTime is 0
      //therefore we set boundries
      //TODO: allow dynamic boundry set up
      if(m_tickTime < MicroSeconds(200) || m_tickTime > MicroSeconds(5000))
        m_tickTime=Seconds(1.0/1024);
      std::cout<<m_tickTime.GetMicroSeconds()<<std::endl;
      break;
    default:
      //default == NONE
      break;

  }
  //reschedule ClockDrift
  //NS_LOG_FUNCTION(this<<" drift "<<m_timeDrift<<" tickTime "<<m_tickTime);
  m_clockDriftEvent=Simulator::Schedule(m_clockDriftPeriod, &SimuClock::ClockDrift, this);
}
  void
  SimuClock::timerFired()
  {

    m_tickEvent = Simulator::Schedule(m_tickTime, &SimuClock::timerFired,this);

    m_callBack(Simulator::Now().GetMicroSeconds());

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

