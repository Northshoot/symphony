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
    RADIO_ON=0,
    RADIO_START=1,
    RADIO_SLEEP=2,
    RADIO_STOP=3,
    RADIO_SET_CHANNEL=4,
    RADIO_GET_CHANNEL=5,
    RADIO_SET_TX_POWER=6,
    RADIO_GET_TX_POWER=7,
    RADIO_SEND=8,
    RADIO_CANCEL=9,
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