/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
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
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include <string>
#include <vector>

#include "tos-node-container.h"
#include "ns3/tos-node-list.h"
#include "ns3/names.h"
#include "ns3/nstime.h"


namespace ns3 {

TosNodeContainer::TosNodeContainer ()
{
}


TosNodeContainer::TosNodeContainer (Ptr<TosNode> TosNode)
{
  m_TosNode.push_back (TosNode);
}

TosNodeContainer::TosNodeContainer (const TosNodeContainer &a, const TosNodeContainer &b)
{
  Add (a);
  Add (b);
}
TosNodeContainer::TosNodeContainer (const TosNodeContainer &a, const TosNodeContainer &b,
                              const TosNodeContainer &c)
{
  Add (a);
  Add (b);
  Add (c);
}
TosNodeContainer::TosNodeContainer (const TosNodeContainer &a, const TosNodeContainer &b,
                              const TosNodeContainer &c, const TosNodeContainer &d)
{
  Add (a);
  Add (b);
  Add (c);
  Add (d);
}

TosNodeContainer::TosNodeContainer (const TosNodeContainer &a, const TosNodeContainer &b,
                              const TosNodeContainer &c, const TosNodeContainer &d,
                              const TosNodeContainer &e)
{
  Add (a);
  Add (b);
  Add (c);
  Add (d);
  Add (e);
}

TosNodeContainer::Iterator
TosNodeContainer::Begin (void) const
{
  return m_TosNode.begin ();
}
TosNodeContainer::Iterator
TosNodeContainer::End (void) const
{
  return m_TosNode.end ();
}

uint32_t 
TosNodeContainer::GetN (void) const
{
  return m_TosNode.size ();
}
Ptr<TosNode>
TosNodeContainer::Get (uint32_t i) const
{
  return m_TosNode[i];
}
void 
TosNodeContainer::Create (uint32_t n)
{
  for (uint32_t i = 0; i < n; i++)
    {
      m_TosNode.push_back (CreateObject<TosNode> (i ,MilliSeconds(0),"./libtos.so"));
    }
}
void 
TosNodeContainer::Create (uint32_t n, uint32_t systemId)
{
  for (uint32_t i = 0; i < n; i++)
    {
      m_TosNode.push_back (CreateObject<TosNode> (systemId));
    }
}
void 
TosNodeContainer::Add (TosNodeContainer other)
{
  for (Iterator i = other.Begin (); i != other.End (); i++)
    {
      m_TosNode.push_back (*i);
    }
}
void 
TosNodeContainer::Add (Ptr<TosNode> TosNode)
{
  m_TosNode.push_back (TosNode);
}
void 
TosNodeContainer::Add (std::string NodeTestName)
{
  Ptr<TosNode> node = Names::Find<TosNode> (NodeTestName);
  m_TosNode.push_back (node);
}

TosNodeContainer
TosNodeContainer::GetGlobal (void)
{
  TosNodeContainer c;
  for (TosNodeList::Iterator i = TosNodeList::Begin (); i != TosNodeList::End (); ++i)
    {
      c.Add (*i);
    }
  return c;
}

} // namespace ns3
