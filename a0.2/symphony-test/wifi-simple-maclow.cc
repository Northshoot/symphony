////
//// ./waf --run "wifi-simple-adhoc --verbose=1"
////
//// When you are done, you will notice two pcap trace files in your directory.
//// If you have tcpdump installed, you can try this:
////
//// tcpdump -r wifi-simple-adhoc-0-0.pcap -nn -tt
////
//
//#include "ns3/core-module.h"
//#include "ns3/common-module.h"
//#include "ns3/node-module.h"
//#include "ns3/helper-module.h"
//#include "ns3/mobility-module.h"
//#include "ns3/contrib-module.h"
//#include "ns3/wifi-module.h"
//#include "ns3/tos-ns-radio.h"
//
//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//
//NS_LOG_COMPONENT_DEFINE ("WifiSimpleLowMAC");
//
//using namespace ns3;
//
//void ReceivePacket (Ptr<Socket> socket)
//{
//  NS_LOG_UNCOND ("Received one packet!");
//}
//
//void ReceivePacket (Ptr<Socket> socket)
//{
//  NS_LOG_UNCOND ("Got from MAC low!");
//}
//
//static void GenerateTraffic (Ptr<Socket> socket, uint32_t pktSize,
//                             uint32_t pktCount, Time pktInterval )
//{
//  if (pktCount > 0)
//    {
//      socket->Send (Create<Packet> (pktSize));
//      Simulator::Schedule (pktInterval, &GenerateTraffic,
//                                      socket, pktSize,pktCount-1, pktInterval);
//    }
//  else
//    {
//      socket->Close ();
//    }
//}
//
//
//int main (int argc, char *argv[])
//{
//  std::string phyMode ("DsssRate1Mbps");
//  double rss = -80;  // -dBm
//  uint32_t packetSize = 1000; // bytes
//  uint32_t numPackets = 10;
//  double interval = 1.0; // seconds
//  bool verbose = false;
//
//  CommandLine cmd;
//
//  cmd.AddValue ("phyMode", "Wifi Phy mode", phyMode);
//  cmd.AddValue ("rss", "received signal strength", rss);
//  cmd.AddValue ("packetSize", "size of application packet sent", packetSize);
//  cmd.AddValue ("numPackets", "number of packets generated", numPackets);
//  cmd.AddValue ("interval", "interval (seconds) between packets", interval);
//  cmd.AddValue ("verbose", "turn on all WifiNetDevice log components", verbose);
//
//  cmd.Parse (argc, argv);
//  // Convert to time object
//  Time interPacketInterval = Seconds (interval);
//
//  // disable fragmentation for frames below 2200 bytes
//  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("2200"));
//  // turn off RTS/CTS for frames below 2200 bytes
//  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("2200"));
//  // Fix non-unicast data rate to be the same as that of unicast
//  Config::SetDefault ("ns3::WifiRemoteStationManager::NonUnicastMode",
//                      StringValue (phyMode));
//
//  NodeContainer c;
//  c.Create (2);
//
//  // The below set of helpers will help us to put together the wifi NICs we want
//  WifiHelper wifi;
//  WifiHelper wifi_low;
//  if (verbose)
//    {
//      wifi.EnableLogComponents ();  // Turn on all Wifi logging
//    }
//  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
//
//  YansWifiPhyHelper wifiPhy =  YansWifiPhyHelper::Default ();
//  // This is one parameter that matters when using FixedRssLossModel
//  // set it to zero; otherwise, gain will be added
//  wifiPhy.Set ("RxGain", DoubleValue (0) );
//  // ns-3 supports RadioTap and Prism tracing extensions for 802.11b
//  wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
//
//  YansWifiChannelHelper wifiChannel ;
//  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
//  // The below FixedRssLossModel will cause the rss to be fixed regardless
//  // of the distance between the two stations, and the transmit power
//  wifiChannel.AddPropagationLoss ("ns3::FixedRssLossModel","Rss",DoubleValue(rss));
//  wifiPhy.SetChannel (wifiChannel.Create ());
//
//  // Add a non-QoS upper mac, and disable rate control
// // NqosWifiMacHelper wifiMac = NqosWifiMacHelper::Default ();
//  MacLow maclow = CreateObject<  TosNsRadio>();
//  maclow->SetRxCallback (MakeCallback (&this::Receive, m_rxMiddle));
//  //Pr<WifiPhy> phy = wifiPhy.Create (c node, device);
//
//  //maclow.SetPhy(phy);
//  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
//                                "DataMode",StringValue(phyMode),
//                                   "ControlMode",StringValue(phyMode));
////  // Set it to adhoc mode
//  wifiMac.SetType ("ns3::AdhocWifiMac");
//  NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, c);
//  //NetDeviceContainer devices_low = wifi_low.Install (wifiPhy, maclow, c);
//
//
//  // Note that with FixedRssLossModel, the positions below are not
//  // used for received signal strength.
//  MobilityHelper mobility;
//  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
//  positionAlloc->Add (Vector (0.0, 0.0, 0.0));
//  positionAlloc->Add (Vector (5.0, 0.0, 0.0));
//  mobility.SetPositionAllocator (positionAlloc);
//  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
//  mobility.Install (c);
//
//  InternetStackHelper internet;
//  internet.Install (c);
//
//  Ipv4AddressHelper ipv4;
//  NS_LOG_INFO ("Assign IP Addresses.");
//  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
//  Ipv4InterfaceContainer i = ipv4.Assign (devices);
//
//  TypeId tid = TypeId::LookupByName ("ns3::UdpSocketFactory");
//  Ptr<Socket> recvSink = Socket::CreateSocket (c.Get (0), tid);
//  InetSocketAddress local = InetSocketAddress (Ipv4Address::GetAny (), 80);
//  recvSink->Bind (local);
//  recvSink->SetRecvCallback (MakeCallback (&ReceivePacket));
//
//  Ptr<Socket> source = Socket::CreateSocket (c.Get (1), tid);
//  InetSocketAddress remote = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
//  source->SetAllowBroadcast (true);
//  source->Connect (remote);
//
//  source->getNode()->
//  // Tracing
//  wifiPhy.EnablePcap ("wifi-simple-adhoc", devices);
//
//  // Output what we are doing
//  NS_LOG_UNCOND ("Testing " << numPackets  << " packets sent with receiver rss " << rss );
//
//  Simulator::ScheduleWithContext (source->GetNode ()->GetId (),
//                                  Seconds (1.0), &GenerateTraffic,
//                                  source, packetSize, numPackets, interPacketInterval);
//
//  Simulator::Run ();
//  Simulator::Destroy ();
//
//  return 0;
//}

