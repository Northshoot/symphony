/*
 * switch-actuator-device.cc
 *
 *  Created on: Jun 5, 2013
 *      Author: onir
 */

#include "switch-actuator-device.h"

namespace ns3 {

SwitchActuatorDevice::SwitchActuatorDevice() {
	// TODO Auto-generated constructor stub

}

SwitchActuatorDevice::~SwitchActuatorDevice() {
	// TODO Auto-generated destructor stub
}

int
SwitchActuatorDevice::SendSwitchPosition(int8_t pos){

	return SwitchActuatorDevice::SendRawData(sizeof (pos), &pos);
}

} /* namespace ns3 */
