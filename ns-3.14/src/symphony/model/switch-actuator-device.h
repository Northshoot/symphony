/*
 * switch-actuator-device.h
 *
 *  Created on: Jun 5, 2013
 *      Author: onir
 */

#ifndef SWITCH_ACTUATOR_DEVICE_H_
#define SWITCH_ACTUATOR_DEVICE_H_

#include "tos-device.h"

namespace ns3 {

class SwitchActuatorDevice: public ns3::TosDevice {
public:
	SwitchActuatorDevice();
	virtual ~SwitchActuatorDevice();

	int SendSwitchPosition(int8_t pos);
};

} /* namespace ns3 */
#endif /* SWITCH_ACTUATOR_DEVICE_H_ */
