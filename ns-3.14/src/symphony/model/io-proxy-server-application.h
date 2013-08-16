/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#ifndef IOProxyServer_H
#define IOProxyServer_H

#include "ns3/application.h"
#include "ns3/traced-callback.h"
#include "ns3/nstime.h"
#include "ns3/average.h"
#include "ns3/simulator.h"
#include <map>

namespace ns3 {

class Socket;

/**
 * Ns-3 proxy that receives data from the I/O clients, processes it and
 * sends it to the correct node.
 */
class IOProxyServer : public Application
{
public:
	static TypeId GetTypeId (void);

	/**
	 * Creates a new IO Server to communicate between the outside and NS3
	 * through a TCP Socket.
	 */
	IOProxyServer ();
	virtual ~IOProxyServer ();

	/**
	 * Sends a string of data to the I/O client using the existing TCP
	 * socket connection
	 */
	void SendData(std::string);

private:

  // inherited from Application base class.
  virtual void StartApplication (void);
  virtual void StopApplication (void);
  virtual void DoDispose (void);
  uint32_t GetApplicationId (void) const;
 
  // management of the Socket callbacks
  void HandleRead (Ptr<Socket>);
  void HandleAccept (Ptr<Socket>, const Address& from);
  void HandlePeerClose (Ptr<Socket>);
  void HandlePeerError (Ptr<Socket>);
  void HandleSend (Ptr<Socket>, uint32_t);

  // TCP Socket to connect ns-3 to the I/O Clients
  Ptr<Socket> m_socket;

  // I/0 Client address
  Address from;

  // Information of remote end point
  int m_remotePortNumber;
  std::string m_remoteIp;

  // Information of local end point
  int m_localPortNumber;
  std::string m_localIp;

  // Number of pair of nodes the simulation is running ( x = x sensors & x actuators)
  int m_nodePairsNumber;
};

} // namespace ns3

#endif /* IOProxyServer_H */
