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

#include "ns3/core-module.h"
//#include "tosns-simulator-impl.h"

#include "ns3/tos-module.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/config-store-module.h"
#include "ns3/wifi-module.h"
#include "ns3/internet-module.h"



using namespace ns3;

int main(void)
{
	  //set real time mode
//  ns3::GlobalValue::Bind("SimulatorImplementationType", ns3::StringValue(
//	      "ns3::RealtimeSimulatorImpl"));


	TosNodeContainer c("/home/lauril/dev/symphony/ns-3.11/build/debug/symphony.xml");
	c.Create(2);






    ns3::Simulator::Stop(ns3::Seconds(10.0));
    ns3::Simulator::Run();
    ns3::Simulator::Destroy ();


	return 0;
}