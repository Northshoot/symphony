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


#include "ns3/wifi-module.h"

using namespace ns3;

int
main(int argc, char *argv[])
{

  std::string nodeModel = "/home/lauril/dev/symphony/ns-3.14/build/symphony.xml";
  std::string nodeImage = "/home/lauril/dev/symphony/ns-3.14/build/libtos.so";
  uint64_t simLength = 10;
  uint32_t numNodes=1;
  bool realTime = true;
  CommandLine cmd;
  cmd.AddValue("nodeModel", "model of the node in XML format", nodeModel);
  cmd.AddValue("nodeImage", "node image", nodeImage);
  cmd.AddValue("simLength", "the length of the simulation", simLength);
  cmd.AddValue("realTime", "true to use real time simulation", realTime);
  cmd.AddValue("numNodes", "number of nodes in simulations", numNodes);
  cmd.Parse(argc, argv);
  LogComponentEnable ("TosNode", LOG_LEVEL_ALL);
// LogComponentEnable ("TosLoader", LOG_LEVEL_ALL);
  if (realTime)
    {
      GlobalValue::Bind("SimulatorImplementationType",
          StringValue("ns3::RealtimeSimulatorImpl"));
    }

  TosNodeContainer c;
  //Create nodes
  c.Create(numNodes, nodeImage.c_str());

  TosHelper wifi;

  //Set node model
  wifi.SetNodeModel(nodeModel);
  wifi.Init(c);



  //Set run-time for the simulation
  ns3::Simulator::Stop(ns3::Seconds(simLength));
  //Run simulation
  ns3::Simulator::Run();
  //Clean up all objects
  ns3::Simulator::Destroy();
  return 0;
}
