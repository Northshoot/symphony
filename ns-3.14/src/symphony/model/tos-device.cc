/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * tos-device.cc
 *
 *  Created on: June 2 , 2013
 *      Author: Jose Angel Fernandez
 */


#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/type-id.h"
#include "ns3/uinteger.h"

#include "tos-device.h"

NS_LOG_COMPONENT_DEFINE("TosDevice");

namespace ns3
{

  NS_OBJECT_ENSURE_REGISTERED(TosDevice);

  TypeId
  TosDevice::GetTypeId(void)
  {
    static TypeId tid =
    	TypeId("ns3::TosDevice")
    	.SetParent<Object>()
    	.AddConstructor<TosDevice>()
    	//TODO Change RsId for Id because is not RawSensor Now
        .AddAttribute("RsId", "The id (unique integer) of this tos-device.",
        		TypeId::ATTR_SET,
        		UintegerValue(0), MakeUintegerAccessor(&TosDevice::m_id),
        		MakeUintegerChecker<uint32_t>())
    	.AddAttribute("DeviceStartDone","Callback for device start done event.",
    			CallbackValue(),
    			MakeCallbackAccessor(&TosDevice::m_StartDone),
    			MakeCallbackChecker ())
    	.AddAttribute("DeviceStopDone","Callback for device stop done event.",
                CallbackValue(),
                MakeCallbackAccessor(&TosDevice::m_StopDone),
                MakeCallbackChecker ())
         .AddAttribute("InterruptDeviceWithData","Callback for device interrupt with data event.",
                CallbackValue(),
                MakeCallbackAccessor(&TosDevice::m_InterruptDeviceWithData),
                MakeCallbackChecker ());

    return tid;
  }

  void
  TosDevice::DoStart(void)
  {
	  NS_LOG_FUNCTION (this);

	  Object::DoStart();
  }

  void
  TosDevice::DoDispose(void)
  {
	  NS_LOG_FUNCTION (this);

	  Object::DoDispose();
  }

  int
  TosDevice::SendRawData(uint16_t size, void* buffer)
  {
	  NS_ASSERT_MSG(!m_InterruptDeviceWithData.IsNull(),"Callback for device interrupt with data is not set");

	  return m_InterruptDeviceWithData(0, size, buffer);
  }

  TosDevice::TosDevice()
  {
	  NS_LOG_FUNCTION (this);
  }

  TosDevice::~TosDevice()
  {
	  NS_LOG_FUNCTION (this);
  }


}//namespace
