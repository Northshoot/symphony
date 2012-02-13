/*
 * wsn-tos-device.cc
 *
 *  Created on: Feb 13, 2012
 *      Author: lauril
 */

#include "ns3/log.h"
#include "ns3/wifi-mac.h"
#include "ns3/wifi-phy.h"
#include "ns3/wifi-remote-station-manager.h"
#include "ns3/wifi-channel.h"
#include "ns3/llc-snap-header.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/pointer.h"
#include "ns3/node.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/log.h"

#include "wsn-tos-device.h"

NS_LOG_COMPONENT_DEFINE("WsnTosDevice");

namespace ns3 {

WsnTosDevice::WsnTosDevice() {
	// TODO Auto-generated constructor stub

}

TypeId WsnTosDevice::GetTypeId(void) {
	static TypeId tid =
			TypeId("ns3::WsnTosDevice").SetParent<Object>().AddConstructor<
			WsnTosDevice>().AddAttribute(
					"Mtu",
					"The MAC-level Maximum Transmission Unit",
					UintegerValue(MAX_MSDU_SIZE - LLC_SNAP_HEADER_LENGTH),
					MakeUintegerAccessor(&WsnTosDevice::SetMtu,
							&WsnTosDevice::GetMtu),
							MakeUintegerChecker<uint16_t>(1,
									MAX_MSDU_SIZE - LLC_SNAP_HEADER_LENGTH)).AddAttribute(
											"Channel", "The channel attached to this device",
											PointerValue(),
											MakePointerAccessor(&WsnTosDevice::DoGetChannel),
											MakePointerChecker<WifiChannel>()).AddAttribute(
													"Phy",
													"The PHY layer attached to this device.",
													PointerValue(),
													MakePointerAccessor(&WsnTosDevice::GetPhy,
															&WsnTosDevice::SetPhy),
															MakePointerChecker<WifiPhy>()).AddAttribute(
																	"Mac",
																	"The MAC layer attached to this device.",
																	PointerValue(),
																	MakePointerAccessor(&WsnTosDevice::GetMac,
																			&WsnTosDevice::SetMac),
																			MakePointerChecker<WifiMac>());
	return tid;
}

WsnTosDevice::~WsnTosDevice() {
	// TODO Auto-generated destructor stub
}

void WsnTosDevice::SetMac(Ptr<TosMacLow> mac) {
	m_mac = mac;
}

void WsnTosDevice::SetPhy(Ptr<WifiPhy> phy) {
	m_phy = phy;
}

Ptr<TosMacLow> WsnTosDevice::GetMac(void) const {
	return m_mac;
}

Ptr<WifiPhy> WsnTosDevice::GetPhy(void) const {
	return m_phy;
}

Ptr<Channel> WsnTosDevice::GetChannel(void) const {
	return m_phy->GetChannel();
}

void WsnTosDevice::SetAddress(Mac48Address address) {
	m_mac->SetAddress(address);
}

Mac48Address WsnTosDevice::GetAddress(void) const {
	return m_mac->GetAddress();
}

void WsnTosDevice::SetMtu(const uint16_t mtu) {
	m_mtu = mtu;
}

uint16_t WsnTosDevice::GetMtu(void) const {
	return m_mtu;
}

bool WsnTosDevice::IsLinkUp(void) const {
	return true;
}

void WsnTosDevice::AddLinkChangeCallback(Callback<void> callback) {
}

bool WsnTosDevice::IsBroadcast(void) const {
	return true;
}

//    Address WsnTosDevice::GetBroadcast(void) const
//    {
//    	return
//    }

bool WsnTosDevice::IsMulticast(void) const {
	return true;
}

Ptr<TosNode> WsnTosDevice::GetNode(void) const {
	return m_node;
}

void WsnTosDevice::SetNode(Ptr<TosNode> node) {
	m_node = node;
}

uint8_t WsnTosDevice::DeviceTurnOff() {
	return 0;
}

uint8_t WsnTosDevice::DeviceStandby() {
	return 0;
}

uint8_t WsnTosDevice::DeviceTurnOn() {
	return 0;
}

uint8_t WsnTosDevice::DeviceSetChannel(uint8_t channel) {
	return 0;
}

void WsnTosDevice::done() {
}

uint8_t WsnTosDevice::DeviceGetChannel() {
	return 0;
}

uint8_t WsnTosDevice::DeviceSend(message_t *msg) {
	return 0;
}

void WsnTosDevice::DeviceendDone(message_t *msg, uint8_t error) {
}

void WsnTosDevice::DeviceCancel(message_t *msg) {
}

bool WsnTosDevice::DeviceRXHeader(message_t *msg) {
	return true;
}

message_t *WsnTosDevice::DeviceReceive(message_t *msg) {
	return m_msg;
}

void WsnTosDevice::DoDispose(void) {
}

void WsnTosDevice::DoStart(void) {
}
bool WsnTosDevice::Send(Ptr<Packet> packet, const Address& dest) {
	//m_mac->TransmitData();
	return true;
}

void WsnTosDevice::ForwardUp(Ptr<Packet> packet, Mac48Address from,
		Mac48Address to) {
}

void WsnTosDevice::LinkUp(void) {
}

void WsnTosDevice::LinkDown(void) {
}

void WsnTosDevice::Setup(void) {
}

Ptr<WifiChannel> WsnTosDevice::DoGetChannel(void) const {
	return m_phy->GetChannel();
}

void WsnTosDevice::CompleteConfig(void) {

}

} /* namespace ns3 */
