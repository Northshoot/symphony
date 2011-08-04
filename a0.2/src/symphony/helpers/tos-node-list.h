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
#ifndef TosNode_LIST_H
#define TosNode_LIST_H

#include <vector>
#include "ns3/ptr.h"

namespace ns3 {

class TosNode;
class CallbackBase;


/**
 * \ingroup TosNode
 *
 * \brief the list of simulation TosNodes.
 *
 * Every TosNode created is automatically added to this list.
 */
class TosNodeList
{
public:
  typedef std::vector< Ptr<TosNode> >::const_iterator Iterator;

  /**
   * \param TosNode TosNode to add
   * \returns index of TosNode in list.
   *
   * This method is called automatically from TosNode::TosNode so
   * the user has little reason to call it himself.
   */
  static uint32_t Add (Ptr<TosNode> TosNode);
  /**
   * \returns a C++ iterator located at the beginning of this
   *          list.
   */
  static Iterator Begin (void);
  /**
   * \returns a C++ iterator located at the end of this
   *          list.
   */
  static Iterator End (void);
  /**
   * \param n index of requested TosNode.
   * \returns the TosNode associated to index n.
   */
  static Ptr<TosNode> GetTosNode (uint32_t n);
  /**
   * \returns the number of TosNodes currently in the list.
   */
  static uint32_t GetNTosNodes (void);
};

}//namespace ns3


#endif /* TosNode_LIST_H */
