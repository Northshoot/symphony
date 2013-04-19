/*
 * Copyright (c) 2013 Laurynas Riliskis.
 *
 * This file is distributed under the terms in 
 */
 
 /**
  * This interface provides access to real time clock in the symphony 
  * framework. The original usage purpose is for measuring clock drift.
  */
#include "ns3/calls-to-ns3.h"
  
   interface RealTimeClock{
     
    uint32_t command  getTime(PRECISION prec);
   }