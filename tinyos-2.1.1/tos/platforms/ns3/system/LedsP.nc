// $Id: LedsP.nc,v 1.6 2008/06/24 05:32:32 regehr Exp $


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


#include "../defines.h"
 

  
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
    dbg( "Led0", "on");
  }

  async command void Leds.led0Off() {
     dbg( "Led0","off");
  }

  async command void Leds.led0Toggle() {
     dbg( "Led0","toggle");
  }

  async command void Leds.led1On() {
     dbg( "Led1","on");
  }

  async command void Leds.led1Off() {
     dbg( "Led1","off");
  }

  async command void Leds.led1Toggle() {
     dbg( "Led1","toggle");
  }

  async command void Leds.led2On() {
     dbg( "Led2","on");
  }

  async command void Leds.led2Off() {
     dbg( "Led2","off");
  }

  async command void Leds.led2Toggle() {
     dbg( "Led2","toggle");
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
