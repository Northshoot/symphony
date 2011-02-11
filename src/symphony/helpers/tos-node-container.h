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
#ifndef TOS_TosNode_CONTAINER_H
#define TOS_TosNode_CONTAINER_H

#include <stdint.h>
#include <vector>
#include "ns3/TosNode.h"
#include "ns3/node-container.h"

namespace ns3 {

/**
 * \brief keep track of a set of TosNode pointers.
 *
 * Typically ns-3 helpers operate on more than one TosNode at a time.  For example
 * a device helper may want to install devices on a large number of similar
 * TosNodes.  The helper Install methods usually take a TosNodeContainer as a
 * parameter.  TosNodeContainers hold the multiple Ptr<TosNode> which are used
 * to refer to the TosNodes.
 */
class TosNodeContainer :public NodeContainer
{
public:
  typedef std::vector<Ptr<TosNode> >::const_iterator Iterator;

  /**
   * Create an empty TosNodeContainer.
   */
  TosNodeContainer ();

  /**
   * Create a TosNodeContainer with exactly one TosNode which has been previously
   * instantiated.  The single TosNode is specified by a smart pointer.
   *
   * \param TosNode The Ptr<TosNode> to add to the container.
   */
  TosNodeContainer (Ptr<TosNode> TosNode);

  /**
   * Create a TosNodeContainer with exactly one TosNode which has been previously
   * instantiated and assigned a name using the Object Name Service.  This 
   * TosNode is then specified by its assigned name.
   *
   * \param TosNodeName The name of the TosNode Object to add to the container.
   */
  TosNodeContainer (std::string TosNodeName);

  /**
   * Create a TosNode container which is a concatenation of two input
   * TosNodeContainers.
   *
   * \param a The first TosNodeContainer
   * \param b The second TosNodeContainer
   *
   * \note A frequently seen idiom that uses these constructors involves the
   * implicit conversion by constructor of Ptr<TosNode>.  When used, two
   * Ptr<TosNode> will be passed to this constructor instead of TosNodeContainer&.
   * C++ will notice the implicit conversion path that goes through the 
   * TosNodeContainer (Ptr<TosNode> TosNode) constructor above.  Using this conversion
   * one may provide optionally provide arguments of Ptr<TosNode> to these
   * constructors.
   */
  TosNodeContainer (const TosNodeContainer &a, const TosNodeContainer &b);

  /**
   * Create a TosNode container which is a concatenation of three input
   * TosNodeContainers.
   *
   * \param a The first TosNodeContainer
   * \param b The second TosNodeContainer
   * \param c The third TosNodeContainer
   *
   * \note A frequently seen idiom that uses these constructors involves the
   * implicit conversion by constructor of Ptr<TosNode>.  When used, two
   * Ptr<TosNode> will be passed to this constructor instead of TosNodeContainer&.
   * C++ will notice the implicit conversion path that goes through the 
   * TosNodeContainer (Ptr<TosNode> TosNode) constructor above.  Using this conversion
   * one may provide optionally provide arguments of Ptr<TosNode> to these
   * constructors.
   */
  TosNodeContainer (const TosNodeContainer &a, const TosNodeContainer &b, const TosNodeContainer &c);

  /**
   * Create a TosNode container which is a concatenation of four input
   * TosNodeContainers.
   *
   * \param a The first TosNodeContainer
   * \param b The second TosNodeContainer
   * \param c The third TosNodeContainer
   * \param d The fourth TosNodeContainer
   *
   * \note A frequently seen idiom that uses these constructors involves the
   * implicit conversion by constructor of Ptr<TosNode>.  When used, two
   * Ptr<TosNode> will be passed to this constructor instead of TosNodeContainer&.
   * C++ will notice the implicit conversion path that goes through the 
   * TosNodeContainer (Ptr<TosNode> TosNode) constructor above.  Using this conversion
   * one may provide optionally provide arguments of Ptr<TosNode> to these
   * constructors.
   */
  TosNodeContainer (const TosNodeContainer &a, const TosNodeContainer &b, const TosNodeContainer &c, const TosNodeContainer &d);

  /**
   * Create a TosNode container which is a concatenation of five input
   * TosNodeContainers.
   *
   * \param a The first TosNodeContainer
   * \param b The second TosNodeContainer
   * \param c The third TosNodeContainer
   * \param d The fourth TosNodeContainer
   * \param e The fifth TosNodeContainer
   *
   * \note A frequently seen idiom that uses these constructors involves the
   * implicit conversion by constructor of Ptr<TosNode>.  When used, two
   * Ptr<TosNode> will be passed to this constructor instead of TosNodeContainer&.
   * C++ will notice the implicit conversion path that goes through the 
   * TosNodeContainer (Ptr<TosNode> TosNode) constructor above.  Using this conversion
   * one may provide optionally provide arguments of Ptr<TosNode> to these
   * constructors.
   */
  TosNodeContainer (const TosNodeContainer &a, const TosNodeContainer &b, const TosNodeContainer &c, const TosNodeContainer &d,
                 const TosNodeContainer &e);

