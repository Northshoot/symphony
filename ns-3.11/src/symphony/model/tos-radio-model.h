/*
 * tos-radio-model.h
 *
 *  Created on: Mar 27, 2012
 *      Author: lauril
 */

#ifndef TOS_RADIO_MODEL_H_
#define TOS_RADIO_MODEL_H_

#include "ns3/nstime.h"
/**
 * Sceleton class for implmenting radio delays
 */
class TosRadioModel
  {
public:
  TosRadioModel();
  virtual ~TosRadioModel();
  /**
   * Examle of radio ack implementation
   */
  virtual void EnableACK(void)  = 0;
  
  /**
   * Delayes related to the hw delyes
   */
  virtual ns3::Time GetStartUpTime(void) =0;
  virtual ns3::Time GetWakeUpTime(void)=0;
  virtual ns3::Time GetChannelSwitchingDelay(void)=0;
  
  virtual ns3::Time GetRadioTxDelay(void)=0;
  virtual ns3::Time GetRadioRxDelay(void)=0;
  
  virtual ns3::Time GetCCADelay(void)=0;
  virtual ns3::Time GetEDDelay(void)=0;

  
  };

#endif /* TOS_RADIO_MODEL_H_ */
