/*
 * calls-to-ns3.h
 *
 *  Created on: Mar 9, 2012
 *      Author: lauril
 */

#ifndef CALLS_TO_NS3_H_
#define CALLS_TO_NS3_H_
//Calls to Radio Device

typedef enum {
    RADIO_ON, RADIO_START, RADIO_SLEEP,RADIO_STOP,
    RADIO_SET_CHANNEL,RADIO_GET_CHANNEL,
    RADIO_SET_TX_POWER, RADIO_GET_TX_POWER, RADIO_SEND, RADIO_CANCEL
}DeviceCall;

typedef enum {
	RADIO_STATE_ON,
	RADIO_STATE_STANDBY,
	RADIO_STATE_OFF,
	RADIO_STATE_SWITCHING_CHANNEL,
	RADIO_STATE_TX,
	RADIO_STATE_RX
} RadioState;
#endif /* CALLS_TO_NS3_H_ */
