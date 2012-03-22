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
#include "ns3/internet-module.h"

#include "ns3/wifi-module.h"
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


	TosNodeContainer nodes("/home/lauril/dev/symphony/ns-3.11/build/debug/symphony.xml");
	nodes.Create(3);
	// 2. Place nodes somehow, this is required by every wireless simulation
	  for (size_t i = 0; i < 3; ++i)
	    {
	      nodes.Get (i)->AggregateObject (CreateObject<ConstantPositionMobilityModel> ());
	    }

	  // 3. Create propagation loss matrix
	  Ptr<MatrixPropagationLossModel> lossModel = CreateObject<MatrixPropagationLossModel> ();
	  lossModel->SetDefaultLoss (200); // set default loss to 200 dB (no link)
	  lossModel->SetLoss (nodes.Get (0)->GetObject<MobilityModel>(), nodes.Get (1)->GetObject<MobilityModel>(), 50); // set symmetric loss 0 <-> 1 to 50 dB
	  lossModel->SetLoss (nodes.Get (2)->GetObject<MobilityModel>(), nodes.Get (1)->GetObject<MobilityModel>(), 50); // set symmetric loss 2 <-> 1 to 50 dB

	TosHelper wifi;

//	  if (verbose)
//	    {
//	      wifi.EnableLogComponents ();  // Turn on all Wifi logging
//	    }
	  wifi.SetStandard (WIFI_PHY_STANDARD_80211b);
	  wifi.EnableLogComponents ();
	 //LogComponentEnableAll(LOG_ALL);

	  // This is one parameter that matters when using FixedRssLossModel
	  // set it to zero; otherwise, gain will be added
	  //wifiPhy.Set ("RxGain", DoubleValue (0) );
	  // ns-3 supports RadioTap and Prism tracing extensions for 802.11b
	  //wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);


	  // 4. Create & setup wifi channel
	  Ptr<YansWifiChannel> wifiChannel = CreateObject <YansWifiChannel> ();
	  wifiChannel->SetPropagationLossModel (lossModel);
	  wifiChannel->SetPropagationDelayModel (CreateObject <ConstantSpeedPropagationDelayModel> ());

	  YansTosPhyHelper wifiPhy =  YansTosPhyHelper::Default ();
    wifiPhy.SetChannel (wifiChannel);


	  TosNetDeviceContainer devices = wifi.Install (wifiPhy,  nodes);


    ns3::Simulator::Stop(ns3::Seconds(10.0));
    ns3::Simulator::Run();
    ns3::Simulator::Destroy ();


	return 0;
}
