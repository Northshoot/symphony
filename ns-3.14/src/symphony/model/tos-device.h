/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * tos-device.h
 *
 *  Created on: June 2 , 2013
 *      Author: Jose Angel Fernandez
 */

#ifndef TOS_DEVICE_H
#define TOS_DEVICE_H

#include "ns3/object.h"

namespace ns3 {

class TosDevice: public Object {

public:

	static TypeId GetTypeId(void);

	TosDevice();
	virtual ~TosDevice();

	void
	DoStart(void);

	void
	DoDispose(void);

	/**
	 * Sends the content of the buffer to the device
	 * in TinyOS as an interruption
	 */
	int
	SendRawData(uint16_t size, void * buffer );

protected:

	/**
	 * Unique identifier of the device
	 */
	uint32_t m_id;

	/**
	 * Notifies the device inside TinyOS that
	 * it has been properly initialized in the simulator.
	 */
    Callback<int, uint8_t> m_StartDone;

	/**
	 * Notifies the device inside TinyOS that
	 * it has been properly stopped in the simulator.
	 */
    Callback<int, uint8_t> m_StopDone;

    /**
     * Sends data to the device as an interruption from
     * the simulator
     */
    Callback<int, uint8_t, uint16_t ,void * > m_InterruptDeviceWithData;
};
}

#endif /* TOS_DEVICE_H */
