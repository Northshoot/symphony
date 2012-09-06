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
#include "ns3/core-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"

#include "ns3/wifi-module.h"




using namespace ns3;

int main(int argc, char *argv[])
{

        std::string nodeModel="/home/lauril/dev/symphony/ns-3.11/build/symphony.xml";
        CommandLine cmd;
        cmd.AddValue ("nodeModel", "model of the node in XML format", nodeModel);
        cmd.Parse (argc, argv);
        //Create TosNodeContainer
	TosNodeContainer c;
	//Create nodes
	c.Create(2,"/home/lauril/dev/symphony/ns-3.11/build/libtos.so");

	//Create helper
	TosHelper wifi;
	//here you can enable logging
//	  if (verbose)
//	    {
//	      wifi.EnableLogComponents ();  // Turn on all Wifi logging
//	    }
	  //sett standart for the communications
	  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
	  wifi.EnableLogComponents ();
	  //Set node model
	  wifi.SetNodeModel(nodeModel);
	 //LogComponentEnableAll(LOG_ALL);
	  //Create physical layer
	  YansTosPhyHelper wifiPhy =  YansTosPhyHelper::Default ();
	  // This is one parameter that matters when using FixedRssLossModel
	  // set it to zero; otherwise, gain will be added
	  wifiPhy.Set ("RxGain", DoubleValue (0) );
	  // ns-3 supports RadioTap and Prism tracing extensions for 802.11b
	  //wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
	  //Create channel
	  YansWifiChannelHelper wifiChannel;
	  //Add propagation
	  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
	  // The below FixedRssLossModel will cause the rss to be fixed regardless
	  // of the distance between the two stations, and the transmit power
	  wifiChannel.AddPropagationLoss ("ns3::FixedRssLossModel","Rss",DoubleValue (-80));
	  wifiPhy.SetChannel (wifiChannel.Create ());

	  //Create devices
	  TosNetDeviceContainer devices = wifi.Install (wifiPhy,  c);
	  // Note that with FixedRssLossModel, the positions below are not
	  // used for received signal strength.
	  //Att mobility
	  TosMobilityHelper mobility;
	  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
	  positionAlloc->Add (Vector (0.0, 0.0, 0.0));
	  positionAlloc->Add (Vector (50.0, 0.0, 0.0));
	  //positionAlloc->Add (Vector (0, 0.0, 0.0));
	  mobility.SetPositionAllocator (positionAlloc);
	  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	  //Install it
	  mobility.Install (c);


   //Set run-time for the simulation
    ns3::Simulator::Stop(ns3::Seconds(20));
    //Run simulation
    ns3::Simulator::Run();
   //Clean up all objects
    ns3::Simulator::Destroy ();
    return 0;
}
