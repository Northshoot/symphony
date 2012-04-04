/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005, 2006 INRIA
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
#ifndef TOS_MAC_LOW_H
#define TOS_MAC_LOW_H

#include <vector>
#include <stdint.h>
#include <list>
#include <ostream>
#include <map>

#include "ns3/wifi-mac-header.h"
#include "ns3/wifi-mode.h"
#
#include "ns3/wifi-preamble.h"
#include "ns3/ctrl-headers.h"
#include "ns3/mgt-headers.h"
#include "ns3/block-ack-agreement.h"
#include "ns3/mac48-address.h"
#include "ns3/callback.h"
#include "ns3/event-id.h"
#include "ns3/packet.h"
#include "ns3/nstime.h"
#include "ns3/block-ack-cache.h"
#include "RF230-radio-model.h"

namespace ns3 {

class WifiPhy;
class WifiMac;


/**
 * \ingroup wifi
 * \brief listen to events coming from ns3::MacLow.
 */
class TosMacLowTransmissionListener
{
public:
	TosMacLowTransmissionListener ();
  virtual ~TosMacLowTransmissionListener ();

  /**
   * \param snr the snr of the cts
   * \param txMode the txMode of the cts
   *
   * ns3::MacLow received an expected CTS within
   * CtsTimeout.
   */
  virtual void GotCts (double snr, WifiMode txMode) = 0;
  /**
   * ns3::MacLow did not receive an expected CTS
   * within CtsTimeout.
   */
  virtual void MissedCts (void) = 0;
  /**
   * \param snr the snr of the ack
   * \param txMode the transmission mode of the ack
   *
   * ns3::MacLow received an expected ACL within
   * AckTimeout. The <i>snr</i> and <i>txMode</i>
   * arguments are not valid when SUPER_FAST_ACK is
   * used.
   */
  virtual void GotAck (double snr, WifiMode txMode) = 0;
  /**
   * ns3::MacLow did not receive an expected ACK within
   * AckTimeout.
   */
  virtual void MissedAck (void) = 0;
  /**
   * \param blockAck Block ack response header
   * \param source Address of block ack sender
   *
   * Invoked when ns3::MacLow receives a block ack frame.
   * Block ack frame is received after a block ack request
   * and contains information about the correct reception
   * of a set of packet for which a normal ack wasn't send.
   * Default implementation for this method is empty. Every
   * queue that intends to be notified by MacLow of reception
   * of a block ack must redefine this function.
   */
  virtual void GotBlockAck (const CtrlBAckResponseHeader *blockAck, Mac48Address source);
  /**
   * ns3::MacLow did not receive an expected BLOCK_ACK within
   * BlockAckTimeout. This method is used only for immediate
   * block ack variant. With delayed block ack, the MissedAck method will be
   * called instead: upon receipt of a block ack request, the rx station will
   * reply with a normal ack frame. Later, when the rx station gets a txop, it
   * will send the block ack back to the tx station which will reply with a
   * normal ack to the rx station.
   */
  virtual void MissedBlockAck (void);
  /**
   * Invoked when ns3::MacLow wants to start a new transmission
   * as configured by MacLowTransmissionParameters::EnableNextData.
   * The listener is expected to call again MacLow::StartTransmission
   * with the "next" data to send.
   */
  virtual void StartNext (void) = 0;

  /**
   * Invoked if this transmission was canceled
   * one way or another. When this method is invoked,
   * you can assume that the packet has not been passed
   * down the stack to the PHY.
   */
  virtual void Cancel (void) = 0;
};




/**
 * \ingroup tos
 * \brief wrapper for sending data from TosNetDevice to yans-wifi-phy
 *
 */
class TosMacLow : public Object
{
public:
  typedef Callback<void, Ptr<Packet>, const WifiMacHeader*> MacLowRxCallback;
  typedef Callback<void, uint8_t> MacLowTxCallback;
  TosMacLow ();
  virtual ~TosMacLow ();

  void SetPhy (Ptr<WifiPhy> phy);

