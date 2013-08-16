/**
 * Ns-3 proxy that receives data from the I/O clients, processes it and
 * sends it to the correct node.
 *
 * @author Jose Angel Fernandez
 */
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
#include "ns3/tos-device.h"
#include "ns3/names.h"
#include "ns3/string.h"
#include "ns3/object.h"

#include "io-proxy-server-application.h"
#include <stdio.h>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("IOProxyServer");
NS_OBJECT_ENSURE_REGISTERED (IOProxyServer);


IOProxyServer::IOProxyServer ()
{
	m_socket = 0;
}

TypeId IOProxyServer::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::IoProxyServer")
    .SetParent<Application> ()
    .AddConstructor<IOProxyServer> ()
    .AddAttribute("RemotePortNumber",
    					"Remote port listening for connections",
    					IntegerValue(9999),
    					MakeIntegerAccessor(&IOProxyServer::m_remotePortNumber),
    					MakeIntegerChecker<int64_t>())
    .AddAttribute("RemoteIp",
    					"Remote IP listening for connections",
    					StringValue("127.0.0.1"),
    					MakeStringAccessor(&IOProxyServer::m_remoteIp),
    					MakeStringChecker())
    .AddAttribute("LocalPortNumber",
    					"Local port for incoming connections",
    					IntegerValue(3333),
    					MakeIntegerAccessor(&IOProxyServer::m_localPortNumber),
    					MakeIntegerChecker<int64_t>())
    .AddAttribute("LocalIp",
    					"Local IP for incoming connections",
    					StringValue("127.0.0.1"),
    					MakeStringAccessor(&IOProxyServer::m_localIp),
    					MakeStringChecker())
    .AddAttribute("NodePairsNumber",
    					"Number of node pairs used on the simulation (e.g 1 = one sensors & one actuator)",
    					IntegerValue(2),
    					MakeIntegerAccessor(&IOProxyServer::m_nodePairsNumber),
    					MakeIntegerChecker<int64_t>());
  return tid;
}

void IOProxyServer::StartApplication (void)
{
  NS_LOG_FUNCTION (this);
  
  m_socket = Socket::CreateSocket (GetNode (), TypeId::LookupByName ("ns3::TcpSocketFactory"));
  NS_ASSERT_MSG (m_socket != 0, "An error has happened when trying to create the socket");
  
  InetSocketAddress src = InetSocketAddress (Ipv4Address::GetAny(), m_localPortNumber );
  InetSocketAddress dest = InetSocketAddress(Ipv4Address(m_remoteIp.c_str()), m_remotePortNumber);

  int status;
  status = m_socket->Bind (src);
  NS_ASSERT_MSG (status != -1, "An error has happened when trying to bind to local end point");
  
  status = m_socket->Connect(dest);
  NS_ASSERT_MSG (status != -1, "An error has happened when trying to connect to remote end point");
  
  // Configures the callbacks for the different events related with the connection

  //m_socket->SetConnectCallback

  m_socket->SetAcceptCallback (
    MakeNullCallback<bool, Ptr<Socket>, const Address &> (),
    MakeCallback (&IOProxyServer::HandleAccept, this));

  m_socket->SetRecvCallback (
	MakeCallback (&IOProxyServer::HandleRead, this));

  m_socket->SetDataSentCallback (
	MakeCallback (&IOProxyServer::HandleSend,this));

  //m_socket->SetSendCallback

  m_socket->SetCloseCallbacks (
    MakeCallback (&IOProxyServer::HandlePeerClose, this),
    MakeCallback (&IOProxyServer::HandlePeerError, this));

  // If we need to configure a reception only socket or a sending only socket
  // we need to call one of the following methods:
  // m_socket->ShutdownSend();
  // m_socket->ShutdownRecv();
}

void IOProxyServer::StopApplication (void)
{
  NS_LOG_FUNCTION (this);
  m_socket->Close();
}

