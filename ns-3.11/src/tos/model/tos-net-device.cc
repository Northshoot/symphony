/*
 * wsn-tos-device.cc
 *
 *  Created on: Feb 13, 2012
 *      Author: lauril
 */

#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/wifi-mac.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-channel.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/pointer.h"
#include "ns3/ptr.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/wifi-mac-header.h"

#include "ns3/tos-net-device.h"
#include "ns3/tos-node.h"
#include "ns3/tos-mac-low.h"

NS_LOG_COMPONENT_DEFINE("TosNetDevice");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (TosNetDevice);

TosNetDevice::TosNetDevice()
: m_configComplete (false){
	NS_LOG_FUNCTION_NOARGS ();

}

TypeId TosNetDevice::GetTypeId(void) {
	static TypeId tid =
			TypeId("ns3::TosNetDevice")
			.SetParent<Object>()
			.AddConstructor<TosNetDevice>()
			.AddAttribute("Mtu","The MAC-level Maximum Transmission Unit",
					UintegerValue(MAX_MSDU_SIZE - 8),
					MakeUintegerAccessor(&TosNetDevice::SetMtu,
							&TosNetDevice::GetMtu),
					MakeUintegerChecker<uint16_t>(1,MAX_MSDU_SIZE - 8)).AddAttribute(
											"Channel", "The channel attached to this device",
					PointerValue(),
				    MakePointerAccessor(&TosNetDevice::DoGetChannel),
					MakePointerChecker<WifiChannel>()).AddAttribute("Phy",
													"The PHY layer attached to this device.",
					PointerValue(),
					MakePointerAccessor(&TosNetDevice::GetPhy,&TosNetDevice::SetPhy),
					MakePointerChecker<WifiPhy>())
					.AddAttribute("Mac","The MAC layer attached to this device.",
					PointerValue(),
					MakePointerAccessor(&TosNetDevice::GetMac,&TosNetDevice::SetMac),
					MakePointerChecker<TosMacLow>());
	return tid;
}

TosNetDevice::~TosNetDevice() {
	// TODO Auto-generated destructor stub
}

void
TosNetDevice::SetMac(Ptr<TosMacLow> mac) {
	NS_LOG_FUNCTION(this<<mac);
	m_tos_mac = mac;
	CompleteConfig ();
}

void
TosNetDevice::SetPhy(Ptr<WifiPhy> phy) {
	m_phy = phy;
}

Ptr<TosMacLow>
TosNetDevice::GetMac(void) const {
	return m_tos_mac;
}

Ptr<WifiPhy>
TosNetDevice::GetPhy(void) const {
	return m_phy;
}

Ptr<Channel>
TosNetDevice::GetChannel(void) const {
	return m_phy->GetChannel();
}

void
TosNetDevice::SetAddress(Mac48Address address) {
	m_tos_mac->SetAddress(address);
}

Mac48Address
TosNetDevice::GetAddress(void) const {
	return m_tos_mac->GetAddress();
}

void
TosNetDevice::SetMtu(const uint16_t mtu) {
	m_mtu = mtu;
}

uint16_t
TosNetDevice::GetMtu(void) const {
	return m_mtu;
}

bool
TosNetDevice::IsLinkUp(void) const {
	return true;
}

void
TosNetDevice::AddLinkChangeCallback(Callback<void> callback) {
}

bool
TosNetDevice::IsBroadcast(void) const {
	return true;
}

//    Address TosNetDevice::GetBroadcast(void) const
//    {
//    	return
//    }

bool
TosNetDevice::IsMulticast(void) const {
	return true;
}

Ptr<TosNode>
TosNetDevice::GetNode(void) const {
	return m_node;
}

void
TosNetDevice::SetNode(Ptr<TosNode> node) {
	m_node = node;
}

uint8_t
TosNetDevice::DeviceTurnOff() {
	return 0;
}

uint8_t
TosNetDevice::DeviceStandby() {
	return 0;
}

uint8_t
TosNetDevice::DeviceTurnOn() {
	return 0;
}

uint8_t
TosNetDevice::DeviceSetChannel(uint8_t channel) {
	return 0;
}

