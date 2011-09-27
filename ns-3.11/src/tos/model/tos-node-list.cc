/* -*- Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: 
 *  Mathieu Lacage <mathieu.lacage@sophia.inria.fr>,
 */

#include "ns3/simulator.h"
#include "ns3/object-vector.h"
#include "ns3/config.h"
#include "ns3/log.h"
#include "ns3/assert.h"
#include "tos-node-list.h"
#include "NodeTest.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TosNodeList");

/**
 * \brief private implementation detail of the NodeList API.
 */
class NodeListPriv : public Object
{
public:
  static TypeId GetTypeId (void);
  NodeListPriv ();
  ~NodeListPriv ();

  uint32_t Add (Ptr<NodeTest> node);
  TosNodeList::Iterator Begin (void) const;
  TosNodeList::Iterator End (void) const;
  Ptr<NodeTest> GetNode (uint32_t n);
  uint32_t GetNNodes (void);

  static Ptr<NodeListPriv> Get (void);

private:
  virtual void DoDispose (void);
  static Ptr<NodeListPriv> *DoGet (void);
  static void Delete (void);
  std::vector<Ptr<NodeTest> > m_nodes;
};

NS_OBJECT_ENSURE_REGISTERED (NodeListPriv);

TypeId 
NodeListPriv::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::NodeListPriv")
    .SetParent<Object> ()
    .AddAttribute ("NodeList", "The list of all nodes created during the simulation.",
                   ObjectVectorValue (),
                   MakeObjectVectorAccessor (&NodeListPriv::m_nodes),
                   MakeObjectVectorChecker<NodeTest> ())
  ;
  return tid;
}

Ptr<NodeListPriv> 
NodeListPriv::Get (void)
{
  return *DoGet ();
}
Ptr<NodeListPriv> *
NodeListPriv::DoGet (void)
{
  static Ptr<NodeListPriv> ptr = 0;
  if (ptr == 0)
    {
      ptr = CreateObject<NodeListPriv> ();
      Config::RegisterRootNamespaceObject (ptr);
      Simulator::ScheduleDestroy (&NodeListPriv::Delete);
    }
  return &ptr;
}
void 
NodeListPriv::Delete (void)
{
  NS_LOG_FUNCTION_NOARGS ();
  Config::UnregisterRootNamespaceObject (Get ());
  (*DoGet ()) = 0;
}


NodeListPriv::NodeListPriv ()
{
  NS_LOG_FUNCTION_NOARGS ();
}
NodeListPriv::~NodeListPriv ()
{
}
void
NodeListPriv::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();
  for (std::vector<Ptr<NodeTest> >::iterator i = m_nodes.begin ();
       i != m_nodes.end (); i++)
    {
      Ptr<NodeTest> node = *i;
      node->Dispose ();
      *i = 0;
    }
  m_nodes.erase (m_nodes.begin (), m_nodes.end ());
  Object::DoDispose ();
}


uint32_t
NodeListPriv::Add (Ptr<NodeTest> node)
{
  uint32_t index = m_nodes.size ();
  m_nodes.push_back (node);
  Simulator::ScheduleWithContext (index, TimeStep (0), &NodeTest::Start, node);
  return index;

}
TosNodeList::Iterator
NodeListPriv::Begin (void) const
{
  return m_nodes.begin ();
}
TosNodeList::Iterator
NodeListPriv::End (void) const
{
  return m_nodes.end ();
}
uint32_t 
NodeListPriv::GetNNodes (void)
{
  return m_nodes.size ();
}

Ptr<NodeTest>
NodeListPriv::GetNode (uint32_t n)
{
  NS_ASSERT_MSG (n < m_nodes.size (), "NodeTest index " << n <<
                 " is out of range (only have " << m_nodes.size () << " nodes).");
  return m_nodes[n];
}

}

/**
 * The implementation of the public static-based API
 * which calls into the private implementation through
 * the simulation singleton.
 */
namespace ns3 {

uint32_t
TosNodeList::Add (Ptr<NodeTest> node)
{
  return NodeListPriv::Get ()->Add (node);
}
TosNodeList::Iterator
TosNodeList::Begin (void)
{
  return NodeListPriv::Get ()->Begin ();
}
TosNodeList::Iterator
TosNodeList::End (void)
{
  return NodeListPriv::Get ()->End ();
}
Ptr<NodeTest>
TosNodeList::GetNode (uint32_t n)
{
  return NodeListPriv::Get ()->GetNode (n);
}
uint32_t
TosNodeList::GetNNodes (void)
{
  return NodeListPriv::Get ()->GetNNodes ();
}

} //namespace ns3
