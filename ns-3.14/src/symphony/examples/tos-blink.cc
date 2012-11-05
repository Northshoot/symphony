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
#include <sys/time.h>

#include "ns3/core-module.h"
#include "ns3/symphony-module.h"
#include "ns3/core-module.h"
#include "ns3/config-store-module.h"
#include "ns3/log.h"




using namespace ns3;

int main(int argc, char *argv[])
{

	  std::string nodeModel = "/home/lauril/dev/symphony/ns-3.14/build/symphony.xml";
	  std::string nodeImage = "/home/lauril/dev/symphony/ns-3.14/build/libtos.so";
	  uint64_t simLength = 2;
	  bool realTime = false;
	  CommandLine cmd;
	  cmd.AddValue("nodeModel", "model of the node in XML format", nodeModel);
	  cmd.AddValue("nodeImage", "node image", nodeImage);
	  cmd.AddValue("simLength", "the length of the simulation", simLength);
	  cmd.AddValue("realTime", "true to use real time simulation", realTime);
	  cmd.Parse(argc, argv);

	  if (realTime)
	    {
	      GlobalValue::Bind("SimulatorImplementationType",
	          StringValue("ns3::RealtimeSimulatorImpl"));
	    }

	  LogComponentEnable ("TosNode", LOG_LEVEL_ALL);
	  LogComponentEnable ("TosLoader", LOG_LEVEL_ALL);
	  TosNodeContainer c;
	  c.Create(1, nodeImage.c_str());
	  TosHelper helper;
	  helper.SetNodeModel(nodeModel);
	  helper.Init(c);

	  ns3::Simulator::Stop(ns3::Seconds(simLength));
	  ns3::Simulator::Run();
	  ns3::Simulator::Destroy ();


 return 0;
}
