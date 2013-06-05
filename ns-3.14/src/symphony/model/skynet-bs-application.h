/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#ifndef SkynetBaseStation_H
#define SkynetBaseStation_H

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
class SkynetBaseStation : public Application
{
public:
	static TypeId GetTypeId (void);

	SkynetBaseStation ();
	virtual ~SkynetBaseStation ();

private:

  // inherited from Application base class.
  virtual void StartApplication (void);
  virtual void StopApplication (void);
  virtual void DoDispose (void);
  uint32_t GetApplicationId (void) const;

  /**
   * Sends the initialization vector SRi and the randomization
   * vector P to each sensor node inside the container.
   *
   * \param container Collection of sensors nodes to initialize
   */
  void DistributeSensorsInitVectors(TosNodeContainer container);

  /**
   * Sends the initialization vector ARi and the randomization
   * vector P to each sensor actuator inside the container.
   *
   * \param container Collection of actuators nodes to initialize
   */
  void DistributeActuatorsInitVectors(TosNodeContainer container);
};

} // namespace ns3

#endif /* SkynetBaseStation_H */
