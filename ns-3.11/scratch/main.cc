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
#include "ns3/event-id.h"
#include "ns3/nstime.h"
#include "ns3/tos-node.h"
#include "ns3/tos-node-container.h"




int main(void)
{
	  //set real time mode
//	  ns3::GlobalValue::Bind("SimulatorImplementationType", ns3::StringValue(
//	      "ns3::TosNsRealtimeSimulatorImpl"));


	ns3::TosNodeContainer c;
	c.Create(2);
//	std::vector<ns3::TosNode * > tos;
//    srand((unsigned)time(0));
//
//    for(int i=0; i<1;i++){
//    	//std::cout<<"Round ./libtos.so "<<i<<std::endl;
//
//    	tos.push_back( new ns3::TosNode((rand()%1000)+1, ns3::MilliSeconds(0)));
//
//
//
//    }


//	ns3::TosNode * n2 = new ns3::TosNode((rand()%1000)+1, ns3::MilliSeconds(0));
//	TinyBridge *tbridge2 = new TinyBridge(n2, "./libtos.so");


    ns3::Simulator::Stop(ns3::Seconds(10.0));
    ns3::Simulator::Run();
    std::cout<<"about to destroy "<<std::endl;
    ns3::Simulator::Destroy ();


	return 0;
}
