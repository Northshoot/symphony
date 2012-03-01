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

#include "ns3/assert.h"
#include "ns3/simulator.h"
#include "ns3/tag.h"
#include "ns3/log.h"
#include "ns3/double.h"

#include "tos-mac-low.h"
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

NS_LOG_COMPONENT_DEFINE ("TosMacLow");

#undef NS_LOG_APPEND_CONTEXT
#define NS_LOG_APPEND_CONTEXT std::clog << "[tos mac=" << m_self << "] "


namespace ns3 {
class PhyMacLowListener : public ns3::WifiPhyListener
{
public:
  PhyMacLowListener (ns3::TosMacLow *macLow)
    : m_macLow (macLow)
  {
  }
  virtual ~PhyMacLowListener ()
  {
  }
  virtual void NotifyRxStart (Time duration)
  {

  }
  virtual void NotifyRxEndOk (void)
  {
  }
  virtual void NotifyRxEndError (void)
  {
  }
  virtual void NotifyTxStart (Time duration)
  {
  }
  virtual void NotifyMaybeCcaBusyStart (Time duration)
  {
  }
  virtual void NotifySwitchingStart (Time duration)
  {
    m_macLow->NotifySwitchingStartNow (duration);
  }
private:
  ns3::TosMacLow *m_macLow;
};

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

  }
  virtual void NotifyRxEndOk (void)
  {
  }
  virtual void NotifyRxEndError (void)
  {
  }
  virtual void NotifyTxStart (Time duration)
  {
  }
  virtual void NotifyMaybeCcaBusyStart (Time duration)
  {
  }
  virtual void NotifySwitchingStart (Time duration)
  {
    m_macLow->NotifySwitchingStartNow (duration);
  }
private:
  ns3::TosMacLow *m_macLow;
};


TosMacLow::TosMacLow ()
  : m_normalAckTimeoutEvent (),
    m_fastAckTimeoutEvent (),
    m_superFastAckTimeoutEvent (),
    m_fastAckFailedTimeoutEvent (),
    m_blockAckTimeoutEvent (),
    m_ctsTimeoutEvent (),
    m_sendCtsEvent (),
    m_sendAckEvent (),
    m_sendDataEvent (),
    m_waitSifsEvent (),
    m_currentPacket (0),
    m_listener (0)
{
  NS_LOG_FUNCTION (this);

//  m_lastNavDuration = Seconds (0);
//  m_lastNavStart = Seconds (0);
}

TosMacLow::~TosMacLow ()
{
  NS_LOG_FUNCTION (this);
}

void
TosMacLow::SetupPhyMacLowListener (Ptr<WifiPhy> phy)
{
  m_phyMacLowListener = new PhyMacLowListener (this);
  phy->RegisterListener (m_phyMacLowListener);
}


void
TosMacLow::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  m_normalAckTimeoutEvent.Cancel ();
  m_fastAckTimeoutEvent.Cancel ();
  m_superFastAckTimeoutEvent.Cancel ();
  m_fastAckFailedTimeoutEvent.Cancel ();
  m_blockAckTimeoutEvent.Cancel ();
  m_ctsTimeoutEvent.Cancel ();
  m_sendCtsEvent.Cancel ();
  m_sendAckEvent.Cancel ();
  m_sendDataEvent.Cancel ();
  m_waitSifsEvent.Cancel ();
  m_phy = 0;
//  m_stationManager = 0;
  delete m_phyMacLowListener;
  m_phyMacLowListener = 0;
}

