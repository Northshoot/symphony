/*
 * RF230-radio-model.cc
 *
 *  Created on: Mar 27, 2012
 *      Author: lauril
 */

#include "RF230-radio-model.h"

//TODO: auto generated from XML
//TODO: values determined experimentaly
RF230RadioModel::RF230RadioModel()
{
  m_ccaDelay      = ns3::MicroSeconds(10);
  m_channelSwith  = ns3::MicroSeconds(10);
  m_edDelay       = ns3::MicroSeconds(10);
  m_rxDelay       = ns3::MicroSeconds(10);
  m_startUp       = ns3::MicroSeconds(500);
  m_txDelay       = ns3::MicroSeconds(100);
  m_wakeUp        = ns3::MicroSeconds(200);
  m_enableACK     = false;

}

RF230RadioModel::~RF230RadioModel()
{
  // TODO Auto-generated destructor stub
}


void
RF230RadioModel::EnableACK(void)
{

}
ns3::Time
RF230RadioModel::GetStartUpTime(void)
{
  return m_startUp;
}
ns3::Time
RF230RadioModel::GetWakeUpTime(void){
  return m_wakeUp;
}
ns3::Time
RF230RadioModel::GetChannelSwitchingDelay(void)
{
  return m_channelSwith;
}

ns3::Time
RF230RadioModel::GetRadioTxDelay(void)
{
  return m_txDelay;
}
ns3::Time
RF230RadioModel::GetRadioRxDelay(void)
{
  return m_rxDelay;
}

ns3::Time
RF230RadioModel::GetCCADelay(void)
{
  return m_ccaDelay;
}
ns3::Time
RF230RadioModel::GetEDDelay(void)
{
  return m_edDelay;
}