  Time
  CalculateTransmissionTime (Ptr<const Packet> packet,
                                     const WifiMacHeader* hdr,
                                     const RF230RadioModel& params) const;

  void TransmitData(Ptr<const Packet> packet, const WifiMacHeader* hdr);
  void StartTransmission (Ptr<const Packet> packet,
          const WifiMacHeader* hdr,
          RF230RadioModel * params,
          TosMacLowTransmissionListener *listener);

  void SetAddress (Mac48Address ad);

  void DoStart (void);
  Mac48Address GetAddress (void) const;

  /**
   * \param callback the callback which receives every incoming packet.
   *
   * This callback typically forwards incoming packets to
   * an instance of ns3::MacRxMiddle.
   */
  void SetRxCallback (Callback<void,Ptr<Packet>,const WifiMacHeader *> callback);
  void SetTxCallback (Callback<void,uint8_t> callback);

  /**
   * \param packet to send (does not include the 802.11 MAC header and checksum)
   * \param hdr header associated to the packet to send.
   * \param parameters transmission parameters of packet.
   *
   * This transmission time includes the time required for
   * the next packet transmission if one was selected.
   */
//  Time CalculateTransmissionTime (Ptr<const Packet> packet,
//                                  const WifiMacHeader* hdr,
//                                  const MacLowTransmissionParameters& parameters) const;



  /**
   * \param packet packet received
   * \param rxSnr snr of packet received
   * \param txMode transmission mode of packet received
   * \param preamble type of preamble used for the packet received
   *
   * This method is typically invoked by the lower PHY layer to notify
   * the MAC layer that a packet was successfully received.
   */
  void ReceiveOk (Ptr<Packet> packet, double rxSnr, WifiMode txMode, WifiPreamble preamble);
  /**
   * \param packet packet received.
   * \param rxSnr snr of packet received.
   *
   * This method is typically invoked by the lower PHY layer to notify
   * the MAC layer that a packet was unsuccessfully received.
   */
  void ReceiveError (Ptr<const Packet> packet, double rxSnr);
  /**
   * \param duration switching delay duration.
   *
   * This method is typically invoked by the PhyMacLowListener to notify
   * the MAC layer that a channel switching occured. When a channel switching
   * occurs, pending MAC transmissions (RTS, CTS, DATA and ACK) are cancelled.
   */
  void NotifySwitchingStartNow (Time duration);

  void SetRadioModel(RF230RadioModel * model);

  MacLowTxCallback m_txCallback;
private:
  void CancelAllEvents (void);

  uint32_t GetSize (Ptr<const Packet> packet, const WifiMacHeader *hdr) const;
  Time NowUs (void) const;
  void ForwardDown (Ptr<const Packet> packet, const WifiMacHeader *hdr,
                    WifiMode txMode);

  WifiMode GetDataTxMode (void) const;


  void MaybeCancelPrevious (void);


  void SendDataPacket (void);
  void SendCurrentTxPacket (void);
  void StartDataTxTimers (void);
  virtual void DoDispose (void);



  void SetupPhyMacLowListener (Ptr<WifiPhy> phy);

  RF230RadioModel * m_txParams;
  class PhyTosMacLowListener *m_phy_listner;
  Ptr<WifiPhy> m_phy;
  MacLowRxCallback m_rxCallback;
  //MacLowTxCallback m_txCallback;
  EventId m_sendDataEvent;

  WifiMode m_wifiMode;

  Ptr<Packet> m_currentPacket;
  WifiMacHeader m_currentHdr;

  TosMacLowTransmissionListener * m_listener;
  Mac48Address m_self ;


  Time m_sifs;
  Time m_slotTime;



  // Listerner needed to monitor when a channel switching occurs.
  class PhyTosMacLowListener * m_phyMacLowListener;

  /*
   * BlockAck data structures.
   */
  typedef std::pair<Ptr<Packet>, WifiMacHeader> BufferedPacket;
  typedef std::list<BufferedPacket>::iterator BufferedPacketI;



};

} // namespace ns3

#endif /* MAC_LOW_H */
