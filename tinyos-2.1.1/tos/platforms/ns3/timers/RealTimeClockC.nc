/*
 * Copyright (c) 2013 Laurynas Riliskis.
 *
 * This file is distributed under the terms in 
 */

#include "Timer.h"
#include "ns3/calls-to-ns3.h"
#include "sim/sim_main.h"

module RealTimeClockC {
  provides {
    interface RealTimeClock;
  }
  
  }
  
  
  implementation {
    
     command uint64_t RealTimeClock.getTime(PRECISION prec){

       uint64_t a = gateway(proxy, 1, prec);
      //printf("now %u\n", gateway(proxy, 1, 0));
      printf("Woj woj %lu\n",a);
      return a;
    }
}