/*
 * wsn-tos-device.cc
 *
 *  Created on: Feb 13, 2012
 *      Author: lauril
 */

#include "ns3/log.h"
#include "ns3/wifi-mac.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-channel.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/pointer.h"
#include "ns3/ptr.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/log.h"

#include "ns3/tos-net-device.h"
#include "ns3/tos-node.h"
#include "ns3/tos-mac-low.h"

NS_LOG_COMPONENT_DEFINE("TosNetDevice");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (TosNetDevice);

TosNetDevice::TosNetDevice() {
	// TODO Auto-generated constructor stub

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
					MakePointerChecker<WifiMac>());
	return tid;
}

TosNetDevice::~TosNetDevice() {
	// TODO Auto-generated destructor stub
}

void
TosNetDevice::SetMac(Ptr<TosMacLow> mac) {
	m_mac = mac;
}

void
TosNetDevice::SetPhy(Ptr<WifiPhy> phy) {
	m_phy = phy;
}

Ptr<TosMacLow>
TosNetDevice::GetMac(void) const {
	return m_mac;
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
	m_mac->SetAddress(address);
}

Mac48Address
TosNetDevice::GetAddress(void) const {
	return m_mac->GetAddress();
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
TosNetDevice::DeviceSend(message_t *msg) {
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
}
bool
TosNetDevice::Send(Ptr<Packet> packet, const Address& dest) {
	//TODO: convert address
	//m_mac->TransmitData();
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

void TosNetDevice::CompleteConfig(void) {

}

} /* namespace ns3 */
