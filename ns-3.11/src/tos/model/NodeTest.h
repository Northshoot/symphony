/*
 * NodeTest.h
 *
 *  Created on: Sep 26, 2011
 *      Author: lauril
 */

#ifndef NODETEST_H_
#define NODETEST_H_

#include <vector>

#include "ns3/object.h"
#include "ns3/callback.h"
#include "ns3/ptr.h"
#include "ns3/net-device.h"
#include "ns3/node.h"

namespace ns3 {

class Application;
class Packet;
class Address;

class NodeTest : public Node
{
public:
  static TypeId GetTypeId (void);

  /**
   * Must be invoked by subclasses only.
   */
  NodeTest();
  /**
   * \param systemId a unique integer used for parallel simulations.
   *
   * Must be invoked by subclasses only.
   */
  NodeTest(uint32_t systemId_t);
  void Construct(void);

  virtual ~NodeTest();

private:
  uint32_t    m_id;         // Node id for this node
  uint32_t    m_sid;        // System id for this node


};
}
#endif /* NODETEST_H_ */
