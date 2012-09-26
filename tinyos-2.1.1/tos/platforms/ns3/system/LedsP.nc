// $Id: LedsP.nc,v 1.6 2008/06/24 05:32:32 regehr Exp $

/*
 * Copyright (c) 2000-2005 The Regents of the University  of California.  
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the University of California nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * The implementation of the standard 3 LED mote abstraction.
 *
 * @author Joe Polastre
 * @author Philip Levis
 *
 * @date   March 21, 2005
 */

/**
 * Virtualized Leds
 *
 * @author Laurynas Riliskis <laurynas.riliskis@ltu.se>
 */
#include <stdint.h>

#include "sim/logprinter.h"
 

  
module LedsP @safe() {
  provides {
    interface Init;
    interface Leds;
  }
    uses {
    interface GeneralIO as Led0;
    interface GeneralIO as Led1;
    interface GeneralIO as Led2;
  }

}
implementation {
  command error_t Init.init() {

    return SUCCESS;
  }



  async command void Leds.led0On() {
    DBVIRTGLED( 0, "on");
  }

  async command void Leds.led0Off() {
    DBVIRTGLED(0,"off");
  }

  async command void Leds.led0Toggle() {
    DBVIRTGLED(0,"toggle");
  }

  async command void Leds.led1On() {
    DBVIRTGLED(1,"on");
  }

  async command void Leds.led1Off() {
    DBVIRTGLED(1,"off");
  }

  async command void Leds.led1Toggle() {
    DBVIRTGLED(1,"toggle");
  }

  async command void Leds.led2On() {
    DBVIRTGLED(2,"on");
  }

  async command void Leds.led2Off() {
    DBVIRTGLED(2,"off");
  }

  async command void Leds.led2Toggle() {
    DBVIRTGLED(2,"toggle");
  }

  async command uint8_t Leds.get() {
//    uint8_t rval;
//    atomic {
//      rval = 0;
//      if (call Led0.get()) {
//	rval |= LEDS_LED0;
//      }
//      if (call Led1.get()) {
//	rval |= LEDS_LED1;
//      }
//      if (call Led2.get()) {
//	rval |= LEDS_LED2;
//      }
//    }
    return 0;
  }

  async command void Leds.set(uint8_t val) {
//    atomic {
//      if (val & LEDS_LED0) {
//	call Leds.led0On();
//      }
//      else {
//	call Leds.led0Off();
//      }
//      if (val & LEDS_LED1) {
//	call Leds.led1On();
//      }
//      else {
//	call Leds.led1Off();
//      }
//      if (val & LEDS_LED2) {
//	call Leds.led2On();
//      }
//      else {
//	call Leds.led2Off();
//      }
//    }
  }
}
