/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006 INRIA
 * Copyright (c) 2009 MIRKO BANCHI
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 * Author: Mirko Banchi <mk.banchi@gmail.com>
 */

#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "ns3/assert.h"
#include "ns3/simulator.h"
#include "ns3/event-id.h"
#include "ns3/nstime.h"
#include "ns3/tag.h"
#include "ns3/log.h"
#include "ns3/double.h"


#include "ns3/wifi-mac-header.h"
#include "ns3/wifi-mode.h"
#include "ns3/wifi-preamble.h"
#include "ns3/wifi-phy.h"
#include "ns3/mgt-headers.h"
#include "ns3/mac48-address.h"
#include "ns3/callback.h"
#include "ns3/packet.h"
#include "ns3/wifi-mac-trailer.h"

#include "tos-mac-low.h"

#include "RF230-radio-model.h"

NS_LOG_COMPONENT_DEFINE ("TosMacLow");


#undef NS_LOG_APPEND_CONTEXT
#define NS_LOG_APPEND_CONTEXT std::clog << "[tos mac=" << m_self << "] "


namespace ns3 {

TosMacLow::TosMacLow ()
  : m_currentPacket (0),
    m_listener (0)
{
  NS_LOG_FUNCTION (this);
  //we change datarate to fit zigbee phy
//  m_wifiMode= WifiModeFactory::CreateWifiMode ("DsssRate1Mbps",
//                                       WIFI_MOD_CLASS_DSSS,
//                                       true,
//                                       22000000, 250000,
//                                       WIFI_CODE_RATE_UNDEFINED,
//                                       2);
  m_wifiMode = WifiPhy::GetDsssRate1Mbps();
}

TosMacLow::~TosMacLow ()
{
  NS_LOG_FUNCTION (this);
}

//void
//TosMacLow::SetupPhyMacLowListener (Ptr<WifiPhy> phy)
//{
//  phy->RegisterListener (m_listener);
//}
//
void
TosMacLow::DoStart(void)
{
  Object::DoStart();
}

void
TosMacLow::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  m_sendDataEvent.Cancel ();
  m_phy = 0;
  Object::DoDispose();
}

void
TosMacLow::CancelAllEvents (void)
{
  NS_LOG_FUNCTION (this);
  bool oneRunning = false;


  if (m_sendDataEvent.IsRunning ())
    {
      m_sendDataEvent.Cancel ();
      oneRunning = true;
    }

  if (oneRunning && m_listener != 0)
    {
      m_listener->Cancel ();
      m_listener = 0;
    }
}

void
TosMacLow::SetPhy (Ptr<WifiPhy> phy)
{
  m_phy = phy;
  m_phy->SetReceiveOkCallback (MakeCallback (&TosMacLow::ReceiveOk, this));
  m_phy->SetReceiveErrorCallback (MakeCallback (&TosMacLow::ReceiveError, this));
}


void
TosMacLow::SetAddress (Mac48Address ad)
{
  m_self = ad;
}

Mac48Address
TosMacLow::GetAddress (void) const
{
  return m_self;
}


void
TosMacLow::SetRxCallback (Callback<void,Ptr<Packet>,const WifiMacHeader *> callback)
{
  m_rxCallback = callback;
}
void
TosMacLow::SetTxCallback (Callback<void,uint8_t> callback){
  m_txCallback = callback;
}

void
TosMacLow::TransmitData(Ptr<const Packet> packet, const WifiMacHeader* hdr){
	  NS_LOG_FUNCTION (this << packet << hdr );
	  m_currentPacket = packet->Copy();
	  m_currentHdr = *hdr;
	  //TODO: need implementation for time delay
	  Time duration = Seconds (0.0);
	  m_currentHdr.SetDuration (duration);

	  m_currentPacket->AddHeader (m_currentHdr);
	  WifiMacTrailer fcs;
	  m_currentPacket->AddTrailer (fcs);

	  NS_LOG_DEBUG ("startTx size=" << GetSize (m_currentPacket, &m_currentHdr) <<
	                ", to=" << m_currentHdr.GetAddr1 () << ", listener=" << m_listener);
	  StartDataTxTimers();
}


