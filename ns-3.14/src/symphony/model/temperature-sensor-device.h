/*
 * temperature-sensor-device.h
 *
 *  Created on: Jun 5, 2013
 *      Author: onir
 */

#ifndef TEMPERATURE_SENSOR_DEVICE_H_
#define TEMPERATURE_SENSOR_DEVICE_H_

#include "tos-device.h"

namespace ns3 {

class TemperatureSensorDevice: public ns3::TosDevice {
public:
	TemperatureSensorDevice();
	virtual ~TemperatureSensorDevice();

	int SendTemperature(int16_t temp);
};

} /* namespace ns3 */
#endif /* TEMPERATURE_SENSOR_DEVICE_H_ */
