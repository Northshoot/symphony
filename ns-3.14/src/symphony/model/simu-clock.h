/*
 * SimuClock.h
 *
 *  Created on: Aug 18, 2010
 *      Author: laurynas
 */
/**
 * Crystal generates 1/1024 tick per second
 * Thus we tick is every
 * 		1/1024*10^9 ns
 * 		1/1024*10^6 µs
 * 		1/1024*10^3 ms *not recommended to use*
 *
 * Through this class the "ticking" is provided to the mode HilTimer in
 * ns3 platform under TinyOS
 */

#ifndef NSTOSCLOCK_H_
#define NSTOSCLOCK_H_

#include <stdint.h>
#include "ns3/ptr.h"
#include "ns3/random-variable-stream.h"
#include "ns3/nstime.h"
#include "ns3/event-id.h"
#include "ns3/callback.h"
#include "ns3/calls-to-ns3.h"





enum TIMEDRIFT {NONE, STATIC, EXPONENTIAL, RANDOM};

namespace ns3 {

  class SimuClock : public Object {
 
    public:
    static TypeId GetTypeId (void);
    
    SimuClock(PRECISION p, Callback<uint32_t, uint64_t> tf);
    SimuClock(PRECISION p , TIMEDRIFT t,  Callback<uint32_t,uint64_t>  tf);

    /**
     * sets time drift parameter
     * default = 0
     */	
    void setTimeDrift(uint64_t timeDrift, PRECISION precision);
	
    /**
     * handle timer event
     */
    void timerFired();
 
    uint64_t getTimeNow();
	
    virtual ~SimuClock();
    protected:
      /**
       * The dispose method. Subclasses must override this method
       * and must chain up to it by calling Node::DoDispose at the
       * end of their own DoDispose method.
       */
    virtual void DoStart(void);
    virtual void DoDispose (void);
private:
    void Construct(void);
    void InitRandom(void);
    Ptr<NormalRandomVariable> randomDriftDistribution;
    double mean;
    double variance;
    /**
     * precision for *tick*
     */
    PRECISION prec;
    /**
     * type of time drift
     */
    TIMEDRIFT type;
 
    /**
     * the value of time drift
     */	
    Time timeDrift;
    /**
     * pointer to callback function
     */
    Callback<uint32_t,uint64_t>  callBack;
 
    /**
     * Tick time
     */
    Time tickTime;
 
    /**
     * tick event
     */
    EventId tick_event;
    uint64_t count; //temp val to count ammount for debugging
    Time getTime(PRECISION p, double crystal);
    Time addTime(PRECISION p, Time tm_1, uint64_t tm_2);
  };

}

#endif /* NSTOSCLOCK_H_ */
