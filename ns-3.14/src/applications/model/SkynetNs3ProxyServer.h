/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

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
 *
 */
class SkynetNs3ProxyServer : public Application
{
public:
	static TypeId GetTypeId (void);

	/**
	 * Create a new IO Server to communicate between the outside and NS3
	 * through a TCP Socket.
	 */
	SkynetNs3ProxyServer ();
	virtual ~SkynetNs3ProxyServer ();

	void SendData(int32_t);

private:

  // inherited from Application base class.
  virtual void StartApplication (void);
  virtual void StopApplication (void);
  virtual void DoDispose (void);
  uint32_t GetApplicationId (void) const;
 
  // management of the callbacks
  void HandleRead (Ptr<Socket>);
  void HandleAccept (Ptr<Socket>, const Address& from);
  void HandlePeerClose (Ptr<Socket>);
  void HandlePeerError (Ptr<Socket>);
  void HandleSend (Ptr<Socket>, uint32_t);

  Ptr<Socket> m_socket;

  // Information of remote end point
  int m_remotePortNumber;
  std::string m_remoteIp;

  // Information of local end point
  int m_localPortNumber;
  std::string m_localIp;

};

} // namespace ns3

#endif /* SkynetNs3ProxyServer_H */