void IOProxyServer::HandleAccept (Ptr<Socket> s, const Address& from)
{
  NS_LOG_FUNCTION (this << s << from);
  s->SetRecvCallback (MakeCallback (&IOProxyServer::HandleRead, this));
}

void IOProxyServer::HandleRead (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
  Ptr<Packet> packet;

  while ((packet = socket->RecvFrom (from)))
    {
      if (packet->GetSize () == 0)
        { //EOF
          break;
        }
        
      if (InetSocketAddress::IsMatchingType (from))
        {
          NS_LOG_INFO ("\n[" << Simulator::Now ().GetSeconds ()
                       << "s] - Rx: "<< packet->GetSize () << " bytes from "
                       << InetSocketAddress::ConvertFrom(from).GetIpv4 ()
                       <<":"<< InetSocketAddress::ConvertFrom (from).GetPort ();
          std::cout << "--> "); 
          
          //Extract the string from the packet
          unsigned char *value = (unsigned char *) malloc(sizeof(uint8_t)*packet->GetSize());
          packet->CopyData(value, packet->GetSize());
          std::string data ((char *)value);

          //Select if its sensor or actuator checking the received string
          if (data.find("Sensor") != std::string::npos)
          {
        	  // Received pattern matches: *Sensor-sensorId:sensorValue
        	  int sensorId = atoi( data.substr(data.find("-") + 1, data.find(":")).c_str());
        	  std::cout << "Sensor Id: " << sensorId;

        	  int sensorValue = atoi(data.substr(data.find(":")+1).c_str());
        	  std::cout << " - Value: " << sensorValue << "\n\n";

        	  std::string name = "/Names/TemperatureSensor";
          	  //Identify the number of the sensors
        	  char numstr[21]; // enough to hold all numbers up to 64-bits
        	  sprintf(numstr, "%d", sensorId);
        	  std::string result = name + numstr;
        	  Ptr<TosDevice> sens = Names::Find<TosDevice>(result);

        	  //Send the measurement to the correct sensor
        	  sens->SendRawData(sizeof(sensorValue), &sensorValue);
        	  //Creates an echo of the message received
              socket->SendTo (packet, 0, from);

          }
          else if (data.find("actuator") != std::string::npos)
          {
        	  // Received pattern matches: *Actuator-actuatorId:actuatorValue
           	  int actuatorId = atoi( data.substr(data.find("-") + 1, data.find(":")).c_str());
              std::cout << "Actuator Id: " << actuatorId;

              int actuatorValue = atoi(data.substr(data.find(":")+1).c_str());
        	  std::cout << " - Value: " << actuatorValue << "\n\n";

        	  std::string name = "/Names/Actuator";
        	  //Identify the number of the sensors
           	  char numstr[21]; // enough to hold all numbers up to 64-bits
           	  sprintf(numstr, "%d", actuatorId);
           	  std::string result = name + numstr;
           	  Ptr<TosDevice> act = Names::Find<TosDevice>(result);

        	  //Send the measurement
           	  act->SendRawData(sizeof(actuatorValue), &actuatorValue);
              //Creates and echo of the message
           	  socket->SendTo (packet, 0, from);
          }
         }
    }
}

void IOProxyServer::SendData(std::string str)
{
	char * cstr = new char [str.length()+1];
	strcpy(cstr, str.c_str());

	Ptr<Packet> packet = Create<Packet>((uint8_t*)cstr, str.length()+1);
	m_socket->Send(packet, 0);

	delete []cstr;
}

void IOProxyServer::HandlePeerClose (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
}

void IOProxyServer::HandlePeerError (Ptr<Socket> socket)
{
  NS_LOG_FUNCTION (this << socket);
}

void IOProxyServer::HandleSend (Ptr<Socket> socket, uint32_t dataSent)
{
  NS_LOG_FUNCTION (this << socket);
}

IOProxyServer::~IOProxyServer ()
{

}

void IOProxyServer::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  m_socket = 0;
  Application::DoDispose ();
}

} // namespace ns3