void
TosMacLow::CancelAllEvents (void)
{
  NS_LOG_FUNCTION (this);
  bool oneRunning = false;
  if (m_normalAckTimeoutEvent.IsRunning ())
    {
      m_normalAckTimeoutEvent.Cancel ();
      oneRunning = true;
    }
  if (m_fastAckTimeoutEvent.IsRunning ())
    {
      m_fastAckTimeoutEvent.Cancel ();
      oneRunning = true;
    }
  if (m_superFastAckTimeoutEvent.IsRunning ())
    {
      m_superFastAckTimeoutEvent.Cancel ();
      oneRunning = true;
    }
  if (m_fastAckFailedTimeoutEvent.IsRunning ())
    {
      m_fastAckFailedTimeoutEvent.Cancel ();
      oneRunning = true;
    }
  if (m_blockAckTimeoutEvent.IsRunning ())
    {
      m_blockAckTimeoutEvent.Cancel ();
      oneRunning = true;
    }
  if (m_ctsTimeoutEvent.IsRunning ())
    {
      m_ctsTimeoutEvent.Cancel ();
      oneRunning = true;
    }
  if (m_sendCtsEvent.IsRunning ())
    {
      m_sendCtsEvent.Cancel ();
      oneRunning = true;
    }
  if (m_sendAckEvent.IsRunning ())
    {
      m_sendAckEvent.Cancel ();
      oneRunning = true;
    }
  if (m_sendDataEvent.IsRunning ())
    {
      m_sendDataEvent.Cancel ();
      oneRunning = true;
    }
  if (m_waitSifsEvent.IsRunning ())
    {
      m_waitSifsEvent.Cancel ();
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
  SetupPhyMacLowListener (phy);
}


void
TosMacLow::SetAddress (Mac48Address ad)
{

  m_self = ad;
}
//void
//TosMacLow::SetAckTimeout (Time ackTimeout)
//{
//  m_ackTimeout = ackTimeout;
//}
//void
//TosMacLow::SetBasicBlockAckTimeout (Time blockAckTimeout)
//{
//  m_basicBlockAckTimeout = blockAckTimeout;
//}
//void
//TosMacLow::SetCompressedBlockAckTimeout (Time blockAckTimeout)
//{
//  m_compressedBlockAckTimeout = blockAckTimeout;
//}
//void
//TosMacLow::SetCtsTimeout (Time ctsTimeout)
//{
//  m_ctsTimeout = ctsTimeout;
//}
void
TosMacLow::SetSifs (Time sifs)
{
  m_sifs = sifs;
}
void
TosMacLow::SetSlotTime (Time slotTime)
{
  m_slotTime = slotTime;
}
void
TosMacLow::SetPifs (Time pifs)
{
  m_pifs = pifs;
}

Mac48Address
TosMacLow::GetAddress (void) const
{
	NS_LOG_FUNCTION(this << " mac: "<< m_self);
  return m_self;
}
//Time
//TosMacLow::GetAckTimeout (void) const
//{
//  return m_ackTimeout;
//}
//Time
//TosMacLow::GetBasicBlockAckTimeout () const
//{
//  return m_basicBlockAckTimeout;
//}
//Time
//TosMacLow::GetCompressedBlockAckTimeout () const
//{
//  return m_compressedBlockAckTimeout;
//}
//Time
//TosMacLow::GetCtsTimeout (void) const
//{
//  return m_ctsTimeout;
//}
Time
TosMacLow::GetSifs (void) const
{
  return m_sifs;
}
Time
TosMacLow::GetSlotTime (void) const
{
  return m_slotTime;
}


void
TosMacLow::SetRxCallback (Callback<void,Ptr<Packet>,const WifiMacHeader *> callback)
{
  m_rxCallback = callback;
}

void
TosMacLow::TransmitData(Ptr<const Packet> packet, const WifiMacHeader* hdr){
	  NS_LOG_FUNCTION (this << packet << hdr );


	  m_currentPacket = packet->Copy();
	  m_currentHdr = *hdr;
//	hdr.SetTypeData ();
//	hdr.SetAddr1 ("00:00:00:00:00:01");
//	hdr.SetAddr2 ("ff:ff:ff:ff:ff:ff");
//	std::cerr <<"TosMacLow::TransmitData about to transmit" << std::endl;
//	hdr.SetDsNotFrom ();
//	hdr.SetDsNotTo ();
//	m_currentHdr.SetSequenceNumber (1);
//	m_currentHdr.SetFragmentNumber (0);
//	m_currentHdr.SetNoMoreFragments ();
//	m_currentHdr.SetNoRetry ();
//	NS_LOG_FUNCTION (this << m_currentHdr );
//	 m_currentPacket = Create<Packet> (Packet(reinterpret_cast<uint8_t const*>("hello"),5));
//	 std::cerr <<"m_currentPacket = packet->Copy " << std::endl;
	 // m_currentHdr = *hdr;
	  //CancelAllEvents ();
	  //m_listener = listener;
//	  m_txParams = params;
	//std::cerr <<m_phy->IsStateIdle ()<< std::endl;

	  //NS_ASSERT (m_phy->IsStateIdle ());
	  //std::cerr <<"TosMacLow::TransmitData about to transmit" << std::endl;
	  //NS_LOG_DEBUG ("startTx size=" << GetSize (m_currentPacket, &m_currentHdr) <<
	               // ", to=" << m_currentHdr.GetAddr1 () );
	  //Need DataMode
	  WifiMode dataTxMode = GetDataTxMode ();
	  m_currentHdr.SetDuration (Seconds (0.0002));

	  m_currentPacket->AddHeader (m_currentHdr);

	  WifiMacTrailer fcs;
	  m_currentPacket->AddTrailer (fcs);
	  NS_LOG_FUNCTION(this);
	  NS_LOG_DEBUG("Forwarding Down");
	  ForwardDown (m_currentPacket, &m_currentHdr, dataTxMode);
	  m_currentPacket = 0;
}
void
TosMacLow::StartTransmission (Ptr<const Packet> packet,
        const WifiMacHeader* hdr,
        MacLowTransmissionParameters params,
        TosMacLowTransmissionListener *listener)
{
  NS_LOG_FUNCTION (this << packet << hdr << params << listener);
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

//  if (m_txParams.MustSendRts ())
//    {
//      SendRtsForPacket ();
//    }
//  else
//    {
      SendDataPacket ();
//    }

  /* When this method completes, we have taken ownership of the medium. */
  NS_ASSERT (m_phy->IsStateTx ());
}

void
TosMacLow::ReceiveError (Ptr<const Packet> packet, double rxSnr)
{
  NS_LOG_FUNCTION (this << packet << rxSnr);
  NS_LOG_DEBUG ("rx failed ");
  if (m_txParams.MustWaitFastAck ())
    {
      NS_ASSERT (m_fastAckFailedTimeoutEvent.IsExpired ());
      //m_fastAckFailedTimeoutEvent = Simulator::Schedule (GetSifs (),
//                                                         &TosMacLow::FastAckFailedTimeout, this);
    }
  return;
}

void
TosMacLow::NotifySwitchingStartNow (Time duration)
{
  NS_LOG_DEBUG ("switching channel. Cancelling MAC pending events");
 // m_stationManager->Reset ();
  CancelAllEvents ();
  if (m_navCounterResetCtsMissed.IsRunning ())
    {
      m_navCounterResetCtsMissed.Cancel ();
    }
//  m_lastNavStart = Simulator::Now ();
//  m_lastNavDuration = Seconds (0);
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

  NS_LOG_DEBUG ("duration/id=" << hdr.GetDuration ());

  if (hdr.GetAddr1 () == m_self)
    {

      goto rxPacket;
    }
  else if (hdr.GetAddr1 ().IsGroup ())
    {
      if (hdr.IsData () || hdr.IsMgt ())
        {
          NS_LOG_DEBUG ("rx group from=" << hdr.GetAddr2 ());
          goto rxPacket;
        }
      else
        {
          // DROP
        }
    }
  else
    {
      //NS_LOG_DEBUG_VERBOSE ("rx not-for-me from %d", GetSource (packet));
    }
  return;
rxPacket:
  m_rxCallback (packet, &hdr);
  return;
}


uint32_t
TosMacLow::GetSize (Ptr<const Packet> packet, const WifiMacHeader *hdr) const
{
  //WifiMacTrailer fcs;
  return packet->GetSize () + hdr->GetSize () ;//;+ fcs.GetSerializedSize ();
}



Time
TosMacLow::CalculateOverallTxTime (Ptr<const Packet> packet,
                                const WifiMacHeader* hdr,
                                const MacLowTransmissionParameters& params) const
{
  //TODO: must fix time calculations!

  Time txTime = Seconds (0);
  //WifiMode rtsMode = GetRtsTxMode (packet, hdr);
  //WifiMode dataMode = GetDataTxMode (packet, hdr);
//  if (params.MustSendRts ())
//    {
//      //txTime += m_phy->CalculateTxDuration (GetRtsSize (), rtsMode, WIFI_PREAMBLE_LONG);
//      //txTime += GetCtsDuration (hdr->GetAddr1 (), rtsMode);
//      txTime += Time (GetSifs () * 2);
//    }
  uint32_t dataSize = GetSize (packet, hdr);
  txTime += m_phy->CalculateTxDuration (dataSize, GetDataTxMode(), WIFI_PREAMBLE_LONG);
//  if (params.MustWaitAck ())
//    {
//      txTime += GetSifs ();
//      //txTime += GetAckDuration (hdr->GetAddr1 (), dataMode);
//    }
  return txTime;
}

Time
TosMacLow::CalculateTransmissionTime (Ptr<const Packet> packet,
                                   const WifiMacHeader* hdr,
                                   const MacLowTransmissionParameters& params) const
{
  Time txTime = CalculateOverallTxTime (packet, hdr, params);
  if (params.HasNextPacket ())
    {
      WifiMode dataMode = GetDataTxMode ();
      txTime += GetSifs ();
      txTime += m_phy->CalculateTxDuration (params.GetNextPacketSize (), dataMode, WIFI_PREAMBLE_LONG);
    }
  return txTime;
}


void
TosMacLow::ForwardDown (Ptr<const Packet> packet, const WifiMacHeader* hdr,
                     WifiMode txMode)
{
  NS_LOG_FUNCTION (this << packet << hdr << txMode);
  NS_LOG_DEBUG ("send " << hdr->GetTypeString () <<
                ", to=" << hdr->GetAddr1 () <<
                ", size=" << packet->GetSize () <<
                ", mode=" << txMode <<
                ", duration=" << hdr->GetDuration () <<
                ", seq=0x" << std::hex << m_currentHdr.GetSequenceControl () << std::dec);
  m_phy->SendPacket (packet, txMode, WIFI_PREAMBLE_LONG, 0);
}



void
TosMacLow::StartDataTxTimers (void)
{
  WifiMode dataTxMode = GetDataTxMode ();
  //TODO: WIFI_PREAMBLE_LONG need to be fixed for specific radio device
  Time txDuration = m_phy->CalculateTxDuration (GetSize (m_currentPacket, &m_currentHdr), dataTxMode, WIFI_PREAMBLE_LONG);
if (m_txParams.HasNextPacket ())
    {
      Time delay = txDuration + GetSifs ();
      NS_ASSERT (m_waitSifsEvent.IsExpired ());
      m_waitSifsEvent = Simulator::Schedule (delay, &TosMacLow::WaitSifsAfterEndTx, this);
    }
  else
    {
      // since we do not expect any timer to be triggered.
      m_listener = 0;
    }
}

void
TosMacLow::SendDataPacket (void)
{
  NS_LOG_FUNCTION (this);
  /* send this packet directly. No RTS is needed. */

  StartDataTxTimers ();
  std::cerr <<"TosMacLow::SendDataPacket about to forward" << std::endl;
  WifiMode dataTxMode = GetDataTxMode ();
//  Time duration = Seconds (0.0);
//  if (m_txParams.HasDurationId ())
//    {
//      duration += m_txParams.GetDurationId ();
//    }
//  else
//    {
//      if (m_txParams.MustWaitBasicBlockAck ())
//        {
//          duration += GetSifs ();
////          duration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), dataTxMode, BASIC_BLOCK_ACK);
//        }
//      else if (m_txParams.MustWaitCompressedBlockAck ())
//        {
//          duration += GetSifs ();
////          duration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), dataTxMode, COMPRESSED_BLOCK_ACK);
//        }
//      else if (m_txParams.MustWaitAck ())
//        {
//          duration += GetSifs ();
////          duration += GetAckDuration (m_currentHdr.GetAddr1 (), dataTxMode);
//        }
//      if (m_txParams.HasNextPacket ())
//        {
//          duration += GetSifs ();
//          duration += m_phy->CalculateTxDuration (m_txParams.GetNextPacketSize (),
//                                                  dataTxMode, WIFI_PREAMBLE_LONG);
//          if (m_txParams.MustWaitAck ())
//            {
//              duration += GetSifs ();
////              duration += GetAckDuration (m_currentHdr.GetAddr1 (), dataTxMode);
//            }
//        }
//    }
//  m_currentHdr.SetDuration (duration);
//
//  m_currentPacket->AddHeader (m_currentHdr);
//  WifiMacTrailer fcs;
//  m_currentPacket->AddTrailer (fcs);
  std::cerr <<"TosMacLow::SendDataPacket about to forward" << std::endl;
  ForwardDown (m_currentPacket, &m_currentHdr, dataTxMode);
  m_currentPacket = 0;
}




void
TosMacLow::WaitSifsAfterEndTx (void)
{
  m_listener->StartNext ();
}
WifiMode
TosMacLow::GetDataTxMode () const
{

  return WifiPhy::GetDsssRate1Mbps();
}

} // namespace ns3
