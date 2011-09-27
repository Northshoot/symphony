/*
 * NodeTest.cpp
 *
 *  Created on: Sep 26, 2011
 *      Author: lauril
 */

#include "NodeTest.h"
#include "ns3/node.h"
#include "ns3/net-device.h"
#include "ns3/application.h"
#include "ns3/packet.h"
#include "ns3/simulator.h"
#include "ns3/object-vector.h"
#include "ns3/uinteger.h"
#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/global-value.h"
#include "ns3/boolean.h"
#include "ns3/simulator.h"
#include "tos-node-list.h"

NS_LOG_COMPONENT_DEFINE ("NodeTest");

namespace ns3 {


GlobalValue g_checksumEnabled  = GlobalValue ("ChecksumEnabled",
                                              "A global switch to enable all checksums for all protocols",
                                              BooleanValue (false),
                                              MakeBooleanChecker ());

TypeId
NodeTest::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::NodeTest")
    .SetParent<Node> ()
    .AddConstructor<NodeTest> ()

  ;
  return tid;
}

NodeTest::NodeTest()
{
  Node ();
}

NodeTest::NodeTest(uint32_t nodesid)
{
  Node(nodesid);

}

//void
//NodeTest::Construct (void)
//{
//
//  m_id = TosNodeList::Add (this);
//}

NodeTest::~NodeTest ()
{
}


}
