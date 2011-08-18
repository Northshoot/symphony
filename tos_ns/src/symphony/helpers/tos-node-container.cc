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
#include "tos-node-container.h"
#include "ns3/tos-node-list.h"
#include "ns3/names.h"

namespace ns3 {

TosNodeContainer::TosNodeContainer ()
{}

TosNodeContainer::TosNodeContainer (Ptr<TosNode> TosNode)
{
  m_TosNodes.push_back (TosNode);
}
TosNodeContainer::TosNodeContainer (std::string TosNodeName)
{
  Ptr<TosNode> tosnode = Names::Find<TosNode> (TosNodeName);
  m_TosNodes.push_back (tosnode);
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
  return m_TosNodes.begin ();
}
TosNodeContainer::Iterator
TosNodeContainer::End (void) const
{
  return m_TosNodes.end ();
}

uint32_t 
TosNodeContainer::GetN (void) const
{
  return m_TosNodes.size ();
}
Ptr<TosNode>
TosNodeContainer::Get (uint32_t i) const
{
  return m_TosNodes[i];
}
void 
TosNodeContainer::Create (uint32_t n)
{
  for (uint32_t i = 0; i < n; i++)
    {
      m_TosNodes.push_back (CreateObject<TosNode> ());
    }
}
void 
TosNodeContainer::Create (uint32_t n, uint32_t systemId)
{
  for (uint32_t i = 0; i < n; i++)
    {
      m_TosNodes.push_back (CreateObject<TosNode> (systemId));
    }
}
void 
TosNodeContainer::Add (TosNodeContainer other)
{
  for (Iterator i = other.Begin (); i != other.End (); i++)
    {
      m_TosNodes.push_back (*i);
    }
}
void 
TosNodeContainer::Add (Ptr<TosNode> tosnode)
{
  m_TosNodes.push_back (tosnode);
}
void 
TosNodeContainer::Add (std::string TosNodeName)
{
  Ptr<TosNode> tosnode = Names::Find<TosNode> (TosNodeName);
  m_TosNodes.push_back (tosnode);
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