void
TosNetDevice::done() {
}

uint8_t
TosNetDevice::DeviceGetChannel() {
	return 0;
}

uint8_t
TosNetDevice::DeviceSend(ns3pack* hder, void * msg) {
	NS_LOG_FUNCTION(this);

	//TODO: logic for device needs to be added
	//TODO: implement callbacks to tos
	//TODO: implement time delay;
	//make ns 3 packet from the tos packet

	  WifiMacHeader hdr;
	  hdr.SetTypeData ();
	  hdr.SetAddr1 (Mac48Address::GetBroadcast());
	  //hdr.SetAddr2 (m_tos_mac->GetAddress ());
//	  hdr.SetAddr3 (GetBssid ());
//	  hdr.SetDsNotFrom ();
//	  hdr.SetDsNotTo ();
//	  Ptr<Packet> pkt = Create<Packet> (Packet(reinterpret_cast<uint8_t const
//		  		*>("hello"),5));
//	  pkt->AddHeader(hdr);
	  NS_LOG_DEBUG(this<<" to: " << hdr.GetAddr1());
	  //m_mac->TransmitData(pkt->Copy(), &hdr);
	return 0;
}

void
TosNetDevice::DeviceSendDone(message_t *msg, uint8_t error) {

}

void
TosNetDevice::DeviceCancel(message_t *msg) {
}

bool
TosNetDevice::DeviceRXHeader(message_t *msg) {
	return true;
}

message_t *
TosNetDevice::DeviceReceive(message_t *msg) {
	return m_msg;
}

void
TosNetDevice::DoDispose(void) {
}

void
TosNetDevice::DoStart(void) {
	NS_LOG_FUNCTION(this);
	m_tos_mac->Start();
	m_phy->Start();
	Object::DoStart();
}
bool
TosNetDevice::Send(Ptr<Packet> packet, const Address& dest) {
	//TODO: convert address
	NS_LOG_ERROR("Function is not in use");
	return true;
}



void
TosNetDevice::ForwardUp(Ptr<Packet> packet, Mac48Address from,
		Mac48Address to) {
}

void
TosNetDevice::LinkUp(void) {
}

void
TosNetDevice::LinkDown(void) {
}

void
TosNetDevice::Setup(void) {
}

Ptr<WifiChannel>
TosNetDevice::DoGetChannel(void) const {
	return m_phy->GetChannel();
}

void
TosNetDevice::CompleteConfig(void) {
	NS_LOG_DEBUG(this << " MAC: " << m_tos_mac
					  << " PHY: " << m_phy
					  << " NOD: " << m_node);
	  if (m_tos_mac == 0
	      || m_phy == 0
	      || m_node == 0)
	    {
		  NS_LOG_FUNCTION_NOARGS();
		 NS_LOG_ERROR("TosNetDevice has not completed configuration");
	      return;
	    }
	  m_tos_mac->SetPhy(m_phy);

	 // m_tos_mac->SetWifiPhy (m_phy);
//	  m_tos_mac->SetForwardUpCallback (MakeCallback (&WifiNetDevice::ForwardUp, this));
//	  m_tos_mac->SetLinkUpCallback (MakeCallback (&WifiNetDevice::LinkUp, this));
//	  m_tos_mac->SetLinkDownCallback (MakeCallback (&WifiNetDevice::LinkDown, this));
	  WifiMacHeader hdr;
	  hdr.SetTypeData ();
	  hdr.SetAddr1 (Mac48Address::GetBroadcast());
	  hdr.SetAddr2 (m_tos_mac->GetAddress ());
//	  hdr.SetAddr3 (GetBssid ());
	  hdr.SetDsNotFrom ();
	  hdr.SetDsNotTo ();
	  Ptr<Packet> pkt = Create<Packet> (Packet(reinterpret_cast<uint8_t const
		  		*>("hello"),5));
	  pkt->AddHeader(hdr);
	  m_tos_mac->TransmitData(pkt->Copy(), &hdr);
	  m_configComplete = true;
}

} /* namespace ns3 */
