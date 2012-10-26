/*
 * main.c
 *
 *  Created on: Feb 25, 2010
 *      Author: laurynas
 */

/***
 * Simple symphony usage example
 */
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include "ns3/symphony-module.h"
#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/wifi-module.h"

#include "ns3/abort.h"
#include "ns3/internet-module.h"
#include "ns3/emu-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include <fstream>
#include "ns3/callback.h"



using namespace ns3;

typedef struct packet32_msg {
        uint32_t nodeID;
        uint32_t timestamp;
        uint32_t size;
        uint8_t rawData[];
} packet32_msg_t;

void
sender(Ptr<WSNGatewayClient> app){
  NS_LOG_INFO("send send");
  packet32_msg_t buff;
  packet32_msg_t * msg = (packet32_msg_t *)&buff;
  uint64_t timestamp = msg->timestamp;
  uint32_t nodeID = msg->nodeID;
  uint8_t flag = 1;
  uint32_t size = msg->size;
  uint32_t m_cellID;
  Ptr<Packet> p;


  std::cout << "Packet " <<std::endl;
  p = Create<Packet> ((uint8_t *)&m_cellID, sizeof(m_cellID));
  app->sendData();
  std::cout << "Packet 1" <<std::endl;
  p = Create<Packet> ((uint8_t *)&nodeID, sizeof(nodeID));
  std::cout << "Packet 2" <<std::endl;
  p = Create<Packet> ((uint8_t *)&flag, sizeof(flag));
  std::cout << "Packet 3" <<std::endl;
  p = Create<Packet> ((uint8_t *)&timestamp, sizeof(timestamp));
  std::cout << "Packet 4" <<std::endl;
  p = Create<Packet> ((uint8_t *)&size, sizeof(size));
  std::cout << "Packet 5" <<std::endl;
  p = Create<Packet> (msg->rawData, size);


  Simulator::Schedule (Seconds(1), &sender,app);

}


int
main(int argc, char *argv[])
{

  //uint64_t simLength = 1;
  std::string deviceName ("eth0");
  std::string remote ("localhost"); // example.com

  Ipv4Address remoteIp (remote.c_str ());
    Ipv4Address localIp ("localhost");
    Ipv4Mask localMask ("255.255.255.0");
    GlobalValue::Bind ("SimulatorImplementationType", StringValue ("ns3::RealtimeSimulatorImpl"));
     GlobalValue::Bind ("ChecksumEnabled", BooleanValue (true));
     Ptr<Node> node = CreateObject<Node> ();
     Ptr<EmuNetDevice> device = CreateObject<EmuNetDevice> ();
     device->SetAttribute ("Address", Mac48AddressValue (Mac48Address::Allocate ()));
     device->SetAttribute ("DeviceName", StringValue (deviceName));

     Ptr<Queue> queue = CreateObject<DropTailQueue> ();
     device->SetQueue (queue);
     node->AddDevice (device);
     InternetStackHelper internetStackHelper;
       internetStackHelper.Install (node);

       NS_LOG_INFO ("Create IPv4 Interface");
       Ptr<Ipv4> ipv4 = node->GetObject<Ipv4> ();
       uint32_t interface = ipv4->AddInterface (device);
       Ipv4InterfaceAddress address = Ipv4InterfaceAddress (localIp, localMask);
       ipv4->AddAddress (interface, address);
       ipv4->SetMetric (interface, 1);
       ipv4->SetUp (interface);
       Ipv4Address gateway ("130.240.231.1");
       NS_ABORT_MSG_IF (gateway == "1.2.3.4", "You must change the gateway IP address before running this example");

       Ipv4StaticRoutingHelper ipv4RoutingHelper;
       Ptr<Ipv4StaticRouting> staticRouting = ipv4RoutingHelper.GetStaticRouting (ipv4);
       staticRouting->SetDefaultRoute (gateway, interface);
       Ptr<WSNGatewayClient> app = CreateObject<WSNGatewayClient> ();
       app->SetAttribute ("Remote", Ipv4AddressValue (remoteIp));

       node->AddApplication (app);
       app->SetStartTime (Seconds (0.0));
       app->SetStopTime (Seconds (5.0));

       EmuHelper emu;
         emu.EnablePcap ("emu-ping", device, true);
         Simulator::Schedule (Seconds(1), &sender,app);







  //Set run-time for the simulation
//  ns3::Simulator::Stop(ns3::Seconds(simLength));
  //Run simulation
  ns3::Simulator::Run();
  //Clean up all objects
  ns3::Simulator::Destroy();
  return 0;
}
