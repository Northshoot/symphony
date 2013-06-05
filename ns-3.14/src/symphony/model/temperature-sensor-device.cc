/*
 * temperature-sensor-device.cpp
 *
 *  Created on: Jun 5, 2013
 *      Author: onir
 */

#include "temperature-sensor-device.h"

namespace ns3 {

TemperatureSensorDevice::TemperatureSensorDevice() {
	// TODO Auto-generated constructor stub

}

TemperatureSensorDevice::~TemperatureSensorDevice() {
	// TODO Auto-generated destructor stub
}

int
TemperatureSensorDevice::SendTemperature(int16_t temp){

	return TemperatureSensorDevice::SendRawData(sizeof (temp), &temp);
}

} /* namespace ns3 */
