/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 */
#ifndef SkynetNs3ProxyServer_H
#define SkynetNs3ProxyServer_H

#include "ns3/application.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/average.h"
#include "ns3/simulator.h"
#include <map>

namespace ns3 {

class Socket;

/**
 * \brief an application which sends one ICMP ECHO request, waits for a REPLYs
 *        and reports the calculated RTT.
 *
 * Note: The RTT calculated is reported through a trace source.
 */
class SkynetNs3ProxyServer : public Application
{
public:
  static TypeId GetTypeId (void);

  /**
   * create a pinger applications
   */
  SkynetNs3ProxyServer ();
  virtual ~SkynetNs3ProxyServer ();

private:

  // inherited from Application base class.
  virtual void StartApplication (void);
  virtual void StopApplication (void);
  virtual void DoDispose (void);
  uint32_t GetApplicationId (void) const;
 
  void HandleRead (Ptr<Socket>);
  void HandleAccept (Ptr<Socket>, const Address& from);
  void HandlePeerClose (Ptr<Socket>);
  void HandlePeerError (Ptr<Socket>);
  void HandleSend (Ptr<Socket>, uint32_t);

  Ptr<Socket> m_socket;
  int m_portNumber;
};

} // namespace ns3

#endif /* SkynetNs3ProxyServer_H */
