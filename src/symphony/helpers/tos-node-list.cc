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
#include "ns3/TosNode.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TosNodeList");

/**
 * \brief private implementation detail of the TosNodeList API.
 */
class TosNodeListPriv : public Object
{
public:
  static TypeId GetTypeId (void);
  TosNodeListPriv ();
  ~TosNodeListPriv ();

  uint32_t Add (Ptr<TosNode> TosNode);
  TosNodeList::Iterator Begin (void) const;
  TosNodeList::Iterator End (void) const;
  Ptr<TosNode> GetTosNode (uint32_t n);
  uint32_t GetNTosNodes (void);

  static Ptr<TosNodeListPriv> Get (void);
  
private:
  virtual void DoDispose (void);
  static Ptr<TosNodeListPriv> *DoGet (void);
  static void Delete (void);
  std::vector<Ptr<TosNode> > m_TosNodes;
};

NS_OBJECT_ENSURE_REGISTERED (TosNodeListPriv);

TypeId 
TosNodeListPriv::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TosNodeListPriv")
    .SetParent<Object> ()
    .AddAttribute ("TosNodeList", "The list of all TosNodes created during the simulation.",
                   ObjectVectorValue (),
                   MakeObjectVectorAccessor (&TosNodeListPriv::m_TosNodes),
                   MakeObjectVectorChecker<TosNode> ())
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
{}
void
TosNodeListPriv::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();
  for (std::vector<Ptr<TosNode> >::iterator i = m_TosNodes.begin ();
       i != m_TosNodes.end (); i++)
    {
      Ptr<TosNode> TosNode = *i;
      TosNode->Dispose ();
      *i = 0;
    }
  m_TosNodes.erase (m_TosNodes.begin (), m_TosNodes.end ());
  Object::DoDispose ();
}


uint32_t
TosNodeListPriv::Add (Ptr<TosNode> TosNode)
{
  uint32_t index = m_TosNodes.size ();
  m_TosNodes.push_back (TosNode);
  Simulator::ScheduleWithContext (index, TimeStep (0), &TosNode::Start, TosNode);
  return index;
  
}
TosNodeList::Iterator
TosNodeListPriv::Begin (void) const
{
  return m_TosNodes.begin ();
}
TosNodeList::Iterator
TosNodeListPriv::End (void) const
{
  return m_TosNodes.end ();
}
uint32_t 
TosNodeListPriv::GetNTosNodes (void)
{
  return m_TosNodes.size ();
}

Ptr<TosNode>
TosNodeListPriv::GetTosNode (uint32_t n)
{
  NS_ASSERT_MSG (n < m_TosNodes.size (), "TosNode index " << n <<
                 " is out of range (only have " << m_TosNodes.size () << " TosNodes).");
  return m_TosNodes[n];
}

}

/**
 * The implementation of the public static-based API
 * which calls into the private implementation through
 * the simulation singleton.
 */
namespace ns3 {

uint32_t
TosNodeList::Add (Ptr<TosNode> TosNode)
{
  return TosNodeListPriv::Get ()->Add (TosNode);
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
Ptr<TosNode>
TosNodeList::GetTosNode (uint32_t n)
{
  return TosNodeListPriv::Get ()->GetTosNode (n);
}
uint32_t
TosNodeList::GetNTosNodes (void)
{
  return TosNodeListPriv::Get ()->GetNTosNodes ();
}

}//namespace ns3
