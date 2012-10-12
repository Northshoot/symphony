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

#include "ns3/core-module.h"
#include "ns3/symphony-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"

#include "ns3/wifi-module.h"

using namespace ns3;

int
main(int argc, char *argv[])
{

  std::string nodeModel = "/home/lauril/dev/symphony/ns-3.14/build/symphony.xml";
  std::string nodeImage = "/home/lauril/dev/symphony/ns-3.14/build/libtos.so";
  uint64_t simLength = 1000;
  bool realTime = false;
  CommandLine cmd;
  cmd.AddValue("nodeModel", "model of the node in XML format", nodeModel);
  cmd.AddValue("nodeImage", "node image", nodeImage);
  cmd.AddValue("simLength", "the length of the simulation", simLength);
  cmd.AddValue("realTime", "true to use real time simulation", realTime);
  cmd.Parse(argc, argv);
  //Create TosNodeContainer

  if (realTime)
    {
      GlobalValue::Bind("SimulatorImplementationType",
          StringValue("ns3::RealtimeSimulatorImpl"));
    }
  TosNodeContainer c;
  //Create nodes
  c.Create(1, nodeImage.c_str());
  TosHelper sens;
  sens.SetNodeModel(nodeModel);
  SymphonySensorContainer sc = sens.InstallSensors(1,c,"/home/lauril/dev/symphony/ns-3.14/bin_pkt/");


  //Set run-time for the simulation
  ns3::Simulator::Stop(ns3::Seconds(simLength));
  //Run simulation
  ns3::Simulator::Run();
  //Clean up all objects
  ns3::Simulator::Destroy();
  return 0;
}
