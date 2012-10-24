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
  uint64_t simLength = 116;
  bool realTime = true;
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

  //The node ID's have to match the sensor data start id, which is always starts with
  //ID# were 3 is node id.
  //This is example of one way to set the tos_node_id
  c.Add(CreateObject<TosNode> (10, MilliSeconds(0), nodeImage.c_str() ));
  c.Add(CreateObject<TosNode> (11, MilliSeconds(0), nodeImage.c_str() ));
//  c.Add(CreateObject<TosNode> (15, MilliSeconds(0), nodeImage.c_str() ));
//  c.Add(CreateObject<TosNode> (19, MilliSeconds(0), nodeImage.c_str() ));
//  c.Add(CreateObject<TosNode> (23, MilliSeconds(0), nodeImage.c_str() ));
//  c.Add(CreateObject<TosNode> (33, MilliSeconds(0), nodeImage.c_str() ));
//  c.Add(CreateObject<TosNode> (46, MilliSeconds(0), nodeImage.c_str() ));

  //another way
//  TosNodeContainer c1;
//  c1.Create(2,nodeImage.c_str() );
//  c1.Get(0)->SetAttribute("TosId", UintegerValue(47));
//  c1.Get(1)->SetAttribute("TosId", UintegerValue(49));
//  c.Add(c1);
 //And there is a third way...
//reacall lecture slides
  TosHelper sens;
  sens.SetNodeModel(nodeModel);
  SymphonySensorContainer sc = sens.InstallSensors(1,c,"/home/lauril/dev/symphony/ns-3.14/bin_pkt/");


  //Set run-time for the simulation
  Simulator::Stop(ns3::Seconds(simLength));
  //Run simulation
  Simulator::Run();
  //Clean up all objects
  Simulator::Destroy();
  return 0;
}
