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

NS_LOG_COMPONENT_DEFINE ("TosNodeListPriv");

/**
 * \brief private implementation detail of the NodeList API.
 */
class TosNodeListPriv : public Object
{
public:
  static TypeId GetTypeId (void);
  TosNodeListPriv ();
  ~TosNodeListPriv ();

  uint32_t Add (Ptr<NodeTest> node);
  TosNodeList::Iterator Begin (void) const;
  TosNodeList::Iterator End (void) const;
  Ptr<NodeTest> GetNode (uint32_t n);
  uint32_t GetNNodes (void);

  static Ptr<TosNodeListPriv> Get (void);

private:
  virtual void DoDispose (void);
  static Ptr<TosNodeListPriv> *DoGet (void);
  static void Delete (void);
  std::vector<Ptr<NodeTest> > m_nodes;
};

NS_OBJECT_ENSURE_REGISTERED (TosNodeListPriv);

TypeId 
TosNodeListPriv::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TosNodeListPriv")
    .SetParent<Object> ()
    .AddAttribute ("NodeList", "The list of all nodes created during the simulation.",
                   ObjectVectorValue (),
                   MakeObjectVectorAccessor (&TosNodeListPriv::m_nodes),
                   MakeObjectVectorChecker<NodeTest> ())
  ;
  return tid;
}

Ptr<TosNodeListPriv>
TosNodeListPriv::Get (void)
{
  return *DoGet ();
}
Ptr<TosNodeListPriv> *
TosNodeListPriv::DoGet (void)
{
  static Ptr<TosNodeListPriv> ptr = 0;
  if (ptr == 0)
    {
      ptr = CreateObject<TosNodeListPriv> ();
      Config::RegisterRootNamespaceObject (ptr);
      Simulator::ScheduleDestroy (&TosNodeListPriv::Delete);
    }
  return &ptr;
}
void 
TosNodeListPriv::Delete (void)
{
  NS_LOG_FUNCTION_NOARGS ();
  Config::UnregisterRootNamespaceObject (Get ());
  (*DoGet ()) = 0;
}


TosNodeListPriv::TosNodeListPriv ()
{
  NS_LOG_FUNCTION_NOARGS ();
}
TosNodeListPriv::~TosNodeListPriv ()
{
}
void
TosNodeListPriv::DoDispose (void)
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
TosNodeListPriv::Add (Ptr<NodeTest> node)
{
  uint32_t index = m_nodes.size ();
  m_nodes.push_back (node);
  Simulator::ScheduleWithContext (index, TimeStep (0), &NodeTest::Start, node);
  return index;

}
TosNodeList::Iterator
TosNodeListPriv::Begin (void) const
{
  return m_nodes.begin ();
}
TosNodeList::Iterator
TosNodeListPriv::End (void) const
{
  return m_nodes.end ();
}
uint32_t 
TosNodeListPriv::GetNNodes (void)
{
  return m_nodes.size ();
}

Ptr<NodeTest>
TosNodeListPriv::GetNode (uint32_t n)
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
  return TosNodeListPriv::Get ()->Add (node);
}
TosNodeList::Iterator
TosNodeList::Begin (void)
{
  return TosNodeListPriv::Get ()->Begin ();
}
TosNodeList::Iterator
TosNodeList::End (void)
{
  return TosNodeListPriv::Get ()->End ();
}
Ptr<NodeTest>
TosNodeList::GetNode (uint32_t n)
{
  return TosNodeListPriv::Get ()->GetNode (n);
}
uint32_t
TosNodeList::GetNNodes (void)
{
  return TosNodeListPriv::Get ()->GetNNodes ();
}

} //namespace ns3
