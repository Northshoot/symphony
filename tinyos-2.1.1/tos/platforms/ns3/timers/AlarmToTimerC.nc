/*
 * Copyright (c) 2009 Communication Group and Eislab at
 * Lulea University of Technology
 *
 * Contact: Laurynas Riliskis, LTU
 * Mail: laurynas.riliskis@ltu.se
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of Communication Group at Lulea University of Technology
 *   nor the names of its contributors may be used to endorse or promote
 *    products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL STANFORD
 * UNIVERSITY OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * AlarmCounterMilli32C provides a 32-bit TMilli alarm and counter.
 *
 * @author 
 * @see  Please refer to TEP 102 for more information about this component.
 */

#include "Timer.h"
#include "sim/sim_main.h"
#define DEBUG_NS_TIMER 
generic module AlarmToTimerC(typedef precision_tag) @safe()
{
  provides interface Timer<precision_tag> as NsTimer;
  //provides interface Alarm<TMilli,uint32_t>;
  provides interface Init as InitNS;
  
  uses interface Timer<TMilli> as FromNs;
}
implementation
{
  
  uint32_t ticks=2;
  
    command void NsTimer.startPeriodic(uint32_t dt){
      #ifdef DEBUG_NS_TIMER
        printf("command void NsTimer.startPeriodic(uint32_t dt)\n");
      #endif
    }

  /**
   * Set a single-short timer to some time units in the future. Replaces
   * any current timer settings. Equivalent to startOneShotAt(getNow(),
   * dt). The <code>fired</code> will be signaled when the timer expires.
   *
   * @param dt Time until the timer fires.
   */
  command void NsTimer.startOneShot(uint32_t dt){
          #ifdef DEBUG_NS_TIMER
        printf("command void NsTimer.startPeriodic(uint32_t dt)\n");
      #endif
  }

  /**
   * Cancel a timer.
   */
  command void NsTimer.stop(){
          #ifdef DEBUG_NS_TIMER
        printf("command void NsTimer.stop()\n");
      #endif
  }

  /**
   * Signaled when the timer expires (one-shot) or repeats (periodic).
   */
//  event void NsTimer.fired(){
//    
//  }

  // extended interface
  /**
   * Check if timer is running. Periodic timers run until stopped or
   * replaced, one-shot timers run until their deadline expires.
   *
   * @return TRUE if the timer is still running.
   */
  command bool NsTimer.isRunning(){
          #ifdef DEBUG_NS_TIMER
        printf("command void NsTimer.startPeriodic(uint32_t dt)\n");
      #endif
    return 0;
    
  }

  /**
   * Check if this is a one-shot timer.
   * @return TRUE for one-shot timers, FALSE for periodic timers.
   */
  command bool NsTimer.isOneShot(){
          #ifdef DEBUG_NS_TIMER
        printf("command void NsTimer.startPeriodic(uint32_t dt)\n");
      #endif
    return 0;
    
  }

  /**
   * Set a periodic timer to repeat every dt time units. Replaces any
   * current timer settings. The <code>fired</code> will be signaled every
   * dt units (first event at t0+dt units). Periodic timers set in the past
   * will get a bunch of events in succession, until the timer "catches up".
   *
   * <p>Because the current time may wrap around, it is possible to use
   * values of t0 greater than the <code>getNow</code>'s result. These
   * values represent times in the past, i.e., the time at which getNow()
   * would last of returned that value.
   *
   * @param t0 Base time for timer.
   * @param dt Time until the timer fires.
   */
  command void NsTimer.startPeriodicAt(uint32_t t0, uint32_t dt){
           #ifdef DEBUG_NS_TIMER
        printf("command void NsTimer.startPeriodic(uint32_t dt)\n");
      #endif
  }

  /**
   * Set a single-short timer to time t0+dt. Replaces any current timer
   * settings. The <code>fired</code> will be signaled when the timer
   * expires. Timers set in the past will fire "soon".
   *
   * <p>Because the current time may wrap around, it is possible to use
   * values of t0 greater than the <code>getNow</code>'s result. These
   * values represent times in the past, i.e., the time at which getNow()
   * would last of returned that value.
   *
   * @param t0 Base time for timer.
   * @param dt Time until the timer fires.
   */
  command void NsTimer.startOneShotAt(uint32_t t0, uint32_t dt){
          #ifdef DEBUG_NS_TIMER
        printf("  command void NsTimer.startOneShotAt(uint32_t t0, uint32_t dt)\n");
      #endif
  }


  /**
   * Return the current time.
   * @return Current time.
   */
  command uint32_t NsTimer.getNow(){
    uint32_t t;
    atomic t=call FromNs.getNow();
      #ifdef DEBUG_NS_TIMER
        printf("command uint32_t NsTimer.getNow() %d\n",t);
      #endif
    return t;
  }

  /**
   * Return the time anchor for the previously started timer or the time of
   * the previous event for periodic timers. The next fired event will occur
   * at gett0() + getdt().
   * @return Timer's base time.
   */
  command uint32_t NsTimer.gett0(){
      #ifdef DEBUG_NS_TIMER
        printf("command uint32_t NsTimer.gett0()\n");
      #endif
    return 0;
  }

  /**
   * Return the delay or period for the previously started timer. The next
   * fired event will occur at gett0() + getdt().
   * @return Timer's interval.
   */
  command uint32_t NsTimer.getdt(){
          #ifdef DEBUG_NS_TIMER
        printf("command uint32_t NsTimer.getdt()\n");
      #endif
    return 0;
    }
  
  command error_t InitNS.init(){
          #ifdef DEBUG_NS_TIMER
        printf("command error_t InitNS.init()\n");
      #endif
    return 0;
    }


  event void FromNs.fired(){
       #ifdef DEBUG_NS_TIMER
        //printf("event void FromNs.fired() tick %d\n", ticks);
        atomic ticks++;
        //signal NsTimer.fired();
      #endif
  }
}

