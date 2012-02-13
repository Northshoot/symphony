/*
 * tos-helper.h
 *
 *  Created on: Feb 13, 2012
 *      Author: lauril
 */

#ifndef TOS_HELPER_H_
#define TOS_HELPER_H_

#include <string>
#include "ns3/attribute.h"
#include "ns3/object-factory.h"
#include "ns3/tos-node-container.h"
#include "ns3/yans-wsn-helper.h"
#include "ns3/net-device-container.h"
#include "ns3/wifi-phy-standard.h"
#include "ns3/trace-helper.h"

namespace ns3 {

class WifiPhy;
class TosMacLow;
class TosNode;
class WsnTosDevice;

class TosHelper {
public:
	TosHelper();
	virtual ~TosHelper();
	static TosHelper Default (void);


  /**
   * \param phy the PHY helper to create PHY objects
   * \param mac the MAC helper to create MAC objects
   * \param c the set of nodes on which a wifi device must be created
   * \returns a device container which contains all the devices created by this method.
   */
  NetDeviceContainer Install (const YansWsnPhyHelper &phy,
                               TosNodeContainer c) const;


  /**
   * \param standard the phy standard to configure during installation
   *
   * By default, all objects are configured for 802.11a
   */
  void SetStandard (enum WifiPhyStandard standard);

  /**
   * Helper to enable all WifiNetDevice log components with one statement
   */
  static void EnableLogComponents (void);



private:

  enum WifiPhyStandard m_standard;


};

} /* namespace ns3 */
#endif /* TOS_HELPER_H_ */