  /**
   * \brief Get an iterator which refers to the first TosNode in the
   * container.
   *
   * TosNodes can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the iterator method and is typically used in a 
   * for-loop to run through the TosNodes
   *
   * \code
   *   TosNodeContainer::Iterator i;
   *   for (i = container.Begin (); i != container.End (); ++i)
   *     {
   *       (*i)->method ();  // some TosNode method
   *     }
   * \endcode
   *
   * \returns an iterator which refers to the first TosNode in the container.
   */
  Iterator Begin (void) const;

  /**
   * \brief Get an iterator which indicates past-the-last TosNode in the
   * container.
   *
   * TosNodes can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the iterator method and is typically used in a 
   * for-loop to run through the TosNodes
   *
   * \code
   *   TosNodeContainer::Iterator i;
   *   for (i = container.Begin (); i != container.End (); ++i)
   *     {
   *       (*i)->method ();  // some TosNode method
   *     }
   * \endcode
   *
   * \returns an iterator which indicates an ending condition for a loop.
   */
  Iterator End (void) const;

  /**
   * \brief Get the number of Ptr<TosNode> stored in this container.
   *
   * TosNodes can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the direct method and is typically used to
   * define an ending condition in a for-loop that runs through the stored
   * TosNodes
   *
   * \code
   *   uint32_t nTosNodes = container.GetN ();
   *   for (uint32_t i = 0 i < nTosNodes; ++i)
   *     {
   *       Ptr<TosNode> p = container.Get (i)
   *       i->method ();  // some TosNode method
   *     }
   * \endcode
   *
   * \returns the number of Ptr<TosNode> stored in this container.
   */
  uint32_t GetN (void) const;

  /**
   * \brief Get the Ptr<TosNode> stored in this container at a given
   * index.
   *
   * TosNodes can be retrieved from the container in two ways.  First,
   * directly by an index into the container, and second, using an iterator.
   * This method is used in the direct method and is used to retrieve the
   * indexed Ptr<Appliation>.
   *
   * \code
   *   uint32_t nTosNodes = container.GetN ();
   *   for (uint32_t i = 0 i < nTosNodes; ++i)
   *     {
   *       Ptr<TosNode> p = container.Get (i)
   *       i->method ();  // some TosNode method
   *     }
   * \endcode
   *
   * \param i the index of the requested TosNode pointer.
   * \returns the requested TosNode pointer.
   */
  Ptr<TosNode> Get (uint32_t i) const;

  /**
   * \brief Create n TosNodes and append pointers to them to the end of this
   * TosNodeContainer.
   *
   * TosNodes are at the heart of any ns-3 simulation.  One of the first tasks that
   * any simulation needs to do is to create a number of TosNodes.  This method
   * automates that task.
   *
   * \param n The number of TosNodes to create
   */
  void Create (uint32_t n);

  /**
   * \brief Create n TosNodes with specified systemId for distributed simulations
   * and append pointers to them to the end of this TosNodeContainer.
   *
   * TosNodes are at the heart of any ns-3 simulation.  One of the first tasks that
   * any simulation needs to do is to create a number of TosNodes.  This method
   * automates that task, and adds the ability to specify systemId for 
   * distributed simulations.
   *
   * \param n The number of TosNodes to create
   * \param systemId The system id or rank associated with this TosNode
   */
  void Create (uint32_t n, uint32_t systemId);

  /**
   * \brief Append the contents of another TosNodeContainer to the end of
   * this container.
   *
   * \param other The TosNodeContainer to append.
   */
  void Add (TosNodeContainer other);

  /**
   * \brief Append a single Ptr<TosNode> to this container.
   *
   * \param TosNode The Ptr<TosNode> to append.
   */
  void Add (Ptr<TosNode> TosNode);

  /**
   * \brief Append to this container the single Ptr<TosNode> referred to
   * via its object name service registered name.
   *
   * \param TosNodeName The name of the TosNode Object to add to the container.
   */
  void Add (std::string TosNodeName);

  /**
   * \brief Create a TosNodeContainer that contains a list of _all_ TosNodes
   * created through TosNodeContainer::Create() and stored in the
   * ns3::TosNodeList.
   *
   * Whenever a TosNode is created, a Ptr<TosNode> is added to a global list of all
   * TosNodes in the system.  It is sometimes useful to be able to get to all
   * TosNodes in one place.  This method creates a TosNodeContainer that is
   * initialized to contain all of the simulation TosNodes,
   *
   * \returns a NoceContainer which contains a list of all TosNodes.
   */
  static TosNodeContainer GetGlobal (void);

 private:
  std::vector<Ptr<TosNode> > m_TosNodes;
};

} // namespace ns3

#endif /* TOS_TosNode_CONTAINER_H */
