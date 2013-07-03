/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#ifndef HvBaseStation_H
#define HvBaseStation_H

#include "ns3/application.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/average.h"
#include "ns3/simulator.h"
#include "ns3/tos-node-container.h"
#include <map>

namespace ns3 {

/**
 *
 */
class HvBaseStation : public Application
{
public:
	static TypeId GetTypeId (void);

	/**
	 *
	 */
	HvBaseStation ();
	virtual ~HvBaseStation ();

	void ReceiveHyperVector(uint16_t length, void* buffer);
	void InitializeNodes(TosNodeContainer container );

private:

  // inherited from Application base class.
  virtual void StartApplication (void);
  virtual void StopApplication (void);
  virtual void DoDispose (void);
  uint32_t GetApplicationId (void) const;

  /**
   * Sends data to the device as an interruption from
   * the simulator
   */
  Callback<int, uint8_t, uint16_t ,void * > m_InitializationInterrupt;
};

} // namespace ns3

#endif /* IOProxyServer_H */
