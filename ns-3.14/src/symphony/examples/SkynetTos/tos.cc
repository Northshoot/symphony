/**
* We will launch 14 nodes, each of them will be connected to the
* gateway through wireless connexion.
* The gateway will be connected tho the back-end on tcp connexion
*
* @author Jose Angel Fernandez
* @date 17 October 2012
*/

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "ns3/symphony-module.h"
#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"

#include "ns3/wifi-module.h"

using namespace ns3;


void Log(uint8_t size, void * buffer){
    typedef struct {
      uint32_t nodeId;
      uint32_t counter;

    } NodePacket;

    NodePacket *npkt = (NodePacket*) buffer;
  
    NS_LOG_UNCOND("[NS3] Node [" << npkt->nodeId << "] sent value " << npkt->counter );
}

int main (int argc, char *argv[])
{

  //LogComponentEnable("SkynetSensor", LOG_LEVEL_ALL);

  std::string nodeModel = "/home/onir/dev/symphony/ns-3.14/build/symphony.xml";
  std::string nodeImage = "/home/onir/dev/symphony/ns-3.14/build/libSkynetTos.so";
  uint64_t simLength = 10;

	
	//Create the node container for the two nodes
  TosNodeContainer allNodes;
  
  //Load our tinyOS image
  allNodes.Create(1, nodeImage.c_str());
  
  //Set the IDs of each nodes
  allNodes.Get(0)->SetAttribute("TosId", UintegerValue(0));

  //Create the wireless communication between the two nodes
  TosHelper wifi;
  wifi.SetStandard (ZIGBEE_PHY_STANDARD_802154);
  wifi.SetNodeModel(nodeModel);
  
  //Create channel
  YansWifiChannelHelper wifiChannel;
  
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FixedRssLossModel","Rss", DoubleValue (-80));
  
  //Create physical layer
  YansTosPhyHelper wifiPhy =  YansTosPhyHelper::Default ();
  wifiPhy.Set ("RxGain", DoubleValue (0) );
  wifiPhy.SetChannel (wifiChannel.Create ());
  
  //wifi.Init(allNodes);
  
  TosNetDeviceContainer devices = wifi.Install (wifiPhy, allNodes);

  // With FixedRssLossModel, the positions below are not
  // used for received signal strength.
  TosMobilityHelper mobility;
  
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (0.0, 0.0, 0.0));
  positionAlloc->Add (Vector (50.0, 0.0, 0.0));

  mobility.SetPositionAllocator (positionAlloc);
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (allNodes);
  
  Ptr<SymphonyApplication> app = CreateObject<SymphonyApplication>();
  allNodes.Get(0)->AddApplication(app);
  app->SetNode(allNodes.Get(0));
  app->SetAttribute("ReceiveDataFromApplication", CallbackValue(MakeCallback(&Log)));
  app->SetStartTime (Seconds (0.0));
  app->SetStopTime (Seconds (20.0));
  app->StartApplication();

  TosHelper sens;
  sens.SetNodeModel(nodeModel);
  SymphonySensorContainer sc = sens.InstallSensors(1, allNodes,"/home/onir/dev/symphony/ns-3.14/bin_pkt/");

  Names::Add("TemperatureSensor", sc.Get(0));

  Config::Set("/Names/TemperatureSensor/TemperatureValue", IntegerValue(40));


  //Set run-time for the simulation
  ns3::Simulator::Stop(ns3::Seconds(simLength));
  //Run simulation
  ns3::Simulator::Run();
  //Clean up all objects
  ns3::Simulator::Destroy();
  return 0;
}

