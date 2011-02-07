/*
 * main.c
 *
 *  Created on: Feb 25, 2010
 *      Author: laurynas
 */


#include <stdio.h>
#include "ns3/core-module.h"
#include "ns3/common-module.h"
//#include "tosns-simulator-impl.h"
#include "ns3/event-id.h"
#include "ns3/nstime.h"
#include "ns3/TosNode.h"
#include "ns3/TinyBridge.h"
#include "ns3/core-module.h"
#include "ns3/common-module.h"
#include "ns3/node-module.h"
#include "ns3/helper-module.h"
#include "ns3/mobility-module.h"
#include "ns3/contrib-module.h"
#include "ns3/wifi-module.h"
#include "ns3/athstats-helper.h"

using namespace ns3;

int main(void)
{
	  //set real time mode
//	  ns3::GlobalValue::Bind("SimulatorImplementationType", ns3::StringValue(
//	      "ns3::TosNsRealtimeSimulatorImpl"));


	std::vector<ns3::TosNode * > tos;
	std::vector<TinyBridge *> bridge;
    srand((unsigned)time(0));

    for(int i=0; i<2;i++){
    	std::cout<<"Round ./libtos.so "<<i<<std::endl;
    	tos.push_back( new ns3::TosNode((rand()%1000)+1, ns3::MilliSeconds(0)));
    	bridge.push_back(new TinyBridge(tos[i], "./libtos.so"));
    }

    YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
    YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default ();
    wifiPhy.SetChannel (wifiChannel.Create ());

//	ns3::TosNode * n2 = new ns3::TosNode((rand()%1000)+1, ns3::MilliSeconds(0));
//	TinyBridge *tbridge2 = new TinyBridge(n2, "./libtos.so");


    Simulator::Stop(ns3::Seconds(10.0));
    Simulator::Run();
    Simulator::Destroy ();
	return 0;
}
