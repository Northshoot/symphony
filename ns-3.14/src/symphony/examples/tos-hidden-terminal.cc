/*
 * main.c
 *
 *  Created on: Feb 25, 2010
 *      Author: laurynas
 */

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include "ns3/propagation-module.h"
#include "ns3/core-module.h"
#include "ns3/propagation-module.h"
#include "ns3/network-module.h"

#include "ns3/mobility-module.h"

#include "ns3/symphony-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"

#include "ns3/log.h"
using namespace ns3;

int
main(int argc, char *argv[])
{

  std::string nodeModel = "/home/lauril/dev/symphony/ns-3.14/build/symphony.xml";
  std::string nodeImage = "/home/lauril/dev/symphony/ns-3.14/build/libtos.so";
  uint64_t simLength = 10;
  bool realTime = false;
  CommandLine cmd;
  cmd.AddValue("nodeModel", "model of the node in XML format", nodeModel);
  cmd.AddValue("nodeImage", "node image", nodeImage);
  cmd.AddValue("simLength", "the length of the simulation", simLength);
  cmd.AddValue("realTime", "true to use real time simulation", realTime);
  cmd.Parse(argc, argv);

 // LogComponentEnableAll(LOG_ALL);

  TosNodeContainer nodes;
  //Create nodes
  nodes.Create(3, nodeImage.c_str());
  if (realTime)
    {
      GlobalValue::Bind("SimulatorImplementationType",
          StringValue("ns3::RealtimeSimulatorImpl"));
    }

  // 2. Place nodes somehow, this is required by every wireless simulation
  for (size_t i = 0; i < 3; ++i)
    {
      nodes.Get(i)->AggregateObject(
          CreateObject<ConstantPositionMobilityModel>());
    }

  // 3. Create propagation loss matrix
  double zero2one = 110;
  double two2one =  110;
  Ptr<MatrixPropagationLossModel> lossModel = CreateObject<
      MatrixPropagationLossModel>();
  lossModel->SetDefaultLoss(200); // set default loss to 200 dB (no link)
  lossModel->SetLoss(nodes.Get(0)->GetObject<MobilityModel>(),
      nodes.Get(1)->GetObject<MobilityModel>(), zero2one); // set symmetric loss 0 <-> 1 to 50 dB
  lossModel->SetLoss(nodes.Get(2)->GetObject<MobilityModel>(),
      nodes.Get(1)->GetObject<MobilityModel>(), two2one); // set symmetric loss 2 <-> 1 to 50 dB

  Ptr<YansWifiChannel> wifiChannel = CreateObject <YansWifiChannel> ();
    wifiChannel->SetPropagationLossModel (lossModel);
    wifiChannel->SetPropagationDelayModel (CreateObject <ConstantSpeedPropagationDelayModel> ());
  //Create helper
  TosHelper wifi;

  //sett standart for the communications
  wifi.SetStandard(ZIGBEE_PHY_STANDARD_802154);
  //wifi.EnableLogComponents ();
  //Set node model
  wifi.SetNodeModel(nodeModel);
  YansTosPhyHelper wifiPhy = YansTosPhyHelper::Default();
  wifiPhy.SetChannel(wifiChannel);



  //Create devices
  TosNetDeviceContainer devices = wifi.Install(wifiPhy, nodes);

  ns3::Simulator::Stop(ns3::Seconds(simLength));
  ns3::Simulator::Run();
  ns3::Simulator::Destroy();

  return 0;
}
