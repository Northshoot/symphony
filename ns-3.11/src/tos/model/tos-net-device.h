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
#include "ns3/net-device.h"
#include "ns3/mac48-address.h"
#include "ns3/wifi-mac-header.h"
#include "ns3/ns3includes.h"
#include "ns3-to-tos-proxy.h"


#include <string>

namespace ns3 {

class TosNode;
class Packet;
class Channel;
class WifiChannel;
class WifiPhy;
class TosMacLow;

class TosNetDevice: public NetDevice {
public:
	typedef Callback<void, message_t *> Ns3ToTosRxCallback;
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

  void setNs3ToTos(Ns3ToTosProxy * nstos);
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
  
//  void SetTosNodeContainer(TosNodeContainer c);

   void SetMac48Address (Mac48Address address);
   Mac48Address GetMac48Address (void) const;

   void ForwardUp (Ptr<Packet> packet, const WifiMacHeader* hdr);

   bool Send (Ptr<Packet> packet, const Address& dest);

  
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

	Ptr<Packet> TosToNsPacket(message_t *msg);

	message_t* NsToTosPacket(Ptr<Packet> pkt);

	  // inherited from NetDevice base class.
	  virtual void SetIfIndex (const uint32_t index);
	  virtual uint32_t GetIfIndex (void) const;
	  virtual Ptr<Channel> GetChannel (void) const;
	  virtual void SetAddress (Address address);
	  virtual Address GetAddress (void) const;
	  virtual bool SetMtu (const uint16_t mtu);
	  virtual uint16_t GetMtu (void) const;
	  virtual bool IsLinkUp (void) const;
	  virtual void AddLinkChangeCallback (Callback<void> callback);
	  virtual bool IsBroadcast (void) const;
	  virtual Address GetBroadcast (void) const;
	  virtual bool IsMulticast (void) const;
	  virtual Address GetMulticast (Ipv4Address multicastGroup) const;
	  virtual bool IsPointToPoint (void) const;
	  virtual bool IsBridge (void) const;
	  virtual bool Send (Ptr<Packet> packet, const Address& dest, uint16_t protocolNumber);
	  virtual Ptr<Node> GetNode (void) const;
	  virtual void SetNode (Ptr<Node> node);
	  virtual bool NeedsArp (void) const;
	  virtual void SetReceiveCallback (NetDevice::ReceiveCallback cb);
	  virtual Address GetMulticast (Ipv6Address addr) const;
	  virtual bool SendFrom (Ptr<Packet> packet, const Address& source, const Address& dest, uint16_t protocolNumber);
	  virtual void SetPromiscReceiveCallback (PromiscReceiveCallback cb);
	  virtual bool SupportsSendFrom (void) const;

private:
  // This value conforms to the 802.11 specification
  static const uint16_t MAX_MSDU_SIZE = 2304;
  Ns3ToTosRxCallback m_ns2totosRx;
  virtual void DoDispose (void);
  virtual void DoStart (void);

  void LinkUp (void);
  void LinkDown (void);
  void Setup (void);
  Ptr<WifiChannel> DoGetChannel (void) const;
  void CompleteConfig (void);

  Ptr<TosMacLow>	m_tos_mac;
  message_t  		m_tx_msg;
  ns3pack  			m_tx_hdr;
  message_t  		m_rx_msg;
  ns3pack			m_rx_hdr;
  Ns3ToTosProxy*  	m_ns3totos;
  TosNodeContainer  m_node_container;


  //inherited from NetDevice
  Ptr<Node> m_node;
  Ptr<WifiPhy> m_phy;
  NetDevice::ReceiveCallback m_forwardUp;
  NetDevice::PromiscReceiveCallback m_promiscRx;

  TracedCallback<Ptr<const Packet>, Mac48Address> m_rxLogger;
  TracedCallback<Ptr<const Packet>, Mac48Address> m_txLogger;

  bool m_busy;

  uint32_t m_ifIndex;
  bool m_linkUp;
  TracedCallback<> m_linkChanges;
  mutable uint16_t m_mtu;
  bool m_configComplete;
  
};

} /* namespace ns3 */
#endif /* WSN_TOS_DEVICE_H_ */
