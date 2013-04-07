/*
 * Create a NS-3 Application that opens a TCP Socket and 
 * waits for incoming connections
 *
 * @author Jose Angel Fernandez
 */
 
#include "SkynetNs3ProxyServer.h"
#include "ns3/icmpv4.h"
#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/ipv4-address.h"
#include "ns3/socket.h"
#include "ns3/integer.h"
#include "ns3/boolean.h"
#include "ns3/inet-socket-address.h"
#include "ns3/packet.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/config.h"
#include "ns3/skynet-sensor.h"
#include "ns3/names.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SkynetNs3ProxyServer");
NS_OBJECT_ENSURE_REGISTERED (SkynetNs3ProxyServer);


SkynetNs3ProxyServer::SkynetNs3ProxyServer ()
{
	m_socket = 0;
	m_portNumber = 9999;
}

TypeId SkynetNs3ProxyServer::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SkynetNs3ProxyServer")
    .SetParent<Application> ()
    .AddConstructor<SkynetNs3ProxyServer> ()
    .AddAttribute("PortNumber",
    							"Listening port for the server",
    							IntegerValue(9999),
    							MakeIntegerAccessor(&SkynetNs3ProxyServer::m_portNumber),
    							MakeIntegerChecker<int64_t>());
  return tid;
}


void SkynetNs3ProxyServer::StartApplication (void)
{
  NS_LOG_FUNCTION (this);
  
  m_socket = Socket::CreateSocket (GetNode (), TypeId::LookupByName ("ns3::TcpSocketFactory"));
  NS_ASSERT (m_socket != 0);
  
  
  InetSocketAddress src = InetSocketAddress (Ipv4Address::GetAny(), m_portNumber );

  InetSocketAddress dest = InetSocketAddress(Ipv4Address("172.16.107.1"), m_portNumber);

  int status;
  status = m_socket->Bind (src);
  NS_ASSERT (status != -1);
  
  status = m_socket->Connect(dest);
  NS_ASSERT (status != -1);
  
  //m_socket->ShutdownSend();
  
  m_socket->SetAcceptCallback (
    MakeNullCallback<bool, Ptr<Socket>, const Address &> (),
    MakeCallback (&SkynetNs3ProxyServer::HandleAccept, this));
  m_socket->SetCloseCallbacks (
    MakeCallback (&SkynetNs3ProxyServer::HandlePeerClose, this),
    MakeCallback (&SkynetNs3ProxyServer::HandlePeerError, this));
  m_socket->SetRecvCallback (
	MakeCallback (&SkynetNs3ProxyServer::HandleRead, this));
  m_socket->SetDataSentCallback (
	MakeCallback (&SkynetNs3ProxyServer::HandleSend,this));
}

void SkynetNs3ProxyServer::StopApplication (void)
{
  NS_LOG_FUNCTION (this);
  m_socket->Close ();
}

void SkynetNs3ProxyServer::HandlePeerClose (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
}
 
void SkynetNs3ProxyServer::HandlePeerError (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
}

void SkynetNs3ProxyServer::HandleSend (Ptr<Socket> socket, uint32_t dataSent)
{
  NS_LOG_FUNCTION (this << socket);
}
 
void SkynetNs3ProxyServer::HandleAccept (Ptr<Socket> s, const Address& from)
{
  NS_LOG_FUNCTION (this << s << from);
  s->SetRecvCallback (MakeCallback (&SkynetNs3ProxyServer::HandleRead, this));
}

void SkynetNs3ProxyServer::HandleRead (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  Ptr<Packet> packet;
  Address from;
  while ((packet = socket->RecvFrom (from)))
    {
      if (packet->GetSize () == 0)
        { //EOF
          break;
        }
        
      if (InetSocketAddress::IsMatchingType (from))
        {
          NS_LOG_INFO ("[" << Simulator::Now ().GetSeconds ()
                       << "s] - Rx: "<< packet->GetSize () << " bytes from "
                       << InetSocketAddress::ConvertFrom(from).GetIpv4 ()
                       <<":"<< InetSocketAddress::ConvertFrom (from).GetPort ();
          std::cout << "--> "); 
          
          //std::ostream* os(&std::cout);
          //packet->CopyData(os, packet->GetSize() );
          
          uint8_t *value = (uint8_t *) malloc(sizeof(uint8_t) * packet->GetSize());
          packet->CopyData(value, packet->GetSize());

          Ptr<SkynetSensor> sens = Names::Find<SkynetSensor>("/Names/TemperatureSensor");
          sens->SetTemperatureValue(atoi((char*)value));

          socket->SendTo (packet, 0, from);
         }

    }
}

SkynetNs3ProxyServer::~SkynetNs3ProxyServer ()
{

}

void SkynetNs3ProxyServer::DoDispose (void)
{
  NS_LOG_FUNCTION (this);

  m_socket = 0;
  Application::DoDispose ();
}

} // namespace ns3