//TODO: not clear here for virtualization what to do?
void
TosMacLow::ReceiveError (Ptr<const Packet> packet, double rxSnr)
{
  NS_LOG_FUNCTION (this << packet << rxSnr);
  NS_LOG_DEBUG ("rx failed ");

  return;
}

void
TosMacLow::ReceiveOk (Ptr<Packet> packet, double rxSnr, WifiMode txMode, WifiPreamble preamble)
{
  NS_LOG_FUNCTION (this << packet << rxSnr << txMode << preamble);
  /* A packet is received from the PHY.
   * When we have handled this packet,
   * we handle any packet present in the
   * packet queue.
   */
  WifiMacHeader hdr;
  packet->RemoveHeader (hdr);
  WifiMacTrailer fcs;
  packet->RemoveTrailer(fcs);
  //TODO: inmplement snr convertion
//  SnrTag tag;
//  packet->RemovePacketTag (tag);
  m_rxCallback (packet,&hdr);
  return;
}


uint32_t
TosMacLow::GetSize (Ptr<const Packet> packet, const WifiMacHeader *hdr) const
{
  //WifiMacTrailer fcs;
  return packet->GetSize () + hdr->GetSize () ;//;+ fcs.GetSerializedSize ();
}



Time
TosMacLow::CalculateTransmissionTime (Ptr<const Packet> packet,
                                   const WifiMacHeader* hdr,
                                   const RF230RadioModel& params) const
{
  //TODO: must fix time calculations!
  Time txTime = Seconds (0);
  uint32_t dataSize = GetSize (packet, hdr);
  txTime += m_phy->CalculateTxDuration (dataSize, GetDataTxMode(), WIFI_PREAMBLE_SHORT);
  return txTime;
}


void
TosMacLow::ForwardDown (Ptr<const Packet> packet, const WifiMacHeader* hdr,
                     WifiMode txMode)
{
  NS_LOG_FUNCTION (this << packet << hdr << txMode );
  NS_LOG_DEBUG ("send " << hdr->GetTypeString () <<
                ", to=" << hdr->GetAddr1 () <<
                ", size=" << packet->GetSize () <<
                ", mode=" << txMode <<
                ", duration=" << hdr->GetDuration () <<
                ", seq=0x" << std::hex << m_currentHdr.GetSequenceControl () << std::dec);
  std::cout<<"TosMacLow::ForwardDown phy state: "<< m_phy->IsStateCcaBusy()<<std::endl;
  m_phy->SendPacket (packet, txMode, WIFI_PREAMBLE_LONG, 0);
}



void
TosMacLow::StartDataTxTimers (void)
{
//  WifiMode dataTxMode = GetDataTxMode ();
////  //TODO: WIFI_PREAMBLE_LONG need to be fixed for specific radio device
//  Time txDuration = m_phy->CalculateTxDuration (GetSize (m_currentPacket, &m_currentHdr), dataTxMode, WIFI_PREAMBLE_LONG);
//  Time delay = txDuration ;//+ GetSifs (); need to add physical delay
//
//  m_sendDataEvent = Simulator::Schedule (delay, &TosMacLow::Test, this,1);

  SendDataPacket();

}
void TosMacLow::Test(int a) {
  std::cout<<"\n\n\t\t\t TosMacLow::Test " << m_sendDataEvent.IsRunning() << std::endl;
  m_sendDataEvent.Cancel ();
  SendDataPacket();
}
void
TosMacLow::SendDataPacket (void)
{
  std::cout<<"\n\n\t\t\t TosMacLow::Test " << m_sendDataEvent.IsRunning() << std::endl;
  ForwardDown (m_currentPacket, &m_currentHdr, GetDataTxMode ());
}

WifiMode
TosMacLow::GetDataTxMode () const
{
  return m_wifiMode;
}
void
TosMacLow::SetRadioModel(RF230RadioModel * model){
  m_txParams = model;
}

} // namespace ns3
