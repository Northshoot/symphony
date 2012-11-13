/*
 * RF230-radio-model.h
 *
 *  Created on: Mar 27, 2012
 *      Author: lauril
 */

#ifndef RF230_RADIO_MODEL_H_
#define RF230_RADIO_MODEL_H_

#include "tos-radio-model.h"
#include "ns3/nstime.h"

class RF230RadioModel : public TosRadioModel {
	public : RF230RadioModel();
		virtual ~RF230RadioModel();
	
		void EnableACK(void);
		ns3::Time GetStartUpTime(void);
		ns3::Time GetWakeUpTime(void);
		ns3::Time GetChannelSwitchingDelay(void);
	
		ns3::Time GetRadioTxDelay(void);
		ns3::Time GetRadioRxDelay(void);
	
		ns3::Time GetCCADelay(void);
		ns3::Time GetEDDelay(void);
	
	private:
	   ns3::Time m_startUp ;
	   ns3::Time m_wakeUp ;
	   ns3::Time m_channelSwith ;
	   ns3::Time m_txDelay ;
	   ns3::Time m_rxDelay ;
	   ns3::Time m_ccaDelay ;
	   ns3::Time m_edDelay ;
	   
	   bool m_enableACK;

};

#endif /* RF230_RADIO_MODEL_H_ */
