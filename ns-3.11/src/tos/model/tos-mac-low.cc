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
#include "ns3/tag.h"
#include "ns3/log.h"
#include "ns3/double.h"


#include "ns3/wifi-mac-header.h"
#include "ns3/wifi-mode.h"
#include "ns3/wifi-preamble.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-remote-station-manager.h"
#include "ns3/ctrl-headers.h"
#include "ns3/mgt-headers.h"
#include "ns3/block-ack-agreement.h"
#include "ns3/mac48-address.h"
#include "ns3/callback.h"
#include "ns3/event-id.h"
#include "ns3/packet.h"
#include "ns3/nstime.h"
#include "ns3/block-ack-cache.h"
#include "ns3/wifi-mac-trailer.h"

#include "tos-mac-low.h"

#include "RF230-radio-model.h"

NS_LOG_COMPONENT_DEFINE ("TosMacLow");


#undef NS_LOG_APPEND_CONTEXT
#define NS_LOG_APPEND_CONTEXT std::clog << "[tos mac=" << m_self << "] "


namespace ns3 {

class PhyTosMacLowListener : public ns3::WifiPhyListener
{
public:
	PhyTosMacLowListener (ns3::TosMacLow *macLow)
    : m_macLow (macLow)
  {
  }
  virtual ~PhyTosMacLowListener ()
  {
  }
  virtual void NotifyRxStart (Time duration)
  {
    std::cout<<" \tNotifyRxStart"<<std::endl;
  }
  virtual void NotifyRxEndOk (void)
  {
    std::cout<<" \tNotifyRxEndOk"<<std::endl;

  }
  virtual void NotifyRxEndError (void)
  {
    std::cout<<" \tNotifyRxEndError"<<std::endl;
  }
  virtual void NotifyTxStart (Time duration)
  {
    m_macLow->m_txCallback(0);
    std::cout<<" \tNotifyTxStart "<< duration.GetMicroSeconds()<< std::endl;
  }
  virtual void NotifyMaybeCcaBusyStart (Time duration)
  {

    std::cout<<" \tNotifyMaybeCcaBusyStart "<<duration.GetMicroSeconds()<<std::endl;
  }
  virtual void NotifySwitchingStart (Time duration)
  {
    std::cout<<" \tNotifySwitchingStart"<<duration.GetMicroSeconds()<<std::endl;
    m_macLow->NotifySwitchingStartNow (duration);
  }
private:
  ns3::TosMacLow *m_macLow;
};


TosMacLow::TosMacLow ()
  : m_currentPacket (0),
    m_listener (0)
{
  NS_LOG_FUNCTION (this);
  //we change datarate to fit zigbee phy
  m_wifiMode= WifiModeFactory::CreateWifiMode ("DsssRate1Mbps",
                                       WIFI_MOD_CLASS_DSSS,
                                       true,
                                       22000000, 250000,
                                       WIFI_CODE_RATE_UNDEFINED,
                                       2);

}

TosMacLow::~TosMacLow ()
{
  NS_LOG_FUNCTION (this);
}

void
TosMacLow::SetupPhyMacLowListener (Ptr<WifiPhy> phy)
{
  m_phyMacLowListener = new PhyTosMacLowListener (this);
  phy->RegisterListener (m_phyMacLowListener);
}

void
TosMacLow::DoStart(void)
{
  SetupPhyMacLowListener(m_phy);
}

void
TosMacLow::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  m_sendDataEvent.Cancel ();
  m_phy = 0;

  delete m_phyMacLowListener;
  m_phyMacLowListener = 0;
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
	NS_LOG_DEBUG(this<< " before PHY: " << m_phy);
  m_phy = phy;
  m_phy_listner = new PhyTosMacLowListener(this);
  m_phy->RegisterListener(m_phy_listner);
  m_phy->SetReceiveOkCallback (MakeCallback (&TosMacLow::ReceiveOk, this));
  m_phy->SetReceiveErrorCallback (MakeCallback (&TosMacLow::ReceiveError, this));
  NS_LOG_DEBUG(this<< " after PHY: " << m_phy);
  SetupPhyMacLowListener (phy);
}


