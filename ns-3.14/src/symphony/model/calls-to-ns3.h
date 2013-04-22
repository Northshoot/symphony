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

typedef enum {
  SENSOR_ON=0,
  SENSOR_OFF=1,
  SENSOR_GET_DATA=2,
  SENSOR_RESET=3,
}SensorCall;

typedef enum {
  APP_ON=1,
  APP_OFF=2,
  APP_RX=3,
}ApplicationCall;

typedef enum  {
  SECOND=1,
  MILLISECOND=1000,
  MICROSECOND=1000000,
  NANOSECOND=1000000000
}PRECISION;

#endif /* CALLS_TO_NS3_H_ */
