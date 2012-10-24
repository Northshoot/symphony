/*
 * gateway-client.cc
 *
 *  Created on: Aug 14, 2012
 *      Author: lauril
 */

#include "gateway-client.h"

#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/socket.h"
#include "ns3/uinteger.h"
#include "ns3/boolean.h"
#include "ns3/inet-socket-address.h"
#include "ns3/packet.h"
#include "ns3/trace-source-accessor.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("WSNGatewayClient");
NS_OBJECT_ENSURE_REGISTERED (WSNGatewayClient);

TypeId
WSNGatewayClient::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::WSNGatewayClient")
    .SetParent<Application> ()
    .AddConstructor<WSNGatewayClient> ()
    .AddAttribute ("Remote",
                   "The address of the machine we want to send packet to.",
                   Ipv4AddressValue (),
                   MakeIpv4AddressAccessor (&WSNGatewayClient::m_remote),
                   MakeIpv4AddressChecker ())
    .AddAttribute ("Port", "The number of the port on remote server.",
                   UintegerValue (56),
                   MakeUintegerAccessor (&WSNGatewayClient::m_size),
                   MakeUintegerChecker<uint32_t> (16));
  ;
  return tid;
}

WSNGatewayClient::WSNGatewayClient()
:   m_socket (0),
    m_port(12345)
  {
  }

WSNGatewayClient::~WSNGatewayClient()
  {
 }
void
WSNGatewayClient::DoDispose()
{
  NS_LOG_FUNCTION (this);
  m_socket = 0;
  Application::DoDispose ();
}
void
WSNGatewayClient::StartApplication(void)
{
  NS_LOG_FUNCTION (this);
  m_started = Simulator::Now ();
  
}

void
WSNGatewayClient::sendData(const uint8_t * data, int size){
//we create a connection and send data the size is the size of data
  NS_LOG_FUNCTION (size);
  //create tcp socket
  m_socket = Socket::CreateSocket (GetNode (), TypeId::LookupByName ("ns3::TcpSocketFactory"));
  NS_ASSERT (m_socket != 0);
  //set rx call back if we expect something back
  m_socket->SetRecvCallback (MakeCallback (&WSNGatewayClient::Receive, this));

  int status;
  InetSocketAddress m_src = InetSocketAddress (Ipv4Address::GetAny (), 0);
  status = m_socket->Bind (m_src);
  NS_ASSERT (status != -1);
  InetSocketAddress dst = InetSocketAddress (m_remote, m_port);
  status = m_socket->Connect (dst);
  NS_ASSERT (status != -1);
  m_socket->Send (data,size, 0);
  m_socket->Close ();
}

void
WSNGatewayClient::StopApplication (void)
{
  NS_LOG_FUNCTION (this);
  
}


void
WSNGatewayClient::Receive (Ptr<Socket> socket)
{
  //if needed a callback function must be created, added, data extracted and forwarded to the proper receiver
  NS_LOG_FUNCTION (this << socket);

}

uint32_t
WSNGatewayClient::GetApplicationId (void) const
{
  Ptr<Node> node = GetNode ();
  for (uint32_t i = 0; i < node->GetNApplications (); ++i)
    {
      if (node->GetApplication (i) == this)
        {
          return i;
        }
    }
  NS_ASSERT_MSG (false, "forgot to add application to node");
  return 0; // quiet compiler
}

}