void
TosMacLow::SetAddress (Mac48Address ad)
{
  m_self = ad;
}

Mac48Address
TosMacLow::GetAddress (void) const
{
	NS_LOG_FUNCTION(this << " mac: "<< m_self);
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
	  //here we just save data

	  m_currentPacket = packet->Copy();
	  m_currentHdr = *hdr;
	  //Need DataMode
//	  WifiMode dataTxMode = GetDataTxMode ();
//	  m_currentHdr.SetDuration (Seconds (0.0002));
//
//	  m_currentPacket->AddHeader (m_currentHdr);
//
//	  WifiMacTrailer fcs;
//	  m_currentPacket->AddTrailer (fcs);
	  StartDataTxTimers ();

	  WifiMode dataTxMode = GetDataTxMode ();
	  //TODO: need implementation for time delay
	  Time duration = Seconds (0.0);

	  m_currentHdr.SetDuration (duration);

	  m_currentPacket->AddHeader (m_currentHdr);
	  WifiMacTrailer fcs;
	  m_currentPacket->AddTrailer (fcs);

	  ForwardDown (m_currentPacket, &m_currentHdr, dataTxMode);
	  m_currentPacket = 0;

	  NS_ASSERT (m_phy->IsStateTx ());
}
void
TosMacLow::StartTransmission (Ptr<const Packet> packet,
        const WifiMacHeader* hdr,
        RF230RadioModel * params,
        TosMacLowTransmissionListener *listener)
{
  //NS_LOG_FUNCTION (this << packet << hdr << params << listener);
  /* m_currentPacket is not NULL because someone started
   * a transmission and was interrupted before one of:
   *   - ctsTimeout
   *   - sendDataAfterCTS
   * expired. This means that one of these timers is still
   * running. They are all cancelled below anyway by the
   * call to CancelAllEvents (because of at least one
   * of these two timer) which will trigger a call to the
   * previous listener's cancel method.
   *
   * This typically happens because the high-priority
   * QapScheduler has taken access to the channel from
   * one of the Edca of the QAP.
   */
  m_currentPacket = packet->Copy ();
  m_currentHdr = *hdr;
  CancelAllEvents ();
  m_listener = listener;
  m_txParams = params;

  //NS_ASSERT (m_phy->IsStateIdle ());

  NS_LOG_DEBUG ("startTx size=" << GetSize (m_currentPacket, &m_currentHdr) <<
                ", to=" << m_currentHdr.GetAddr1 () << ", listener=" << m_listener);

  /* When this method completes, we have taken ownership of the medium. */
  NS_ASSERT (m_phy->IsStateTx ());
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
TosMacLow::NotifySwitchingStartNow (Time duration)
{
  NS_LOG_DEBUG ("switching channel. Cancelling MAC pending events");
  CancelAllEvents ();
  //TODO: notify if packet drop if there is one
  m_currentPacket = 0;
  m_listener = 0;
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
  //TODO: inmplement snr convertion
//  SnrTag tag;
//  packet->RemovePacketTag (tag);
  NS_LOG_DEBUG ("duration/id=" << hdr.GetDuration ());

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
  WifiMode dataTxMode = GetDataTxMode ();
  //TODO: WIFI_PREAMBLE_LONG need to be fixed for specific radio device
  Time txDuration = m_phy->CalculateTxDuration (GetSize (m_currentPacket, &m_currentHdr), dataTxMode, WIFI_PREAMBLE_LONG);
  Time delay = txDuration ;//+ GetSifs ();
  //NS_ASSERT (m_waitSifsEvent.IsExpired ());
  m_sendDataEvent = Simulator::Schedule (delay, &TosMacLow::SendDataPacket, this);

}

void
TosMacLow::SendDataPacket (void)
{
  NS_LOG_FUNCTION (this<<"NOT IMPLEMENTED");
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
