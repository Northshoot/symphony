/*
 * wsn-tos-device.h
 *
 *  Created on: Feb 13, 2012
 *      Author: lauril
 */

#ifndef TOS_NET_DEVICE_H_
#define TOS_NET_DEVICE_H_


#include "ns3/callback.h"
#include "ns3/object.h"
#include "ns3/ptr.h"
#include "ns3/traced-callback.h"
#include "ns3/mac48-address.h"
#include "ns3/ns3includes.h"


#include <string>

namespace ns3 {

class TosNode;
class Packet;
class Channel;
class WifiChannel;
class WifiPhy;
class TosMacLow;

class TosNetDevice: public Object {
public:
	static TypeId GetTypeId (void);	

	TosNetDevice();
	virtual ~TosNetDevice();
	
	  /**
   * \param mac the mac layer to use.
   */
  void SetMac (Ptr<TosMacLow> mac);
  /**
   * \param phy the phy layer to use.
   */
  void SetPhy (Ptr<WifiPhy> phy);
  /**
   * \param manager the manager to use.
   */
  /**
   * \returns the mac we are currently using.
   */
  Ptr<TosMacLow> GetMac (void) const;
  /**
   * \returns the phy we are currently using.
   */
  Ptr<WifiPhy> GetPhy (void) const;
  

   virtual Ptr<Channel> GetChannel (void) const;
   void SetAddress (Mac48Address address);
   Mac48Address GetAddress (void) const;
   void SetMtu (const uint16_t mtu);
   uint16_t GetMtu (void) const;
   bool IsLinkUp (void) const;
   void AddLinkChangeCallback (Callback<void> callback);
   bool IsBroadcast (void) const;

   bool IsMulticast (void) const;


   bool Send (Ptr<Packet> packet, const Address& dest);


   Ptr<TosNode> GetNode (void) const;
   void SetNode (Ptr<TosNode> node);


  // void SetPromiscReceiveCallback (PromiscReceiveCallback cb);

  
  //commands from tos-radio emulations
  //implementation of radio state
	uint8_t DeviceTurnOff();
	uint8_t DeviceStandby();
	uint8_t DeviceTurnOn();
	uint8_t DeviceSetChannel(uint8_t channel);
	//call back function
	void done();
	uint8_t DeviceGetChannel();

  //implementation of RadioSend
	uint8_t DeviceSend(ns3pack* hdr, void * msg);
	//callback
	void DeviceSendDone(message_t* msg, uint8_t error);
	void DeviceCancel(message_t* msg);
  //implementation of BareReceive
	//callback
	bool DeviceRXHeader(message_t* msg);
	//callback
	message_t* DeviceReceive(message_t* msg);



private:
  // This value conforms to the 802.11 specification
  static const uint16_t MAX_MSDU_SIZE = 2304;

  virtual void DoDispose (void);
  virtual void DoStart (void);
  void ForwardUp (Ptr<Packet> packet, Mac48Address from, Mac48Address to);
  void LinkUp (void);
  void LinkDown (void);
  void Setup (void);
  Ptr<WifiChannel> DoGetChannel (void) const;
  void CompleteConfig (void);

  Ptr<TosNode> m_node;
  Ptr<WifiPhy> m_phy;
  Ptr<TosMacLow> m_mac;
  message_t * m_msg;


//  TracedCallback<Ptr<const Packet>, Mac48Address> m_rxLogger;
//  TracedCallback<Ptr<const Packet>, Mac48Address> m_txLogger;

  uint32_t m_ifIndex;
  bool m_linkUp;
  TracedCallback<> m_linkChanges;
  mutable uint16_t m_mtu;
  bool m_configComplete;
  
};

} /* namespace ns3 */
#endif /* WSN_TOS_DEVICE_H_ */
