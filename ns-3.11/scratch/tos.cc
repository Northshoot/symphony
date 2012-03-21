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

	TosHelper wifi;

//	  if (verbose)
//	    {
//	      wifi.EnableLogComponents ();  // Turn on all Wifi logging
//	    }
	  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
	  //wifi.EnableLogComponents ();
	 //LogComponentEnableAll(LOG_ALL);
	  YansTosPhyHelper wifiPhy =  YansTosPhyHelper::Default ();
	  // This is one parameter that matters when using FixedRssLossModel
	  // set it to zero; otherwise, gain will be added
	  wifiPhy.Set ("RxGain", DoubleValue (0) );
	  // ns-3 supports RadioTap and Prism tracing extensions for 802.11b
	  //wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);

	  YansWifiChannelHelper wifiChannel;
	  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
	  // The below FixedRssLossModel will cause the rss to be fixed regardless
	  // of the distance between the two stations, and the transmit power
	  wifiChannel.AddPropagationLoss ("ns3::RandomPropagationLossModel");
	  wifiPhy.SetChannel (wifiChannel.Create ());

	  TosNetDeviceContainer devices = wifi.Install (wifiPhy,  c);
	  // Note that with FixedRssLossModel, the positions below are not
	  // used for received signal strength.
	  TosMobilityHelper mobility;
	  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
	  positionAlloc->Add (Vector (0.0, 0.0, 0.0));
	  positionAlloc->Add (Vector (100000.0, 0.0, 0.0));
	  mobility.SetPositionAllocator (positionAlloc);
	  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
	  mobility.Install (c);




    ns3::Simulator::Stop(ns3::Seconds(10.0));
    ns3::Simulator::Run();
    ns3::Simulator::Destroy ();


	return 0;
}
