/*
 * sensor.h
 *
 *  Created on: Oct 4, 2012
 *      Author: lauril
 */

#ifndef SYMPHONY_SENSOR_H_
#define SYMPHONY_SENSOR_H_

#include <string>
#include <map>
#include <stdint.h>
#include "ns3/uinteger.h"
#include "ns3/object.h"
#include "ns3/event-id.h"
#include "ns3/nstime.h"

namespace ns3 {

	class Sensor : public Object {
		public : static TypeId GetTypeId(void);
			Sensor();
			virtual ~Sensor();
	
			void DoStart(void);
			void DoDispose(void);

		private : EventId m_started;
		    void ReadData(void);
			EventId m_next;
			std :: string m_path;
			std :: map < uint64_t, std :: string > m_queue;
			void Init(void);
			uint32_t m_id;
	}
	;
}

#endif /* SYMPHONY_SENSOR_H_ */
