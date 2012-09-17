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
                   "The address of the machine we want to ping.",
                   Ipv4AddressValue (),
                   MakeIpv4AddressAccessor (&WSNGatewayClient::m_remote),
                   MakeIpv4AddressChecker ())
    .AddAttribute ("Verbose",
                   "Produce usual output.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&WSNGatewayClient::m_verbose),
                   MakeBooleanChecker ())
    .AddAttribute ("Size", "The number of data bytes to be sent, real packet will be 8 (ICMP) + 20 (IP) bytes longer.",
                   UintegerValue (56),
                   MakeUintegerAccessor (&WSNGatewayClient::m_size),
                   MakeUintegerChecker<uint32_t> (16));
  ;
  return tid;
}

WSNGatewayClient::WSNGatewayClient()
:   m_size (56),
    m_socket (0),
    m_seq (0),
    m_verbose (false),
    m_recv (0),
    m_port(21567)
  {
  }

WSNGatewayClient::~WSNGatewayClient()
  {
 }
void
WSNGatewayClient::DoDispose()
{
  NS_LOG_FUNCTION (this);
  m_socket->Close ();
  m_socket = 0;
  Application::DoDispose ();
}
void
WSNGatewayClient::StartApplication(void)
{
  NS_LOG_FUNCTION (this);
  m_started = Simulator::Now ();
  m_socket = Socket::CreateSocket (GetNode (), TypeId::LookupByName ("ns3::TcpSocketFactory"));
  NS_ASSERT (m_socket != 0);
  //m_socket->SetAttribute ("Protocol", UintegerValue (6));
  m_socket->SetRecvCallback (MakeCallback (&WSNGatewayClient::Receive, this));
  int status;
  InetSocketAddress m_src =InetSocketAddress (Ipv4Address::GetAny (), 0);
  status = m_socket->Bind (m_src);
  NS_ASSERT (status != -1);
  InetSocketAddress dst = InetSocketAddress (m_remote, m_port);
  status = m_socket->Connect (dst);
  NS_ASSERT (status != -1);

}
void
WSNGatewayClient::connect(){

}

void
WSNGatewayClient::sendData(const uint8_t * data, int size){
  NS_LOG_FUNCTION (m_seq);
  Ptr<Packet> p = Create<Packet> ();

  m_seq++;

  //
  // We must write quantities out in some form of network order.  Since there
  // isn't an htonl to work with we just follow the convention in pcap traces
  // (where any difference would show up anyway) and borrow that code.  Don't
  // be too surprised when you see that this is a little endian convention.
  //


  uint32_t tmp = GetNode ()->GetId ();
  Write32 (&data[0 * sizeof(uint32_t)], tmp);

  tmp = GetApplicationId ();
  Write32 (&data[1 * sizeof(uint32_t)], tmp);

  Ptr<Packet> dataPacket = Create<Packet> ((const uint8_t *) data, m_size);

 // p->AddHeader (tcpheader);
//  Icmpv4Header header;
//  header.SetType (TcpHeader::);
//  header.SetCode (0);
//  if (Node::ChecksumEnabled ())
//    {
//      header.EnableChecksum ();
//    }
//  p->AddHeader (tcpheader);
  m_sent.insert (std::make_pair (m_seq - 1, Simulator::Now ()));
  m_socket->Send (dataPacket, 0);
//  m_next = Simulator::Schedule (m_interval, &V4Ping::Send, this);
  //delete[] data;
}

void
WSNGatewayClient::StopApplication (void)
{
  NS_LOG_FUNCTION (this);
  m_next.Cancel ();
  m_socket->Close ();

}

void
WSNGatewayClient::disconnect() {
  NS_LOG_FUNCTION (this);
  m_next.Cancel ();
  m_socket->Close ();
}
void
WSNGatewayClient::Receive (Ptr<Socket> socket)
{
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
// Writes data to buffer in little-endian format; least significant byte
// of data is at lowest buffer address
void
WSNGatewayClient::Write32 (uint8_t *buffer, const uint32_t data)
{
  buffer[0] = (data >> 0) & 0xff;
  buffer[1] = (data >> 8) & 0xff;
  buffer[2] = (data >> 16) & 0xff;
  buffer[3] = (data >> 24) & 0xff;
}

// Writes data from a little-endian formatted buffer to data
void
WSNGatewayClient::Read32 (const uint8_t *buffer, uint32_t &data)
{
  data = (buffer[3] << 24) + (buffer[2] << 16) + (buffer[1] << 8) + buffer[0];
}
}
