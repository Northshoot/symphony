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
#include "ns3/wifi-phy-standard.h"
#include "ns3/trace-helper.h"

#include "ns3/tos-net-device.h"
#include "tos-node-container.h"
#include "tos-net-device-container.h"
#include "symphony-xml.h"
#include "ns3/tos-device.h"
#include "ns3/symphony-sensor-container.h"

namespace ns3
{

  class WifiPhy;
  class TosMacLow;
  class TosNode;
  class TosNetDevice;

  class TosPhyHelper
  {
  public:
    virtual
    ~TosPhyHelper();

    /**
     * \param node the node on which the PHY object will reside
     * \param device the device within which the PHY object will reside
     * \returns a new PHY object.
     *
     * Subclasses must implement this method to allow the ns3::WsnHelper class
     * to create PHY objects from ns3::WsnHelper::Install.
     */
    virtual Ptr<WifiPhy>
    Create(Ptr<TosNode> node, Ptr<TosNetDevice> device) const = 0;

  };

  class TosHelper
  {
  public:
    TosHelper();
    virtual
    ~TosHelper();
    static TosHelper
    Default(void);

    /**
     * \param phy the PHY helper to create PHY objects
     * \param mac the MAC helper to create MAC objects
     * \param c the set of nodes on which a wifi device must be created
     * \returns a device container which contains all the devices created by this method.
     */
    TosNetDeviceContainer
    Install(const TosPhyHelper &phyHelper, TosNodeContainer c) ;

    /**
     * \param standard the phy standard to configure during installation
     *
     * By default, all objects are configured for 802.11a
     */
    void
    SetStandard(enum WifiPhyStandard standard);

    /**
     * Helper to enable all WifiNetDevice log components with one statement
     */
    static void
    EnableLogComponents(void);

    static void
    EnableLogComponentsAll(LogLevel level);

    void SetNodeModel(std::string file);
    SymphonySensorContainer
    InstallSensors(uint32_t i , TosNodeContainer c, std::string path) ;

    void
    Init(TosNodeContainer c) const;

  private:
    void Inited(void);
    std::vector<std::string> m_tosExternals;
    Ptr<HardwareModel> m_radioModel;
    std::string m_xmlFile;
    SymphonyXML sym;
    enum WifiPhyStandard m_standard;
    bool m_inited;

  };

} /* namespace ns3 */
#endif /* TOS_HELPER_H_ */
