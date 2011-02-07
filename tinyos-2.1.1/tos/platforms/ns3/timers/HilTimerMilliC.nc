// $Id: HilTimerMilliC.nc,v 1.4 2006/12/12 18:23:44 vlahan Exp $
/*
 * Copyright (c) 2005-2006 Intel Corporation
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached INTEL-LICENSE     
 * file. If you do not find these files, copies can be found by writing to
 * Intel Research Berkeley, 2150 Shattuck Avenue, Suite 1300, Berkeley, CA, 
 * 94704.  Attention:  Intel License Inquiry.
 */

configuration HilTimerMilliC
{
  provides interface Init;

  provides interface Timer<TMilli> as TimerMilli[ uint8_t num ];
  //provides interface LocalTime<TMilli>;
}
implementation
{
  //components new AlarmToTimerC(TMilli);
  components new VirtualizeTimerC(TMilli,uniqueCount(UQ_TIMER_MILLI));
  components NsTimerP;

  //AlarmToTimerC.FromNs->NsTimerP;

  TimerMilli = VirtualizeTimerC;
  //LocalTime = CounterToLocalTimeC;

  VirtualizeTimerC.TimerFrom -> NsTimerP;
  //AlarmToTimerC.Alarm -> AlarmCounterMilli32C.Alarm;
  //CounterToLocalTimeC.Counter -> AlarmCounterMilli32C.Counter;
  Init = NsTimerP;
}
