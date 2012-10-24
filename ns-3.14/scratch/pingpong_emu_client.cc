/* big parts are copied from the ns3 example- and sourcefiles */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"
#include "ns3/emu-helper.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

NS_LOG_COMPONENT_DEFINE ("PingPong");

using namespace ns3;

 //seconds

void startSending (Ptr<Socket> socket, InetSocketAddress addr)
{
	  uint32_t counter=0;
	  int status;
	  NS_LOG_UNCOND ("Start to send pingpong package with counter= '" << counter << "'!");
	  status = socket->Connect (addr);
	  NS_LOG_UNCOND ("Status != -1 remote " << (status != -1));
//	  uint8_t *temp = (uint8_t*) &counter;
//          socket->Send ( temp, 20);
//          socket->Close();


}

void ReceivePacket (Ptr<Socket> socket)
{
      NS_LOG_FUNCTION_NOARGS();
    Ptr<Packet> packet;
    Address from;
    while ((packet = socket->RecvFrom (from)))
      {
    	uint32_t packetSize = packet->GetSize(); // bytes
        if (InetSocketAddress::IsMatchingType (from))
          {
            NS_LOG_UNCOND ("At time " << Simulator::Now ().GetSeconds () << "s application received " << packet->GetSize () << " bytes from " <<
                         InetSocketAddress::ConvertFrom (from).GetIpv4 () << " port " <<
                         InetSocketAddress::ConvertFrom (from).GetPort ());
          }
        else if (Inet6SocketAddress::IsMatchingType (from))
          {
            NS_LOG_UNCOND ("At time " << Simulator::Now ().GetSeconds () << "s application received " << packet->GetSize () << " bytes from " <<
                         Inet6SocketAddress::ConvertFrom (from).GetIpv6 () << " port " <<
                         InetSocketAddress::ConvertFrom (from).GetPort ());
          }
     	uint8_t *buffer = new uint8_t[packetSize];
        packet->CopyData(buffer, packetSize);
        uint32_t counter = *(uint32_t *)(buffer);
        NS_LOG_UNCOND ("Received package with counter= '" << counter << "'!");
        counter++;

//        uint8_t *temp = (uint8_t*) &counter;
//        packet->RemoveAllPacketTags ();
//        packet->RemoveAllByteTags ();

        NS_LOG_UNCOND ("Echoing packet with counter='"<<counter<<'.');
        Simulator::Schedule (Seconds (1), &startSending, socket, InetSocketAddress::ConvertFrom (from));


        if (InetSocketAddress::IsMatchingType (from))
          {
            NS_LOG_UNCOND ("At time " << Simulator::Now ().GetSeconds () << "s application sent " << packet->GetSize () << " bytes to " <<
                         InetSocketAddress::ConvertFrom (from).GetIpv4 () << " port " <<
                         InetSocketAddress::ConvertFrom (from).GetPort ());
          }
        else if (Inet6SocketAddress::IsMatchingType (from))
          {
            NS_LOG_UNCOND ("At time " << Simulator::Now ().GetSeconds () << "s application sent " << packet->GetSize () << " bytes to " <<
                         Inet6SocketAddress::ConvertFrom (from).GetIpv6 () << " port " <<
                         InetSocketAddress::ConvertFrom (from).GetPort ());
          }
      }
}

int main (int argc, char *argv[])
{
  std::string deviceName ("eth0");
  std::string remote ("54.247.35.133");
  std::string local ("130.240.231.18");
  std::string gatewayip ("130.240.231.1");
  uint16_t remotePort = 11111;
  uint32_t simulationTime = 100;
  //uint16_t localPort = 80;

  CommandLine cmd;

  cmd.AddValue ("simulationTime", "number of seconds, the simulation will run", simulationTime);
  cmd.AddValue ("deviceName", "network device used for the emunet device (f.e. eth0)", deviceName);
  cmd.AddValue ("remote", "IP address of the remote host", remote);
  cmd.AddValue ("local", "local (own) IP address", local);
  cmd.AddValue ("gatewayip", "IP of the connected gateway to update the routing table there", gatewayip);
  cmd.AddValue ("remotePort", "Port of the remote host", remotePort);
  //cmd.AddValue ("localPort", "Port of the socket on this host", localPort);

  cmd.Parse (argc, argv);

  Ipv4Address remoteIp (remote.c_str ());
  Ipv4Address localIp (local.c_str());
  Ipv4Mask localMask ("255.255.255.0");

  GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::RealtimeSimulatorImpl"));
  GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));

  NS_LOG_INFO ("Create Node");
  Ptr<Node> node = CreateObject<Node> ();

  NS_LOG_INFO ("Create Device");
  Ptr<EmuNetDevice> device = CreateObject<EmuNetDevice> ();
  device->SetAttribute ("Address", Mac48AddressValue (Mac48Address::Allocate ()));
  device->SetAttribute ("DeviceName", StringValue (deviceName));

  Ptr<Queue> queue = CreateObject<DropTailQueue> ();
  device->SetQueue (queue);
  node->AddDevice (device);

  NS_LOG_INFO ("Add Internet Stack");
  InternetStackHelper internetStackHelper;
  internetStackHelper.Install (node);

  NS_LOG_INFO ("Create IPv4 Interface");
  Ptr<Ipv4> ipv4 = node->GetObject<Ipv4> ();
  uint32_t interface = ipv4->AddInterface (device);
  Ipv4InterfaceAddress address = Ipv4InterfaceAddress (localIp, localMask);
  ipv4->AddAddress (interface, address);
  ipv4->SetMetric (interface, 1);
  ipv4->SetUp (interface);

  Ipv4Address gateway (gatewayip.c_str());
  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> staticRouting = ipv4RoutingHelper.GetStaticRouting (ipv4);
  staticRouting->SetDefaultRoute (gateway, interface);


  Ptr<Socket> localSocket = Socket::CreateSocket (node, TypeId::LookupByName ("ns3::TcpSocketFactory"));
  NS_LOG_UNCOND ("localsocket != 0 : " << (localSocket != 0));
  localSocket->SetRecvCallback (MakeCallback (&ReceivePacket));
  //int status;
  //InetSocketAddress localSocketAddress = InetSocketAddress (localIp, localPort);
  //status = localSocket->Bind (localSocketAddress);
  //NS_LOG_UNCOND ("status != -1 local:" << status != -1);

  InetSocketAddress remoteSocketAddress = InetSocketAddress (remoteIp, remotePort);

  /*localSocket->Send (data,size, 0);
  localSocket->Close ();*/

  /*Ptr<Socket> source = Socket::CreateSocket (c.Get (1), tid);
  InetSocketAddress remote = InetSocketAddress (Ipv4Address ("130.240.94.84"), 80);
  source->SetAllowBroadcast (true);
  source->Connect (remote);
  source->SetRecvCallback (MakeCallback (&ReceivePacket));*/

  // Output what we are doing
  //NS_LOG_UNCOND ("Testing emunetdevices (local: " <<local <<", localPort: " << localPort << ", remote: " << remote << ", remotePort: " << remotePort << ", gatewayip: " << gatewayip << ")");

  std::ofstream ascii;
  ascii.open ("emunet-pingpong.tr");
  EmuHelper emu;
  emu.EnablePcap ("emunet-pingpong", device, true);

  Simulator::Schedule (Seconds (0.01), &startSending, localSocket, remoteSocketAddress);

  //
  // Now, do the actual emulation.
  //
  NS_LOG_INFO ("Run Emulation.");
  Simulator::Stop(Seconds(10));
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
