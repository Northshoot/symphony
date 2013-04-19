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
    
     command uint32_t RealTimeClock.getTime(PRECISION prec){

       uint32_t a = 0;
      a=gatewayTime(proxy, prec);
      printf("now %u\n", gateway(proxy, 1, 0));
      printf("Woj woj %u\n",a);
      return a;
    }
}